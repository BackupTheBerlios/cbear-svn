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
#ifndef CBEAR_BERLIOS_DE_COM_THREAD_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_COM_THREAD_HPP_INCLUDED

// boost::mutex
#include <boost/thread/mutex.hpp>
// boost::thread
#include <boost/thread/thread.hpp>

#include <cbear.berlios.de/com/system.hpp>

namespace cbear_berlios_de
{
namespace com
{

class thread: public boost::thread
{
public:
	
	thread() {}

	template<class Function>
	thread(Function X): boost::thread(function(X)) {}

	template<class Function>
	class function_result
	{
	public:
		function_result(Function X): X(X) {}
		void operator()() const
		{
			system System(system::multithreaded);
			this->X();
		}
	private:
		Function X;
	};

	template<class Function>
	static function_result<Function> function(Function X)
	{
		return function_result<Function>(X);
	}
private:
	thread(const thread &);
	thread &operator=(const thread &);
};

}
}

#endif
