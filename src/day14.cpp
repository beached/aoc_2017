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

#include <array>
#include <bitset>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "day10.h"
#include "day14.h"

namespace daw {
	namespace aoc_2017 {
		namespace day14 {
			using grid_t = std::array<std::array<char, 128>, 128>;
			namespace {
				std::string nibble_to_bin( char c ) {
					struct unknown_nibble_exception {};
					switch( c ) {
					case '0':
						return "0000";
					case '1':
						return "0001";
					case '2':
						return "0010";
					case '3':
						return "0011";
					case '4':
						return "0100";
					case '5':
						return "0101";
					case '6':
						return "0110";
					case '7':
						return "0111";
					case '8':
						return "1000";
					case '9':
						return "1001";
					case 'a':
					case 'A':
						return "1010";
					case 'b':
					case 'B':
						return "1011";
					case 'c':
					case 'C':
						return "1100";
					case 'd':
					case 'D':
						return "1101";
					case 'e':
					case 'E':
						return "1110";
					case 'f':
					case 'F':
						return "1111";
					default:
						throw unknown_nibble_exception{};
					}
				}

				std::string do_knot_hash( std::string str ) {
					std::vector<int> init_state{};
					init_state.resize( 256 );
					std::iota( init_state.begin( ), init_state.end( ), 0 );
					return day10::do_hash2( init_state, str );
				}

				std::string hex_to_bin( std::string hx ) {
					std::string result{};
					for( auto c : hx ) {
						result += nibble_to_bin( c );
					}
					return result;
				}

				std::string get_row( std::string str, size_t row ) {
					str += "-" + std::to_string( row );
					return hex_to_bin( do_knot_hash( str ) );
				}

				size_t count_row( std::string str, size_t row ) {
					return std::bitset<128>{get_row( std::move( str ), row ).c_str( )}.count( );
				}

				grid_t get_map( std::string str ) {
					grid_t result{0};
					for( size_t n=0; n<128; ++n ) {
						auto r = get_row( str, n );
						std::copy( r.cbegin( ), r.cend( ), result[n].begin( ) );
					}
					return result;
				}

				void fill_region( grid_t & grid, intmax_t row, intmax_t column ) {
					if( row < 0 || row >= 128 || column < 0 || column >= 128 ) {
						return;
					}
					if( grid[row][column] != '1' ) {
						return;
					}
					grid[static_cast<size_t>( row )][static_cast<size_t>(column)] = 'F';
					fill_region( grid, row-1, column );
					fill_region( grid, row+1, column );
					fill_region( grid, row, column-1 );
					fill_region( grid, row, column+1 );
				}

				size_t find_region( grid_t & grid, size_t row ) {
					size_t count = 0;
					for( size_t n=0; n<grid[row].size( ); ++n ) {
						if( grid[row][n] == '1' ) {
							fill_region( grid, static_cast<intmax_t>( row ), static_cast<intmax_t>( n ) );
							++count;
						}
					}
					return count;
				}
			} // namespace

			size_t count_used( std::string const &str ) {
				size_t sum = 0;
				for( size_t n=0; n<128; ++n ) {
					sum += count_row( str, n );
				}
				return sum;
			}

			size_t count_regions( std::string const &str ) {
				auto grid = get_map( str );
				size_t count = 0;
				for( size_t n=0; n<128; ++n ) {
					count += find_region( grid, n );
				}
				return count;
			}
		} // namespace day14
	}   // namespace aoc_2017
} // namespace daw

