const util = require("util");
const path = require("path");
const mysql = require("mysql");
const promisify = util.promisify;
const logger = require("morgan");
const express = require("express");
const createError = require("http-errors");
const cookieParser = require("cookie-parser");
const { v4: uuidv4 } = require("uuid");
const bcrypt = require("bcrypt");
const csrf = require("csurf");

// ################################################
//  Config
// ################################################

const app = express();

app.set("views", path.join(__dirname, "views"));
app.set("view engine", "ejs");

app.use(logger("common"));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, "public")));
app.disable("x-powered-by");

// MySQL
const dbinfo = {
  host: process.env.MYSQL_HOST,
  port: process.env.MYSQL_PORT,
  user: process.env.MYSQL_USER,
  password: process.env.MYSQL_PASSWORD,
  database: process.env.MYSQL_DATABASE,
  connectionLimit: 10,
};
const db = mysql.createPool(dbinfo);
app.set("db", db);

// Redis
const Redis = require("ioredis");
let redisClient = new Redis({
  host: process.env.REDIS_HOST,
  port: process.env.REDIS_PORT,
});
redisClient.set("queued_count", 0);
redisClient.set("proceeded_count", 0);

// Session
const session = require("express-session");
let RedisStore = require("connect-redis")(session);
app.use(
  session({
    store: new RedisStore({ client: redisClient }),
    secret: process.env.SESSION_SECRET,
    resave: false,
    saveUninitialized: true,
    name: "SESSION",
  })
);

// CSRF Token
app.use(csrf({ cookie: false }));

// CSP
app.use(function (req, res, next) {
  res.setHeader(
    "Content-Security-Policy",
    "style-src 'self' ; script-src 'self' ; object-src 'none' ; font-src 'none'"
  );
  next();
});

// ################################################
//  API
// ################################################

app.get("/", async (req, res, next) => {
  // Deny the user not logged in
  if (!req.session.username) {
    return res.redirect("/login");
  }
  // Get user's memo
  const getConnection = promisify(db.getConnection.bind(db));
  const connection = await getConnection();
  const query = promisify(connection.query.bind(connection));
  try {
    const memo = await query("SELECT * FROM memo WHERE user_id = ?", [
      req.session.user_id,
    ]);
    return res.render("index", {
      username: req.session.username,
      magic_token: req.session.magic_token,
      memos: memo,
      csrfToken: req.csrfToken(),
    });
  } catch (e) {
    next(e);
  } finally {
    await connection.release();
  }
});

app.post("/memo", async (req, res, next) => {
  // Deny the user not logged in
  if (!req.session.username) {
    return res.redirect("/login");
  }
  // Parameter check
  if (!req.body.text) {
    return res.redirect("/");
  }
  // Create new memo
  const text = req.body.text.toString();
  if (text.length > 1024) {
    return res.status(400).send("Text is too long.");
  }
  const getConnection = promisify(db.getConnection.bind(db));
  const connection = await getConnection();
  const query = promisify(connection.query.bind(connection));
  try {
    console.log("Memo saved :", text);
    await query("INSERT INTO memo (user_id, text) VALUES (?, ?)", [
      req.session.user_id,
      text,
    ]);
    return res.redirect("/");
  } catch (e) {
    next(e);
  } finally {
    await connection.release();
  }
});

app.post("/memo/delete", async (req, res, next) => {
  // Deny the user not logged in
  if (!req.session.username) {
    return res.redirect("/login");
  }
  // Parameter check
  if (!req.body.id) {
    return res.redirect("/");
  }
  // Delete memo
  const id = req.body.id.toString();
  const getConnection = promisify(db.getConnection.bind(db));
  const connection = await getConnection();
  const query = promisify(connection.query.bind(connection));
  try {
    await query("DELETE FROM memo WHERE id=? AND user_id=?", [
      id,
      req.session.user_id,
    ]);
    return res.redirect("/");
  } catch (e) {
    next(e);
  } finally {
    await connection.release();
  }
});

app.get("/register", async (req, res, next) => {
  res.render("register", { message: "", csrfToken: req.csrfToken() });
});

app.post("/register", async (req, res, next) => {
  // Parameter check
  if (!req.body.username || !req.body.password) {
    return res.render("register", {
      message: "invalid parameter",
      csrfToken: req.csrfToken(),
    });
  }
  const username = req.body.username.toString();
  const password = req.body.password.toString();
  if (username.length < 8 || 64 < username.length) {
    return res.render("register", {
      message: "The username must be 8-64 characters in length.",
      csrfToken: req.csrfToken(),
    });
  }
  if (password.length < 8 || 64 < password.length) {
    return res.render("register", {
      message: "The password must be 8-64 characters in length.",
      csrfToken: req.csrfToken(),
    });
  }
  const pcheck = /^(?=.*?[a-z])(?=.*?[0-9])/;
  if (!pcheck.test(password)) {
    return res.render("register", {
      message:
        "The password must contain at least 1 lower case letter, and 1 numeric character.",
      csrfToken: req.csrfToken(),
    });
  }
  const getConnection = promisify(db.getConnection.bind(db));
  const connection = await getConnection();
  const query = promisify(connection.query.bind(connection));
  try {
    const result = await query(
      "SELECT COUNT(*) AS count FROM user WHERE name = ?",
      [username]
    );
    if (result[0].count !== 0) {
      return res.render("register", {
        message: "A user already exists.",
        csrfToken: req.csrfToken(),
      });
    }
    const hash = await bcrypt.hash(password, 10);
    const magic_token = uuidv4();
    await query("INSERT INTO user (name, pass, magic_token) VALUES (?, ?, ?)", [
      username,
      hash,
      magic_token,
    ]);
    const result2 = await query("SELECT * FROM user WHERE name = ?", [
      username,
    ]);
    req.session.user_id = result2[0].id;
    req.session.username = result2[0].name;
    req.session.magic_token = result2[0].magic_token;
    return res.redirect("/");
  } catch (e) {
    next(e);
  } finally {
    await connection.release();
  }
});

app.get("/login", async (req, res, next) => {
  return res.render("login", { message: "", csrfToken: req.csrfToken() });
});

app.post("/login", async (req, res, next) => {
  // Parameter check
  if (!req.body.username || !req.body.password) {
    return res.render("login", {
      message: "invalid parameter",
      csrfToken: req.csrfToken(),
    });
  }
  const username = req.body.username.toString();
  const password = req.body.password.toString();
  const getConnection = promisify(db.getConnection.bind(db));
  const connection = await getConnection();
  const query = promisify(connection.query.bind(connection));
  try {
    const result = await query("SELECT * FROM user WHERE name = ?", [username]);
    if (result.length !== 1) {
      return res.render("login", {
        message: "Username or password is wrong.",
        csrfToken: req.csrfToken(),
      });
    }
    const cmp = await bcrypt.compare(password, result[0].pass);
    if (cmp) {
      req.session.user_id = result[0].id;
      req.session.username = result[0].name;
      req.session.magic_token = result[0].magic_token;
      return res.redirect("/");
    } else {
      return res.render("login", {
        message: "Username or password is wrong.",
        csrfToken: req.csrfToken(),
      });
    }
  } catch (e) {
    next(e);
  } finally {
    await connection.release();
  }
});

app.get("/magic", async (req, res, next) => {
  // Parameter check
  if (!req.query.token) {
    return res.send("invalid parameter");
  }
  const token = req.query.token.toString();
  const getConnection = promisify(db.getConnection.bind(db));
  const connection = await getConnection();
  const query = promisify(connection.query.bind(connection));
  try {
    const result = await query(
      "SELECT id, name FROM user WHERE magic_token = ?",
      [token]
    );
    if (result.length !== 1) {
      return res.status(200).send(escapeHTML(token) + " is invalid token.");
    }
    req.session.user_id = result[0].id;
    req.session.username = result[0].name;
    req.session.magic_token = token;
    return res.redirect("/");
  } catch (e) {
    next(e);
  } finally {
    await connection.release();
  }
  return res.redirect("/login");
});

function escapeHTML(string) {
  return string
    .replace(/\&/g, "&amp;")
    .replace(/\</g, "&lt;")
    .replace(/\>/g, "&gt;")
    .replace(/\"/g, "&quot;")
    .replace(/\'/g, "&#x27");
}

app.get("/logout", async (req, res, next) => {
  req.session.destroy();
  return res.redirect("/login");
});

app.get("/report", async (req, res, next) => {
  // Deny the user not logged in
  if (!req.session.username) {
    return res.redirect("/login");
  }
  res.render("report", {
    success: "",
    error: "",
    csrfToken: req.csrfToken(),
  });
});

app.post("/report", async (req, res, next) => {
  // Deny the user not logged in
  if (!req.session.username) {
    return res.redirect("/login");
  }
  // Parameter check
  if (!req.body.path) {
    return res.render("report", {
      success: "",
      error: "invalid parameter",
      csrfToken: req.csrfToken(),
    });
  }
  const path = req.body.path.toString();
  if (path === "") {
    return res.render("report", {
      success: "",
      error: "Please set path.",
      csrfToken: req.csrfToken(),
    });
  }
  try {
    // Enqueued jobs are processed by crawl.js
    redisClient
      .rpush("query", path)
      .then(() => {
        redisClient.incr("queued_count");
      })
      .then(() => {
        console.log("Report enqueued :", path);
        return res.render("report", {
          success: "OK. Admin will check the URL you sent.",
          error: "",
          csrfToken: req.csrfToken(),
        });
      });
  } catch (e) {
    console.log("Report error :", e);
    return res.render("report", {
      success: "",
      error: "Internal error",
      csrfToken: req.csrfToken(),
    });
  }
});

// ################################################
//  Error
// ################################################

// catch 404 and forward to error handler
app.use(function (req, res, next) {
  next(createError(404));
});

// error handler
app.use(function (err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get("env") === "development" ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render("error");
});

module.exports = app;
