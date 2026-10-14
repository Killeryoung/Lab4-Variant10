add_library(GraphConnectivity SHARED src/GraphConnectivity.cpp)

target_include_directories(GraphConnectivity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_compile_features(GraphConnectivity PRIVATE cxx_std_20)


target_compile_definitions(GraphConnectivity PRIVATE GRAPHCONN_EXPORTS)

# Експортуємо тільки те, що позначено GC_API
set_target_properties(GraphConnectivity PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON)

if(WIN32)
    # встановлюємо префікс і суфікс для бібліотеки імпорту, щоб не було libGraphConnectivity.lib
    set_target_properties(GraphConnectivity PROPERTIES
        PREFIX ""
        IMPORT_PREFIX ""
        IMPORT_SUFFIX ".lib")
endif()

if(MINGW)
    # Вбудовуємо runtime всередину DLL,
    # щоб партнеру не треба було нічого, окрім нашої DLL
    target_link_options(GraphConnectivity PRIVATE -static -static-libgcc -static-libstdc++)
endif()

# Складання SDK
install(TARGETS GraphConnectivity
        RUNTIME DESTINATION bin      # .dll
        ARCHIVE DESTINATION lib)     # .lib (бібліотека імпорту)
install(FILES include/GraphConnectivity.h DESTINATION include)
install(FILES README.md DESTINATION .)
