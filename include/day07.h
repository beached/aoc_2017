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

#include <daw/daw_string_view.h>

namespace daw {
	namespace aoc_2017 {
		namespace day07 {
			struct prog_t {
				std::string name;
				intmax_t weight;
				std::vector<std::string> children;
				std::string parent;

				prog_t( std::string Name, intmax_t Weight, std::vector<std::string> Children );
			};
			using nodes_t = std::unordered_map<std::string, prog_t>;
			using root_t = std::pair<std::string, nodes_t>;

			root_t get_root( std::vector<std::string> const &rows );
			intmax_t get_new_weight( std::vector<std::string> const &rows );
		} // namespace day07
	}   // namespace aoc_2017
} // namespace daw
