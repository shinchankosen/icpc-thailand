s=list(input())
n=len(s)
l=[1]*n
for i in range(n-1):
    if s[i+1]==s[i]:
        l[i+1]+=l[i]
a=[]
for i in range(n):
    if i==n-1 or s[i+1]!=s[i]:
        a.append((int(s[i]),l[i]))
d={2:['a','b','c'],3:['d','e','f'],4:['g','h','i'],5:['j','k','l'],6:['m','n','o'],7:['p','q','r','s'],8:['t','u','v'],9:['w','x','y','z']}
ans=[]
for i,c in a:
    m=len(d[i])
    if c%m:
        ans.append(d[i][c%m-1])
    for j in range(c//m):
        ans.append(d[i][-1])
print(''.join(ans))
