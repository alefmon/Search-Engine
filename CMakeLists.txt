cmake_minimum_required (VERSION 2.8.8)
project (Simple-Web-Server)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

include_directories(.)
include_directories(Searcher/)
include_directories(Searcher/util)

file(GLOB SOURCES "Searcher/boolean.cpp")
file(GLOB SOURCES_B "Searcher/vectorModel.cpp")
file(GLOB SOURCES_C "Searcher/anchorRank.cpp")
file(GLOB SOURCES_D "Searcher/pageRank.cpp")
file(GLOB SOURCES_E "Searcher/searcher.cpp")


find_package(Threads REQUIRED)

find_package(Boost 1.54.0 COMPONENTS regex system thread filesystem date_time REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIR})



#TODO: add requirement for version 1.0.1g (can it be done in one line?)
find_package(OpenSSL)


add_executable(http_examples http_examples.cpp)
target_link_libraries(http_examples ${Boost_LIBRARIES})
target_link_libraries(http_examples ${SOURCES})
target_link_libraries(http_examples ${SOURCES_B})
target_link_libraries(http_examples ${SOURCES_C})
target_link_libraries(http_examples ${SOURCES_D})
target_link_libraries(http_examples ${SOURCES_E})
target_link_libraries(http_examples ${CMAKE_THREAD_LIBS_INIT})


if(MSYS) #TODO: Is MSYS true when MSVC is true?
    target_link_libraries(http_examples ws2_32 wsock32)
endif()
