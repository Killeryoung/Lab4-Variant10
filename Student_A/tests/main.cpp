#include "GraphPaths.h"
#include <iostream>
int main() {
    const int n=5;
    const int g[n*n]={
       -1, 4, 1,-1,-1,
       -1,-1,-1, 1, 7,
       -1, 2,-1, 5,-1,
       -1,-1,-1,-1, 3,
       -1,-1,-1,-1,-1
    };
    long long dist[n];int parent[n],path[n];
    if(!dijkstra(g,n,0,dist,parent)) return 1;
    std::cout << "Distances:";
    for(auto d:dist) std::cout << ' ' << d;
    std::cout << '\n';
    int count=shortestPath(g,n,0,4,path,n);
    std::cout << "Path 0 -> 4:";
    for(int i=0;i<count;++i) std::cout << ' ' << path[i];
    std::cout << "\nLength: " << pathLength(g,n,path,count) << '\n';
    std::cout << "nullptr rejected: " << (dijkstra(nullptr,n,0,dist,parent)==0) << '\n';
    return count==5 && pathLength(g,n,path,count)==7 ? 0 : 1;
}
