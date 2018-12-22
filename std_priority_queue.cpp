// Luogu P4779
// https://www.luogu.org/problemnew/show/P4779
#include<bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 7;
const int maxm = 200000 + 7;
const long long inf = 1ll << 60;

struct QMember {
    int order;
    long long dist;
    QMember() {}
    QMember(int order, long long dist) : order(order), dist(dist) {} 
    bool operator < (const QMember& A) const {
        return dist > A.dist;
    }
};

struct Edge {
    int go, next, wi;
    Edge() {}
    Edge(int go, int next, int wi) : go(go), next(next), wi(wi) {}
}edge[maxm << 1];

int n, m, s, head[maxn];
bool vis[maxn];
long long dist[maxn];

void AddEdge(int u, int v, int w)
{
    static int tot = 0;
    edge[++ tot] = Edge(v, head[u], w);
    head[u] = tot;
}

void ReadIn()
{
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1, u, v, w; i <= m; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        AddEdge(u, v, w);
    }
}

void Dijkstra()
{
    for (int i = 1; i <= n; ++ i)
        dist[i] = inf, vis[i] = false;
    priority_queue<QMember> Q;
    dist[s] = 0ll;
    Q.push(QMember(s, 0ll));
    while (!Q.empty()) {
        int u = Q.top().order;Q.pop();
        if (vis[u]) continue;
        for (int i = head[u]; i; i = edge[i].next) {
            if (dist[edge[i].go] > dist[u] + edge[i].wi) {
                dist[edge[i].go] = dist[u] + edge[i].wi;
                Q.push(QMember(edge[i].go, dist[edge[i].go]));
            }
        }
        vis[u] = true;
    }
    for (int i = 1; i <= n; ++ i)
        cout << dist[i] << " ";
}

int main()
{
    ReadIn();
    Dijkstra();
    return 0;
}