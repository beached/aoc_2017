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

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>

#include <daw/daw_string.h>
#include <daw/daw_string_view.h>

#include "day12.h"
#include "str_splitter.h"

namespace daw {
	namespace aoc_2017 {
		namespace day12 {
			namespace {
				std::pair<std::string, std::set<std::string>> parse_line( daw::string_view line ) {
					std::pair<std::string, std::set<std::string>> result{};

					result.first = daw::string::trim_copy( line.substr( 0, line.find( ' ' ) ).to_string( ) );
					line.remove_prefix( line.find( '>' ) + 1 );
					str_splitter splt{daw::string::trim_copy( line.to_string( ) ), ","};
					while( splt ) {
						result.second.insert( daw::string::trim_copy( splt( ) ) );
					}
					return result;
				}

				std::set<std::string> get_group( std::map<std::string, std::set<std::string>> const &nodes,
				                                 daw::string_view cur_node ) {
					std::set<std::string> visited{};
					std::vector<std::string> to_visit{};
					to_visit.push_back( cur_node.to_string( ) );
					while( !to_visit.empty( ) ) {
						auto tmp = to_visit.back( );
						to_visit.pop_back( );
						visited.insert( tmp );
						for( auto const &node : nodes.find( tmp )->second ) {
							if( visited.count( node ) == 0 ) {
								to_visit.push_back( node );
							}
						}
					}
					return visited;
				}

				std::map<std::string, std::set<std::string>> parse_input( std::vector<std::string> lines ) {
					std::map<std::string, std::set<std::string>> nodes{};
					for( auto const &line : lines ) {
						auto tmp = parse_line( line );
						nodes[tmp.first].insert( tmp.second.begin( ), tmp.second.end( ) );
						for( auto const &node : tmp.second ) {
							nodes[node].insert( tmp.first );
						}
					}
					return nodes;
				}
			} // namespace

			intmax_t count_connections_to_zero( std::vector<std::string> lines ) {
				auto nodes = parse_input( lines );
				return static_cast<intmax_t>( get_group( nodes, "0" ).size( ) );
			}

			intmax_t num_groups( std::vector<std::string> lines ) {
				auto nodes = parse_input( lines );
				std::set<std::set<std::string>> groups{};
				for( auto const &n : nodes ) {
					groups.insert( get_group( nodes, n.first ) );
				}
				return static_cast<intmax_t>( groups.size( ) );
			}
		} // namespace day12
	}   // namespace aoc_2017
} // namespace daw
