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

#define BOOST_TEST_MODULE aoc_2017_day18
#include <daw/boost_test.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "day18.h"

namespace daw {
	namespace aoc_2017 {
		namespace day18 {
			BOOST_AUTO_TEST_CASE( test_001 ) {
				std::vector<std::string> const tst = {"set a 1", "add a 2", "mul a a",  "mod a 5", "snd a",
				                                      "set a 0", "rcv a",   "jgz a -1", "set a 1", "jgz a -2"};

				// auto state = compute_state( tst );
				// BOOST_REQUIRE_EQUAL( state.last_freq, 4 );
			}
			BOOST_AUTO_TEST_CASE( test_002 ) {
				std::vector<std::string> const tst = {
				  "set i 31", "set a 1",   "mul p 17",    "jgz p p",    "mul a 2",   "add i -1",     "jgz i -2",
				  "add a -1", "set i 127", "set p 622",   "mul p 8505", "mod p a",   "mul p 129749", "add p 12345",
				  "mod p a",  "set b p",   "mod b 10000", "snd b",      "add i -1",  "jgz i -9",     "jgz a 3",
				  "rcv b",    "jgz b -1",  "set f 0",     "set i 126",  "rcv a",     "rcv b",        "set p a",
				  "mul p -1", "add p b",   "jgz p 4",     "snd a",      "set a b",   "jgz 1 3",      "snd b",
				  "set f 1",  "add i -1",  "jgz i -11",   "snd a",      "jgz f -16", "jgz a -19	"};

				state_t ans1 = compute_state( tst );
				// BOOST_REQUIRE_EQUAL( ans1.last_freq, );
				std::cout << "answer 2: " << ans1.m_threads[1].op_count( operation::operator_type::snd ) << '\n';
			}
		} // namespace day18
	}   // namespace aoc_2017
} // namespace daw
