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

#pragma once

#include <daw/daw_string_view.h>

namespace daw {
	namespace aoc_2017 {
		namespace day15 {
			using value_t = uint64_t;
			struct gen_t {
				value_t cur_value;
				value_t factor;
				value_t mult_of;
				constexpr gen_t( value_t init_value, value_t fact, value_t mult = 1 ) noexcept
				  : cur_value{init_value}
				  , factor{fact}
				  , mult_of{mult} {}

				constexpr value_t operator( )( ) noexcept {
					do {
						cur_value = ( cur_value * factor ) % 2147483647;
					} while( ( cur_value % mult_of ) != 0 );
					return cur_value;
				}
			};

			constexpr value_t count_matches( value_t init_a, value_t init_b, value_t count, value_t mult_of_a = 1,
			                                 value_t mult_of_b = 1 ) noexcept {
				value_t matches = 0;
				gen_t a{init_a, 16807, mult_of_a};
				gen_t b{init_b, 48271, mult_of_b};

				constexpr value_t mask = 0x0000'0000'0000'FFFF;
				for( value_t n = 0; n < count; ++n ) {
					value_t val_a = a( );
					value_t val_b = b( );

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

