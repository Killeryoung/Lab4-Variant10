#include "GraphPaths.h"
#include <vector>
#include <limits>
#include <queue>
#include <functional>
#include <utility>

int dijkstra(const int* matrix, int n, int source, long long* dist, int* parent) {
    if (!matrix || !dist || !parent || n <= 0 || source < 0 || source >= n) return 0;
    for (int i=0;i<n;++i) for (int j=0;j<n;++j) if (matrix[static_cast<size_t>(i)*n+j] < -1) return 0;
    constexpr long long INF = std::numeric_limits<long long>::max();
    for(int i=0;i<n;++i) { dist[i]=INF; parent[i]=-1; }
    using Node=std::pair<long long,int>;
    std::priority_queue<Node,std::vector<Node>,std::greater<Node>> pq;
    dist[source]=0; pq.push({0,source});
    while(!pq.empty()) {
        auto [d,u]=pq.top();pq.pop();
        if(d!=dist[u]) continue;
        for(int v=0;v<n;++v) {
            int w=matrix[static_cast<size_t>(u)*n+v];
            if(w<0 || d>INF-w) continue;
            if(d+w<dist[v]) {dist[v]=d+w;parent[v]=u;pq.push({dist[v],v});}
        }
    }
    for(int i=0;i<n;++i) if(dist[i]==INF) dist[i]=-1;
    return 1;
}
int reconstructPath(const int* parent,int n,int source,int target,int* path,int capacity) {
    if(!parent||!path||n<=0||capacity<n||source<0||target<0||source>=n||target>=n) return -1;
    std::vector<int> rev; std::vector<bool> seen(n,false);
    int cur=target;
    while(cur!=-1) {
        if(cur<0||cur>=n||seen[cur]) return -1;
        seen[cur]=true;rev.push_back(cur);
        if(cur==source) break;
        cur=parent[cur];
    }
    if(rev.back()!=source) return 0;
    for(size_t i=0;i<rev.size();++i) path[i]=rev[rev.size()-1-i];
    return static_cast<int>(rev.size());
}
int shortestPath(const int* matrix,int n,int source,int target,int* path,int capacity) {
    if(!matrix||!path||n<=0||capacity<n||target<0||target>=n) return -1;
    std::vector<long long> dist(n);std::vector<int> parent(n);
    if(!dijkstra(matrix,n,source,dist.data(),parent.data())) return -1;
    if(dist[target]<0) return 0;
    return reconstructPath(parent.data(),n,source,target,path,capacity);
}
long long pathLength(const int* matrix,int n,const int* path,int count) {
    if(!matrix||!path||n<=0||count<=0) return -1;
    long long sum=0;
    for(int i=0;i<count;++i) if(path[i]<0||path[i]>=n) return -1;
    for(int i=1;i<count;++i) {
        int w=matrix[static_cast<size_t>(path[i-1])*n+path[i]];
        if(w<0||sum>std::numeric_limits<long long>::max()-w) return -1;
        sum+=w;
    }
    return sum;
}
