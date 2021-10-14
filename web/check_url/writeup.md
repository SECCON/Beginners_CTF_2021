# check_url - Writeup

ソースコードが配られる。  
`$_SERVER["REMOTE_ADDR"] === "127.0.0.1"`にてローカルからのアクセスではAdminだと判断されるが、Trueにはならない。  
curlを実行できるようなのでSSRFでフラグを読みだせばよいとすぐにわかる。  
しかし、スーパーサニタイズによってアルファベットと数字以外弾かれる。  
```php
if ($url !== "https://www.example.com"){
  $url = preg_replace("/[^a-zA-Z0-9\/:]+/u", "👻", $url); //Super sanitizing
}
if(stripos($url,"localhost") !== false || stripos($url,"apache") !== false){
  die("do not hack me!");
}
```
`127.0.0.1`にはドットが含まれている。  
`localhost`ならばアルファベットのみだがこれも許可されていない。  
`localhost`の別の記述方法を探すと`2130706433`や`0x7F000001`や`017700000001`と表せる([参考](https://qiita.com/naka_kyon/items/88478be20b300e757fc0))。  
curl_execでは使用できないパターンもあるが、無事`?url=http://0x7F000001`でフラグが得られる。  