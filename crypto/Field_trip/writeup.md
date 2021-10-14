# Writeup - Field_trip
典型的なナップザック暗号。

密度を計算すると`d = 0.6232`なので、低密度攻撃（LO法, CLOS法）を用いて解読可能である。

基底`M`を

<img src="https://user-images.githubusercontent.com/46185629/116289030-0f31fa80-a7cd-11eb-970d-66b1b48774d7.png" width="280" height="120">

とおく。そして`M`が貼る格子をLLLで殴れば、適当な`i`において`M[i][0]`が0でそれ以外が1か-1のベクトルが得られ、それがフラグとなる。
