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

#include <cmath>
#include <daw/daw_string_view.h>

namespace daw {
	namespace aoc_2017 {
		namespace day11 {
			namespace impl {
				struct point {
					intmax_t x;
					intmax_t y;
				};
				template<typename T>
				constexpr T abs( T t ) noexcept {
					if( t < 0 ) {
						return -t;
					}
					return t;
				}

				constexpr intmax_t calc_hex_dist( intmax_t x, intmax_t y ) noexcept {
					if( abs( x ) > abs( y ) ) {
						return abs( x - y );
					}
					return abs( y - x );
				}
			} // namespace impl

			constexpr auto calc_dist( daw::string_view moves ) noexcept {
				struct result_t {
					intmax_t furthest = 0;
					intmax_t final;

					constexpr void set_max( intmax_t x, intmax_t y ) noexcept {
						auto tmp = impl::calc_hex_dist( x, y );
						if( tmp > furthest ) {
							furthest = tmp;
						}
					}
				} result{0, 0};
				impl::point p{0, 0};
				while( !moves.empty( ) ) {
					auto cur_move = moves.substr( 0, moves.find( "," ) );
					moves.remove_prefix( cur_move.size( ) );
					moves.remove_prefix( );
					if( cur_move == "n" ) {
						++p.y;
					} else if( cur_move == "ne" ) {
						++p.x;
						++p.y;
					} else if( cur_move == "se" ) {
						++p.x;
					} else if( cur_move == "s" ) {
						--p.y;
					} else if( cur_move == "sw" ) {
						--p.x;
						--p.y;
					} else { // nw
						--p.x;
					}
					result.set_max( p.x, p.y );
				}
				result.final = impl::calc_hex_dist( p.x, p.y );
				return result;
			}
		} // namespace day11
	}   // namespace aoc_2017
} // namespace daw

