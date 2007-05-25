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

namespace cbear_berlios_de.windows.com
{
    using IO = System.IO;
    using Reflection = System.Reflection;
    using BitConverter = System.BitConverter;
    using InteropServices = System.Runtime.InteropServices;

    public class io
    {
        private static T get_custom_attribute<T>(
            Reflection.FieldInfo Field, bool Inherit, int I)
        {
            return (T)Field.GetCustomAttributes(typeof(T), Inherit)[I];
        }

        private static object read(IO.Stream Stream, System.Type T, object[] A)
        {
            if (T.IsPrimitive)
            {
                if (Stream == null) return System.Activator.CreateInstance(T);
                return stream.binary.primitive_type.read(Stream, T);
            }

            if (T.IsArray)
            {
                System.Array R = 
                    (System.Array)System.Activator.CreateInstance(T, A);
                for (int I = 0; I < R.Length; ++I)
                {
                    R.SetValue(
                        read(Stream, T.GetElementType(), (object[])null), I);
                }
                return R;
            }

            {
                object R = System.Activator.CreateInstance(T);
                foreach (Reflection.FieldInfo F in T.GetFields())
                {
                    System.Type FT = F.FieldType;
                    F.SetValue(
                        R,
                        read(
                            Stream,
                            FT,
                            FT.IsArray ?
                                new object[] 
                                {
                                    get_custom_attribute<
                                        InteropServices.MarshalAsAttribute>(
                                        F, false, 0).SizeConst
                                } :
                                null));
                }
                return R;
            }
        }

        public static object @new(System.Type T) 
        { 
            return read(null, T, null);
        }

        public static T @new<T>() { return (T)@new(typeof(T)); }

        public static object read(IO.Stream Stream, System.Type T)
        {
            return read(Stream, T, null);
        }

        public static T read<T>(IO.Stream Stream)
        {
            return (T)read(Stream, typeof(T));
        }

        public static void write(IO.Stream Stream, object Value)
        {
            System.Type T = Value.GetType();

            if (T.IsPrimitive)
            {
                stream.binary.primitive_type.write(Stream, Value);
                return;
            }

            if (T.IsArray)
            {
                System.Array R = (System.Array)Value;
                foreach (object O in R)
                {
                    write(Stream, O);
                }
                return;
            }

            foreach (Reflection.FieldInfo F in T.GetFields())
                write(Stream, F.GetValue(Value));
        }

        public static void write<T>(IO.Stream Stream, T Value)
        {
            write(Stream, (object)Value);
        }
    }
}
