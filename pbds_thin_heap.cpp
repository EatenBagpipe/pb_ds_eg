// Luogu P4779
// https://www.luogu.org/problemnew/show/P4779
#include<bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;

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

typedef __gnu_pbds::priority_queue <QMember, less<QMember>, thin_heap_tag> pq;
int n, m, s, head[maxn];
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
        dist[i] = inf;
    pq Q;
    dist[s] = 0ll;
    vector<pq::point_iterator> id;
    id.reserve(maxn);
    id[s] = Q.push(QMember(s, 0ll));
    while (!Q.empty()) {
        int u = Q.top().order;Q.pop();
        for (int i = head[u]; i; i = edge[i].next) {
            if (dist[edge[i].go] > dist[u] + edge[i].wi) {
                dist[edge[i].go] = dist[u] + edge[i].wi;
                if (id[edge[i].go] != 0)
                    Q.modify(id[edge[i].go], QMember(edge[i].go, dist[edge[i].go]));
                else
                    id[edge[i].go] = Q.push(QMember(edge[i].go, dist[edge[i].go]));
            }
        }
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