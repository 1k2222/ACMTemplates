/*
需要自行定义的变量：
1. maxn:数据最大长度
2. lgmaxn = log(maxn) / log(2)
3. N:当前数据长度
*/
/*#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cassert>

const int maxn = 100000;
const int N = 100;
const int lgmaxn = 9;*/

struct RMQ
{
    const int *data;
    int f[maxn][lgmaxn], lg[maxn + 1];

    int operator[](int x)
    {
        return data[x];
    }

    void callg()
    {
        lg[1] = 0;
        for (int i = 2; i <= maxn; ++i) lg[i] = (i & (i - 1)) ? lg[i - 1] : lg[i - 1] + 1;
        // for (int i = 1; i <= maxn; ++i) printf("lg[%d]=%d\n", i, lg[i]);
    }

    void init()
    {
        int i, j;
        for (i = 0; i < N; ++i) f[i][0] = data[i];
        for (i = 0; i < lg[N]; ++i)
        {
            int len = (1 << i);
            for (j = 0; j + len < N; ++j)
            {
                f[j][i + 1] = std::min(f[j][i], f[j + len][i]);
            }
            for (; j < N; ++j) f[j][i + 1] = f[j][i];
        }
    }

    int query(int x, int y)
    {
        int len = y - x + 1;
        // printf("%d %d %d %d\n", lg[len], x, y - (1 << lg[len]) + 1, lg[len]);
        return std::min(f[x][lg[len]], f[y - (1 << lg[len]) + 1][lg[len]]);
    }
};

//测试程序
/*int main()
{
    srand(time(NULL));
    RMQ a;
    int i, j, k, d[N];
    for (i = 0; i < N; ++i) d[i] = rand();
    a.data = d;
    a.callg();
    a.init();
    for (int i = 0; i < N; ++i)
    for (int j = i; j < N; ++j)
    {
        int t = a[i];
        for (k = i + 1; k <= j; ++k) t = std::min(t, a[k]);
        assert(t == a.query(i, j));
    }
}*/