// The MIT License (MIT)
//
// Copyright (c) 2017 Darrell Wright
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#define BOOST_TEST_MODULE aoc_2017_day3
#include <daw/boost_test.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "day3.h"

namespace daw {
	namespace aoc_2017 {
		namespace day3 {
			/*
			BOOST_AUTO_TEST_CASE( test_1 ) {
				BOOST_REQUIRE_EQUAL( 0, calc_distance( 1 ) );
			}

			BOOST_AUTO_TEST_CASE( test_12 ) {
				BOOST_REQUIRE_EQUAL( 3, calc_distance( 12 ) );
			}

			BOOST_AUTO_TEST_CASE( test_23 ) {
				BOOST_REQUIRE_EQUAL( 2, calc_distance( 23 ) );
			}

			BOOST_AUTO_TEST_CASE( test_1024 ) {
				BOOST_REQUIRE_EQUAL( 31, calc_distance( 1024 ) );
			}

			BOOST_AUTO_TEST_CASE( test_25 ) {
				BOOST_REQUIRE_EQUAL( 4, calc_distance( 25 ) );
			}

			BOOST_AUTO_TEST_CASE( test_21 ) {
				BOOST_REQUIRE_EQUAL( 4, calc_distance( 21 ) );
			}

			BOOST_AUTO_TEST_CASE( test_17 ) {
				BOOST_REQUIRE_EQUAL( 4, calc_distance( 17 ) );
			}

			BOOST_AUTO_TEST_CASE( test_13 ) {
				BOOST_REQUIRE_EQUAL( 4, calc_distance( 13 ) );
			}

			BOOST_AUTO_TEST_CASE( test_11 ) {
				BOOST_REQUIRE_EQUAL( 2, calc_distance( 11 ) );
			}

			BOOST_AUTO_TEST_CASE( test_10 ) {
				BOOST_REQUIRE_EQUAL( 3, calc_distance( 10 ) );
			}
			*/
			BOOST_AUTO_TEST_CASE( test_325489 ) {
				auto answer1 = calc_distance( 325489 );
				BOOST_REQUIRE_EQUAL( 552, answer1 );
				std::cout << "answer 1: " << answer1 << '\n';
			}
		} // namespace day3
	}   // namespace aoc_2017
} // namespace daw

