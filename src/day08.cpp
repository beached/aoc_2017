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
#include <functional>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

#include "day08.h"
#include "str_splitter.h"

namespace daw {
	namespace aoc_2017 {
		namespace day08 {
			namespace {
				template<typename Func>
				std::pair<std::string const, std::function<bool( intmax_t, intmax_t )>> make_op( std::string op,
				                                                                                       Func f ) {
					std::function<bool( intmax_t, intmax_t )> op_func = [f]( intmax_t const &lhs, intmax_t const &rhs ) {
						return f( lhs, rhs );
					};
					return {std::move( op ), std::move( op_func )};
				}
			} // namespace

			struct computer_t {
				std::unordered_map<std::string, intmax_t> registers;
				std::unordered_map<std::string, std::function<bool( intmax_t, intmax_t )>> operators;
				std::pair<std::string, intmax_t> largest_ever;

				intmax_t to_value( std::string val ) {
						auto i = strtol( val.c_str( ), nullptr, 10 );
						if( i != 0 || errno == 0 ) {
							return i;
						}
						return registers[val];
				}

				computer_t( )
				  : registers{}
				  , operators{make_op( "<", []( intmax_t l, intmax_t r ) { return l < r; } ),
				              make_op( ">", []( intmax_t l, intmax_t r ) { return l > r; } ),
				              make_op( "<=", []( intmax_t l, intmax_t r ) { return l <= r; } ),
				              make_op( ">=", []( intmax_t l, intmax_t r ) { return l >= r; } ),
				              make_op( "==", []( intmax_t l, intmax_t r ) { return l == r; } ),
				              make_op( "!=", []( intmax_t l, intmax_t r ) { return l != r; } )}
				  , largest_ever{std::string{""}, std::numeric_limits<intmax_t>::min( )} {}

				void process_line( std::string const & call ) {
					auto tokens = str_splitter( call, " " ).to_strings( );
					if( operators.find( tokens[5] )->second( to_value( tokens[4] ), to_value( tokens[6] ) ) ) {
						intmax_t amt = to_value( tokens[2] );
						if( tokens[1] == "dec" ) {
							amt *= -1;
						}
						registers[tokens[0]] += amt;
					}
					if( registers[tokens[0]] > largest_ever.second ) {
						largest_ever.first = tokens[0];
						largest_ever.second = registers[tokens[0]];
					}
				}
			};

			intmax_t largest_value( std::vector<std::string> const &calls ) {
				computer_t comp{};
				for( auto const & call: calls ) {
					comp.process_line( call );
				}
				intmax_t result = std::numeric_limits<intmax_t>::min( );
				for( auto const & reg: comp.registers ) {
					if( reg.second > result ) {
						result = reg.second;
					}
				}
				return result;
			}

			std::pair<std::string, intmax_t> largest_value_ever( std::vector<std::string> const &calls ) {
				computer_t comp{};
				for( auto const & call: calls ) {
					comp.process_line( call );
				}
				return comp.largest_ever;
			}
		} // namespace day08
	}   // namespace aoc_2017
} // namespace daw

