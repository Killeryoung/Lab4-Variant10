#pragma once


#if defined(_WIN32) || defined(__CYGWIN__)
  #if defined(GRAPHCONN_EXPORTS)
    #define GC_API __declspec(dllexport)   //збиражмо
  #else
    #define GC_API __declspec(dllimport)   //користуємося длл
  #endif
#else
  #define GC_API __attribute__((visibility("default")))
#endif


#define GC_OK                0
#define GC_ERR_NULL         -1
#define GC_ERR_BAD_ARG      -2
#define GC_ERR_BUFFER_SMALL -3
#define GC_ERR_INTERNAL     -4

#define GC_MAX_VERTICES 1000000

#ifdef __cplusplus
extern "C" {
#endif

// Неорієнтований граф: n вершин (0..n-1), m ребер: 

// ця функція визначає компоненти зв'язності графа
GC_API int connectedComponents(int n, int m, const int* from, const int* to,
                               int* componentOf, int* componentCount);

// ця функція визначає, чи є граф зв'язним, повертає 1, якщо зв'язний, інакше 0
GC_API int isConnected(int n, int m, const int* from, const int* to, int* result);

// ця визначає, чи є цикл у графі, повертає 1, якщо є цикл, інакше 0
GC_API int hasCycle(int n, int m, const int* from, const int* to, int* result);

// оця визначає розміри компонентів зв'язаності графу
GC_API int componentSizes(int n, int m, const int* from, const int* to,
                          int* sizes, int capacity, int* count);

#ifdef __cplusplus
}
#endif