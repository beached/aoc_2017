cmake_minimum_required( VERSION 2.8.12 )

project( aoc_2017_prj )

include( ExternalProject )

find_package( Boost 1.59.0 REQUIRED COMPONENTS system filesystem regex unit_test_framework program_options iostreams )

add_definitions( -DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK )

find_package( Threads REQUIRED )

if( ${CMAKE_CXX_COMPILER_ID} STREQUAL 'MSVC' )
	add_compile_options( -D_WIN32_WINNT=0x0601 /std:c++latest )
else( )
	if( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang" )
		add_compile_options(-std=c++14 -march=native -pthread -Weverything -Wno-c++98-compat -Wno-covered-switch-default -Wno-padded -Wno-exit-time-destructors -Wno-c++98-compat-pedantic -Wno-unused-parameter -Wno-missing-noreturn -Wno-missing-prototypes -Wno-disabled-macro-expansion)
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g -O3")
	elseif( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
		add_compile_options(-std=c++14 -march=native -pthread -Wall -Wno-deprecated-declarations -Wduplicated-cond -Wlogical-op -Wnull-dereference -Wold-style-cast -Wshadow)
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g -O3")
	endif( )
endif( )

externalproject_add(
    header_libraries_prj
    GIT_REPOSITORY "https://github.com/beached/header_libraries.git"
    SOURCE_DIR "${CMAKE_BINARY_DIR}/dependencies/header_libraries"
    GIT_TAG "master"
    INSTALL_DIR "${CMAKE_BINARY_DIR}/install"
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install
)

externalproject_add(
    function_stream_prj
    GIT_REPOSITORY "https://github.com/beached/function_stream.git"
    SOURCE_DIR "${CMAKE_BINARY_DIR}/dependencies/function_stream"
    GIT_TAG "master"
    INSTALL_DIR "${CMAKE_BINARY_DIR}/install"
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install
)



include_directories( SYSTEM "${CMAKE_BINARY_DIR}/install/include" )
link_directories( "${CMAKE_BINARY_DIR}/install/lib" )

include_directories( SYSTEM ${Boost_INCLUDE_DIRS} )
include_directories( SYSTEM ${CURL_INCLUDE_DIRS} )
link_directories( ${Boost_LIBRARY_DIRS} )

set( HEADER_FOLDER "include" )
set( SOURCE_FOLDER "src" )
set( TEST_FOLDER "tests" )

include_directories( ${HEADER_FOLDER} )

set( HEADER_FILES
	#	${HEADER_FOLDER}/buff_2d.h
	${HEADER_FOLDER}/day01.h
	${HEADER_FOLDER}/day02.h
	${HEADER_FOLDER}/day03.h
	${HEADER_FOLDER}/day04.h
	${HEADER_FOLDER}/day05.h
	${HEADER_FOLDER}/str_splitter.h
)

set( SOURCE_FILES
	${SOURCE_FOLDER}/day01.cpp
	${SOURCE_FOLDER}/day02.cpp
	${SOURCE_FOLDER}/day03.cpp
)

enable_testing( )

add_library ( aoc_2017 STATIC ${HEADER_FILES} ${SOURCE_FILES} )
add_dependencies( aoc_2017 header_libraries_prj )

add_library ( str_splitter STATIC ${HEADER_FILES} ${SOURCE_FOLDER}/str_splitter.cpp )
add_dependencies( str_splitter header_libraries_prj )

add_executable( aoc_2017_day01_bin ${HEADER_FILES} ${TEST_FOLDER}/day01_tests.cpp )
target_link_libraries( aoc_2017_day01_bin aoc_2017 ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day01_bin header_libraries_prj )
add_test( aoc_2017_day01_test aoc_2017_day01_bin )

add_executable( aoc_2017_day02_bin ${HEADER_FILES} ${TEST_FOLDER}/day02_tests.cpp )
target_link_libraries( aoc_2017_day02_bin aoc_2017 ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day02_bin header_libraries_prj )
add_test( aoc_2017_day02_test aoc_2017_day02_bin )

add_executable( aoc_2017_day03_bin ${HEADER_FILES} ${TEST_FOLDER}/day03_tests.cpp )
target_link_libraries( aoc_2017_day03_bin aoc_2017 ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day03_bin header_libraries_prj )
add_test( aoc_2017_day03_test aoc_2017_day03_bin )

add_executable( aoc_2017_day04_bin ${HEADER_FILES} ${SOURCE_FOLDER}/day04.cpp ${TEST_FOLDER}/day04_tests.cpp )
target_link_libraries( aoc_2017_day04_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day04_bin header_libraries_prj )
add_test( aoc_2017_day04_test aoc_2017_day04_bin )

add_executable( aoc_2017_day05_bin ${HEADER_FILES} ${SOURCE_FOLDER}/day05.cpp ${TEST_FOLDER}/day05_tests.cpp )
target_link_libraries( aoc_2017_day05_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day05_bin header_libraries_prj )
add_test( aoc_2017_day05_test aoc_2017_day05_bin )

add_executable( aoc_2017_day06_bin ${HEADER_FILES} ${SOURCE_FOLDER}/day06.cpp ${TEST_FOLDER}/day06_tests.cpp )
target_link_libraries( aoc_2017_day06_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day06_bin header_libraries_prj )
add_test( aoc_2017_day06_test aoc_2017_day06_bin )

add_executable( aoc_2017_day07_bin ${HEADER_FILES} ${SOURCE_FOLDER}/day07.cpp ${TEST_FOLDER}/day07_tests.cpp )
target_link_libraries( aoc_2017_day07_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day07_bin header_libraries_prj )
add_test( aoc_2017_day07_test aoc_2017_day07_bin )

add_executable( aoc_2017_day08_bin ${HEADER_FILES} ${SOURCE_FOLDER}/day08.cpp ${TEST_FOLDER}/day08_tests.cpp )
target_link_libraries( aoc_2017_day08_bin str_splitter ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day08_bin header_libraries_prj )
add_test( aoc_2017_day08_test aoc_2017_day08_bin )

add_executable( aoc_2017_day09_bin ${HEADER_FILES} ${SOURCE_FOLDER}/day09.cpp ${TEST_FOLDER}/day09_tests.cpp )
target_link_libraries( aoc_2017_day09_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day09_bin header_libraries_prj )
add_test( aoc_2017_day09_test aoc_2017_day09_bin )

add_executable( aoc_2017_day10_bin ${HEADER_FOLDER}/day10.h ${SOURCE_FOLDER}/day10.cpp ${TEST_FOLDER}/day10_tests.cpp )
target_link_libraries( aoc_2017_day10_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day10_bin header_libraries_prj )
add_test( aoc_2017_day10_test aoc_2017_day10_bin )

add_executable( aoc_2017_day11_bin ${HEADER_FOLDER}/day11.h ${SOURCE_FOLDER}/day11.cpp ${TEST_FOLDER}/day11_tests.cpp )
target_link_libraries( aoc_2017_day11_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day11_bin header_libraries_prj )
add_test( aoc_2017_day11_test aoc_2017_day11_bin )

add_executable( aoc_2017_day12_bin ${HEADER_FOLDER}/day12.h ${SOURCE_FOLDER}/day12.cpp ${TEST_FOLDER}/day12_tests.cpp )
target_link_libraries( aoc_2017_day12_bin str_splitter ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day12_bin header_libraries_prj )
add_test( aoc_2017_day12_test aoc_2017_day12_bin )

add_executable( aoc_2017_day13_bin ${HEADER_FOLDER}/day13.h ${SOURCE_FOLDER}/day13.cpp ${TEST_FOLDER}/day13_tests.cpp )
target_link_libraries( aoc_2017_day13_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day13_bin header_libraries_prj )
add_test( aoc_2017_day13_test aoc_2017_day13_bin )

add_executable( aoc_2017_day14_bin ${HEADER_FOLDER}/day14.h ${SOURCE_FOLDER}/day14.cpp ${TEST_FOLDER}/day14_tests.cpp )
target_link_libraries( aoc_2017_day14_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day14_bin header_libraries_prj )
add_test( aoc_2017_day14_test aoc_2017_day14_bin )

add_executable( aoc_2017_day15_bin ${HEADER_FOLDER}/day15.h ${SOURCE_FOLDER}/day15.cpp ${TEST_FOLDER}/day15_tests.cpp )
target_link_libraries( aoc_2017_day15_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day15_bin header_libraries_prj )
add_test( aoc_2017_day15_test aoc_2017_day15_bin )

add_executable( aoc_2017_day16_bin ${HEADER_FOLDER}/day16.h ${SOURCE_FOLDER}/day16.cpp ${TEST_FOLDER}/day16_tests.cpp )
target_link_libraries( aoc_2017_day16_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day16_bin header_libraries_prj )
add_test( aoc_2017_day16_test aoc_2017_day16_bin )

add_executable( aoc_2017_day17_bin ${HEADER_FOLDER}/day17.h ${SOURCE_FOLDER}/day17.cpp ${TEST_FOLDER}/day17_tests.cpp )
target_link_libraries( aoc_2017_day17_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day17_bin header_libraries_prj )
add_test( aoc_2017_day17_test aoc_2017_day17_bin )

add_executable( aoc_2017_day18_bin ${HEADER_FOLDER}/day18.h ${SOURCE_FOLDER}/day18.cpp ${TEST_FOLDER}/day18_tests.cpp )
target_link_libraries( aoc_2017_day18_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day18_bin header_libraries_prj )
add_test( aoc_2017_day18_test aoc_2017_day18_bin )

add_executable( aoc_2017_day19_bin ${HEADER_FOLDER}/day19.h ${SOURCE_FOLDER}/day19.cpp ${TEST_FOLDER}/day19_tests.cpp )
target_link_libraries( aoc_2017_day19_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day19_bin header_libraries_prj )
add_test( aoc_2017_day19_test aoc_2017_day19_bin )

add_executable( aoc_2017_day20_bin ${HEADER_FOLDER}/day20.h ${SOURCE_FOLDER}/day20.cpp ${TEST_FOLDER}/day20_tests.cpp )
target_link_libraries( aoc_2017_day20_bin task_scheduler_lib function_stream_lib ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} ${CMAKE_THREAD_LIBS_INIT} )
add_dependencies( aoc_2017_day20_bin function_stream_prj header_libraries_prj )
add_test( aoc_2017_day20_test aoc_2017_day20_bin )

