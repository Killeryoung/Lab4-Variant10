#include "GraphConnectivity.h"
#include <vector>
#include <numeric>
#include <algorithm>

namespace {

// Система неперетинних множин (DSU): швидко з'єднує вершини в компоненти
struct DSU {
    std::vector<int> p;
    explicit DSU(int n) : p(n) { std::iota(p.begin(), p.end(), 0); }
    int find(int x) {
        while (p[x] != x) { p[x] = p[p[x]]; x = p[x]; }
        return x;
    }
    // false, якщо вершини вже в одній компоненті (це ознака циклу)
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        p[a] = b;
        return true;
    }
};

int validate(int n, int m, const int* from, const int* to) {
    if (n <= 0 || n > GC_MAX_VERTICES || m < 0) return GC_ERR_BAD_ARG;
    if (m > 0 && (!from || !to)) return GC_ERR_NULL;
    for (int i = 0; i < m; ++i)
        if (from[i] < 0 || from[i] >= n || to[i] < 0 || to[i] >= n) return GC_ERR_BAD_ARG;
    return GC_OK;
}

// Спільна робота для всіх функцій: мітки компонент, розміри, наявність циклу
int analyze(int n, int m, const int* from, const int* to,
            std::vector<int>& label, std::vector<int>& sizes, bool& cycle) {
    int rc = validate(n, m, from, to);
    if (rc != GC_OK) return rc;

    DSU d(n);
    cycle = false;
    for (int i = 0; i < m; ++i)
        if (!d.unite(from[i], to[i])) cycle = true;

    label.assign(n, -1);
    sizes.clear();
    std::vector<int> rootLabel(n, -1);
    for (int v = 0; v < n; ++v) {
        int r = d.find(v);
        if (rootLabel[r] == -1) {
            rootLabel[r] = static_cast<int>(sizes.size());
            sizes.push_back(0);
        }
        label[v] = rootLabel[r];
        ++sizes[label[v]];
    }
    return GC_OK;
}

} // namespace

int connectedComponents(int n, int m, const int* from, const int* to,
                        int* componentOf, int* componentCount) {
    try {
        if (!componentOf || !componentCount) return GC_ERR_NULL;
        std::vector<int> label, sizes; bool cycle;
        int rc = analyze(n, m, from, to, label, sizes, cycle);
        if (rc != GC_OK) return rc;
        std::copy(label.begin(), label.end(), componentOf);
        *componentCount = static_cast<int>(sizes.size());
        return GC_OK;
    } catch (...) {
        return GC_ERR_INTERNAL;
    }
}

int isConnected(int n, int m, const int* from, const int* to, int* result) {
    try {
        if (!result) return GC_ERR_NULL;
        std::vector<int> label, sizes; bool cycle;
        int rc = analyze(n, m, from, to, label, sizes, cycle);
        if (rc != GC_OK) return rc;
        *result = (sizes.size() == 1) ? 1 : 0;
        return GC_OK;
    } catch (...) {
        return GC_ERR_INTERNAL;
    }
}

int hasCycle(int n, int m, const int* from, const int* to, int* result) {
    try {
        if (!result) return GC_ERR_NULL;
        std::vector<int> label, sizes; bool cycle;
        int rc = analyze(n, m, from, to, label, sizes, cycle);
        if (rc != GC_OK) return rc;
        *result = cycle ? 1 : 0;
        return GC_OK;
    } catch (...) {
        return GC_ERR_INTERNAL;
    }
}

int componentSizes(int n, int m, const int* from, const int* to,
                   int* sizes, int capacity, int* count) {
    try {
        if (!sizes || !count) return GC_ERR_NULL;
        std::vector<int> label, sz; bool cycle;
        int rc = analyze(n, m, from, to, label, sz, cycle);
        if (rc != GC_OK) return rc;
        *count = static_cast<int>(sz.size());
        if (capacity < *count) return GC_ERR_BUFFER_SMALL;
        std::copy(sz.begin(), sz.end(), sizes);
        return GC_OK;
    } catch (...) {
        return GC_ERR_INTERNAL;
    }
}
