cmake_minimum_required(VERSION 3.20)
project(webdemo)

add_definitions(-w)
set (CMKAE_CXX_STANDARD 14)
set (CMAKE_BUILD_TYPE Debug)

list(APPEND CMAKE_PREFIX_PATH "thirdparty/poco")


find_package(Poco REQUIRED COMPONENTS 
	JSON
	Foundation
	Util
	Net 
	XML
)

link_directories("thirdparty/poco/lib")

set (CMAKE_INSTALL_PREFIX ./install)
set (SOURCE_DIR		"${CMAKE_CURRENT_LIST_DIR}/src")
set (INCLUDE_DIR	"${CMAKE_CURRENT_LIST_DIR}/src")
set (POCO_INC		"${CMAKE_CURRENT_LIST_DIR}/thirdparty/poco/include")
set (POCO_LIB		"${CMAKE_CURRENT_LIST_DIR}/thirdparty/poco/lib")

set(ENV{LD_LIBRARY_PATH} "$ENV{LD_LIBRARY_PATH}:${PROJECT_SOURCE_DIR}/thirdparty/poco/lib")

link_directories(
	${POCO_LIB}
)

message(STATUS "include path: ${CMAKE_LIBRARY_PATH}")

include_directories(
	${INCLUDE_DIR}
	${POCO_INC}
)

file(GLOB_RECURSE SRC_FILES
    "${SOURCE_DIR}/*.c*"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE Poco::JSON
	PRIVATE Poco::Foundation
	PRIVATE Poco::Util
	PRIVATE Poco::Net
	PRIVATE Poco::XML
)

# 输出一些调试信息
message(STATUS "Poco_LIBRARIES: ${Poco_LIBRARIES}")
message(STATUS "Poco_VERSION: ${Poco_VERSION}")

