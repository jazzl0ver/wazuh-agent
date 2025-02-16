cmake_minimum_required(VERSION 3.12.4)

project(utils_unit_test)

file(GLOB UTIL_CXX_UNITTEST_WINDOWS_SRC)

file(GLOB UTIL_CXX_UNITTEST_COMMON_SRC
    "cmdHelper_test.cpp"
    "main.cpp"
)

file(GLOB UTIL_CXX_UNITTEST_LINUX_SRC)

file(COPY input_files DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

link_directories(${SRC_FOLDER}/external/googletest/lib)
link_directories(${SRC_FOLDER}/external/libarchive/.libs/)

if(CMAKE_SYSTEM_NAME STREQUAL "HP-UX")
  add_definitions(-DPROMISE_TYPE=PromiseType::SLEEP)
else()
  add_definitions(-DPROMISE_TYPE=PromiseType::NORMAL)
endif(CMAKE_SYSTEM_NAME STREQUAL "HP-UX")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_executable(utils_unit_test
      ${UTIL_CXX_UNITTEST_COMMON_SRC}
      ${UTIL_CXX_UNITTEST_WINDOWS_SRC}
      ${UTIL_CXX_UNITTEST_CPP17_SRC}
    )
    add_definitions(-DWIN32=1
                    -D_WIN32_WINNT=0x600)
    target_link_libraries(utils_unit_test
        debug gtestd
        debug gmockd
        optimized gtest
        optimized gmock
        pthread
        crypto
        ssl
        -static-libgcc
        ws2_32
        crypt32
    )
else()

    if (APPLE)
      add_executable(utils_unit_test
        ${UTIL_CXX_UNITTEST_COMMON_SRC}
        ${UTIL_CXX_UNITTEST_CPP17_SRC}
      )
    else()
      add_executable(utils_unit_test
        ${UTIL_CXX_UNITTEST_COMMON_SRC}
        ${UTIL_CXX_UNITTEST_LINUX_SRC}
        ${UTIL_CXX_UNITTEST_CPP17_SRC}
      )
    endif(APPLE)

    target_link_libraries(utils_unit_test
        debug gtestd
        debug gmockd
        optimized gtest
        optimized gmock
        rocksdb
        crypto
        dl
        pthread
        rt
        lzma
        z
        minizip
        archive
    )
endif(CMAKE_SYSTEM_NAME STREQUAL "Windows")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_link_libraries(utils_unit_test -fprofile-arcs)
else()
  target_link_libraries(utils_unit_test gcov)
endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

add_test(NAME utils_unit_test
         COMMAND utils_unit_test)
