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

#define BOOST_TEST_MODULE aoc_2017_day14
#include <daw/boost_test.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "day14.h"

namespace daw {
	namespace aoc_2017 {
		namespace day14 {
			BOOST_AUTO_TEST_CASE( test_001 ) {
				std::string tst = "flqrgnkx";
				auto ans1 = count_used( tst );
				BOOST_REQUIRE_EQUAL( ans1, 8108 );
			}

			BOOST_AUTO_TEST_CASE( test_002 ) {
				std::string tst = "hxtvlmkl";
				auto ans1 = count_used( tst );
				std::cout << "Answer #1: " << ans1 << '\n';
				auto ans2 = count_regions( tst );
				std::cout << "Answer #2: " << ans2 << '\n';
				BOOST_REQUIRE_EQUAL( ans1, 8214 );
				//BOOST_REQUIRE_EQUAL( ans2, );
			}

		} // namespace day14
	}   // namespace aoc_2017
} // namespace daw

