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

#include <cctype>
#include <limits>
#include <string>
#include <vector>

#include <daw/daw_string.h>
#include <daw/daw_string_view.h>

#include "day1.h"

namespace daw {
	namespace aoc_2017 {
		namespace day2 {
			namespace {
				std::vector<std::string> split_row( daw::string_view row ) {
					static auto const splitter = []( auto c ) {
						return !(std::isdigit( c ) || c == '-');
					};
					std::vector<std::string> results{};
					for( auto item : daw::split( row, splitter ) ) {
						auto str = daw::string::trim_copy( item.to_string( ) );
						if( !str.empty( ) ) {
							results.push_back( std::move( str ) );
						}
					}
					return results;
				}

				intmax_t checksum_row( std::string const &str ) {
					if( str.empty( ) ) {
						throw std::runtime_error( "unexpected empty string" );
					}
					intmax_t min = std::numeric_limits<intmax_t>::max( );
					intmax_t max = std::numeric_limits<intmax_t>::min( );
					for( auto const &s : split_row( str ) ) {
						std::stringstream ss{s};
						intmax_t i = 0;
						ss >> i;
						if( i < min ) {
							min = i;
						}
						if( i > max ) {
							max = i;
						}
					}
					return max - min;
				}
			} // namespace

			intmax_t checksum_values( std::vector<std::string> const &str_arry ) {
				intmax_t checksum = 0;
				for( auto const &row : str_arry ) {
					checksum += checksum_row( row );
				}
				return checksum;
			}
		} // namespace day2
	}   // namespace aoc_2017
} // namespace daw

