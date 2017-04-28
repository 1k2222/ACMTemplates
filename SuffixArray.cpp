/*
需要自行定义的变量：
1. maxn:数据最大长度
2. N:当前数据长度
*/

struct SuffixArray
{
    int bucket[maxn];
    int sa[maxn];
    int ran[maxn];
    char str[maxn];
    int tmp1[maxn], tmp2[maxn];
    int height[maxn];
    

    static inline bool cmp(int a, int b, int l, int *r)
    {
        if ((b + l >= N) || (a + l) >= N) return false;
        return (r[a] == r[b]) && (r[a + l] == r[b + l]);
    }

    void getsa()
    {
        int i, j, t, p, *x = tmp1, *y = tmp2;

        for (i = 0; i < N; ++i) sa[i] = str[i];
        for (i = 0; i < M; ++i) bucket[i] = 0;
        for (i = 0; i < N; ++i)
            ++bucket[str[i]];
        for (i = 1; i < M; ++i) bucket[i] += bucket[i - 1];
        for (i = 0; i < N; ++i) sa[--bucket[str[i]]] = i;
        for (i = 1, p = 0, x[sa[0]] = 0; i < N; ++i)
            x[sa[i]] = (str[sa[i]] == str[sa[i - 1]]) ? p : ++p;

        j = 1;
        for (j = 1; j < N; j <<= 1)
        {

            for (i = N - j, p = 0; i < N; ++i) y[p++] = i;
            for (i = 0; i < N; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
            for (i = 0; i < N; ++i) bucket[i] = 0;
            for (i = 0; i < N; ++i) ++bucket[x[i]];
            for (i = 1; i < N; ++i) bucket[i] += bucket[i - 1];
            for (i = N - 1; i >= 0; --i) sa[--bucket[x[y[i]]]] = y[i];
            swap(x, y);
            for (i = 1, p = 0, x[sa[0]] = 0; i < N; ++i) x[sa[i]] = (cmp(sa[i], sa[i - 1], j, y)) ? p : ++p;
            if (p == N - 1) break;
        }

        for (i = 0; i < N; ++i) ran[i] = x[i];
    }

    void getheight()
    {
        int i, h = 0;
        for (i = 0; i < N; ++i)
        if (ran[i] > 0)
        {
            while (str[i + h] == str[sa[ran[i] - 1] + h])
            {
                if (i + h >= N || sa[ran[i] - 1] + h >= N) break;
                ++h;
            }
            height[ran[i]] = h;
            if (h > 0) --h;
        }
    }

    void cal()
    {
        getsa();
        getheight();
    }
};