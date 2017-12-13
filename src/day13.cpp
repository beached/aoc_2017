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
#include <string>
#include <utility>
#include <vector>

#include <daw/daw_container_algorithm.h>
#include <daw/daw_exception.h>
#include <daw/daw_parser_addons.h>

#include "day13.h"

namespace daw {
	namespace aoc_2017 {
		namespace day13 {
			namespace {
				struct layer_t {
					intmax_t depth;
					intmax_t range;

					constexpr intmax_t pos( intmax_t t ) const noexcept {
						return ( t + depth ) % range;
					}

					constexpr intmax_t cost( intmax_t t ) const noexcept {
						intmax_t result = pos( t ) == 0 ? 1 : 0;
						result *= depth * ( ( range / 2 ) + 1 );
						return result;
					}
				};
				using firewall_t = std::vector<layer_t>;

				constexpr layer_t parse_line( daw::string_view line ) {
					layer_t layer{0, 0};
					auto pos = line.find( ':' );
					auto depth_str = line.substr( 0, pos );
					line.remove_prefix( pos + 2 );
					daw::parser::parse_unsigned_int( depth_str.cbegin( ), depth_str.cend( ), layer.depth );
					daw::parser::parse_unsigned_int( line.cbegin( ), line.cend( ), layer.range );
					layer.range = layer.range == 0 ? 0 : ( layer.range - 1 ) * 2;
					return layer;
				}

				firewall_t parse_input( std::vector<std::string> lines ) {
					firewall_t result{};
					std::transform( lines.cbegin( ), lines.cend( ), std::back_inserter( result ),
					                []( std::string const &str ) { return parse_line( str ); } );
					daw::container::sort( result, []( auto const &lhs, auto const &rhs ) { return lhs.depth < rhs.depth; } );
					return result;
				}

				//*********************************************
				intmax_t simulate( firewall_t firewall ) {
					return std::accumulate( firewall.cbegin( ), firewall.cend( ), static_cast<intmax_t>( 0 ),
					                        []( auto res, layer_t const &l ) { return res + l.cost( 0 ); } );
				}

				intmax_t calc_delay( firewall_t firewall ) {
					intmax_t delay = 1;
					while( std::find_if( firewall.cbegin( ), firewall.cend( ),
					                     [delay]( layer_t const &l ) { return l.pos( delay ) == 0; } ) != firewall.cend( ) ) {
						++delay;
					}
					return delay;
				}
			} // namespace

			intmax_t severity( std::vector<std::string> const &lines ) {
				auto firewall = parse_input( lines );
				return simulate( std::move( firewall ) );
			}

			intmax_t min_cost( std::vector<std::string> const &lines ) {
				auto firewall = parse_input( lines );
				return calc_delay( std::move( firewall ) );
			}
		} // namespace day13
	}   // namespace aoc_2017
} // namespace daw
