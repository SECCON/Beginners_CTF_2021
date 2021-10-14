<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0"/>
  <title>c(heck)_url</title>

  <!-- CSS  -->
  <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
  <link href="css/materialize.min.css" type="text/css" rel="stylesheet" media="screen,projection"/>
  <link href="css/style.css" type="text/css" rel="stylesheet" media="screen,projection"/>
</head>
<body>

  <nav class="light-blue lighten-1" role="navigation">
    <div class="nav-wrapper container">
      <a id="logo-container" href="/" class="brand-logo">c(heck)_url</a>
    </div>
  </nav>

  <div class="section no-pad-bot" id="index-banner">
    <div class="container">
      <br><br>
      <h1 class="header center orange-text">c(heck)_url</h1>
      <div class="row center">
        <h5 class="header col s12 light">
        You can run <b>curl</b> <a href="/?url=https://www.example.com">like this</a>!<br><br>
          <?php
            error_reporting(0);
            if ($_SERVER["REMOTE_ADDR"] === "127.0.0.1"){
              echo "Hi, Admin or SSSSRFer<br>";
              echo "ctf4b{5555rf_15_53rv3r_51d3_5up3r_54n171z3d_r3qu357_f0r63ry}";
            }else{
              echo "Here, take this<br>";
              $url = $_GET["url"];
              if ($url !== "https://www.example.com"){
                $url = preg_replace("/[^a-zA-Z0-9\/:]+/u", "👻", $url); //Super sanitizing
              }
              if(stripos($url,"localhost") !== false || stripos($url,"apache") !== false){
                die("do not hack me!");
              }
              echo "URL: ".$url."<br>";
              $ch = curl_init();
              curl_setopt($ch, CURLOPT_URL, $url);
              curl_setopt($ch, CURLOPT_CONNECTTIMEOUT_MS, 2000);
              curl_setopt($ch, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
              echo "<iframe srcdoc='";
              curl_exec($ch);
              echo "' width='750' height='500'></iframe>";
              curl_close($ch);
            }
          ?>
        </h5>
      </div>

    </div>
  </div>


  <!--  Scripts-->
  <script src="https://code.jquery.com/jquery-2.1.1.min.js"></script>
  <script src="js/materialize.min.js"></script>
  <script src="js/init.js"></script>

  </body>
</html>
