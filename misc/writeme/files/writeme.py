#!/usr/bin/env python3
import os

assert os.path.isfile("flag")

if __name__ == "__main__":
    open("writeme", "w").write("The Answer to the Ultimate Question of Life, the Universe, and Everything is 42.")
    print(eval(input("Chance: ")[:5])) # 42=99 :)
    path = input("File: ")
    if not os.path.exists(path):
        exit("File not found")
    if not os.path.isfile(path):
        exit("Not a file")
    if "flag" in path:
        exit("Path not allowed")
    try:
        fd = open(path, "r+")
        fd.seek(int(input("Seek: ")))
        fd.write("Hack")
        fd.flush()
        fd.seek(0)
    except:
        exit("Error")

    if 42 >= 99:
        print(open("flag").readline()) # Congrats!
    else:
        print(fd.readline())
