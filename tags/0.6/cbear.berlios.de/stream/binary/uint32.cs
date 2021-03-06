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

namespace cbear_berlios_de.stream.binary
{
    using IO = System.IO;

    public class uint32 : dynamic_implementation<System.UInt32>
    {
        public static System.UInt32 static_read(IO.Stream Stream)
        {
            @base.uint32 X;
            X.low = @uint16.static_read(Stream);
            X.high = @uint16.static_read(Stream);
            return X;
        }

        public static void static_write(IO.Stream Stream, System.UInt32 Value)
        {
            @base.uint32 X = Value;
            uint16.static_write(Stream, X.low);
            uint16.static_write(Stream, X.high);
        }

        protected override System.UInt32 read(System.IO.Stream Stream)
        {
            return static_read(Stream);
        }

        protected override void write(
            System.IO.Stream Stream, System.UInt32 Value)
        {
            static_write(Stream, Value);
        }
    }
}
