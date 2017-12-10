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

#include "day9.h"

namespace daw {
	namespace aoc_2017 {
		namespace day9 {
			namespace {
				std::pair<size_t,size_t> count_groups( daw::string_view &input, size_t depth ) {
					input.remove_prefix( );
					size_t grp_count = 1;
					size_t grb_count = 0;
					bool in_garbage = false;
					bool skipped = false;
					while( !input.empty( ) ) {
						skipped = false;
						switch( input.front( ) ) {
						case '{':
							if( !in_garbage ) {
								auto tmp = count_groups( input, depth + 1 );
								grp_count += tmp.first;
								grb_count += tmp.second;
							}
							break;
						case '<':
							if( !in_garbage ) {
								skipped = true;
							}
							in_garbage = true;
							break;
						case '>':
							skipped = true;
							in_garbage = false;
							break;
						case '!':
							input.remove_prefix( );
							skipped = true;
							break;
						case '}':
							if( !in_garbage ) {
								return {grp_count + depth, grb_count };
							}
							break;
						}
						if( !skipped && in_garbage ) {
							++grb_count;
						}
						input.remove_prefix( );
					}
					throw std::runtime_error( "Unexpected state" );
				}
			} // namespace

			size_t count_groups( daw::string_view input ) {
				auto result = count_groups( input, 0 );
				return result.first;
			}

			size_t count_groups2( daw::string_view input ) {
				auto result = count_groups( input, 0 );
				return result.second;
			}
		} // namespace day9
	}   // namespace aoc_2017
} // namespace daw

