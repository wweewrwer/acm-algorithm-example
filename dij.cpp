#include<algorithm>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>

const int maxn = 100010, maxm = 500010;
const int inf=1e9+1;
using namespace std;

struct edge
{
    int to, next, w;
}e[maxm];
int first[maxn],np;
int dis[maxn],vis[maxn];
int n, m, s;

void add_edge(int u, int v, int d)
{
	e[++np]=(edge){v,first[u],d};
	first[u]=np;
}

struct node
{
    int dis;
    int pos;
    friend bool operator <(node one,node two)
    {
        return one.dis > two.dis;
    }
};
priority_queue<node> q;

void dijkstra()
{
	for(int i = 1; i <= n; ++i)dis[i] = inf;
    dis[s] = 0;
    q.push( ( node ){0, s} );
    while( !q.empty() )
    {
        node tmp = q.top();
        q.pop();
        int x = tmp.pos, d = tmp.dis;
        if( vis[x] )
            continue;
        vis[x] = 1;
        for( int i = first[x]; i; i = e[i].next )
        {
            int y = e[i].to;
            if( dis[y] > dis[x] + e[i].w )
            {
                dis[y] = dis[x] + e[i].w;
                if( !vis[y] )
                {
                    q.push( ( node ){dis[y], y} );
                }
            }
        }
    }
}

int main()
{
    scanf( "%d%d%d", &n, &m, &s );
    
    for(int i = 0; i < m; ++i )
    {
        int u, v, d;
        scanf( "%d%d%d", &u, &v, &d );
        add_edge( u, v, d );
    }
    dijkstra();
    for( int i = 1; i <= n; i++ )
        printf( "%d ", dis[i] );
    return 0;
}
