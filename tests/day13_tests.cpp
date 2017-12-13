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

#define BOOST_TEST_MODULE aoc_2017_day13
#include <daw/boost_test.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "day13.h"

namespace daw {
	namespace aoc_2017 {
		namespace day13 {
			BOOST_AUTO_TEST_CASE( test_001 ) {
				std::vector<std::string> const tst = {"0: 3", "1: 2", "4: 4", "6: 4"};
				auto const ans1 = severity( tst );
				BOOST_REQUIRE_EQUAL( ans1, 24 );

				auto const ans2 = min_cost( tst );
				BOOST_REQUIRE_EQUAL( ans2, 10 );
			}

			BOOST_AUTO_TEST_CASE( test_002 ) {
				std::vector<std::string> const tst = {
				  "0: 5",   "1: 2",   "2: 3",   "4: 4",   "6: 6",   "8: 4",   "10: 6",  "12: 10", "14: 6",  "16: 8",  "18: 6",
				  "20: 9",  "22: 8",  "24: 8",  "26: 8",  "28: 12", "30: 12", "32: 8",  "34: 8",  "36: 12", "38: 14", "40: 12",
				  "42: 10", "44: 14", "46: 12", "48: 12", "50: 24", "52: 14", "54: 12", "56: 12", "58: 14", "60: 12", "62: 14",
				  "64: 12", "66: 14", "68: 14", "72: 14", "74: 14", "80: 14", "82: 14", "86: 14", "90: 18", "92: 17"};
				auto const ans1 = severity( tst );
				BOOST_REQUIRE_EQUAL( ans1, 788 );
				std::cout << "Answer #1: " << ans1 << '\n';
				auto const ans2 = min_cost( tst );
				BOOST_REQUIRE_EQUAL( ans2, 3905748 );
				std::cout << "Answer #2: " << ans2 << '\n';
			}
		} // namespace day13
	}   // namespace aoc_2017
} // namespace daw
