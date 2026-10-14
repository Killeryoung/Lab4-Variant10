
#pragma once

#ifdef GRAPHPATHS_STATIC
    #define GP_API extern "C"
#elif defined(GRAPH_PATHS_EXPORTS)
    #define GP_API extern "C" __declspec(dllexport)
#elif defined(_WIN32)
    #define GP_API extern "C" __declspec(dllimport)
#else
    #define GP_API extern "C"
#endif

// Matrix is row-major n*n; -1 means no edge.
// All other weights must be >= 0.

// Returns 1 on success, 0 for invalid input.
GP_API int dijkstra(
    const int* matrix, int n, int source,
    long long* dist, int* parent
);

// Returns vertex count, 0 if unreachable, -1 if invalid.
GP_API int reconstructPath(
    const int* parent, int n, int source,
    int target, int* path, int capacity
);

// Returns vertex count, 0 if unreachable, -1 if invalid.
GP_API int shortestPath(
    const int* matrix, int n, int source,
    int target, int* path, int capacity
);

// Returns path weight or -1 on error.
GP_API long long pathLength(
    const int* matrix, int n,
    const int* path, int count
);
