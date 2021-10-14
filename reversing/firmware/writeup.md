## 解法

まずはfileコマンドでファイルの中身を確認します。

```
$ file firmware.bin
firmware.bin: data
```

バイナリデータのようなのでstringsコマンドでフラグがそのまま含まれていないか調べます。

```
$ strings firmware.bin | grep ctf4b
This is a IoT device made by ctf4b networks. Password authentication is required to operate.
  <title>SuperRouter - ctf4b networks</title>
  <meta name="description" content=" - ctf4b networks">
  <h1>SuperRouter - ctf4b networks</h1>
```

フラグ文字列はありませんでした。次にbinwalkでどんなファイルが含まれているか調べます。

```
$ binwalk firmware.bin

DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
1682          0x692           Copyright string: "Copyright 2011-2021 The Bootstrap Authors"
1727          0x6BF           Copyright string: "Copyright 2011-2021 Twitter, Inc."
82842         0x1439A         ELF, 32-bit LSB shared object, ARM, version 1 (SYSV)
93155         0x16BE3         Unix path: /usr/lib/gcc/arm-linux-gnueabihf/9/../../../arm-linux-gnueabihf/Scrt1.o
96237         0x177ED         HTML document header
97092         0x17B44         HTML document footer
97100         0x17B4C         PNG image, 594 x 100, 8-bit grayscale, non-interlaced
97141         0x17B75         Zlib compressed data, best compression
104190        0x196FE         JPEG image data, JFIF standard 1.01
```

様々なファイルが含まれているようです。

binwalkは`-e`オプションで含まれているファイルを自動で取り出してくれます。

```
$ binwalk -e firmware.bin
$ cd _firmware.bin.extracted/ ; ls
17B75 17B75.zlib
```

しかし、このファイルに対してはうまく動かないようなのでHexEditorを使って手作業で取り出します。

TXT, CSS, WOFF2, SVG, HTML, ELF, PNG, JPGファイルが入っており、問題文の「このファイルの中からパスワードを探してください」からLinuxの実行ファイルであるELFの中にフラグがありそうです。

取り出したELFファイル名を「firm」とすると

```
$ file firm
firm: ELF 32-bit LSB pie executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux-armhf.so.3, BuildID[sha1]=d4fde2a811fccb987ffb2e075b170db18f797b8a, for GNU/Linux 3.2.0, not stripped
```

```
$ strings firm | grep ctf4b
This is a IoT device made by ctf4b networks. Password authentication is required to operate.
```

ARMアーキテクチャの32bit CPUで動作する通称armhfのELFファイルで、パスワード認証が実装されていそうです。

まずは静的解析をGhidraで行います。main関数を見てみると`0x1f90`(8080)番ポートでsocket通信を行い、

```cpp
recv(wsock,input,0x1000,0); // 処理1
memcpy(data,&DAT_00010ea4,0xf4); // 処理2
input_length = strlen((char *)input); // 処理3
if (input_length != 0x3d) {
  ...
  send(wsock,error_message,error_message_length,0);
  close(wsock);
}
i = 0;  // 処理4
while (i < 0x3d) {
  if ((uint)(input[i] ^ 0x53) != data[i]) {
    ...
    send(wsock,error_message,error_message_length,0);
    close(wsock);
  }
  i = i + 1;
}
...
send(wsock,success_message,success_message_length,0); // 処理5
close(wsock);
```

1. ユーザー入力を受け付ける
2. メモリ領域`data`へ`&DAT_00010ea4`の内容をコピーする
3. ユーザー入力の長さが0x3dではない場合、エラーメッセージを送信して接続を閉じる
4. ユーザー入力を1文字ずつ`0x53`とXORした値が`data`と等しいか確認し、等しくない場合エラーメッセージを送信して接続を閉じる
5. 成功メッセージを送信して接続を閉じる

という処理を行っています。そして`&DAT_00010ea4`には

```
  DAT_00010ea4
00010ea4 30
00010ea5 00
00010ea6 00
00010ea7 00
00010ea8 27
00010ea9 00
00010eaa 00
00010eab 00
00010eac 35
00010ead 00
00010eae 00
00010eaf 00
00010eb0 67
00010eb1 00
```

このようにXORして比較するための値があります。これらを取り出して成功メッセージが送信される入力を求めると

```python
data = [0x30, 0x27, 0x35, 0x67, 0x31, 0x28, 0x3A, 0x63, 0x27, 0xC, 0x37, 0x36, 0x25, 0x62, 0x30, 0x36, 0xC, 0x35, 0x3A, 0x21, 0x3E, 0x24, 0x67, 0x21, 0x36, 0xC, 0x32, 0x3D, 0x32, 0x62, 0x2A, 0x20, 0x3A, 0x60, 0xC, 0x21, 0x36, 0x25, 0x60, 0x32, 0x62, 0x20, 0xC, 0x32, 0xC, 0x3F, 0x63, 0x27, 0xC, 0x3C, 0x35, 0xC, 0x66, 0x36, 0x30, 0x21, 0x36, 0x64, 0x20, 0x2E, 0x59]

flag = []

for i in range(len(data)):
    flag.append(chr(data[i] ^ 0x53))

print("".join(flag))
# ctf4b{i0t_dev1ce_firmw4re_ana1ysi3_rev3a1s_a_l0t_of_5ecre7s}
```

となりフラグ`ctf4b{i0t_dev1ce_firmw4re_ana1ysi3_rev3a1s_a_l0t_of_5ecre7s}`を取得できました。
