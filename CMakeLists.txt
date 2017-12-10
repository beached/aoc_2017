cmake_minimum_required( VERSION 2.8.12 )

project( aoc_2017_prj )

include( ExternalProject )

find_package( Boost 1.59.0 REQUIRED COMPONENTS system filesystem regex unit_test_framework program_options iostreams )

add_definitions( -DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK )

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
	${HEADER_FOLDER}/buff_2d.h
	${HEADER_FOLDER}/day1.h
	${HEADER_FOLDER}/day2.h
	${HEADER_FOLDER}/day3.h
	${HEADER_FOLDER}/day4.h
	${HEADER_FOLDER}/day5.h
	${HEADER_FOLDER}/str_splitter.h
)

set( SOURCE_FILES
	${SOURCE_FOLDER}/day1.cpp
	${SOURCE_FOLDER}/day2.cpp
	${SOURCE_FOLDER}/day3.cpp
)

enable_testing( )

add_library ( aoc_2017 STATIC ${HEADER_FILES} ${SOURCE_FILES} )
add_dependencies( aoc_2017 header_libraries_prj )

add_library ( str_splitter STATIC ${HEADER_FILES} ${SOURCE_FOLDER}/str_splitter.cpp )
add_dependencies( str_splitter header_libraries_prj )

add_executable( aoc_2017_day1_bin ${HEADER_FILES} ${TEST_FOLDER}/day1_tests.cpp )
target_link_libraries( aoc_2017_day1_bin aoc_2017 ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day1_bin header_libraries_prj )
add_test( aoc_2017_day1_test aoc_2017_day1_bin )

add_executable( aoc_2017_day2_bin ${HEADER_FILES} ${TEST_FOLDER}/day2_tests.cpp )
target_link_libraries( aoc_2017_day2_bin aoc_2017 ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day2_bin header_libraries_prj )
add_test( aoc_2017_day2_test aoc_2017_day2_bin )

add_executable( aoc_2017_day3_bin ${HEADER_FILES} ${TEST_FOLDER}/day3_tests.cpp )
target_link_libraries( aoc_2017_day3_bin aoc_2017 ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day3_bin header_libraries_prj )
add_test( aoc_2017_day3_test aoc_2017_day3_bin )

add_executable( aoc_2017_day4_bin ${HEADER_FILES} ${SOURCE_FOLDER}/day4.cpp ${TEST_FOLDER}/day4_tests.cpp )
target_link_libraries( aoc_2017_day4_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day4_bin header_libraries_prj )
add_test( aoc_2017_day4_test aoc_2017_day4_bin )

add_executable( aoc_2017_day5_bin ${HEADER_FILES} ${SOURCE_FOLDER}/day5.cpp ${TEST_FOLDER}/day5_tests.cpp )
target_link_libraries( aoc_2017_day5_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day5_bin header_libraries_prj )
add_test( aoc_2017_day5_test aoc_2017_day5_bin )

add_executable( aoc_2017_day6_bin ${HEADER_FILES} ${SOURCE_FOLDER}/day6.cpp ${TEST_FOLDER}/day6_tests.cpp )
target_link_libraries( aoc_2017_day6_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day6_bin header_libraries_prj )
add_test( aoc_2017_day6_test aoc_2017_day6_bin )

add_executable( aoc_2017_day7_bin ${HEADER_FILES} ${SOURCE_FOLDER}/day7.cpp ${TEST_FOLDER}/day7_tests.cpp )
target_link_libraries( aoc_2017_day7_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day7_bin header_libraries_prj )
add_test( aoc_2017_day7_test aoc_2017_day7_bin )

add_executable( aoc_2017_day8_bin ${HEADER_FILES} ${SOURCE_FOLDER}/day8.cpp ${TEST_FOLDER}/day8_tests.cpp )
target_link_libraries( aoc_2017_day8_bin str_splitter ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day8_bin header_libraries_prj )
add_test( aoc_2017_day8_test aoc_2017_day8_bin )

add_executable( aoc_2017_day9_bin ${HEADER_FILES} ${SOURCE_FOLDER}/day9.cpp ${TEST_FOLDER}/day9_tests.cpp )
target_link_libraries( aoc_2017_day9_bin ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( aoc_2017_day9_bin header_libraries_prj )
add_test( aoc_2017_day9_test aoc_2017_day9_bin )

