## 解法

### 概要

- X-Forwarded-Forヘッダーによるアクセス制限の突破

- jsonパーサーの解釈不一致による検証バイパス

```
$ curl -X POST \
  -H 'X-Forwarded-For:192.168.111.1' \
  -H "Content-Type: application/json" \
  -d '{"id":2, "id":0}' \
  http://localhost
```

### アクセス制限を突破する

アクセスしてみると「このページはローカルネットワーク(192.168.111.0/24)内の端末からのみ閲覧できます」と表示されます。

よってアクセスするIPアドレスを`192.168.111.1`のようなローカルネットワーク内のものにしてこの制限を突破します。

このシステムは以下の3つのサービスで構成されています。

```
  HTTP   +---------+     +-------+     +-------+
-------> |  Nginx  +---> |  BFF  +---> |  API  |
         +---------+     +-------+     +-------+
```

そしてBFFサービスのソースコードにはIPアドレスのチェック部分があります。

```go
// check if the accessed user is in the local network (192.168.111.0/24)
func checkLocal() gin.HandlerFunc {
	return func(c *gin.Context) {
		clientIP := c.ClientIP()
		ip := net.ParseIP(clientIP).To4()
		if ip[0] != byte(192) || ip[1] != byte(168) || ip[2] != byte(111) {
			c.HTML(200, "error.tmpl", gin.H{
				"ip": clientIP,
			})
			c.Abort()
			return
		}
	}
}
```

`c.ClientIP()`でIPアドレスを取得していますが、上記のシステムの構成だと取得できるIPアドレスは`Nginx`のものになってしまいます。そこで一般的に用いられる手法としてX-Forwarded-Forヘッダーを使用するというものがあります。

`Nginx`からBFFサービスへリクエストを送るときに「`Nginx`のアクセス元のIPアドレスをX-Forwarded-Forヘッダーに付与し」、「BFFサービスではX-Forwarded-Forヘッダーの値をアクセス元IPアドレスとする」ことで本当のIPアドレスを取得します。

しかし、このシステムでは`Nginx`の設定に誤りがあります。

```
location / {
    proxy_pass   http://bff:8080;
    proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
}
```

この`$proxy_add_x_forwarded_for`は

- リクエストにX-Forwarded-Forヘッダーがない場合は、アクセス元IPアドレスをX-Forwarded-Forヘッダーにセットしてproxy_passへリクエストを送る

- リクエストにX-Forwarded-Forヘッダーがある場合は、その値をX-Forwarded-Forヘッダーにセットしてproxy_passへリクエストを送る

という設定です。これは既にプロキシを経由したリクエストに対しては有用なものですが、このサービスが外部から最初にリクエストを受け取る場合、X-Forwarded-Forヘッダーをセットしたリクエストを送ることでアクセス元IPアドレスを偽装することが可能になります。

よって以下のコマンドでローカルネットワーク内限定ページを表示することができます。

```
$ curl -H 'X-Forwarded-For:192.168.111.1' http://localhost
```

### jsonの検証バイパス

次はローカルネットワーク内限定ページの`Select item`から`Flag`を取得しようとしますが、エラーメッセージ`It is forbidden to retrieve Flag from this BFF server.`が出てしまいます。

このFlag取得の仕組みは

```
  HTTP     +-------+          +-------+
           |       |          |       |
  {"id"=1} |  BFF  | {"id"=1} |  API  |
  -------> |       +--------> |       |
           +-------+          +-------+
```

まずユーザーからのリクエスト`{"id"=1}`をBFFサービスが受け取り、`id`が0か1の時APIサービスへ再度内部でリクエストを送る流れになっています。

APIサービスは`id=2`だとFlagを返してくれるのですが、BFFサービスがブロックしています。なんとかしてBFFサービスを騙してFlagを取得しましょう。

そこで使える手法が「2重keyを含むjsonのパーサー解釈不一致」です。

jsonにおいて二重キーは基本的に許可されない表現であるため、もし二重キーを含むjsonが渡された時jsonパーサーは2つあるキーのどちらかを優先して使用します。しかしこの優先順位はライブラリによって異なっており、例えば`{"id":0, "id":1}`というjsonをパースする場合、goの標準ライブラリは後のキーの`id=1`と解釈しますが`github.com/buger/jsonparser`は前のキーの`id=0`と解釈します。

そして今回のアプリでは「BFFサービスは受け取ったjsonが問題ない場合、受け取ったjsonをそのままAPIサービスへ渡す」実装になっています。ここで二重キーの解釈の差異を利用すると

1. `{"id":2, "id":0}`をBFFサービスへ送る。BFFサービスはgoの標準ライブラリを使用しているので`id=0`と解釈し弾かない
2. BFFサービスから`{"id":2, "id":0}`がAPIサービスへ渡される。APIサービスでは`github.com/buger/jsonparser`を使用しているので`id=2`と解釈しFlagを返す

というように二重キーを含んだjsonを送ることで本来ならばブロックされるFlag(`id=2`)を取得することができます。

```
$ curl -X POST \
  -H 'X-Forwarded-For:192.168.111.1' \
  -H "Content-Type: application/json" \
  -d '{"id":2, "id":0}' \
  http://localhost

{"result":"ctf4b{j50n_is_v4ry_u5efu1_bu7_s0metim3s_it_bi7es_b4ck}"}
```

### 参考

[An Exploration of JSON Interoperability Vulnerabilities](https://labs.bishopfox.com/tech-blog/an-exploration-of-json-interoperability-vulnerabilities)
