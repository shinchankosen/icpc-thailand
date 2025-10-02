from collections import deque
T=int(input())
for _ in range(T):
    K,M=map(int,input().split())
    n=int(input())
    E=list(map(int,input().split()))
    P=list(map(int,input().split()))
    dp=[[[0]*(2**n) for i in range(101)] for i in range(101)]
    q=deque([])
    i=100;j=0;t=0
    while i>K:
        i-=K
        t+=1
        dp[i][0][0]=t
        q.append((i,0,0,t))
    while q:
        i,j,k,t=q.popleft()
        if dp[i][j][k]>t:continue
        for d in range(n):
            if k&(2**d):continue
            if j+P[d]>=100:continue
            ii=min(100,i+E[d])
            jj=j+P[d]
            kk=k+2**d
            tt=t
            while ii>K:
                ii-=K
                jj=max(0,jj-M)
                tt+=1
                if dp[ii][jj][kk]>=tt:break
                dp[ii][jj][kk]=tt
                q.append((ii,jj,kk,tt))
    ans=0
    for i in range(101):
        for j in range(101):
            for k in range(2**n):
                ans=max(ans,dp[i][j][k])
    print(ans)
