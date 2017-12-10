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
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

#include <daw/daw_utility.h>
namespace daw {
	namespace aoc_2017 {
		namespace day10 {
			namespace impl {
				template<typename T, typename Trans>
				std::vector<T> make_subset( intmax_t pos, intmax_t length, Trans &translate ) {
					std::vector<T> result{};
					for( intmax_t n = 0; n < length; ++n ) {
						result.push_back( translate( pos + n ) );
					}
					return result;
				}

				template<typename T, typename Trans>
				void copy_to( std::vector<T> const &subset, intmax_t pos, intmax_t length, Trans &translate ) {
					for( intmax_t n = 0; n < length; ++n ) {
						translate( pos + n ) = subset[static_cast<size_t>( n )];
					}
				}
			} // namespace impl

			template<typename Container>
			intmax_t do_hash( Container &lst, std::vector<intmax_t> const &lengths ) {
				using value_type = std::decay_t<decltype( lst[0] )>;
				auto const get_at = [&lst]( intmax_t pos ) -> intmax_t & {
					size_t n;
					if( pos >= static_cast<intmax_t>( lst.size( ) ) ) {
						n = static_cast<size_t>( pos ) % lst.size( );
					} else if( pos < 0 ) {
						pos *= -1;
						pos %= static_cast<intmax_t>( lst.size( ) );
						n = ( lst.size( ) - 1 ) - static_cast<size_t>( pos );
					} else {
						n = static_cast<size_t>( pos );
					}
					return lst[n];
				};
				intmax_t pos = 0;
				intmax_t skip_sz = 0;
				for( auto lng : lengths ) {
					auto cur_subset = impl::make_subset<value_type>( pos, lng, get_at );
					std::reverse( cur_subset.begin( ), cur_subset.end( ) );
					impl::copy_to( cur_subset, pos, lng, get_at );
					pos += lng + skip_sz;
					++skip_sz;
				}
				return lst[0] * lst[1];
			}

			namespace impl {
				constexpr char to_nibble( char c ) noexcept {
					if( c < 10 ) {
						return '0' + c;
					}
					return 'a' + (c-10);
				}
				template<typename T>
				std::string to_hex( T c ) {
					std::string result{};
					result += to_nibble( (c & 0xF0) >> 4 );
					result += to_nibble( c & 0x0F );
					return result;
				}
			} // namespace impl
			template<typename Container>
			std::string do_hash2( Container &lst, std::string lengths ) {
				using value_type = std::decay_t<decltype( lst[0] )>;
				static_assert( daw::is_same_v<value_type, char>, "Must be characters" );
				lengths.push_back( 17 );
				lengths.push_back( 31 );
				lengths.push_back( 73 );
				lengths.push_back( 47 );
				lengths.push_back( 23 );

				auto const get_at = [&lst]( intmax_t pos ) -> char & {
					size_t n;
					if( pos >= static_cast<intmax_t>( lst.size( ) ) ) {
						n = static_cast<size_t>( pos ) % lst.size( );
					} else if( pos < 0 ) {
						pos *= -1;
						pos %= static_cast<intmax_t>( lst.size( ) );
						n = ( lst.size( ) - 1 ) - static_cast<size_t>( pos );
					} else {
						n = static_cast<size_t>( pos );
					}
					return lst[n];
				};
				intmax_t pos = 0;
				intmax_t skip_sz = 0;
				for( size_t n = 0; n < 64; ++n ) {
					for( auto lng : lengths ) {
						auto cur_subset = impl::make_subset<value_type>( pos, lng, get_at );
						std::reverse( cur_subset.begin( ), cur_subset.end( ) );
						impl::copy_to( cur_subset, pos, lng, get_at );
						pos += lng + skip_sz;
						++skip_sz;
					}
				}
				std::array<value_type, 16> dense_hash{0};
				for( size_t n = 0; n < dense_hash.size( ); ++n ) {
					auto first = std::next( lst.begin( ), n * 16 );
					dense_hash[n] = std::accumulate( first, std::next( first, 16 ), static_cast<char>( 0 ),
					                                 []( auto lhs, auto rhs ) { return lhs ^ rhs; } );
				}
				std::string result{};
				for( auto c: dense_hash ) {
					result += impl::to_hex( c );
				}
				return result;
			}
		} // namespace day10
	}   // namespace aoc_2017
} // namespace daw
