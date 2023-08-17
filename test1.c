#include <stdio.h>

#define MAX(a, b) ((a>b)?a:b)

void User_Code(void)
{
    // 输入参数
    int m, n, M, N;
    scanf("%d %d %d %d", &M, &N, &m, &n);
    char RawData[M][N];
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            scanf("%d", &RawData[i][j]);
    // 遍历计算
    for (int i = 0; i < M - m; ++i)
    {
        for (int j = 0; j < N - n; ++j)
        {

        }
    }
}

int main(int argc, char *argv[])
{
    User_Code();
    return 0;
}
