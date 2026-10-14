#include <iostream>
#include "GraphConnectivity.h"

int main() {
    const int n = 6, m = 3;
    const int from[] = {0, 1, 3};
    const int to[] = {1, 2, 4};
    int componentOf[n] = {}, components = 0;
    int connected = -1, cycle = -1, sizes[n] = {}, sizeCount = 0;
    int status = connectedComponents(n, m, from, to, componentOf, &components);
    std::cout << "connectedComponents status: " << status << ", count: " << components << "\n";
    std::cout << "componentOf:";
    for (int v : componentOf) std::cout << ' ' << v;
    std::cout << "\n";
    std::cout << "isConnected status: " << isConnected(n, m, from, to, &connected) << ", result: " << connected << "\n";
    std::cout << "hasCycle status: " << hasCycle(n, m, from, to, &cycle) << ", result: " << cycle << "\n";
    std::cout << "componentSizes status: " << componentSizes(n, m, from, to, sizes, n, &sizeCount) << ", count: " << sizeCount << "\n";
    std::cout << "sizes:";
    for (int i = 0; i < sizeCount; ++i) std::cout << ' ' << sizes[i];
    std::cout << "\n";
    std::cout << "nullptr status: " << connectedComponents(n, m, from, to, nullptr, &components) << " (expected -1)\n";
    const int badFrom[] = {0}, badTo[] = {99};
    std::cout << "invalid vertex status: " << hasCycle(n, 1, badFrom, badTo, &cycle) << " (expected -2)\n";
    std::cout << "small buffer status: " << componentSizes(n, m, from, to, sizes, 1, &sizeCount) << " (expected -3)\n";
    return 0;
}
