<!-- HTML Template -->
          <?php
            error_reporting(0);
            if ($_SERVER["REMOTE_ADDR"] === "127.0.0.1"){
              echo "Hi, Admin or SSSSRFer<br>";
              echo "********************FLAG********************";
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
<!-- HTML Template -->
