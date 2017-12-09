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

#define BOOST_TEST_MODULE aoc_2017_day6
#include <daw/boost_test.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "day6.h"

namespace daw {
	namespace aoc_2017 {
		namespace day6 {
			BOOST_AUTO_TEST_CASE( test_001 ) {
				std::vector<intmax_t> tst = {0, 2, 7, 0};
				BOOST_REQUIRE_EQUAL( find_loops( make_span( tst ) ), 5 );
			}

			BOOST_AUTO_TEST_CASE( test_002 ) {
				std::vector<intmax_t> tst = {4, 10, 4, 1, 8, 4, 9, 14, 5, 1, 14, 15, 0, 15, 3, 5};
				auto const ans1 = find_loops( make_span( tst ) );
				BOOST_REQUIRE_EQUAL( ans1, 12841 );
				std::cout << "Answer #1: " << ans1 << '\n';
			}

			BOOST_AUTO_TEST_CASE( test_p2_001 ) {
				std::vector<intmax_t> tst = {0, 2, 7, 0};
				auto spn = make_span( tst );
				find_loops( spn );
				BOOST_REQUIRE_EQUAL( find_loops2( spn ), 4 );
			}

			BOOST_AUTO_TEST_CASE( test_p2_002 ) {
				std::vector<intmax_t> tst = {4, 10, 4, 1, 8, 4, 9, 14, 5, 1, 14, 15, 0, 15, 3, 5};
				auto spn = make_span( tst );
				find_loops( spn );
				auto ans2 = find_loops2( spn );
				BOOST_REQUIRE_EQUAL( ans2, 8038 );
				std::cout << "Answer #2: " << ans2 << '\n';
			}


		} // namespace day6
	}   // namespace aoc_2017
} // namespace daw

