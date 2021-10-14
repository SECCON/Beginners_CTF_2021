## 解法
1. git reflogでコミット履歴を確認し、該当コミットハッシュを取得する

```bash
$ git reflog
e0b545f (HEAD -> master) HEAD@{0}: commit (amend): feat: めもを追加
80f3044 HEAD@{1}: commit (amend): feat: めもを追加
b3bfb5c HEAD@{2}: rebase -i (finish): returning to refs/heads/master
b3bfb5c HEAD@{3}: commit (amend): feat: めもを追加
7387982 HEAD@{4}: rebase -i: fast-forward
36a4809 HEAD@{5}: rebase -i (start): checkout HEAD~2
7387982 HEAD@{6}: reset: moving to HEAD
7387982 HEAD@{7}: commit: feat: めもを追加
36a4809 HEAD@{8}: commit: feat: commit-treeの説明を追加
9ac9b0c HEAD@{9}: commit: change: 順番を変更
8fc078d HEAD@{10}: commit: feat: git cat-fileの説明を追加
d3b47fe HEAD@{11}: commit: feat: fsckを追記する
f66de64 HEAD@{12}: commit: feat: reflogの説明追加
d5aeffe HEAD@{13}: commit: feat: resetの説明を追加
a4f7fe9 HEAD@{14}: commit: feat: git logの説明を追加
9fcb006 HEAD@{15}: commit: feat: git commitの説明追加
6d21e22 HEAD@{16}: commit: feat: git addの説明を追加
656db59 HEAD@{17}: commit: feat: add README.md
c27f346 HEAD@{18}: commit (initial): initial commit
```

2. git cat-file -pでtree->blobのコミットハッシュを取得する

```bash
$ git cat-file -p 73879
tree a5b6b52f47aba96730ab61471ddcdff864e5dd8c
parent 36a4809f1ae8013432eb52cfd2f9f062a3269499
author task4233 <29667656+task4233@users.noreply.github.com> 1620491725 +0900
committer task4233 <29667656+task4233@users.noreply.github.com> 1620491725 +0900

feat: めもを追加
$ git cat-file -p a5b6b
100644 blob 16290835a0f74ccf30cbf30d791c84392a9dcce6    README.md
100644 blob 4cbb035d2ff072127b4e22919485127d2273e88e    flag.txt
100644 blob 62337fdb59ceb048f7da9eaf768923d744930842    note.md
```

3. 該当コミットのblobをzlibでdecompressしようとすると、data checkで落ちる

```bash
$ git cat-file -p 4cbb03
ctf4b{0verwr1te_1s_n0t_c0mplete_1n_G1t}
```
