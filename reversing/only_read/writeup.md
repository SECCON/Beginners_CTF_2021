# Writeup - only read

## 問題の概要
flagのチェックをするバイナリ．

stringsでは見えないが，定数畳み込みにより比較するASCIIは生で入ってるので読める．

## 解法
`main`を読む

```
    11dc:       3c 66                   cmp    al,0x66
    11de:       75 76                   jne    1256 <main+0xcd>
    11e0:       0f b6 45 ea             movzx  eax,BYTE PTR [rbp-0x16]
    11e4:       3c 6c                   cmp    al,0x6c
    11e6:       75 6e                   jne    1256 <main+0xcd>
    11e8:       0f b6 45 eb             movzx  eax,BYTE PTR [rbp-0x15]
    11ec:       3c 61                   cmp    al,0x61
    11ee:       75 66                   jne    1256 <main+0xcd>
    11f0:       0f b6 45 ec             movzx  eax,BYTE PTR [rbp-0x14]
    11f4:       3c 67                   cmp    al,0x67
    11f6:       75 5e                   jne    1256 <main+0xcd>
    11f8:       0f b6 45 ed             movzx  eax,BYTE PTR [rbp-0x13]
    11fc:       3c 7b                   cmp    al,0x7b
    11fe:       75 56                   jne    1256 <main+0xcd>
    1200:       0f b6 45 ee             movzx  eax,BYTE PTR [rbp-0x12]
    1204:       3c 68                   cmp    al,0x68
    1206:       75 4e                   jne    1256 <main+0xcd>
    1208:       0f b6 45 ef             movzx  eax,BYTE PTR [rbp-0x11]
    120c:       3c 6f                   cmp    al,0x6f
    120e:       75 46                   jne    1256 <main+0xcd>
    1210:       0f b6 45 f0             movzx  eax,BYTE PTR [rbp-0x10]
    1214:       3c 67                   cmp    al,0x67
    1216:       75 3e                   jne    1256 <main+0xcd>
    1218:       0f b6 45 f1             movzx  eax,BYTE PTR [rbp-0xf]
    121c:       3c 65                   cmp    al,0x65
    121e:       75 36                   jne    1256 <main+0xcd>
    1220:       0f b6 45 f2             movzx  eax,BYTE PTR [rbp-0xe]
    1224:       3c 66                   cmp    al,0x66
    1226:       75 2e                   jne    1256 <main+0xcd>
    1228:       0f b6 45 f3             movzx  eax,BYTE PTR [rbp-0xd]
    122c:       3c 75                   cmp    al,0x75
    122e:       75 26                   jne    1256 <main+0xcd>
    1230:       0f b6 45 f4             movzx  eax,BYTE PTR [rbp-0xc]
    1234:       3c 67                   cmp    al,0x67
    1236:       75 1e                   jne    1256 <main+0xcd>
    1238:       0f b6 45 f5             movzx  eax,BYTE PTR [rbp-0xb]
    123c:       3c 61                   cmp    al,0x61
    123e:       75 16                   jne    1256 <main+0xcd>
    1240:       0f b6 45 f6             movzx  eax,BYTE PTR [rbp-0xa]
    1244:       3c 7d                   cmp    al,0x7d
```
