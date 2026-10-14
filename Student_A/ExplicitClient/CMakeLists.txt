cmake_minimum_required(VERSION 3.20)
project(ExplicitClient LANGUAGES CXX)
add_executable(ExplicitClient main.cpp)
target_compile_features(ExplicitClient PRIVATE cxx_std_17)
set(SDK "${CMAKE_CURRENT_SOURCE_DIR}/../PartnerSDK/GraphConnectivity_SDK")
add_custom_command(TARGET ExplicitClient POST_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SDK}/bin/GraphConnectivity.dll" "$<TARGET_FILE_DIR:ExplicitClient>")
