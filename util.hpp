/*
  Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>
  Published under the terms of the MIT License, see the LICENSE file.
*/

#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <sstream>
#include <iostream>
#include <ostream>
#include <string>


#define STR(e) ([&]() -> std::string {			\
			std::ostringstream _STR_o;	\
			_STR_o << e;			\
			return _STR_o.str();		\
		})()

#define WARN(e) (std::cerr << e << "\n")

#ifdef DEBUG
#define DEBUGWARN(e) WARN(e)
#else
#define DEBUGWARN(e)
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define NORETURN __attribute__ ((noreturn))
#define UNUSED __attribute__ ((unused))


#endif /* UTIL_HPP_ */
