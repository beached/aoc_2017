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

#include <daw/daw_algorithm.h>
#include <daw/daw_parser_helper_sv.h>

#include "day16.h"

namespace daw {
	namespace aoc_2017 {
		namespace day16 {
			namespace {
				void process_spin( daw::string_view &sv, std::string &dancers ) noexcept {
					auto const num_moves = daw::parser::parse_unsigned_int<size_t>( sv.pop_front( "," ) );

					daw::algorithm::rotate(
					  dancers.rbegin( ), daw::next( dancers.rbegin( ), num_moves % dancers.size( ) ), dancers.rend( ) );
				}

				void process_exchange( daw::string_view &sv, std::string &dancers ) noexcept {
					auto const pos1 = daw::parser::parse_unsigned_int<size_t>( sv.pop_front( "/" ) );
					auto const pos2 = daw::parser::parse_unsigned_int<size_t>( sv.pop_front( "," ) );
					std::swap( dancers[pos1], dancers[pos2] );
				}

				void process_partner( daw::string_view &sv, std::string &dancers ) noexcept {
					auto pos1 = dancers.find( sv.pop_front( ) );
					sv.remove_prefix( );
					auto pos2 = dancers.find( sv.pop_front( ) );
					std::swap( dancers[pos1], dancers[pos2] );
					sv.remove_prefix( );
				}
			} // namespace

			std::string go_dancing( std::string dancers, daw::string_view dance_moves ) {
				while( !dance_moves.empty( ) ) {
					switch( dance_moves.pop_front( ) ) {
					case 's':
						process_spin( dance_moves, dancers );
						break;
					case 'x':
						process_exchange( dance_moves, dancers );
						break;
					case 'p':
						process_partner( dance_moves, dancers );
						break;
					}
				}
				return dancers;
			}

			std::string go_dancing2( std::string dancers, daw::string_view dance_moves ) {
				for( size_t n=0; n<1'000'000'000; ++n ) {
					dancers = go_dancing( std::move( dancers ), dance_moves );
					if( std::is_sorted( dancers.begin( ), dancers.end( ) ) ) {
						for( size_t m=0; m<(1'000'000'000%(n+1)); ++m ) {
							dancers = go_dancing( std::move( dancers ), dance_moves );
						}
						return dancers;
					}
				}
				return dancers;
			}
		} // namespace day16
	}   // namespace aoc_2017
} // namespace daw
