# Writeup - p-8RSA
近い素数`p`, `q`と`GCD(phi, e) != 1`が特徴のRSA暗号。

素数`p`, `q`が近い値だとわかっているとき、フェルマー法で素因数分解することができる。

`GCD(phi, e) != 1`のときの複合方法は、カーマイケルの定理を使っていい感じに復号する。具体的な式はソルバ参照。
