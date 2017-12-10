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

#define BOOST_TEST_MODULE aoc_2017_day10
#include <daw/boost_test.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "day10.h"

namespace daw {
	namespace aoc_2017 {
		namespace day10 {
			BOOST_AUTO_TEST_CASE( test_001 ) {
				std::vector<intmax_t> tst = {0, 1, 2, 3, 4};
				std::vector<intmax_t> const lengths = {3, 4, 1, 5};
				auto ans = do_hash( tst, lengths );
				BOOST_REQUIRE_EQUAL( ans, 12 );
			}

			BOOST_AUTO_TEST_CASE( test_002 ) {
				std::vector<intmax_t> tst( 256 );
				std::iota( tst.begin( ), tst.end( ), 0 );
				std::vector<intmax_t> const lengths = {97, 167, 54, 178, 2, 11, 209, 174, 119, 248, 254, 0, 255, 1, 64, 190};
				auto ans = do_hash( tst, lengths );
				BOOST_REQUIRE_EQUAL( ans, 8536 );
				std::cout << "Answer 1: " << ans << '\n';
			}

			BOOST_AUTO_TEST_CASE( test_p2_001 ) {
				std::vector<char> tst( 256 );
				std::iota( tst.begin( ), tst.end( ), 0 );
				std::string lengths{};
				auto ans = do_hash2( tst, lengths );
				BOOST_REQUIRE_EQUAL( ans, "a2582a3a0e66e6e86e3812dcb672a272" );
			}

			BOOST_AUTO_TEST_CASE( test_p2_002 ) {
				std::vector<char> tst( 256 );
				std::iota( tst.begin( ), tst.end( ), 0 );
				std::string lengths{"AoC 2017"};
				auto ans = do_hash2( tst, lengths );
				BOOST_REQUIRE_EQUAL( ans, "33efeb34ea91902bb2f59c9920caa6cd" );
			}

			BOOST_AUTO_TEST_CASE( test_p2_003 ) {
				std::vector<char> tst( 256 );
				std::iota( tst.begin( ), tst.end( ), 0 );
				std::string lengths{"1,2,3"};
				auto ans = do_hash2( tst, lengths );
				BOOST_REQUIRE_EQUAL( ans, "3efbe78a8d82f29979031a4aa0b16a9d" );
			}

			BOOST_AUTO_TEST_CASE( test_p2_004 ) {
				std::vector<char> tst( 256 );
				std::iota( tst.begin( ), tst.end( ), 0 );
				std::string lengths{"1,2,4"};
				auto ans = do_hash2( tst, lengths );
				BOOST_REQUIRE_EQUAL( ans, "63960835bcdc130f0b66d7ff4f6a5a8e" );
			}

			BOOST_AUTO_TEST_CASE( test_p2_005 ) {
				std::vector<char> tst( 256 );
				std::iota( tst.begin( ), tst.end( ), 0 );
				std::string lengths{"97,167,54,178,2,11,209,174,119,248,254,0,255,1,64,190"};
				auto ans = do_hash2( tst, lengths );
				BOOST_REQUIRE_EQUAL( ans, "aff593797989d665349efe11bb4fd99b" );
				std::cout << "Answer 2: " << ans << '\n';
			}

		} // namespace day10
	}   // namespace aoc_2017
} // namespace daw
