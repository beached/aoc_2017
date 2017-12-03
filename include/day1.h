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
		namespace day1 {
			namespace impl {
				struct summer_t {
					daw::string_view orig;
					size_t difference;
					size_t pos;

					constexpr summer_t( daw::string_view str, size_t diff = 1 ) noexcept
					  : orig{str}
					  , difference{diff}
					  , pos{0} {}

					constexpr size_t operator( )( size_t sum, char cur_val ) noexcept {
						auto other_pos = ( pos + difference ) % orig.size( );
						auto other = orig[other_pos];
						if( cur_val == other ) {
							sum += static_cast<size_t>( cur_val - '0' );
						}
						++pos;
						return std::move( sum );
					}
				};
			} // namespace impl

			constexpr size_t sum_values( daw::string_view str, size_t diff = 1 ) noexcept {
				impl::summer_t summer{str, diff};
				return daw::algorithm::accumulate( str.cbegin( ), str.cend( ), static_cast<size_t>( 0 ), summer );
			}

			//constexpr size_t sum_values_p2( daw::string_view str ) noexcept {}
		} // namespace day1
	}   // namespace aoc_2017
} // namespace daw

