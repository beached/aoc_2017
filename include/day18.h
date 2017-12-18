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

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <daw/daw_static_array.h>

namespace daw {
	namespace aoc_2017 {
		namespace day18 {
			namespace impl {
				constexpr bool is_digit( char c ) noexcept {
					return ( '0' <= c && c <= '9' ) || c == '-';
				}
			} // namespace impl
			using word_t = intmax_t;

			class operand {
				enum class operand_type : uint8_t { nop = 0, cst, reg };
				word_t m_value;
				operand_type m_type;

			public:
				struct invalid_operation_exception {};
				struct register_t {};
				struct constant_t {};
				struct noop_t {};

				constexpr operand( register_t, word_t location ) noexcept
				  : m_value{location}
				  , m_type{operand_type::reg} {}

				constexpr operand( constant_t, word_t value ) noexcept
				  : m_value{value}
				  , m_type{operand_type::cst} {}

				constexpr operand( noop_t ) noexcept
				  : m_value{0}
				  , m_type{operand_type::nop} {}

				template<typename State>
				constexpr word_t get( State &state ) const {
					switch( m_type ) {
					case operand_type::cst:
						return m_value;
					case operand_type::reg:
						return state[m_value];
					default:
						throw invalid_operation_exception{};
					}
				}

				template<typename State>
				constexpr void set( State &state, word_t value ) const noexcept {
					if( m_type == operand_type::reg ) {
						state[m_value] = value;
					}
				}
			};

			struct operation {
				struct invalid_set_exception {};
				enum class operator_type { add, jgz, mod, mul, rcv, set, snd };
				operator_type m_operator;
				daw::static_array_t<operand, 2> m_operands;

				constexpr operation( operator_type op, daw::static_array_t<operand, 2> operands ) noexcept
				  : m_operator{op}
				  , m_operands{std::move( operands )} {}

				template<typename State>
				constexpr void execute( State &state ) const {
					switch( m_operator ) {
					case operator_type::add:
						m_operands[0].set( state, m_operands[0].get( state ) + m_operands[1].get( state ) );
						return;
					case operator_type::jgz:
						if( m_operands[0].get( state ) > 0 ) {
							state.jump( m_operands[1].get( state ) );
						}
						return;
					case operator_type::mod:
						m_operands[0].set( state, m_operands[0].get( state ) % m_operands[1].get( state ) );
						return;
					case operator_type::mul:
						m_operands[0].set( state, m_operands[0].get( state ) * m_operands[1].get( state ) );
						return;
					case operator_type::rcv: {
						word_t tmp = 0;
						if( state.try_receive( tmp ) ) {
							m_operands[0].set( state, tmp );
						}
					}
						return;
					case operator_type::set:
						m_operands[0].set( state, m_operands[1].get( state ) );
						return;
					case operator_type::snd:
						state.send( m_operands[0].get( state ) );
						return;
					}
				}
			};

			class exec_context_t {
				daw::static_array_t<word_t, 26> m_registers;
				enum class flags { waiting = 0, stop_clock = 1 };
				word_t m_pc;
				std::bitset<2> m_flags;

			public:
				size_t m_send_count;
				std::list<word_t> m_rcv_queue;
				std::list<word_t> m_snd_queue;

				exec_context_t( size_t id );
				exec_context_t( exec_context_t const & ) = default;
				exec_context_t( exec_context_t && ) = default;
				exec_context_t &operator=( exec_context_t const & ) = default;
				exec_context_t &operator=( exec_context_t && ) = default;
				~exec_context_t( ) = default;

				daw::static_array_t<word_t, 26> const &registers( ) const noexcept;
				daw::static_array_t<word_t, 26> &registers( ) noexcept;
				word_t const &pc( ) const noexcept;
				bool waiting( ) const noexcept;

				inline auto waiting( ) noexcept {
					return m_flags[static_cast<size_t>( flags::waiting )];
				}

				void jump( word_t diff ) noexcept;
				bool tick( operation const &op );
				bool try_receive( word_t &dest );
				void send( word_t msg );
				word_t const &operator[]( size_t pos ) const noexcept;
				word_t &operator[]( size_t pos ) noexcept;
			};

			std::vector<operation> compile_program( std::vector<std::string> const &program );

			class state_t {
				std::vector<operation> m_program_memory;

			public:
				daw::static_array_t<exec_context_t, 2> m_threads;

				state_t( );

				state_t( std::vector<std::string> const &program );

				state_t( state_t const & ) = default;
				state_t( state_t && ) noexcept = default;
				state_t &operator=( state_t const & ) = default;
				state_t &operator=( state_t && ) noexcept = default;
				~state_t( ) noexcept = default;

				bool tick( );
			};

			state_t compute_state( std::vector<std::string> const &program ) noexcept;
		} // namespace day18
	}   // namespace aoc_2017
} // namespace daw
