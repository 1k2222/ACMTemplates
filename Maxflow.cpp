/*
最大流SAP算法
POJ1273
*/

#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cassert>

typedef int valueType;

class Maxflow
{
public:
	Maxflow(int N);
	~Maxflow();
	void insertEdge(int from, int to, valueType r, valueType c);
	int max_flow();
	void print();
	static const valueType INF;
private:
	int dfs(int x, valueType y);
private:
	struct edge
	{
		int from, to, next;
		valueType r, c;
		inline edge(){}
		inline edge(int from, int to, int next, valueType f, valueType c) :from(from), to(to), next(next), r(f), c(c){}
	};
	std::vector<edge> edges;
	int *head, *st, *h, *vh, T;

};

const valueType Maxflow::INF = 0x3fffffff;

Maxflow::Maxflow(int N)
	:T(N)
{
	head = new int[N + 2];
	st = new int[N + 2];
	h = new int[N + 2];
	vh = new int[N + 2];

	for (int i = 0; i <= N; ++i)
	{
	    head[i] = -1;
	    h[i] = st[i] = vh[i] = 0;
	}
	memset(head, -1, sizeof(head));
	memset(h, 0, sizeof(h));
	memset(st, 0, sizeof(st));
	memset(vh, 0, sizeof(vh));
}


Maxflow::~Maxflow()
{
	delete[]head;
	delete[]st;
	delete[]vh;
	delete[]h;
}

void Maxflow::insertEdge(int from, int to, valueType r, valueType c)
{
	int cur = edges.size();
	edges.push_back(edge(from, to, head[from], r, c));
	head[from] = cur;
	edges.push_back(edge(to, from, head[to], c - r, c));
	head[to] = cur + 1;
}

int Maxflow::dfs(int x, valueType y)
{
//    printf("%d %d\n", x, y);
    assert(y >= 0);
	if (x == T) return y;
	int sig = st[x], minh = T + 1;
	do
	{
	    edge &ce = edges.at(st[x]);
        edge &rce = edges.at(st[x] ^ 1);
//        printf("%d %d %d\n", x, st[x], ce.to);
//        system("pause");
		if (ce.r > 0)
		{
			if (h[ce.to] + 1 == h[x])
			{
				int k = dfs(ce.to, std::min(y, ce.r));
				if (k > 0)
				{
					ce.r -= k;
					rce.r += k;
					return k;
				}
			}
			minh = std::min(minh, h[ce.to] + 1);
			if (h[0] > T) return 0;
		}
		st[x] = ce.next;
		if (st[x] == -1) st[x] = head[x];
	} while (sig != st[x]);
	if (vh[h[x]]-- == 0) h[0] = T + 1;
	vh[h[x] = minh]++;
	return 0;
}

int Maxflow::max_flow()
{
	for (int i = 0; i <= T; i++) h[i] = vh[i] = 0;
	for (int i = 0; i <= T; i++) st[i] = head[i];
	vh[0] = T + 1;
	int ret = 0;
	while (h[0] <= T)
    {
        ret += dfs(0, INF);
//        printf("%d\n", ret);
    }
	return ret;
}

void Maxflow::print()
{
    int i, j;

    for (i = 0; i <= T; ++i)
        printf("%d:%d\n", i, head[i]);

    for (i = 0; i <= T; ++i)
    {
        printf("%d:\n", i);
        for (j = head[i]; j != -1; j = edges[j].next)
            printf("(id:%d to:%d,r:%d,c:%d,next:%d)\n", j, edges[j].to, edges[j].r, edges[j].c, edges[j].next);
        puts("");
    }
    puts("");
}

int N, M;

int main()
{
//    freopen("input.txt", "r", stdin);
    while (scanf("%d %d", &M, &N) != EOF)
    {
        if (M == 0 || N == 0)
        {
            puts("0");
            continue;
        }
        --N;
        Maxflow gc(N);

        int from, to, f, i;
        for (i = 0; i < M; ++i)
        {
            scanf("%d %d %d", &from, &to, &f);
            gc.insertEdge(from - 1, to - 1, f, f);
        }


//        gc.print();
        printf("%d\n", gc.max_flow());
    }
}
