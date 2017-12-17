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
#include <list>
#include <memory>
#include <vector>

#include "day17.h"
#include <daw/daw_fixed_stack.h>

namespace daw {
	namespace aoc_2017 {
		namespace day17 {
			namespace {
				constexpr node_t *next( node_t *n, value_t steps ) noexcept {
					while( steps-- > 0 ) {
						n = n->m_next;
					}
					return n;
				}

				template<typename Nodes>
				constexpr node_t *insert( Nodes &nodes, size_t pos, node_t *cur_node, value_t value ) noexcept {
					nodes[pos] = node_t{cur_node->m_next, value};
					cur_node->m_next = &nodes[pos];
					return &nodes[pos];
				}

				template<typename Nodes>
				constexpr node_t *do_work( Nodes &nodes, size_t count, value_t puzzle_input ) {
					auto cur_node = &nodes[0];
					cur_node->m_next = &nodes[0];

					for( size_t n = 1; n <= count; ++n ) {
						cur_node = next( cur_node, puzzle_input );
						cur_node = insert( nodes, n, cur_node, static_cast<value_t>( n ) );
					}
					return cur_node;
				}
			} // namespace

			value_t calc_buffer_value( value_t puzzle_input ) {
				std::vector<node_t> nodes( 2018, node_t{nullptr, 0} );
				return do_work( nodes, 2017, puzzle_input )->m_next->value;
			}

			value_t calc_buffer_value2( value_t puzzle_input ) {
				std::vector<node_t> nodes( 50'000'001, node_t{nullptr, 0} );
				do_work( nodes, 50'000'000, puzzle_input );
				return nodes[0].m_next->value;
			}
		} // namespace day17
	}   // namespace aoc_2017
} // namespace daw
