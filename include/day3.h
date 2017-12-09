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

#include <string>
#include <vector>

#include <daw/daw_algorithm.h>

/*
 *
 *	17  16  15  14  13   n*n = 25, 9, or 1
 *	18   5   4   3  12
 *	19   6   1   2  11
 *	20   7   8   9  10
 *	21  22  23  24  25
 *
 *  4  3  2  3  4	(n-1) = 4, 2, or 0
 *  3  2  1  2  3   (n-1)/2 = 2, 1, or 0
 *  2  1  0  1  2
 *  3  2  1  2  3
 *  4  3  2  3  4
 *
 */

namespace daw {
	namespace aoc_2017 {
		namespace day3 {
			constexpr intmax_t dist_from( intmax_t a, intmax_t b ) noexcept {
				a -= b;
				if( a < 0 ) {
					a *= -1;
				}
				return a;
			}

			constexpr auto find_diagonal( intmax_t value ) noexcept {
				struct result_t {
					intmax_t corner_value; // n*n
					intmax_t distance;     // (n-1/2)
					intmax_t side_length;  // (n-1)
				};
				intmax_t n = 1;
				while( value > n * n ) {
					n += 2;
				}
				return result_t{n * n, ( n - 1 ) / 2, ( n - 1 )};
			}

			constexpr intmax_t calc_distance( intmax_t value ) noexcept {
				auto vals = find_diagonal( value );
				// Find closest corner
				while( ( vals.corner_value - vals.side_length ) >= value ) {
					vals.corner_value -= vals.side_length;
				}
				auto dist1 = dist_from( value, vals.corner_value );
				auto dist2 = dist_from( value, vals.corner_value - vals.side_length );
				return vals.side_length - daw::min( dist1, dist2 );
			}

			namespace impl {
				std::pair<intmax_t, intmax_t> spiral_length_to_xy( intmax_t len );
			}
			intmax_t calc_sum( intmax_t value );
		} // namespace day3
	}   // namespace aoc_2017
} // namespace daw
