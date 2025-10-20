def rotate(t,pp,f):
    x,y,u,l,d,r=pp
    if f:
        return [t-y+1,x,l,d,r,u]
    else:
        return [x,y,u,l,d,r]
def solve():
    ans=[]
    def place(t,y,ii,jj):
        f=t<y
        t,y=max(t,y),min(t,y)
        if y==3:
            p=[[2,1,0,1,1,1],[1,3,1,0,2,1],[3,4,2,1,1,0],[2,6,1,1,0,1]]
            dd=[[0,0,0,0,0,0],[0,0,0,0,1,0],[0,0,0,0,1,0],[0,1,1,0,0,0]]
        elif y==4:
            p=[[2,1,0,1,1,1],[1,3,1,0,1,1],[3,4,1,1,0,1],[4,2,1,1,1,0]]
            dd=[[0,0,0,0,1,0],[0,1,1,0,0,0],[0,1,1,0,0,0],[0,0,0,0,1,0]]
        elif y==5:
            p=[[2,1,0,1,2,1],[1,4,2,0,1,1],[4,2,1,1,1,0],[3,5,2,1,0,1],[5,4,3,1,1,0]]
            dd=[[0,0,0,0,1,0],[0,1,1,0,0,0],[0,0,0,0,1,0],[0,1,1,0,0,0],[0,1,1,0,0,0]]
        elif y==6:
            p=[[2,1,0,1,1,2],[5,2,1,1,2,0],[1,3,1,0,1,1],[3,3,1,0,1,1],[2,5,1,1,0,1],[6,5,4,1,1,0],[4,6,2,3,0,1]]
            dd=[[0,0,0,0,0,0],[0,0,0,0,1,0],[0,0,0,0,1,0],[0,0,0,0,1,0],[0,1,1,0,0,0],[0,1,1,0,0,0],[0,1,1,0,0,0]]
        elif y==7:
            p=[[1,2,1,0,4,1],[2,7,4,1,0,3],[3,1,0,1,1,3],[3,4,1,0,1,1],[4,6,1,1,0,1],[5,3,0,1,1,1],[6,5,1,1,2,0],[7,2,1,3,5,0]]
            dd=[[0,0,0,0,0,0] for i in range(len(p))]
        for i in range(len(p)):
            for j in range(6):
                if y==3:
                    p[i][j]+=dd[i][j]*(t-6)
                else:
                    p[i][j]+=dd[i][j]*(t-y)
            p[i]=rotate(t,p[i],f)
        for i in range(len(p)):
            p[i][0]+=jj
            p[i][1]+=ii
        for i in p:
            ans.append(i)
        return
    r,c=map(int,input().split())
    if r<3 or c<3:
        print(-1)
        return
    if r==3 and c<6:
        print(-1)
        return
    if c==3 and r<6:
        print(-1)
        return
    if r==3 or c==3:
        place(r,c,0,0)
    elif r>7 and c>7:
        for i in range(0,r-7,4):
            for j in range(0,c-7,4):
                place(4,4,i,j)
        for j in range(0,c-7,4):
            place(r-((r-4)//4*4),4,(r-4)//4*4,j)
        for i in range(0,r-7,4):
            place(4,c-((c-4)//4*4),i,(c-4)//4*4)
        place(r-((r-4)//4*4),c-((c-4)//4*4),(r-4)//4*4,(c-4)//4*4)
    elif r>7:
        for i in range(0,r-7,4):
            place(4,c,i,0)
        place(r-((r-4)//4*4),c,(r-4)//4*4,0)
    elif c>7:
        for j in range(0,c-7,4):
            place(r,4,0,j)
        place(r,c-((c-4)//4*4),0,(c-4)//4*4)
    else:
        place(r,c,0,0)
    print(len(ans))
    for i in ans:
        print(*i)
T=int(input())
for _ in range(T):
    solve()
