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

#define BOOST_TEST_MODULE aoc_2017_day03
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <daw/boost_test.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "buff_2d.h"
#include "day03.h"

namespace daw {
	namespace aoc_2017 {
		namespace day03 {
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

			BOOST_AUTO_TEST_CASE( test_325489 ) {
			  auto const answer1 = calc_distance( 325489 );
			  BOOST_REQUIRE_EQUAL( 552, answer1 );
			  std::cout << "answer 1: " << answer1 << '\n';
			}

			BOOST_AUTO_TEST_CASE( test_p2_buff_001 ) {
				std::cout << "2d Buffer test\n";
				daw::buffer_2d<boost::optional<intmax_t>> buff{5, 5};
				intmax_t count = 0;
				for( intmax_t n = 0; n < 5; ++n ) {
					for( intmax_t m = 0; m < 5; ++m ) {
						buff( m, n ) = count++;
						buff.display( );
					}
				}
			}

			BOOST_AUTO_TEST_CASE( test_p2_offset_001 ) {
				std::cout << "2d Buffer test - offset\n";
				daw::buffer_2d<boost::optional<intmax_t>> buff{5, 5};
				buff.set_offset( -2, -2 );
				intmax_t count = 0;
				for( intmax_t n = -2; n <= 2; ++n ) {
					for( intmax_t m = -2; m <= 2; ++m ) {
						buff( m, n ) = count++;
						buff.display( );
					}
				}
			}

			BOOST_AUTO_TEST_CASE( test_p2_spiral_to_xy_001 ) {
				daw::buffer_2d<boost::optional<intmax_t>> buff{5, 5};
				buff.set_offset( -2, -2 );
				buff.display( );
				for( intmax_t n = 1; n <= 25; ++n ) {
					auto pos = impl::spiral_length_to_xy( n );
					std::cout << "setting: (" << pos.first << ", " << pos.second << ") to " << n << '\n';
					buff( pos.first, pos.second ) = n;
					buff.display( );
				}
				buff.display( );
			}
			*/

			BOOST_AUTO_TEST_CASE( test_p2_1 ) {
				BOOST_REQUIRE_EQUAL( 1, calc_sum( 1 ) );
			}

			BOOST_AUTO_TEST_CASE( test_p2_2 ) {
				BOOST_REQUIRE_EQUAL( 1, calc_sum( 2 ) );
			}

			BOOST_AUTO_TEST_CASE( test_p2_3 ) {
				BOOST_REQUIRE_EQUAL( 2, calc_sum( 3 ) );
			}

			BOOST_AUTO_TEST_CASE( test_p2_4 ) {
				BOOST_REQUIRE_EQUAL( 4, calc_sum( 4 ) );
			}

			BOOST_AUTO_TEST_CASE( test_p2_5 ) {
				BOOST_REQUIRE_EQUAL( 5, calc_sum( 5 ) );
			}

			BOOST_AUTO_TEST_CASE( test_p2_6 ) {
				BOOST_REQUIRE_EQUAL( 10, calc_sum( 6 ) );
			}

			BOOST_AUTO_TEST_CASE( test_p2_7 ) {
				BOOST_REQUIRE_EQUAL( 11, calc_sum( 7 ) );
			}

			BOOST_AUTO_TEST_CASE( test_p2_325489 ) {
				auto const answer2 = calc_sum( 325489 );
				// BOOST_REQUIRE_EQUAL( , answer2 );
				std::cout << "answer 2: " << answer2 << '\n';
			}

		} // namespace day03
	}   // namespace aoc_2017
} // namespace daw
