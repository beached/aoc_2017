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

#include <algorithm>
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#include <daw/daw_heap_array.h>

//#include "buff_2d.h"
#include "day03.h"
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

#include <boost/optional.hpp>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#include <daw/daw_heap_array.h>

#include "day03.h"

namespace daw {
	namespace aoc_2017 {
		namespace day03 {
			namespace impl {
				std::pair<intmax_t, intmax_t> spiral_length_to_xy( intmax_t len ) {
					/*
					 * (-m, -m) 2 2 2 3 (m, -m)
					 *          1     3
					 *          1     3
					 * (-m,  m) 1 0 0 0 (m, m)
					 */
					auto cur_vals = find_diagonal( len );
					if( cur_vals.side_length == 0 ) {
						return {0, 0};
					}
					auto const mid_length = cur_vals.side_length / 2;
					auto dist1 = dist_from( len, cur_vals.corner_value );

					if( dist1 < cur_vals.side_length ) {
						// Corner 0
						return {mid_length - dist1, mid_length};
					}
					dist1 -= cur_vals.side_length;
					if( dist1 < cur_vals.side_length ) {
						// Corner 1
						return {-mid_length, mid_length - dist1};
					}
					dist1 -= cur_vals.side_length;
					if( dist1 < cur_vals.side_length ) {
						// Corner 2
						return {-mid_length + dist1, -mid_length};
					}
					dist1 -= cur_vals.side_length;
					return {mid_length, -mid_length + dist1};
				}

				template<typename Buff>
				intmax_t sum_neighbors( Buff &buff, intmax_t pos ) {
					auto gp = impl::spiral_length_to_xy( pos );
					auto const &x = gp.first;
					auto const &y = gp.second;
					intmax_t sum = 0;

					intmax_t const min_y = std::max( buff.min_y( ), y - 1 );
					intmax_t const max_y = std::min( buff.max_y( ) - 1, y + 1 );
					intmax_t const min_x = std::max( buff.min_x( ), x - 1 );
					intmax_t const max_x = std::min( buff.max_x( ) - 1, x + 1 );

					for( intmax_t u = min_y; u <= max_y; ++u ) {
						for( intmax_t v = min_x; u <= max_x; ++u ) {
							if( !( u == y && v == x ) ) {
								sum += buff( v, u );
							}
						}
					}

					return sum;
				}
			} // namespace impl

			intmax_t calc_sum( intmax_t value ) {
				return 0;	/// TODO
			/*
				if( value == 1 ) {
					return 1;
				}
				auto vals = find_diagonal( value );
				auto side_length = vals.side_length;
				auto mid_length = ( side_length + 1 ) / 2;

				daw::buffer_2d<intmax_t> buff{side_length + 1, side_length + 1, 0};
				buff.set_offset( -mid_length, -mid_length );

				auto spiral_pos_at = [&buff]( intmax_t pos ) -> decltype( auto ) {
					auto grid_pos = impl::spiral_length_to_xy( pos );
					return buff( grid_pos.first, grid_pos.second );
				};

				buff.display( );
				spiral_pos_at( 1 ) = 1;
				buff.display( );
				for( intmax_t n = 2; n <= value; ++n ) {
					spiral_pos_at( n ) = impl::sum_neighbors( buff, n );
					buff.display( );
					if( n == value ) {
						std::cout << "done\n";
						buff.display( );
						return spiral_pos_at( n );
					}
				}
				throw std::runtime_error( "Should never reach here" );
				*/
			}
		} // namespace day03
	}   // namespace aoc_2017
} // namespace daw
