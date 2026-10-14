#pragma once

#if defined(GRAPHCONN_STATIC)
  #define GC_API extern "C"
#elif defined(GRAPHCONN_EXPORTS)
  #define GC_API extern "C" __declspec(dllexport)
#else
  #define GC_API extern "C" __declspec(dllimport)
#endif

#define GC_OK                0
#define GC_ERR_NULL         -1
#define GC_ERR_BAD_ARG      -2
#define GC_ERR_BUFFER_SMALL -3

#define GC_MAX_VERTICES 1000000

// Неорієнтований граф: n вершин (0..n-1), m ребер: from[i] -- to[i]

// componentOf[v] = номер компоненти вершини v (0..k-1), componentCount = k
GC_API int connectedComponents(int n, int m, const int* from, const int* to,
                               int* componentOf, int* componentCount);

// result = 1, якщо граф зв'язний, інакше 0
GC_API int isConnected(int n, int m, const int* from, const int* to, int* result);

// result = 1, якщо в графі є цикл (петля або кратне ребро теж цикл), інакше 0
GC_API int hasCycle(int n, int m, const int* from, const int* to, int* result);

// sizes[i] = кількість вершин у компоненті i; count = k
GC_API int componentSizes(int n, int m, const int* from, const int* to,
                          int* sizes, int capacity, int* count);