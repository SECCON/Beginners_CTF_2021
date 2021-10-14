flag = "ctf4b{i0t_dev1ce_firmw4re_ana1ysi3_rev3a1s_a_l0t_of_5ecre7s}\n"

ans = []

for i in range(len(flag)):
    ans.append(ord(flag[i]) ^ 0x53)

print(len(flag))
print(ans)
