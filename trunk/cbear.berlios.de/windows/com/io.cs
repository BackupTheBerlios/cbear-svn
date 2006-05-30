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
namespace cbear_berlios_de.windows.com
{
    using IO = System.IO;
    using Reflection = System.Reflection;
    using BitConverter = System.BitConverter;
    using InteropServices = System.Runtime.InteropServices;

    public class io
    {
        private static T GetCustomAttribute<T>(
            Reflection.FieldInfo Field, bool Inherit, int I)
        {
            return (T)Field.GetCustomAttributes(typeof(T), Inherit)[I];
        }

        private static object @new(System.Type T, object[] A, IO.Stream Stream)
        {
            if (T.IsPrimitive)
            {
                if (Stream == null) return System.Activator.CreateInstance(T);
                return stream.binary.primitive_type.read(T, Stream);
            }

            object R = System.Activator.CreateInstance(T, A);
            if (T.IsArray)
            {
                System.Array RA = (System.Array)R;
                for (int I = 0; I < RA.Length; ++I)
                {
                    RA.SetValue(
                        @new(T.GetElementType(), (object[])null, Stream), I);
                }
            }
            else
            {
                foreach (Reflection.FieldInfo F in T.GetFields())
                {
                    System.Type FT = F.FieldType;
                    F.SetValue(
                        R,
                        @new(
                            FT,
                            FT.IsArray ?
                                new object[] 
                                {
                                    GetCustomAttribute<
                                        InteropServices.MarshalAsAttribute>(
                                        F, false, 0).SizeConst
                                } :
                                null,
                            Stream));
                }
            }
            return R;
        }

        public static object @new(System.Type T) 
        { 
            return @new(T, null, null);
        }

        public static object read(System.Type T, IO.Stream Stream)
        {
            return @new(T, null, Stream); 
        }

        public static T @new<T>() { return (T)@new(typeof(T)); }

        public static T read<T>(IO.Stream Stream)
        { 
            return (T)read(typeof(T), Stream); 
        }
    }
}
