cmake_minimum_required(VERSION 3.5)
project(ades-code-engine-api-framework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MACOSX_RPATH OFF)

#set(RUN_TESTS OFF)
set(ENV{RUN_TESTS} OFF)
set(ENV{IMPORT_YAML_CPP} OFF)
set(YAML_CPP_BUILD_TESTS OFF: FORCE)

add_subdirectory(3ty/yaml-cpp-0.6.3)
include_directories(3ty/yaml-cpp-0.6.3/include)

add_subdirectory(3ty/proc-comm-lib-argo)
add_subdirectory(3ty/proc-comm-lib-cwl)
add_subdirectory(3ty/proc-comm-zoo)

include_directories(cmake-build-debug/3ty/proc-comm-lib-argo/proc-comm-lib-argo/includes)
include_directories(cmake-build-debug/3ty/proc-comm-lib-cwl/proc-comm-lib-cwl/include)

SET(MODS_LIBS
        z m dl
        )


set(src_main src/main.cpp
        src/zoo/zooargo.hpp)

set(LIB_SRC  src/zoo/zooargo.hpp
        src/zoo/argolib.cpp
        )

add_library(argo_interface SHARED ${LIB_SRC})
TARGET_LINK_LIBRARIES(argo_interface )#sources eoepcaargo

add_executable(ades_main ${src_main})
TARGET_LINK_LIBRARIES(ades_main ${MODS_LIBS})





