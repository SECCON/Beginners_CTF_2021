# please not trace me

rc4で暗号化されたフラグを復号している．

`main`も多少難読化されてはいるが，`ptrace`の呼び出しがあるので，NOPで潰す．

あとは`gdb`で`generate_key`の後で鍵を読むなり，復号後にFlagを読むなりすれば良い
