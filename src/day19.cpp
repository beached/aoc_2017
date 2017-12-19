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

#include "day19.h"

namespace daw {
	namespace aoc_2017 {
		namespace day19 {
			namespace {
				enum class directions { up = 0, down, left, right, halt };
				struct pos_t {
					size_t x;
					size_t y;
				};

				result_t move_down( pos_t &pos, grid_t const &grid ) {
					result_t result{};
					++pos.y;
					++result.count;
					while( grid[pos.y][pos.x] != '+' ) {
						if( std::isalpha( grid[pos.y][pos.x] ) ) {
							result.visits += grid[pos.y][pos.x];
						} else if( grid[pos.y][pos.x] == ' ' ) {
							--pos.y;
							return result;
						}
						++pos.y;
						++result.count;
					}
					return result;
				}

				result_t move_up( pos_t &pos, grid_t const &grid ) {
					result_t result{};
					--pos.y;
					++result.count;
					while( grid[pos.y][pos.x] != '+' ) {
						if( std::isalpha( grid[pos.y][pos.x] ) ) {
							result.visits += grid[pos.y][pos.x];
						} else if( grid[pos.y][pos.x] == ' ' ) {
							++pos.y;
							return result;
						}
						--pos.y;
						++result.count;
					}
					return result;
				}

				result_t move_left( pos_t &pos, grid_t const &grid ) {
					result_t result{};
					--pos.x;
					++result.count;
					while( grid[pos.y][pos.x] != '+' ) {
						if( std::isalpha( grid[pos.y][pos.x] ) ) {
							result.visits += grid[pos.y][pos.x];
						} else if( grid[pos.y][pos.x] == ' ' ) {
							++pos.x;
							return result;
						}
						--pos.x;
						++result.count;
					}
					return result;
				}

				result_t move_right( pos_t &pos, grid_t const &grid ) {
					result_t result{};
					++pos.x;
					++result.count;
					while( grid[pos.y][pos.x] != '+' ) {
						if( std::isalpha( grid[pos.y][pos.x] ) ) {
							result.visits += grid[pos.y][pos.x];
						} else if( grid[pos.y][pos.x] == ' ' ) {
							--pos.x;
							return result;
						}
						++pos.x;
						++result.count;
					}
					return result;
				}

				directions determine_action( directions prev_dir, pos_t const &pos, grid_t const &grid ) {
					if( grid[pos.y][pos.x] != '+' ) {
						return directions::halt;
					}

					auto is_horiz = []( char c ) {
						if( std::isalpha( c ) ) {
							return true;
						}
						if( c == '-' ) {
							return true;
						}
						return false;
					};

					auto is_vert = []( char c ) {
						if( std::isalpha( c ) ) {
							return true;
						}
						if( c == '|' ) {
							return true;
						}
						return false;
					};

					switch( prev_dir ) {
					case directions::up:
					case directions::down:
						if( is_horiz( grid[pos.y][pos.x - 1] ) ) {
							return directions::left;
						}
						if( is_horiz( grid[pos.y][pos.x + 1] ) ) {
							return directions::right;
						}
						throw std::runtime_error( "Unknown state" );
					case directions::left:
					case directions::right:
						if( is_vert( grid[pos.y - 1][pos.x] ) ) {
							return directions::up;
						}
						if( is_vert( grid[pos.y + 1][pos.x] ) ) {
							return directions::down;
						}
					case directions::halt:
					default:
						throw std::runtime_error( "Unknown state" );
					}
				}
			} // namespace

			void result_t::append( result_t val ) {
				visits += val.visits;
				count += val.count;
			}

			using mover_t = std::add_pointer_t<result_t( pos_t &, grid_t const & )>;

			result_t compute_path( grid_t const &grid ) {
				// Find start
				pos_t pos{grid[0].find( '|' ), 0};
				std::array<mover_t, 4> const actions = {&move_up, &move_down, &move_left, &move_right};
				result_t result{std::string{}, 0};
				directions dir = directions::down;
				while( dir != directions::halt ) {
					result.append( actions[static_cast<size_t>( dir )]( pos, grid ) );
					dir = determine_action( dir, pos, grid );
				}
				return result;
			}
		} // namespace day19
	}   // namespace aoc_2017
} // namespace daw
