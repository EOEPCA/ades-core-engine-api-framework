cmake_minimum_required(VERSION 3.5)
project(ades-code-engine-api-framework)


#set(RUN_TESTS OFF)
set(ENV{RUN_TESTS} OFF)
set(ENV{IMPORT_YAML_CPP} OFF)

set(YAML_CPP_BUILD_TESTS OFF: FORCE)





add_subdirectory(3ty/yaml-cpp-0.6.3)
include_directories(3ty/yaml-cpp-0.6.3/include)

add_subdirectory(3ty/proc-comm-lib-argo)
add_subdirectory(3ty/proc-comm-lib-cwl)
add_subdirectory(3ty/proc-comm-zoo)




