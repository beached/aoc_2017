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

#include <cstring>
#include <string>
#include <vector>

#include "str_splitter.h"

namespace daw {
	str_splitter::str_splitter( std::string str, std::string delems )
	  : m_str{std::move( str )}
	  , m_delems{std::move( delems )}
	  , m_ptr{strtok( &m_str[0], m_delems.c_str( ) )} {}

	str_splitter::operator bool( ) const noexcept {
		return m_ptr != nullptr;
	}

	std::string str_splitter::operator( )( ) {
		if( m_ptr == nullptr ) {
			return "";
		}
		std::string result{m_ptr};
		m_ptr = strtok( nullptr, m_delems.c_str( ) );
		return result;
	}

	std::vector<std::string> str_splitter::to_strings( ) {
		std::vector<std::string> result{};
		while( m_ptr != nullptr ) {
			result.push_back( operator( )( ) );
		}
		return result;
	}
} // namespace daw

