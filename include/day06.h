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

#include <algorithm>
#include <set>

#include <daw/daw_string_view.h>
#include <daw/daw_span.h>
#include <daw/daw_generic_hash.h>

namespace daw {
	namespace aoc_2017 {
		namespace day06 {
			template<typename T>
			void permute( daw::span<T> blocks ) {
				if( blocks.empty( ) ) {
					return;
				}
				auto const pos = std::max_element( blocks.begin( ), blocks.end( ) );
				T count = *pos;
				*pos = 0;
				auto it = std::next( pos );
				while( count > 0 ) {
					if( it == blocks.end( ) ) {
						it = blocks.begin( );
					}
					++(*it);
					--count;
					++it;
				}
			}

			template<typename T>
			size_t find_loops( daw::span<T> blocks ) {
				size_t count = 0;
				std::set<size_t> seen{};
				seen.insert( daw::generic_hash( blocks.cbegin( ), blocks.cend( ) ) );
				while( true ) {
					++count;
					permute( blocks );
					auto hash = daw::generic_hash( blocks.cbegin( ), blocks.cend( ) );
					if( seen.count( hash ) > 0 ) {
						return count;
					}
					seen.insert( hash );
				}
			}

			template<typename T>
			size_t find_loops2( daw::span<T> blocks ) {
				size_t count = 0;
				auto hash_to_find = daw::generic_hash( blocks.cbegin( ), blocks.cend( ) );
				while( true ) {
					++count;
					permute( blocks );
					if( hash_to_find == daw::generic_hash( blocks.cbegin( ), blocks.cend( ) ) ) {
						return count;
					}
				}
			}

		} // namespace day06
	}   // namespace aoc_2017
} // namespace daw

