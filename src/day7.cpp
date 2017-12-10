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
#include <unordered_map>
#include <vector>

#include <daw/cpp_17.h>
#include <daw/daw_container_algorithm.h>
#include <daw/daw_string.h>

#include "day7.h"

namespace daw {
	namespace aoc_2017 {
		namespace day7 {
			namespace {
				class str_splitter_t {
					std::string m_str;
					std::string m_delems;
					char *m_ptr;

				public:
					str_splitter_t( std::string str, std::string delems )
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
						std::string result{m_ptr};
						m_ptr = strtok( nullptr, m_delems.c_str( ) );
						return result;
					}

					std::vector<std::string> to_strings( ) {
						std::vector<std::string> result{};
						while( m_ptr != nullptr ) {
							result.push_back( operator( )( ) );
						}
						return result;
					}
				};

				prog_t parse_row( std::string const &row ) {
					if( row.empty( ) ) {
						throw std::runtime_error( "unexpected empty string" );
					}
					static char const delems[] = "\n\t\v\r ";
					auto items = str_splitter_t( row, delems ).to_strings( );
					auto name = daw::string::trim_copy( items[0] );
					auto weight = daw::string::trim_copy( items[1] );
					std::vector<std::string> children{};
					for( size_t n = 3; n < items.size( ); ++n ) {
						items[n] = daw::string::trim_copy( std::move( items[n] ) );
						if( items[n].back( ) == ',' ) {
							items[n].resize( items[n].size( ) - 1 );
						}
						if( !items[n].empty( ) ) {
							children.push_back( std::move( items[n] ) );
						}
					}
					intmax_t i = strtol( weight.substr( 1, weight.size( ) - 2 ).c_str( ), nullptr, 10 );
					if( i == 0 && errno != 0 ) {
						throw std::runtime_error( "unexpected weight string" );
					}
					return prog_t( std::move( name ), i, std::move( children ) );
				}
			} // namespace
			prog_t::prog_t( std::string Name, intmax_t Weight, std::vector<std::string> Children )
			  : name{std::move( Name )}
			  , weight{Weight}
			  , children{std::move( Children )}
			  , parent{} {}

			root_t get_root( std::vector<std::string> const &rows ) {
				std::unordered_map<std::string, prog_t> programs{};
				for( auto const &row : rows ) {
					auto prg = parse_row( row );
					programs.insert( programs.end( ), std::pair<std::string, prog_t>{prg.name, prg} );
				}
				for( auto const &prg : programs ) {
					for( auto const &child : prg.second.children ) {
						auto pos = programs.find( child );
						pos->second.parent = child;
					}
				}
				for( auto const &prg : programs ) {
					if( prg.second.parent.empty( ) ) {
						return root_t{prg.first, programs};
					}
				}
				throw std::runtime_error( "Unexpected state" );
			}

			namespace {
				prog_t &get_node( std::string const &node, nodes_t &nodes ) {
					return nodes.find( node )->second;
				}

				intmax_t &get_weight( std::string const &node, nodes_t &nodes ) {
					return get_node( node, nodes ).weight;
				}

				intmax_t sum_weights( std::string node, nodes_t &nodes ) {
					auto &cur_node = get_node( node, nodes );
					intmax_t weight = 0;
					for( auto &child : cur_node.children ) {
						weight += sum_weights( child, nodes );
					}
					cur_node.weight += weight;
					return cur_node.weight;
				}

				std::pair<std::string, intmax_t> find_baddy( prog_t & cur_root, nodes_t &nodes ) {
					daw::container::sort( cur_root.children, [&nodes]( std::string const &lhs, std::string const &rhs ) {
						return get_weight( lhs, nodes ) < get_weight( rhs, nodes );
					} );

					auto first_weight = get_weight( cur_root.children.front( ), nodes );
					auto second_weight = get_weight( cur_root.children[1], nodes );
					auto last_weight = get_weight( cur_root.children.back( ), nodes );

					if( first_weight == second_weight && second_weight != last_weight ) {
						auto & child_node = get_node( cur_root.children.back( ), nodes );
						if( child_node.children.size( ) > 2 ) {
							auto result = find_baddy( child_node, nodes );
							if( result.second == 0 ) {
								return { child_node.name, first_weight - last_weight };
							}
							return result;
						}
						return { child_node.name, first_weight - last_weight };
					} else if( second_weight == last_weight && second_weight != first_weight ) {
						auto & child_node = get_node( cur_root.children.front( ), nodes );
						if( child_node.children.size( ) > 2 ) {
							auto result = find_baddy( child_node, nodes );
							if( result.second == 0 ) {
								return {get_node( cur_root.children.front( ), nodes ).name, last_weight - first_weight};
							}
							return result;
						}
						return {get_node( cur_root.children.front( ), nodes ).name, last_weight - first_weight};
					}
					return { cur_root.name, 0};
				}

				std::pair<std::string, intmax_t> get_new_weight( std::string root, nodes_t nodes ) {
					auto &cur_root = get_node( root, nodes );
					if( cur_root.children.empty( ) ) {
						throw std::runtime_error( "Unexpected state, no children in root node" );
					}
					sum_weights( root, nodes );
					return find_baddy( cur_root, nodes );
				}
			} // namespace

			intmax_t get_new_weight( std::vector<std::string> const &rows ) {
				auto root = get_root( rows );
				auto result = get_new_weight( root.first, root.second );
				auto orig_weight = get_weight( result.first, root.second );
				return orig_weight + result.second;
			}
		} // namespace day7
	}   // namespace aoc_2017
} // namespace daw
