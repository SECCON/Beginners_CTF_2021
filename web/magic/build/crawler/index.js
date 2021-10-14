const { v4: uuidv4 } = require("uuid");
const puppeteer = require("puppeteer");
const Redis = require("ioredis");
const connection = new Redis({
  host: process.env.REDIS_HOST,
  port: process.env.REDIS_PORT,
});

const USERNAME = process.env.USERNAME; // admin username
const PASSWORD = process.env.PASSWORD; // admin password
const APP_URL = process.env.APP_URL;   // https://magic.quals.beginners.seccon.jp/
const FLAG = process.env.FLAG;         // FLAG!!!

const crawl = async (path, ID) => {
  const browser = await puppeteer.launch({
    args: [
      "--no-sandbox",
      "--disable-background-networking",
      "--disk-cache-dir=/dev/null",
      "--disable-default-apps",
      "--disable-extensions",
      "--disable-gpu",
      "--disable-sync",
      "--disable-translate",
      "--hide-scrollbars",
      "--metrics-recording-only",
      "--mute-audio",
      "--no-first-run",
      "--safebrowsing-disable-auto-update",
    ],
  });
  const page = await browser.newPage();
  try {
    // login admin's page
    await page.goto(APP_URL + "login", {
      waitUntil: "networkidle2",
      timeout: 3000,
    });
    await page.type('input[name="username"]', USERNAME);
    await page.type('input[name="password"]', PASSWORD);
    await Promise.all([
      page.click('button[type="submit"]'),
      page.waitForNavigation({
        waitUntil: "networkidle2",
        timeout: 3000,
      }),
    ]);

    // type FLAG in memo field
    await page.type('input[name="text"]', FLAG);
    await page.click("h1");

    // Oh, a URL has arrived. Let's check it.
    // (If you set `login` as path in Report page, admin accesses `https://magic.quals.beginners.seccon.jp/login` here.)
    await page.goto(APP_URL + path, {
      waitUntil: "networkidle2",
      timeout: 3000,
    });

    await page.close();
  } catch (err) {
    console.error("crawl", ID, err.message);
  } finally {
    await browser.close();
    console.log("crawl", ID, "browser closed");
  }
};

(async () => {
  while (true) {
    console.log(
      "[*] waiting new query",
      await connection.get("queued_count"),
      await connection.get("proceeded_count")
    );
    const ID = uuidv4();
    await connection
      .blpop("query", 0)
      .then((v) => {
        const path = v[1];
        console.log("crawl", ID, path);
        return crawl(path, ID);
      })
      .then(() => {
        console.log("crawl", ID, "finished");
        return connection.incr("proceeded_count");
      })
      .catch((e) => {
        console.log("crawl", ID, e);
      });
  }
})();
