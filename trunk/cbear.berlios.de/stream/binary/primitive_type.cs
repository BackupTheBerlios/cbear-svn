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
namespace cbear_berlios_de.stream.binary
{
    using IO = System.IO;

    class primitive_type
    {
        public readonly static dynamic[] list =
        {
            new @byte(),
            new @sbyte(),
            new uint16(),
            new int16(),
            new uint32(),
            new int32(),
            new uint64(),
            new int64(),
        };

        public static object read(System.Type T, IO.Stream Stream)
        {
            foreach (
                stream.binary.dynamic D in
                stream.binary.primitive_type.list)
            {
                if (D.type() == T)
                {
                    return D.read(Stream);
                }
            }
            throw new System.Exception("Unknown Primitive Type");
        }
    }
}

