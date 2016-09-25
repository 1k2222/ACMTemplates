#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>

typedef int T;

T func(T x, T y)
{
    return std::max(x, y);
}

const int maxn = 200010;

struct SegmentTree
{
    static const int capability = maxn;

    struct NodeType
    {
        int l, r;
        T value;
    };
    int N;
    NodeType nodes[capability << 2];
    int leaf[capability];


    inline int lc(int x) {return x << 1;}
    inline int rc(int x) {return ((x << 1) | 1);}

    void init(int n)
    {
        N = n;
        memset(nodes, 0, sizeof(NodeType) * (4 * N));
        nodes[1].l = 1;
        nodes[1].r = N;
        int lim = (N << 2);
        for (int i = 1; i < lim; ++i)
        {
            if (nodes[i].l == nodes[i].r)
            {
                leaf[nodes[i].l] = i;
                continue;
            }
            int mid = ((nodes[i].l + nodes[i].r) >> 1);
            nodes[lc(i)].l = nodes[i].l;
            nodes[lc(i)].r = mid;
            nodes[rc(i)].l = mid + 1;
            nodes[rc(i)].r = nodes[i].r;
        }
    }

    void fillZero()
    {
        memset(nodes, 0, sizeof(NodeType) * (4 * N));
    }

    void putArray(T *array, int len)
    {
        int i, last;
        for (last = 1; last < N; last <<= 1);
        --last;
        for (i = 0; i < len; ++i) nodes[leaf[i + 1]].value = array[i];

        for (i = last; i > 0; --i)
        {
            if (nodes[i].l < nodes[i].r)
                nodes[i].value = func(nodes[lc(i)].value, nodes[rc(i)].value);
        }
    }

    void print()
    {
        int lim = (N << 2);
        for (int i = 1; i < lim; ++i)
         printf("%d %d %d %d\n", i, nodes[i].l, nodes[i].r, nodes[i].value);
    }

    void update(int pos, T x)
    {
        nodes[leaf[pos]].value = x;
        for (int i = (leaf[pos] >> 1); i > 0; i >>= 1)
            nodes[i].value = func(nodes[lc(i)].value, nodes[rc(i)].value);
    }

    T query(int l, int r)
    {
        T ret = 0;
        int h;
        std::queue<int> q;
        q.push(1);
        while (!q.empty())
        {
            int h = q.front();
            q.pop();
            if (l <= nodes[h].l && nodes[h].r <= r) ret = std::max(ret, nodes[h].value);
            else
            {
                int mid = ((nodes[h].l + nodes[h].r) >> 1);
                if (l <= mid) q.push(lc(h));
                if (r > mid) q.push(rc(h));
            }
        }

        return ret;
    }
};
