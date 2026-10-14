add_executable(MyApplication main.cpp)
target_compile_features(MyApplication PRIVATE cxx_std_20)
target_link_libraries(MyApplication PRIVATE GraphConnectivity)

# DLL має лежати поруч з .exe, інакше Windows її не знайде при запуску
add_custom_command(TARGET MyApplication POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:GraphConnectivity>
            $<TARGET_FILE_DIR:MyApplication>)
