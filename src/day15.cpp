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

#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "day15.h"

namespace daw {
	namespace aoc_2017 {
		namespace day15 {
			struct gen_t {
				uint64_t cur_value;
				uint64_t factor;
				uint64_t mult_of;
				constexpr gen_t( uint64_t init_value, uint64_t fact, uint64_t mult = 1 ) noexcept
				  : cur_value{init_value}
				  , factor{fact}
				  , mult_of{mult} {}

				constexpr uint64_t operator( )( ) noexcept {
					do {
						cur_value = ( cur_value * factor ) % 2147483647;
					} while( ( cur_value % mult_of ) != 0 );
					return cur_value;
				}
			};

			uint64_t count_matches( uint64_t init_a, uint64_t init_b, uint64_t count, uint64_t mult_of_a,
			                        uint64_t mult_of_b ) noexcept {
				uint64_t matches = 0;
				gen_t a{init_a, 16807, mult_of_a};
				gen_t b{init_b, 48271, mult_of_b};

				constexpr uint64_t mask = 0x0000'0000'0000'FFFF;
				for( uint64_t n = 0; n < count; ++n ) {
					uint64_t val_a = a( );
					uint64_t val_b = b( );

					val_a &= mask;
					val_b &= mask;

					if( val_a == val_b ) {
						++matches;
					}
				}
				return matches;
			}

		} // namespace day15
	}   // namespace aoc_2017
} // namespace daw
