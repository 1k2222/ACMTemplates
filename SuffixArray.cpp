#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 200010;
const int M = 180;

int bucket[maxn];
int sa[maxn];
int rank[maxn];
int str[maxn];
int tmp1[maxn], tmp2[maxn];
int height[maxn];

int N;

void printArray(char *name, int *a, int n)
{
    printf("%s:", name);
    for (int i = 0; i < n; ++i) printf("%d(%d) ", a[i], i);
    putchar('\n');
}

inline bool cmp(int a, int b, int l, int *r)
{
    if ((b + l >= N) || (a + l) >= N) return false;
    return (r[a] == r[b]) && (r[a + l] == r[b + l]);
}

void SuffixArray()
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
//        printArray("\nrank", x, N);
        if (p == N - 1) break;
    }

    for (i = 0; i < N; ++i) rank[i] = x[i];
}

void getheight()
{
    int i, h = 0;
    for (i = 0; i < N; ++i)
    if (rank[i] > 0)
    {
        while (str[i + h] == str[sa[rank[i] - 1] + h])
        {
            if (i + h >= N || sa[rank[i] - 1] + h >= N) break;
            ++h;
        }
        height[rank[i]] = h;
        if (h > 0) --h;
    }
}


int main()
{
    freopen("input.txt", "r", stdin);

    scanf("%d\n", &N);
    for (int i = 0; i < N; ++i) scanf("%d", &str[i]);
    SuffixArray();
    getheight();
    printArray("sa", sa, N);
    printArray("rank", rank, N);
}
