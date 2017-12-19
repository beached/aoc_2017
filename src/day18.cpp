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
#include <vector>

#include <daw/daw_container_algorithm.h>
#include <daw/daw_parser_helper_sv.h>

#include "day18.h"

namespace daw {
	namespace aoc_2017 {
		namespace day18 {
			namespace {
				constexpr daw::static_array_t<operand, 2> parse_asm_arguments( daw::string_view sv,
				                                                               size_t arg_count ) noexcept {
					daw::static_array_t<operand, 2> result = {operand::Noop{}, operand::Noop{}};
					auto arg1 = sv.pop_front( " " );
					if( impl::is_digit( arg1.front( ) ) ) {
						result[0] = operand{operand::Constant{}, daw::parser::parse_int<word_t>( arg1 )};
					} else {
						result[0] = operand{operand::Register{}, arg1.front( ) - 'a'};
					}
					if( arg_count == 2 ) {
						if( impl::is_digit( sv.front( ) ) ) {
							result[1] = operand{operand::Constant{}, daw::parser::parse_int<word_t>( sv )};
						} else {
							result[1] = operand{operand::Register{}, sv.front( ) - 'a'};
						}
					}
					return result;
				}

				std::pair<operation::operator_type, size_t> encode_operation( daw::string_view op ) {
					if( op == "add" ) {
						return {operation::operator_type::add, 2};
					}
					if( op == "jgz" ) {
						return {operation::operator_type::jgz, 2};
					}
					if( op == "mod" ) {
						return {operation::operator_type::mod, 2};
					}
					if( op == "mul" ) {
						return {operation::operator_type::mul, 2};
					}
					if( op == "rcv" ) {
						return {operation::operator_type::rcv, 1};
					}
					if( op == "set" ) {
						return {operation::operator_type::set, 2};
					}
					if( op == "snd" ) {
						return {operation::operator_type::snd, 1};
					}
					throw invalid_asm_inst_exception{};
				}

				machine_code_t assemble_program( std::vector<std::string> const &program ) {
					machine_code_t result{};

					daw::container::transform( program, std::back_inserter( result ), []( std::string const &line ) -> operation {
						auto args = daw::make_string_view( line );
						auto cmd = args.pop_front( " " );
						auto op = encode_operation( cmd );
						return {op.first, parse_asm_arguments( args, op.second )};
					} );
					return result;
				}
			} // namespace

			state_t::state_t( std::vector<machine_code_t> programs ): m_threads{} {
				daw::exception::Assert( programs.size( ) == 2, "Only 2 threads of execution supported" );
				daw::container::transform( programs, std::back_inserter( m_threads ), [&]( machine_code_t const & prog ) {
					return exec_context_t{ prog };
				} );
			}

			bool state_t::tick( ) {
				size_t wait_count = 0;

				bool result = true;
				result &= m_threads[0].tick( );
				result &= ( m_threads[0].pc( ) >= 0 ) && ( m_threads[0].pc( ) < m_threads[0].program_size( ) );
				wait_count += m_threads[0].waiting( ) ? 1 : 0;

				result &= m_threads[1].tick( );
				result &= ( m_threads[1].pc( ) >= 0 ) && ( m_threads[1].pc( ) < m_threads[1].program_size( ) );
				wait_count += m_threads[1].waiting( ) ? 1 : 0;

				if( !result || wait_count == 2 ) {
					return false;
				}

				// For now, hardwire 2 threads of execution always messaging each other
				daw::container::transform( m_threads[0].m_snd_queue, std::back_inserter( m_threads[1].m_rcv_queue ),
				                           []( auto const &msg ) { return msg.value; } );
				daw::container::transform( m_threads[1].m_snd_queue, std::back_inserter( m_threads[0].m_rcv_queue ),
				                           []( auto const &msg ) { return msg.value; } );

				for( auto &th : m_threads ) {
					if( !th.m_rcv_queue.empty( ) ) {
						th.waiting( ) = false;
					}
				}
				m_threads[0].m_snd_queue.clear( );
				m_threads[1].m_snd_queue.clear( );
				return true;
			}

			exec_context_t::exec_context_t( machine_code_t program_memory )
			  : m_registers{0}
			  , m_pc{0}
			  , m_flags{0}
			  , m_program_memory{std::move( program_memory )}
			  , m_op_counts{0}
			  , m_rcv_queue{}
			  , m_snd_queue{} {}

			daw::static_array_t<word_t, 26> const &exec_context_t::registers( ) const noexcept {
				return m_registers;
			}

			daw::static_array_t<word_t, 26> &exec_context_t::registers( ) noexcept {
				return m_registers;
			}

			word_t const &exec_context_t::pc( ) const noexcept {
				return m_pc;
			}

			bool exec_context_t::waiting( ) const noexcept {
				return m_flags[static_cast<size_t>( flags::waiting )];
			}

			bool exec_context_t::tick( ) {
				auto const &op = m_program_memory[m_pc];
				if( waiting( ) ) {
					return true;
				}
				++m_op_counts[static_cast<size_t>( op.type( ) )];
				op.execute( *this );
				if( m_flags.none( ) ) {
					++m_pc;
				}
				m_flags[static_cast<size_t>( flags::stop_clock )] = false;
				return true;
			}

			word_t const &exec_context_t::operator[]( size_t pos ) const noexcept {
				return m_registers[pos];
			}

			word_t &exec_context_t::operator[]( size_t pos ) noexcept {
				return m_registers[pos];
			}

			void exec_context_t::send( word_t msg ) {
				m_snd_queue.push_back( {0, msg} );
			}

			bool exec_context_t::try_receive( word_t &dest ) {
				if( waiting( ) = m_rcv_queue.empty( ) ) {
					return false;
				}
				dest = m_rcv_queue.front( );
				m_rcv_queue.pop_front( );
				return true;
			}

			void exec_context_t::jump( word_t diff ) noexcept {
				m_pc += diff;
				m_flags[static_cast<size_t>( flags::stop_clock )] = true;
			}

			size_t exec_context_t::op_count( operation::operator_type op ) const noexcept {
				return m_op_counts[static_cast<size_t>( op )];
			}

			word_t exec_context_t::program_size( ) const noexcept {
				return static_cast<word_t>( m_program_memory.size( ) );
			}

			void exec_context_t::set_reg( char r, word_t value ) {
				m_registers[r - 'a'] = value;
			}

			state_t compute_state1( std::vector<std::string> const &program ) noexcept {
				std::vector<std::string> program1 = {"jgz 1 0"};
				state_t state{{assemble_program( program ), assemble_program( program1 )}};
				state.m_threads[1].waiting( ) = true;
				while( state.tick( ) ) {
					state.m_threads[1].waiting( ) = true;
				}
				return state;
			}

			state_t compute_state2( std::vector<std::string> const &program ) noexcept {
				auto mc = assemble_program( program );
				state_t state{{mc, mc}};
				for( size_t n = 0; n < state.m_threads.size( ); ++n ) {
					state.m_threads[n].set_reg( 'p', static_cast<word_t>( n ) );
				}
				while( state.tick( ) ) {
				}

				return state;
			}

		} // namespace day18
	}   // namespace aoc_2017
} // namespace daw
