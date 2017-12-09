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

#include <cstdint>

#include <daw/daw_span.h>
#include <daw/daw_string_view.h>

namespace daw {
	namespace aoc_2017 {
		namespace day5 {
			template<typename T>
			constexpr size_t count_steps( daw::span<T> maze ) noexcept {
				size_t pos = 0;
				intmax_t next_pos = 0;
				size_t count = 0;
				while( 0 <= next_pos && next_pos < static_cast<intmax_t>( maze.size( ) ) ) {
					++count;
					pos = static_cast<size_t>( next_pos );
					next_pos += static_cast<intmax_t>( maze[pos] );
					++maze[pos];
				}
				return count;
			}

			template<typename T>
			constexpr size_t count_steps2( daw::span<T> maze ) noexcept {
				size_t pos = 0;
				intmax_t next_pos = 0;
				size_t count = 0;
				while( 0 <= next_pos && next_pos < static_cast<intmax_t>( maze.size( ) ) ) {
					++count;
					pos = static_cast<size_t>( next_pos );
					next_pos += static_cast<intmax_t>( maze[pos] );
					if( maze[pos] >= 3 ) {
						--maze[pos];
					} else {
						++maze[pos];
					}
				}
				return count;
			}

		} // namespace day5
	}   // namespace aoc_2017
} // namespace daw

