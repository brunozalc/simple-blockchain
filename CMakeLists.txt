cmake_minimum_required(VERSION 3.10)
project(simple-blockchain)

set(CMAKE_CXX_STANDARD 17)

# add source files
set(SOURCES main.cpp src/Blockchain.cpp src/Block.cpp src/Transaction.cpp)

# include directories
find_package(Curses REQUIRED)
find_package(OpenSSL REQUIRED)
include_directories(include)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(${OPENSSL_INCLUDE_DIR})

# add executable
add_executable(simple-blockchain main.cpp ${SOURCES})

# link libraries 
target_link_libraries(simple-blockchain ${CURSES_LIBRARIES} ${OPENSSL_LIBRARIES})
