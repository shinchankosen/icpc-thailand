from collections import defaultdict
n,m=map(int,input().split())
a=list(map(int,input().split()))
d=defaultdict(list)
for i in range(n):
    d[a[i]].append(i)
dp=[-1]*n
s=sorted(list(set(a)))
for i in s:
    ndp=dp[:]
    for j in d[i]:
        for k in range(max(0,j-m),min(j+m+1,n)):
            ndp[j]=max(ndp[j],dp[k]+1)
    dp=ndp[:]
print(max(dp))
