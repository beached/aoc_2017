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

#include <string>
#include <vector>

#include <daw/daw_parser_helper_sv.h>
#include <daw/daw_static_array.h>
#include <daw/daw_string_view.h>

namespace daw {
	namespace aoc_2017 {
		namespace day20 {
			using value_t = intmax_t;
			namespace impl {
				struct point_t {
					value_t x;
					value_t y;
					value_t z;

					constexpr point_t( ) noexcept
					  : x{0}
					  , y{0}
					  , z{0} {}
					constexpr point_t( value_t X, value_t Y, value_t Z ) noexcept
					  : x{X}
					  , y{Y}
					  , z{Z} {}

					constexpr point_t( daw::string_view str )
					  : x{daw::parser::parse_int<value_t>( str.pop_front( "," ) )}
					  , y{daw::parser::parse_int<value_t>( str.pop_front( "," ) )}
					  , z{daw::parser::parse_int<value_t>( str.pop_front( ">" ) )} {}

					constexpr value_t quadrant( ) const noexcept {
						if( x >= 0 && z >= 0 ) {
							return 0;
						}
						if( x < 0 && z >= 0 ) {
							return 1;
						}
						if( x >= 0 && z < 0 ) {
							return 2;
						}
						return 3;
					}
					constexpr point_t( point_t const &other ) noexcept
					  : x{other.x}
					  , y{other.y}
					  , z{other.z} {}

					constexpr point_t( point_t &&other ) noexcept
					  : x{std::move( other.x )}
					  , y{std::move( other.y )}
					  , z{std::move( other.z )} {}

					constexpr point_t &operator=( point_t const &rhs ) noexcept {
						x = rhs.x;
						y = rhs.y;
						z = rhs.z;
						return *this;
					}

					constexpr point_t &operator=( point_t &&rhs ) noexcept {
						x = std::move( rhs.x );
						y = std::move( rhs.y );
						z = std::move( rhs.z );
						return *this;
					}

					~point_t( ) noexcept = default;

					constexpr point_t &operator+=( point_t const &rhs ) noexcept {
						x += rhs.x;
						y += rhs.y;
						z += rhs.z;
						return *this;
					}

					constexpr point_t &operator/=( point_t const &rhs ) noexcept {
						x /= rhs.x;
						y /= rhs.y;
						z /= rhs.z;
						return *this;
					}

					constexpr point_t operator-( ) const noexcept {
						auto tmp{*this};
						tmp.x *= -1;
						tmp.y *= -1;
						tmp.z *= -1;
						return tmp;
					}
				};

				constexpr point_t operator-( point_t lhs, point_t const &rhs ) noexcept {
					lhs.x -= rhs.x;
					lhs.y -= rhs.y;
					lhs.z -= rhs.z;
					return lhs;
				}

				constexpr point_t operator+( point_t lhs, point_t const &rhs ) noexcept {
					lhs.x += rhs.x;
					lhs.y += rhs.y;
					lhs.z += rhs.z;
					return lhs;
				}

				constexpr point_t operator*( point_t lhs, point_t const &rhs ) noexcept {
					lhs.x *= rhs.x;
					lhs.y *= rhs.y;
					lhs.z *= rhs.z;
					return lhs;
				}

				constexpr point_t operator/( point_t lhs, point_t const &rhs ) noexcept {
					lhs.x /= rhs.x;
					lhs.y /= rhs.y;
					lhs.z /= rhs.z;
					return lhs;
				}

				constexpr bool operator==( point_t const &lhs, value_t rhs ) noexcept {
					return lhs.x == rhs && lhs.y == rhs && lhs.z == rhs;
				}

				constexpr bool operator!=( point_t const &lhs, value_t rhs ) noexcept {
					return lhs.x != rhs || lhs.y != rhs || lhs.z != rhs;
				}

				constexpr point_t operator*( point_t lhs, value_t const &rhs ) noexcept {
					lhs.x *= rhs;
					lhs.y *= rhs;
					lhs.z *= rhs;
					return lhs;
				}

				constexpr bool operator==( point_t const &lhs, point_t const &rhs ) noexcept {
					return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
				}

				constexpr bool operator!=( point_t const &lhs, point_t const &rhs ) noexcept {
					return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
				}

				constexpr value_t distance( point_t const &lhs, point_t const &rhs ) noexcept {
					using daw::math::abs;
					return abs( lhs.x - rhs.x ) + abs( lhs.y - rhs.y ) + abs( lhs.z - rhs.z );
				}

				constexpr value_t dist_to_orig( point_t const &p ) noexcept {
					using daw::math::abs;
					return abs( p.x ) + abs( p.y ) + abs( p.z );
				}

				struct particle {
					point_t position;
					point_t velocity;
					point_t acceleration;
					size_t id;

					constexpr particle( ) noexcept
					  : position{}
					  , velocity{}
					  , acceleration{}
					  , id{0} {}

					constexpr particle( particle const &other ) noexcept
					  : position{other.position}
					  , velocity{other.velocity}
					  , acceleration{other.acceleration}
					  , id{other.id} {}

					constexpr particle( particle &&other ) noexcept
					  : position{std::move( other.position )}
					  , velocity{std::move( other.velocity )}
					  , acceleration{std::move( other.acceleration )}
					  , id{std::move( other.id )} {}

					constexpr particle &operator=( particle const &rhs ) noexcept {
						position = rhs.position;
						velocity = rhs.velocity;
						acceleration = rhs.acceleration;
						id = rhs.id;
						return *this;
					}

					constexpr particle &operator=( particle &&rhs ) noexcept {
						position = std::move( rhs.position );
						velocity = std::move( rhs.velocity );
						acceleration = std::move( rhs.acceleration );
						id = std::move( rhs.id );
						return *this;
					}

					~particle( ) noexcept = default;

					constexpr particle( daw::string_view str, size_t Id ) noexcept
					  : position{str.consume_front( "<" ).pop_front( ">" )}
					  , velocity{str.consume_front( "<" ).pop_front( ">" )}
					  , acceleration{str.consume_front( "<" ).pop_front( ">" )}
					  , id{Id} {}

					constexpr point_t position_at_t( value_t t ) const noexcept {
						++t;
						point_t result{position};
						auto const t2 = t * t / 2;
						result += velocity * t + acceleration * t2;
						return result;
					}

					constexpr particle tick( ) const noexcept {
						auto result{*this};
						result.velocity += acceleration;
						result.position += result.velocity;
						return result;
					}

					constexpr value_t distance_at_t( value_t t ) const noexcept {
						auto const result = position_at_t( t );
						return daw::math::abs( result.x ) + daw::math::abs( result.y ) + daw::math::abs( result.z );
					}
				};

				constexpr point_t abs( point_t p ) noexcept {
					using daw::math::abs;
					p.x = abs( p.x );
					p.y = abs( p.y );
					p.z = abs( p.z );
					return p;
				}

				struct collision_t {
					value_t time;
					size_t id1;
					size_t id2;
				};

				constexpr auto is_evenly_divisible( value_t p, value_t v ) noexcept {
					struct result_t {
						bool test;
						value_t result;

						explicit operator bool( ) const {
							return test;
						}
					};
					auto tmp = p / v;
					return result_t{( tmp * v == p ), tmp};
				}

				struct any_intercept {};
				struct never_intercepts {};
				struct intercept_t {
					enum types : uint8_t { none = 0, one_point, two_points, any  };
					types type;
					daw::static_array_t<value_t, 2> values;

					constexpr intercept_t( any_intercept ) noexcept
					  : type{types::any}
					  , values{0, 0} {}

					constexpr intercept_t( never_intercepts ) noexcept
					  : type{types::none}
					  , values{std::numeric_limits<value_t>::max( ), std::numeric_limits<value_t>::max( )} {}

					constexpr intercept_t( value_t t0 ) noexcept
							: type{types::one_point}
							, values{t0, t0} {}

					constexpr intercept_t( value_t t0, value_t t1 ) noexcept
					  : type{types::two_points}
					  , values{t0, t1} {}

					constexpr intercept_t( intercept_t const &other ) noexcept
					  : type{other.type}
					  , values{other.values} {}

					constexpr intercept_t( intercept_t &&other ) noexcept
					  : type{std::move( other.type )}
					  , values{std::move( other.values )} {}

					constexpr intercept_t &operator=( intercept_t const &rhs ) noexcept {
						type = rhs.type;
						values = rhs.values;
						return *this;
					}
				};
			} // namespace impl

			size_t closest_to_zero( std::vector<std::string> const &input );
			size_t remove_on_collide( std::vector<std::string> const &input );
		} // namespace day20
	}   // namespace aoc_2017
} // namespace daw
