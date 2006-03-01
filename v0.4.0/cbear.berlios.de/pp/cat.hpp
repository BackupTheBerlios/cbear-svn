/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef CBEAR_BERLIOS_DE_PP_CAT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_PP_CAT_HPP_INCLUDED

#include <boost/preprocessor/cat.hpp>

#define CBEAR_BERLIOS_DE_PP_CAT3(A0, A1, A2) \
	BOOST_PP_CAT(BOOST_PP_CAT(A0, A1), A2)
#define CBEAR_BERLIOS_DE_PP_CAT4(A0, A1, A2, A3) \
	CBEAR_BERLIOS_DE_PP_CAT3(BOOST_PP_CAT(A0, A1), A2, A3)
#define CBEAR_BERLIOS_DE_PP_CAT5(A0, A1, A2, A3, A4) \
	CBEAR_BERLIOS_DE_PP_CAT4(BOOST_PP_CAT(A0, A1), A2, A3, A4)
#define CBEAR_BERLIOS_DE_PP_CAT6(A0, A1, A2, A3, A4, A5) \
	CBEAR_BERLIOS_DE_PP_CAT5(BOOST_PP_CAT(A0, A1), A2, A3, A4, A5)

#endif
