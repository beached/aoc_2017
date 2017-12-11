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

#include <daw/daw_circular_iterator.h>
#include <daw/daw_utility.h>

namespace daw {
	namespace aoc_2017 {
		namespace day10 {
			namespace impl {
				template<typename Trans>
				void reverse_subset( size_t const pos, size_t const length, Trans &translate ) {
					for( size_t n = 0; n < length / 2; ++n ) {
						using std::swap;
						swap( translate( pos + n ), translate( ( pos + length - 1 ) - n ) );
					}
				}

				template<typename Container>
				struct translator_t {
					Container &lst;

					explicit constexpr translator_t( Container &c ) noexcept
					  : lst{c} {}

					constexpr auto &operator( )( size_t pos ) noexcept {
						if( pos >= lst.size( ) ) {
							pos %= lst.size( );
						}
						return lst[pos];
					}
				};

				template<typename Container>
				constexpr auto make_translator( Container &c ) noexcept {
					return translator_t<Container>{c};
				}
			} // namespace impl

			template<typename Container, typename Lengths>
			constexpr auto do_hash( Container &initial_state, Lengths const &lengths, size_t const rounds = 1 ) noexcept {
				daw::exception::DebugAssert( rounds > 0, "There must be a positive/non-zero number of rounds" );
				size_t position = 0;
				intmax_t skip_size = 0;
				auto translator = impl::make_translator( initial_state );
				for( size_t round = 0; round < rounds; ++round ) {
					for( auto current_length : lengths ) {
						impl::reverse_subset( position, static_cast<size_t>( current_length ), translator );
						position += static_cast<size_t>( current_length ) + skip_size;
						++skip_size;
					}
				}
				auto result = initial_state[0] * initial_state[1];
				daw::exception::DebugAssert( result >= 0, "Expected a positive result" );
				return result;
			}

			template<typename Container, typename Lengths>
			std::string do_hash2( Container &initial_state, Lengths &&lengths ) {
				daw::exception::DebugAssert( initial_state.size( ) == 256, "Initial state must be 256 elements in size" );
				lengths.insert( lengths.end( ), {17, 31, 73, 47, 23} );

				do_hash( initial_state, lengths, 64 );

				std::string result{};
				for( size_t n = 0; n < 16; ++n ) {
					auto const first = std::next( initial_state.begin( ), static_cast<intmax_t>( n ) * 16 );
					char const tmp =
					  std::accumulate( first, std::next( first, 16 ),
					                   static_cast<char>( 0 ), []( auto lhs, auto rhs ) noexcept { return lhs ^ rhs; } );
					daw::hex_lc( tmp, std::back_inserter( result ) );
				}
				daw::exception::DebugAssert( result.size( ) == 32, "Expected a result of 32 characters" );
				return result;
			}
		} // namespace day10
	}   // namespace aoc_2017
} // namespace daw
