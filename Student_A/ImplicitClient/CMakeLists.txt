cmake_minimum_required(VERSION 3.20)
project(ImplicitClient LANGUAGES CXX)
add_executable(ImplicitClient main.cpp)
target_compile_features(ImplicitClient PRIVATE cxx_std_17)
set(SDK "${CMAKE_CURRENT_SOURCE_DIR}/../PartnerSDK/GraphConnectivity_SDK")
target_include_directories(ImplicitClient PRIVATE "${SDK}/include")
target_link_libraries(ImplicitClient PRIVATE "${SDK}/lib/GraphConnectivity.lib")
add_custom_command(TARGET ImplicitClient POST_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SDK}/bin/GraphConnectivity.dll" "$<TARGET_FILE_DIR:ImplicitClient>")
