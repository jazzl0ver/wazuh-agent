add_library(randombytes STATIC src/randombytes.c)

get_filename_component(COMMON_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)
target_include_directories(randombytes PUBLIC
    include
    ${COMMON_FOLDER}/error_messages/include
    ${COMMON_FOLDER}/pal/include)

target_link_libraries(randombytes
    utils
    Logger
    time_op)
