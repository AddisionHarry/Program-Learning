import matplotlib

n=10 # 定义点数
c=[0 for i in range(0,n)]
r=[1 for i in range(0,n)]
k=[i for i in range(0,n)]
for i in range(1,n):
    c[i]=r[i]+0.5*c[i-1]
print(c)
