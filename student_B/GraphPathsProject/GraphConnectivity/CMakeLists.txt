add_library(GraphConnectivity STATIC src/GraphConnectivity.cpp)

target_include_directories(GraphConnectivity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(GraphConnectivity PUBLIC cxx_std_20)
target_compile_definitions(GraphConnectivity PUBLIC GRAPHCONN_STATIC)