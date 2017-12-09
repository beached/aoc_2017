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

#include <iostream>
#include <utility>
#include <vector>

#include <daw/daw_array_view.h>
#include <daw/daw_span.h>

namespace daw {
	template<typename SizePtrT, typename... Positions>
	constexpr intmax_t project_impl( daw::array_view<SizePtrT> dimensions, Positions... positions ) noexcept {
		if( !dimensions.empty( ) ) {
			return 
		}
		return 0;
	}

	template<typename T>
	struct projection {
		daw::span<T> m_data;
		std::vector<size_t> m_dimensions;
		std::vector<intmax_t> m_offsets;

		projection( daw::span<T> data, std::initializer_list<size_t> dimensions )
		  : m_data{data}
		  , m_dimensions{dimensions} {}

		explicit projection( daw::span<T> data )
		  : projection{data, {static_cast<size_t>( data.size( ) )}} {}

		projection( projection const & ) = default;
		projection( projection && ) noexcept = default;
		projection &operator=( projection const & ) = default;
		projection &operator=( projection && ) noexcept = default;
		~projection( ) = default;

		template<intmax_t... Position>
		dectype( auto ) operator( )( Position... pos ) {
			daw::exception::daw_throw_on_false( sizeof...( Position ) == m_dimensions.size( ), "Invalid position" );
		}
	};

	template<typename T>
	class buffer_2d {
		// daw::heap_array<T> m_buff;
		std::vector<T> m_buff;
		std::pair<intmax_t, intmax_t> m_offset;
		std::pair<intmax_t, intmax_t> m_max;

		void clip_range( intmax_t &x, intmax_t &y ) const noexcept {
			// Ensures wrapping around
			if( x < 0 ) {
				x *= -1;
				x = x % m_max.first;
				x = ( m_max.first - 1 ) - x;
			} else if( x >= m_max.first ) {
				x = x % m_max.first;
			}
			if( y < 0 ) {
				y *= -1;
				y = y % m_max.second;
				y = ( m_max.second - 1 ) - y;
			} else if( y >= m_max.second ) {
				x = y % m_max.second;
			}
		}

		size_t to_buff_pos( intmax_t x, intmax_t y ) const {
			auto pos = static_cast<size_t>( x + ( y * m_max.first ) );
			return pos;
		}

	public:
		using reference = T &;
		using const_reference = T const &;

		buffer_2d( intmax_t maxx, intmax_t maxy, T def_value = T{} )
		  : m_buff( static_cast<size_t>( maxx * maxy ), def_value )
		  , m_offset{0, 0}
		  , m_max{maxx, maxy} {}

		void set_offset( intmax_t off_x, intmax_t off_y ) noexcept {
			m_offset = {off_x, off_y};
		}

		const_reference operator( )( intmax_t x, intmax_t y ) const {
			x -= m_offset.first;
			y -= m_offset.second;
			clip_range( x, y );
			return m_buff.at( to_buff_pos( x, y ) );
		}

		reference operator( )( intmax_t x, intmax_t y ) {
			x -= m_offset.first;
			y -= m_offset.second;
			clip_range( x, y );
			return m_buff.at( to_buff_pos( x, y ) );
		}

		intmax_t min_x( ) const noexcept {
			return m_offset.first;
		}

		intmax_t max_x( ) const noexcept {
			return m_max.first + m_offset.first;
		}

		intmax_t min_y( ) const noexcept {
			return m_offset.second;
		}

		intmax_t max_y( ) const noexcept {
			return m_max.second + m_offset.second;
		}

		void display( ) const {
			for( size_t y = 0; y < m_max.second; ++y ) {
				for( size_t x = 0; x < m_max.first; ++x ) {
					std::cout << m_buff[to_buff_pos( x, y )] << '	';
				}
				std::cout << '\n';
			}
			std::cout << '\n';
		}
	};
} // namespace daw
