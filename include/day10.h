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
				template<typename Trans>
				void reverse_subset( intmax_t pos, intmax_t length, Trans &translate ) {
					for( intmax_t n = 0; n < length / 2; ++n ) {
						using std::swap;
						swap( translate( pos + n ), translate( ( pos + length - 1 ) - n ) );
					}
				}

				template<typename Container>
				struct translator_t {
					Container &lst;

					translator_t( Container &c )
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
					return translator_t<Container>{c};
				}

				constexpr char to_nibble( uint8_t c ) noexcept {
					if( c < 10 ) {
						return '0' + c;
					}
					return 'a' + ( c - 10 );
				}

				constexpr char to_hex_low_nibble( char c ) noexcept {
					uint8_t n = static_cast<uint8_t>(c) & 0x0F;
					return to_nibble( n );
				}

				constexpr char to_hex_high_nibble( char c ) noexcept {
					uint8_t n = static_cast<uint8_t>(c) & 0xF0;
					n >>= 4;
					return to_nibble( n );
				}

				template<typename Container, typename Lengths>
				constexpr auto do_hash_impl( Container &lst, Lengths const &lengths, intmax_t position = 0,
				                             intmax_t skip_size = 0 ) noexcept {
					struct state_t {
						intmax_t position;
						intmax_t skip_size;
						std::decay_t<decltype( lst[0] )> result;
					};
					state_t state{position, skip_size, 0};
					auto translator = impl::make_translator( lst );
					for( auto lng : lengths ) {
						impl::reverse_subset( state.position, lng, translator );
						state.position += lng + state.skip_size;
						++state.skip_size;
					}
					state.result = lst[0] * lst[1];
					return state;
				}
			} // namespace impl

			template<typename Container, typename Lengths>
			constexpr intmax_t do_hash( Container &lst, Lengths const &lengths ) noexcept {
				return impl::do_hash_impl( lst, lengths ).result;
			}

			template<typename Container, typename Lengths>
			std::string do_hash2( Container &init_state, Lengths lengths ) {
				lengths.insert( lengths.end( ), {17, 31, 73, 47, 23} );

				auto state = impl::do_hash_impl( init_state, lengths, 0, 0 );
				for( size_t round = 1; round < 64; ++round ) {
					state = impl::do_hash_impl( init_state, lengths, state.position, state.skip_size );
				}

				std::string result{};
				for( size_t n = 0; n < 16; ++n ) {
					auto const first = std::next( init_state.begin( ), n * 16 );
					char const tmp = std::accumulate( first, std::next( first, 16 ), static_cast<char>( 0 ),
					                                  []( auto lhs, auto rhs ) { return lhs ^ rhs; } );
					result += impl::to_hex_high_nibble( tmp );
					result += impl::to_hex_low_nibble( tmp );
				}
				return result;
			}
		} // namespace day10
	}   // namespace aoc_2017
} // namespace daw

