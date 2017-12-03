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
					char last_val;
					constexpr summer_t( char first_val ) noexcept
					  : last_val{first_val} {}

					constexpr size_t operator( )( size_t sum, char cur_val ) noexcept {
						if( cur_val == last_val ) {
							sum += static_cast<size_t>( cur_val - '0' );
						}
						last_val = cur_val;
						return std::move( sum );
					}
				};
			} // namespace impl

			constexpr size_t sum_values( daw::string_view str ) noexcept {
				impl::summer_t summer{str.front( )};
				auto sum =
				  daw::algorithm::accumulate( daw::next( str.cbegin( ) ), str.cend( ), static_cast<size_t>( 0 ), summer );
				sum = summer( sum, str.front( ) );
				return sum;
			}
		} // namespace day1
	}   // namespace aoc_2017
} // namespace daw

