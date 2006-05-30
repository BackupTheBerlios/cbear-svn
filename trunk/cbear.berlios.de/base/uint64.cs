#region Copyright (c) 2005 C Bear (http://cbear.berlios.de)
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
#endregion

namespace cbear_berlios_de.@base
{
    public struct uint64
    {
        public System.UInt32 high;
        public System.UInt32 low;

        public static implicit operator System.UInt64(uint64 This)
        {
            return (System.UInt64)(
                (((System.UInt64)This.high) << 16) + This.low);
        }

        public static implicit operator uint64(System.UInt64 Value)
        {
            uint64 This;
            This.high = (System.UInt32)(Value >> 16);
            This.low = (System.UInt32)Value;
            return This;
        }
    }
}
