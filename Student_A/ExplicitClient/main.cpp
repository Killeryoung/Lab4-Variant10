#include <windows.h>
#include <iostream>

using CC = int (*)(int, int, const int*, const int*, int*, int*);
using Check = int (*)(int, int, const int*, const int*, int*);
using Sizes = int (*)(int, int, const int*, const int*, int*, int, int*);

int main() {
    HMODULE dll = LoadLibraryA("GraphConnectivity.dll");
    if (!dll) { std::cerr << "Cannot load GraphConnectivity.dll (error " << GetLastError() << ")\n"; return 1; }
    auto cc = reinterpret_cast<CC>(GetProcAddress(dll, "connectedComponents"));
    auto isConnected = reinterpret_cast<Check>(GetProcAddress(dll, "isConnected"));
    auto hasCycle = reinterpret_cast<Check>(GetProcAddress(dll, "hasCycle"));
    auto componentSizes = reinterpret_cast<Sizes>(GetProcAddress(dll, "componentSizes"));
    if (!cc || !isConnected || !hasCycle || !componentSizes) {
        std::cerr << "Missing exported function\n"; FreeLibrary(dll); return 2;
    }
    const int n = 6, m = 3;
    const int from[] = {0, 1, 3}, to[] = {1, 2, 4};
    int componentOf[n] = {}, count = 0, connected = -1, cycle = -1, sizes[n] = {}, sizeCount = 0;
    std::cout << "DLL loaded successfully\n";
    std::cout << "connectedComponents status: " << cc(n, m, from, to, componentOf, &count) << ", count: " << count << "\n";
    std::cout << "componentOf:";
    for (int v : componentOf) std::cout << ' ' << v;
    std::cout << "\n";
    std::cout << "isConnected status: " << isConnected(n, m, from, to, &connected) << ", result: " << connected << "\n";
    std::cout << "hasCycle status: " << hasCycle(n, m, from, to, &cycle) << ", result: " << cycle << "\n";
    std::cout << "componentSizes status: " << componentSizes(n, m, from, to, sizes, n, &sizeCount) << ", count: " << sizeCount << "\n";
    std::cout << "sizes:";
    for (int i = 0; i < sizeCount; ++i) std::cout << ' ' << sizes[i];
    std::cout << "\n";
    std::cout << "nullptr status: " << cc(n, m, from, to, nullptr, &count) << " (expected -1)\n";
    const int badFrom[] = {0}, badTo[] = {99};
    std::cout << "invalid vertex status: " << hasCycle(n, 1, badFrom, badTo, &cycle) << " (expected -2)\n";
    std::cout << "small buffer status: " << componentSizes(n, m, from, to, sizes, 1, &sizeCount) << " (expected -3)\n";
    FreeLibrary(dll);
    std::cout << "DLL unloaded\n";
    return 0;
}
