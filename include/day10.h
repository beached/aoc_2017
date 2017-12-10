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

				template<typename Trans>
				void reverse_subset( intmax_t pos, intmax_t length, Trans &translate ) {
					for( intmax_t n = 0; n < length / 2; ++n ) {
						using std::swap;
						swap( translate( pos + n ), translate( ( pos + length - 1 ) - n ) );
					}
				}

				template<typename Container>
				struct translator {
					Container &lst;
					translator( Container &c )
					  : lst{c} {}

					constexpr auto &operator( )( intmax_t pos ) noexcept {
						if( pos >= static_cast<intmax_t>( lst.size( ) ) ) {
							return lst[static_cast<size_t>( pos ) % lst.size( )];
						} else if( pos < 0 ) {
							pos *= -1;
							pos %= static_cast<intmax_t>( lst.size( ) );
							return lst[( lst.size( ) - 1 ) - static_cast<size_t>( pos )];
						}
						return lst[static_cast<size_t>( pos )];
					}

					constexpr auto const &operator( )( intmax_t pos ) const noexcept {
						if( pos >= static_cast<intmax_t>( lst.size( ) ) ) {
							return lst[static_cast<size_t>( pos ) % lst.size( )];
						} else if( pos < 0 ) {
							pos *= -1;
							pos %= static_cast<intmax_t>( lst.size( ) );
							return lst[( lst.size( ) - 1 ) - static_cast<size_t>( pos )];
						}
						return lst[static_cast<size_t>( pos )];
					}
				};

				template<typename Container>
				constexpr auto make_translator( Container &c ) noexcept {
					return translator<Container>{c};
				}
			} // namespace impl

			template<typename Container>
			constexpr intmax_t do_hash( Container &lst, std::vector<intmax_t> const &lengths ) noexcept {
				auto get_at = impl::make_translator( lst );
				intmax_t pos = 0;
				intmax_t skip_sz = 0;
				for( auto lng : lengths ) {
					impl::reverse_subset( pos, lng, get_at );
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
					return 'a' + ( c - 10 );
				}

				template<typename T>
				char *to_hex( T c, char *dst ) {
					*dst++ = to_nibble( ( c & 0xF0 ) >> 4 );
					*dst++ = to_nibble( c & 0x0F );
					return dst;
				}

				struct ascii_hash {
					char hash[33];

					constexpr ascii_hash( ) noexcept
					  : hash{0} {}

					constexpr ascii_hash( ascii_hash const &other ) noexcept
					  : hash{0} {
						for( size_t n = 0; n < 33; ++n ) {
							hash[n] = other.hash[n];
						}
					}

					constexpr ascii_hash( ascii_hash &&other ) noexcept
					  : hash{0} {
						for( size_t n = 0; n < 33; ++n ) {
							hash[n] = other.hash[n];
						}
					}

					constexpr ascii_hash &operator=( ascii_hash const &rhs ) noexcept {
						for( size_t n = 0; n < 33; ++n ) {
							hash[n] = rhs.hash[n];
						}
						return *this;
					}

					constexpr ascii_hash &operator=( ascii_hash &&rhs ) noexcept {
						for( size_t n = 0; n < 33; ++n ) {
							hash[n] = rhs.hash[n];
						}
						return *this;
					}

					~ascii_hash( ) noexcept = default;

					operator std::string( ) const {
						return std::string{hash};
					}
				};

				template<typename Container, typename Lengths>
				constexpr impl::ascii_hash do_hash2( Container &lst, Lengths lengths ) noexcept {
					auto get_at = impl::make_translator( lst );
					lengths.insert( lengths.end( ), {17, 31, 73, 47, 23} );

					intmax_t pos = 0;
					intmax_t skip_sz = 0;
					for( size_t n = 0; n < 64; ++n ) {
						for( auto lng : lengths ) {
							impl::reverse_subset( pos, lng, get_at );
							pos += lng + skip_sz;
							++skip_sz;
						}
					}

					impl::ascii_hash result{};
					char *res_ptr = result.hash;
					for( size_t n = 0; n < 16; ++n ) {
						auto const first = std::next( lst.begin( ), n * 16 );
						char const tmp = std::accumulate( first, std::next( first, 16 ), static_cast<char>( 0 ),
						                                  []( auto lhs, auto rhs ) { return lhs ^ rhs; } );
						res_ptr = impl::to_hex( tmp, res_ptr );
					}
					return result;
				}
			} // namespace impl

			template<typename Container>
			std::string do_hash2( Container &lst, std::string lengths ) {
				return impl::do_hash2( lst, std::move( lengths ) );
			}
		} // namespace day10
	}   // namespace aoc_2017
} // namespace daw
