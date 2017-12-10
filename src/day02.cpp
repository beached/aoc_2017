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

#include <daw/daw_array_view.h>
#include <daw/daw_string.h>
#include <daw/daw_string_view.h>

#include "day02.h"

namespace daw {
	namespace aoc_2017 {
		namespace day02 {
			namespace {
				class str_splitter {
					std::string m_str;
					std::string m_delems;
					char * m_ptr;

				public:
					str_splitter( std::string str, std::string delems )
					  : m_str{std::move( str )}
					  , m_delems{std::move( delems )}
					  , m_ptr{strtok( &m_str[0], m_delems.c_str( ) )} {}


					explicit operator bool( ) const noexcept {
						return m_ptr != nullptr;
					}

					std::string operator( )( ) {
						if( m_ptr == nullptr ) {
							return "";
						}
						std::string result{ m_ptr };
						m_ptr = strtok( nullptr, m_delems.c_str( ) );
						return result;
					}
				};

				intmax_t checksum_row( std::string const &str ) {
					static char const delems[] = "\n\t\v\r ";
					if( str.empty( ) ) {
						throw std::runtime_error( "unexpected empty string" );
					}
					intmax_t min = std::numeric_limits<intmax_t>::max( );
					intmax_t max = std::numeric_limits<intmax_t>::min( );
					str_splitter spl( str, delems );
					while( spl ) {
						errno = 0;
						auto i = strtol( spl( ).c_str( ), nullptr, 10 );
						if( i != 0 || errno == 0 ) {
							if( i < min ) {
								min = i;
							}
							if( i > max ) {
								max = i;
							}
						}
					}
					return max - min;
				}

				intmax_t checksum_row2( std::string const &str ) {
					static char const delems[] = "\n\t\v\r ";
					if( str.empty( ) ) {
						throw std::runtime_error( "unexpected empty string" );
					}
					str_splitter spl( str, delems );
					std::vector<intmax_t> nums{};
					while( spl ) {
						errno = 0;
						auto i = strtol( spl( ).c_str( ), nullptr, 10 );
						if( i != 0 || errno == 0 ) {
							nums.push_back( i );
						}
					}
					for( size_t n=0; n < nums.size( ); ++n ) {
						for( size_t m=n+1; m < nums.size( ); ++m ) {
							auto mm = std::minmax( nums[n], nums[m] );
							auto v = mm.second/mm.first;
							if( v*mm.first == mm.second ) {
								return v;
							}
						}
					}
					return 0;
				}

			} // namespace

			intmax_t checksum_values( std::vector<std::string> const &str_arry ) {
				intmax_t checksum = 0;
				for( auto const &row : str_arry ) {
					checksum += checksum_row( row );
				}
				return checksum;
			}

			intmax_t checksum_values2( std::vector<std::string> const & rows ) {
				intmax_t checksum = 0;
				for( auto const &row: rows ) {
					checksum += checksum_row2( row );
				}
				return checksum;
			}
		} // namespace day02
	}   // namespace aoc_2017
} // namespace daw

