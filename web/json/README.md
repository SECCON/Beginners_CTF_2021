# json

## 問題文

外部公開されている社内システムを見つけました。このシステムからFlagを取り出してください。

## 題材とする脆弱性

2重keyを含むjsonのパーサー解釈不一致による検証バイパス

## 実現するためのテーマ

`{"id":0, "id":1}`というjsonを与えた時、goの標準ライブラリは`id=1`と解釈するが`github.com/buger/jsonparser`は`id=0`と解釈する。この違いを利用して、本来ならばブロックされるFLAGを取ることができる。

## 想定する参加者が解答までに至る思考経路

ソースコードからjsonパーサーが違うことに気づく

## 想定する難易度

Medium

## 参考資料

[An Exploration of JSON Interoperability Vulnerabilities](https://labs.bishopfox.com/tech-blog/an-exploration-of-json-interoperability-vulnerabilities)
