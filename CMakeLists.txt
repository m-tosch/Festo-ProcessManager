CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)

set(PROJECT_NAME client)
project(${PROJECT_NAME})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")


set(SOURCES main.cpp festoconnection.cpp) 
set(HEADERS festoconnection.h)



# This will create you executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

qt5_use_modules(${PROJECT_NAME} Core Network)

# This will link necessary Qt5 libraries to your project
target_link_libraries(${PROJECT_NAME} Qt5::Network)
