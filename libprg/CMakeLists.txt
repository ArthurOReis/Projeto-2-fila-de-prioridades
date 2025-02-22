cmake_minimum_required(VERSION 3.21)

# Add header files here manually
set(HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/src/include/libprg/libprg.h"
        "${CMAKE_CURRENT_LIST_DIR}/src/include/libprg/lista_linear.h"
        "${CMAKE_CURRENT_LIST_DIR}/src/include/libprg/Fila.h"
)
# Add source files here manually
set(SOURCES 
       "${CMAKE_CURRENT_LIST_DIR}/src/libprg/lista_linear.c"
       "${CMAKE_CURRENT_LIST_DIR}/src/libprg/fila.c"
)

add_library(libprg
        src/include/libprg/Fila.h
        src/libprg/fila.c
        src/include/libprg/Pilha.h
        src/libprg/pilha.c
        src/libprg/THash.c
        src/include/libprg/Apb.h
        src/libprg/apb.c)
target_sources(libprg PUBLIC ${SOURCES})
target_include_directories(libprg PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/include)

target_compile_features(libprg PUBLIC c_std_17)

# https://cmake.org/cmake/help/latest/prop_tgt/AUTOGEN_TARGETS_FOLDER.html
source_group(
       TREE "${PROJECT_SOURCE_DIR}/libprg/src/include"
       PREFIX "Header Files"
       FILES ${HEADERS})

# https://cmake.org/cmake/help/latest/command/install.html
install(TARGETS libprg DESTINATION lib)
install(FILES ${HEADER_LIST} DESTINATION include)