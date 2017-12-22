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
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

#include <daw/daw_container_algorithm.h>
#include <daw/daw_math.h>
#include <daw/daw_parser_helper_sv.h>
#include <daw/daw_static_array.h>
#include <daw/daw_string_view.h>
#include <daw/fs/algorithms.h>

#include "day20.h"

namespace daw {
	namespace aoc_2017 {
		namespace day20 {
			namespace impl {
				namespace {
					std::pair<bool, value_t> is_perfect_square( value_t n ) {
						uint8_t h = static_cast<uint8_t>( static_cast<uintmax_t>( n ) & 0xF ); // last hexadecimal "digit"
						if( h > 9 ) {
							return {false, 0}; // return immediately in 6 cases out of 16.
						}

						// Take advantage of Boolean short-circuit evaluation
						if( h != 2 && h != 3 && h != 5 && h != 6 && h != 7 && h != 8 ) {
							// take square root if you must
							auto sqroot = static_cast<value_t>( sqrt( static_cast<double>( n ) ) );
							return {n == ( sqroot * sqroot ), sqroot};
						}
						return {false, 0};
					}

					intercept_t find_linear_intercept( value_t v, value_t p ) noexcept {
						// No acceleration, one 1 intercept max
						// intercept = -P/V when -P/V is a whole number
						if( ( v > 0 && p > 0 ) || ( v < 0 && p < 0 ) ) {
							// Can never cross 0 as the velocity has same sign as position
							return intercept_t{never_intercepts{}};
						}
						if( v == 0 ) {
							if( p == 0 ) {
								// Two particles with same velocity and position on this axis
								return intercept_t{any_intercept{}};
							}
							// Fixed distance between particles that isn't ever going to collide
							return intercept_t{never_intercepts{}};
						}
						auto const tmp = is_evenly_divisible( p, -v );
						if( tmp ) {
							// On this axis two particles match at t = tmp.result
							// result is only meaningful if >= 0 as we are not going back in time
							// result will always be >= 0 as it would be caught above where signs match
							return intercept_t{tmp.result};
						}
						// Only a intercept if it crosses on a whole number, not fractional
						return intercept_t{never_intercepts{}};
					}

					intercept_t find_intercept( value_t a, value_t v, value_t p ) noexcept {
						if( a == 0 ) {
							return find_linear_intercept( v, p );
						}

						auto const tmp_p1 = 2 * a * p;
						auto tmp = v * v;
						// Check if vertex is <= 0 for upward(+a), >0 for downward < 0
						// upward -> 2*a*p > v^2
						// downward -> 2*a*p > v^2
						if( tmp_p1 > tmp ) {
							// Parabola who's vertex is on the same side of axis as the sign of a(e.g. above axis and upward)
							return intercept_t{never_intercepts{}};
						}

						// quadratic, use quadratic equation, up to two times
						// See if there is an integral answer to sqrt portion, if not we never collide
						tmp -= tmp_p1;
						if( tmp < 0 ) {
							// Only real roots
							return intercept_t{never_intercepts{}};
						}
						auto const sqrt_tmp = is_perfect_square( tmp );
						if( sqrt_tmp.first ) {
							// sqrt_tmp is a perfect square and will have an Integer solution

							// Find positive interceptions
							auto const roots = daw::algorithm::minmax_item( -v + sqrt_tmp.second, -v - sqrt_tmp.second );
							if( roots.second < 0 ) {
								// No positive roots
								return intercept_t{never_intercepts{}};
							}
							if( roots.first < 0 ) {
								// One positive root
								return intercept_t{roots.second / a};
							}
							// Two positive roots
							return intercept_t{roots.first, roots.second / a};
						}
						// No integral solution for roots
						return intercept_t{never_intercepts{}};
					}

					constexpr intercept_t intersect_intercept( intercept_t const &a, intercept_t const &b ) noexcept {
						if( a.type == intercept_t::none || b.type == intercept_t::none ) {
							return intercept_t{never_intercepts{}};
						}
						if( a.type == intercept_t::any ) {
							return b;
						}
						if( b.type == intercept_t::any ) {
							return a;
						}

						struct cmp_t {
							bool operator( )( intercept_t const &lhs, intercept_t const &rhs ) const noexcept {
								uint8_t const l_t = static_cast<uint8_t>( lhs.type );
								uint8_t const r_t = static_cast<uint8_t>( rhs.type );
								return std::tie( l_t, lhs.values[0], lhs.values[1] ) < std::tie( r_t, rhs.values[0], rhs.values[1] );
							}
						};
						auto tmp = daw::algorithm::minmax_item( a, b, cmp_t{} );
						if( tmp.second.type == intercept_t::one_point ) {
							if( a.values[0] == b.values[0] ) {
								return intercept_t{a.values[0]};
							}
							return intercept_t{intercept_t::none};
						}
						if( tmp.first.type == intercept_t::one_point ) {
							if( a.values[0] == b.values[0] || a.values[0] == b.values[1] ) {
								return intercept_t{a.values[0]};
							}
							return intercept_t{intercept_t::none};
						}
						// Both two points
						auto const a_last = a.values[0] == a.values[1] ? daw::next( a.values.begin( ) ) : a.values.end( );
						auto const b_last = b.values[0] == b.values[1] ? daw::next( b.values.begin( ) ) : b.values.end( );
						intercept_t result{never_intercepts{}};
						auto out_last = daw::algorithm::set_intersection( a.values.cbegin( ), a_last, b.values.cbegin( ), b_last,
						                                                  result.values.begin( ) );
						switch( daw::distance( result.values.begin( ), out_last ) ) {
						case 0:
							break;
						case 1:
							result.type = intercept_t::one_point;
							break;
						case 2:
							result.type = intercept_t::two_points;
							break;
						}
						return result;
					}

					std::vector<collision_t> can_collide( particle const &part1, particle const &part2 ) noexcept {
						/*
						 * Construct formula for distance between part1 and part2
						 * A = part1.acceleration - part2.acceleration
						 * V = part1.velocity - part2.velocity
						 * P = part1.position - part2.position
						 *
						 * 0.5A*t^2 + Vt + P = 0 if they do
						 *
						 * (-b +- sqrt( b^2 - 4ac ))/2a
						 * a = 0.5A
						 * b = V
						 * c = P
						 * (-V +- sqrt( V^2 - 2AP ) )/A = 0
						 *
						 * We can save work by checking for zero crossings and
						 * eliminating parts that can never cross zero.  Also, it must cross
						 * when t is an Integral(e.g Not Real or Imaginary)
						 *
						 * Use quadratic formula, if acceleration != 0, or line intercepts to determine
						 * when/if they collide.
						 *
						 * If acceleration is 0 for any axis, it is a line
						 * f(t) = Vt + P
						 * intercept = -P/V when evenly divisible, otherwise no collision
						 *
						 * All three axis must have same a common for collision.
						 *
						 * Do each axis separately and check for common times afterwards.
						 */

						auto const A = part1.acceleration - part2.acceleration;
						auto const V = part1.velocity - part2.velocity;
						auto const P = part1.position - part2.position;

						auto const interx = find_intercept( A.x, V.x, P.x );
						auto const intery = find_intercept( A.y, V.y, P.y );
						auto const interz = find_intercept( A.z, V.z, P.z );

						auto const intercepts = intersect_intercept( intersect_intercept( interx, intery ), interz );

						switch( intercepts.type ) {
						case intercept_t::none:
							return std::vector<collision_t>{};
						case intercept_t::one_point:
							return std::vector<collision_t>{collision_t{intercepts.values[0], part1.id, part2.id}};
						case intercept_t::two_points:
							return std::vector<collision_t>{collision_t{intercepts.values[0], part1.id, part2.id},
							                                collision_t{intercepts.values[1], part1.id, part2.id}};
						case intercept_t::any:
							return std::vector<collision_t>{collision_t{0, part1.id, part2.id}};
						}
					}

					std::vector<particle> remove_collisions( std::vector<particle> const &particles ) {
						std::vector<collision_t> all_collisions{};

						for( auto const &p : particles ) {
							for( size_t n = p.id + 1; n < particles.size( ); ++n ) {
								auto tmp = can_collide( p, particles[n] );
								all_collisions.insert( all_collisions.end( ), tmp.begin( ), tmp.end( ) );
							}
						}
						std::sort( all_collisions.begin( ), all_collisions.end( ),
						           []( collision_t const &lhs, collision_t const &rhs ) { return lhs.time < rhs.time; } );

						std::cout << "Potential collisions: " << all_collisions.size( ) << '\n';

						std::vector<char> has_collided( particles.size( ), false );
						for( size_t n = 0; n < all_collisions.size( ); ++n ) {
							has_collided[all_collisions[n].id1] = true;
							has_collided[all_collisions[n].id2] = true;
							auto remove_from = daw::safe_next( all_collisions.begin( ), all_collisions.end( ), n + 1 );
							all_collisions.erase(
							  std::remove_if( remove_from, all_collisions.end( ),
							                  [&]( collision_t const &c ) {
								                  return c.time > all_collisions[n].time &&
								                         ( all_collisions[n].id1 == c.id1 || all_collisions[n].id1 == c.id2 ||
								                           all_collisions[n].id2 == c.id1 || all_collisions[n].id2 == c.id2 );
							                  } ),
							  all_collisions.end( ) );
						}
						std::cout << "Actual collisions: " << all_collisions.size( ) << '\n';
						std::vector<particle> result{};
						for( auto const &p : particles ) {
							if( !has_collided[p.id] ) {
								result.push_back( p.tick( ) );
							}
						}
						return result;
					}

					std::vector<particle> process_input( std::vector<std::string> const &input ) {
						std::vector<particle> particles{};
						daw::container::transform(
						  input, std::back_inserter( particles ), [Id = static_cast<size_t>( 0 )]( daw::string_view sv ) mutable {
							  return particle{sv, Id++};
						  } );
						return particles;
					}
				} // namespace
			}   // namespace impl

			size_t closest_to_zero( std::vector<std::string> const &input ) {
				// Day 20 - part 1
				auto particles = impl::process_input( input );
				auto const diff_calc = []( auto const &particle ) noexcept {
					return particle.distance_at_t( 5'000'000 );
				};
				size_t particle_pos = 0;
				value_t particle_diff = diff_calc( particles[0] );
				for( size_t n = 1; n < particles.size( ); ++n ) {
					auto tmp = diff_calc( particles[n] );
					if( tmp < particle_diff ) {
						particle_pos = n;
						particle_diff = tmp;
					}
				}
				return particle_pos;
			}

			size_t remove_on_collide( std::vector<std::string> const &input ) {
				// Day 20 - part 2
				auto particles = impl::process_input( input );

				std::cout << "Starting with " << particles.size( ) << " particles\n";
				particles = impl::remove_collisions( std::move( particles ) );
				std::cout << "Left with " << particles.size( ) << " particles\n";
				auto result = particles.size( );
				return result;
			}
		} // namespace day20
	}   // namespace aoc_2017
} // namespace daw
