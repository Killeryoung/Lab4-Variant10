#include <iostream>
#include "GraphConnectivity.h"

int main() {
    // 6 вершин
    int from[] = {0, 1, 3};
    int to[]   = {1, 2, 4};
    const int n = 6, m = 3;

    int labels[6], k = 0;
    int rc = connectedComponents(n, m, from, to, labels, &k);
    std::cout << "rc=" << rc << " k=" << k << " labels:";
    for (int i = 0; i < n; ++i) std::cout << ' ' << labels[i];
    std::cout << "\n";                       // очікуємо k=3, labels: 0 0 0 1 1 2

    int conn = -1, cyc = -1;
    isConnected(n, m, from, to, &conn);      // очікуємо 0
    hasCycle(n, m, from, to, &cyc);          // очікуємо 0
    std::cout << "connected=" << conn << " cycle=" << cyc << "\n";

    int sizes[6], cnt = 0;
    componentSizes(n, m, from, to, sizes, 6, &cnt);   // очікуємо 3 2 1
    for (int i = 0; i < cnt; ++i) std::cout << sizes[i] << ' ';
    std::cout << "\n";

    // Додаємо ребро 2-0: утворюється цикл
    int from2[] = {0, 1, 3, 2};
    int to2[]   = {1, 2, 4, 0};
    hasCycle(n, 4, from2, to2, &cyc);
    std::cout << "cycle after 2-0: " << cyc << " (expecting 1)\n";

    // Граничні випадки
    std::cout << "nullptr: " << isConnected(n, m, nullptr, nullptr, &conn)
              << " (expecting " << GC_ERR_NULL << ")\n";
    std::cout << "n=0: " << isConnected(0, 0, nullptr, nullptr, &conn)
              << " (expecting " << GC_ERR_BAD_ARG << ")\n";
    return 0;
}