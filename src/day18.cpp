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
				constexpr daw::static_array_t<operand, 2> parse_arguments( daw::string_view sv, bool parse2 ) noexcept {
					daw::static_array_t<operand, 2> result = {operand::Noop{}, operand::Noop{}};
					auto arg1 = sv.pop_front( " " );
					if( impl::is_digit( arg1.front( ) ) ) {
						result[0] = operand{operand::Constant{}, daw::parser::parse_int<word_t>( arg1 )};
					} else {
						result[0] = operand{operand::Register{}, arg1.front( ) - 'a'};
					}
					if( parse2 ) {
						if( impl::is_digit( sv.front( ) ) ) {
							result[1] = operand{operand::Constant{}, daw::parser::parse_int<word_t>( sv )};
						} else {
							result[1] = operand{operand::Register{}, sv.front( ) - 'a'};
						}
					}
					return result;
				} // namespace
			}   // namespace

			state_t::state_t( )
			  : m_program_memory{}
			  , m_threads{exec_context_t{0}, exec_context_t{1}} {}

			state_t::state_t( std::vector<std::string> const &program )
			  : m_program_memory{compile_program( program )}
			  , m_threads{exec_context_t{0}, exec_context_t{1}} {}

			bool state_t::tick( ) {
				size_t wait_count = 0;

				bool result = true;
				result &= m_threads[0].tick( m_program_memory[m_threads[0].pc( )] );
				result &= m_threads[0].pc( ) >= 0 && m_threads[0].pc( ) < static_cast<word_t>( m_program_memory.size( ) );
				wait_count += m_threads[0].waiting( ) ? 1 : 0;

				result &= m_threads[1].tick( m_program_memory[m_threads[1].pc( )] );
				result &= m_threads[1].pc( ) >= 0 && m_threads[1].pc( ) < static_cast<word_t>( m_program_memory.size( ) );
				wait_count += m_threads[1].waiting( ) ? 1 : 0;

				if( !result || wait_count == 2 ) {
					return false;
				}

				daw::container::transform( m_threads[0].m_snd_queue, std::back_inserter( m_threads[1].m_rcv_queue ), []( auto const & msg ) { return msg.value; } );
				daw::container::transform( m_threads[1].m_snd_queue, std::back_inserter( m_threads[0].m_rcv_queue ), []( auto const & msg ) { return msg.value; } );
				m_threads[0].m_snd_queue.clear( );
				m_threads[1].m_snd_queue.clear( );
				return true;
			}

			std::vector<operation> compile_program( std::vector<std::string> const &program ) {
				std::vector<operation> result{};
				for( auto const &line : program ) {
					auto args = daw::make_string_view( line );
					auto cmd = args.pop_front( " " );
					switch( cmd.pop_front( ) ) {
					case 'a':
						result.emplace_back( operation::Add{}, parse_arguments( args, true ) );
						break;
					case 'j':
						result.emplace_back( operation::Jgz{}, parse_arguments( args, true ) );
						break;
					case 'm':
						switch( cmd.pop_front( ) ) {
						case 'o':
							result.emplace_back( operation::Mod{}, parse_arguments( args, true ) );
							break;
						case 'u':
							result.emplace_back( operation::Mul{}, parse_arguments( args, true ) );
							break;
						}
						break;
					case 'r':
						result.emplace_back( operation::Rcv{}, parse_arguments( args, false ) );
						break;
					case 's':
						switch( cmd.pop_front( ) ) {
						case 'e':
							result.emplace_back( operation::Set{}, parse_arguments( args, true ) );
							break;
						case 'n':
							result.emplace_back( operation::Snd{}, parse_arguments( args, false ) );
						}
						break;
					}
				}
				return result;
			}

			exec_context_t::exec_context_t( size_t id )
			  : m_registers{0}
			  , m_pc{0}
			  , m_flags{0}
			  , m_op_counts{0}
			  , m_rcv_queue{}
			  , m_snd_queue{} {

				m_registers['p' - 'a'] = static_cast<word_t>( id );
			}

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

			bool exec_context_t::tick( operation const &op ) {
				if( waiting( ) && op.type( ) != operation::operator_type::rcv ) {
					// This is so that non-used threads that are always waiting are not executing
					return false;
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

			size_t exec_context_t::op_count( operation::operator_type op ) noexcept {
				return m_op_counts[static_cast<size_t>(op)];
			}

			state_t compute_state( std::vector<std::string> const &program ) noexcept {
				state_t state{program};
				while( state.tick( ) ) {
				}

				return state;
			}

		} // namespace day18
	}   // namespace aoc_2017
} // namespace daw
