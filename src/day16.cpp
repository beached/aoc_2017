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
#include <daw/daw_parser_addons.h>

#include "day16.h"

namespace daw {
	namespace aoc_2017 {
		namespace day16 {
			namespace {
				void process_spin( daw::string_view &sv, std::string &dancers ) noexcept {
					sv.remove_prefix( );
					auto pos = sv.find_first_of( ',' );
					size_t num_moves = 0;
					daw::parser::parse_unsigned_int( sv.begin( ), sv.begin( ) + pos, num_moves );
					daw::algorithm::rotate(
					  dancers.rbegin( ), daw::next( dancers.rbegin( ), num_moves % dancers.size( ) ), dancers.rend( ) );
					sv.remove_prefix( pos );
					sv.remove_prefix( );
				}

				void process_exchange( daw::string_view &sv, std::string &dancers ) noexcept {
					sv.remove_prefix( );
					auto pos = sv.find( '/' );
					size_t pos1 = 0;
					daw::parser::parse_unsigned_int( sv.begin( ), sv.begin( ) + pos, pos1 );
					sv.remove_prefix( pos + 1 );
					pos = sv.find( ',' );
					if( pos > sv.size( ) ) {
						pos = sv.size( );
					}
					size_t pos2 = 0;
					daw::parser::parse_unsigned_int( sv.begin( ), sv.begin( ) + pos, pos2 );
					std::swap( dancers[pos1], dancers[pos2] );
					sv.remove_prefix( pos );
					sv.remove_prefix( );
				}

				void process_partner( daw::string_view &sv, std::string &dancers ) noexcept {
					sv.remove_prefix( );
					auto pos1 = dancers.find( sv.front( ) );
					sv.remove_prefix( 2 );
					auto pos2 = dancers.find( sv.front( ) );
					std::swap( dancers[pos1], dancers[pos2] );
					sv.remove_prefix( 2 );
				}
			} // namespace

			std::string go_dancing( std::string dancers, daw::string_view dance_moves ) {
				while( !dance_moves.empty( ) ) {
					switch( dance_moves.front( ) ) {
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
