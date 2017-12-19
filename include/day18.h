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

			struct operand {
				enum class operand_type : uint8_t { noop = 0, csnt, rgst };

			private:
				word_t m_value;
				operand_type m_type;

			public:
				struct invalid_operation_exception {};
				struct Register {};
				struct Constant {};
				struct Noop {};

				constexpr operand( Register, word_t location ) noexcept
				  : m_value{location}
				  , m_type{operand_type::rgst} {}

				constexpr operand( Constant, word_t value ) noexcept
				  : m_value{value}
				  , m_type{operand_type::csnt} {}

				constexpr operand( Noop ) noexcept
				  : m_value{0}
				  , m_type{operand_type::noop} {}

				constexpr operand_type type( ) const {
					return m_type;
				}

				template<typename State>
				constexpr word_t get( State &state ) const {
					switch( m_type ) {
					case operand_type::csnt:
						return m_value;
					case operand_type::rgst:
						return state[m_value];
					default:
						throw invalid_operation_exception{};
					}
				}

				template<typename State>
				constexpr void set( State &state, word_t value ) const noexcept {
					if( m_type == operand_type::rgst ) {
						state[m_value] = value;
					}
				}
			};

			struct operation {
				struct invalid_set_exception {};
				enum class operator_type : uint8_t { add = 0, jgz, mod, mul, rcv, set, snd };

			private:
				operator_type m_operator;
				daw::static_array_t<operand, 2> m_operands;

			public:
				constexpr operator_type type( ) const noexcept {
					return m_operator;
				}

				struct Add {
					static constexpr operator_type type = operator_type::add;
				};
				struct Jgz {
					static constexpr operator_type type = operator_type::jgz;
				};
				struct Mod {
					static constexpr operator_type type = operator_type::mod;
				};
				struct Mul {
					static constexpr operator_type type = operator_type::mul;
				};
				struct Rcv {
					static constexpr operator_type type = operator_type::rcv;
				};
				struct Set {
					static constexpr operator_type type = operator_type::set;
				};
				struct Snd {
					static constexpr operator_type type = operator_type::snd;
				};

				template<typename Operation,
				         std::enable_if_t<daw::traits::is_one_of_v<Operation, Add, Jgz, Mod, Mul, Rcv, Set, Snd>,
				                          std::nullptr_t> = nullptr>
				constexpr operation( Operation, daw::static_array_t<operand, 2> operands ) noexcept
				  : m_operator{Operation::type}
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
				std::vector<operation> m_program_memory;

			public:
				struct msg_t {
					size_t dest;
					word_t value;
				};
				std::array<size_t, 7> m_op_counts;
				std::list<word_t> m_rcv_queue;
				std::list<msg_t> m_snd_queue;

				exec_context_t( size_t id, std::vector<operation> program_memory );
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

				size_t op_count( operation::operator_type op ) const noexcept;

				void jump( word_t diff ) noexcept;
				bool tick( );
				bool try_receive( word_t &dest );
				void send( word_t msg );
				word_t const &operator[]( size_t pos ) const noexcept;
				word_t &operator[]( size_t pos ) noexcept;
				word_t program_size( ) const noexcept;
			};

			std::vector<operation> assemble_program( std::vector<std::string> const &program );

			class state_t {

			public:
				state_t( std::vector<std::string> const &program0 );
				state_t( std::vector<std::string> const &program0, std::vector<std::string> const &program1 );

				daw::static_array_t<exec_context_t, 2> m_threads;

				state_t( state_t const & ) = default;
				state_t( state_t && ) noexcept = default;
				state_t &operator=( state_t const & ) = default;
				state_t &operator=( state_t && ) noexcept = default;
				~state_t( ) noexcept = default;

				bool tick( );
			};

			state_t compute_state1( std::vector<std::string> const &program ) noexcept;
			state_t compute_state2( std::vector<std::string> const &program ) noexcept;
		} // namespace day18
	}   // namespace aoc_2017
} // namespace daw
