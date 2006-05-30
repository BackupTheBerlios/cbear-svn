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

    public class @struct
    {
        private static T GetCustomAttribute<T>(
            Reflection.FieldInfo Field, bool Inherit, int I)
        {
            return (T)Field.GetCustomAttributes(typeof(T), Inherit)[I];
        }

        private static object @new(System.Type T, object[] A)
        {
            object R = System.Activator.CreateInstance(T, A);

            if (T.IsPrimitive)
            {
            }
            else if (T.IsArray)
            {
                System.Array RA = (System.Array)R;
                for (int I = 0; I < RA.Length; ++I)
                {
                    RA.SetValue(@new(T.GetElementType(), (object[])null), I);
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
                                }:
                                null));
                }
            }
            return R;
        }

        private static object @new(System.Type T, object[] A, IO.Stream Stream)
        {
            throw new System.Exception();
        }

        public static object @new(System.Type T) { return @new(T, (object[])null); }

        public static object @new(System.Type T, IO.Stream Stream)
        {
            return @new(T, null, Stream); 
        }

        public static T @new<T>() { return (T)@new(typeof(T)); }

        public static T @new<T>(IO.Stream Stream) { return (T)@new(typeof(T), Stream); }

        /*
        public static void write(IO.Stream Stream, System.Byte O)
        {
            Stream.WriteByte(O);
        }

        public static void read(IO.Stream Stream, out System.Byte O)
        {
            O = (System.Byte)Stream.ReadByte();
        }

        public static void write(IO.Stream Stream, System.SByte O)
        {
            write(Stream, (System.Byte)O);
        }

        public static void read(IO.Stream Stream, out System.SByte O)
        {
            System.Byte O1;
            read(Stream, out O1);
            O = (System.SByte)O1;
        }

        public static void write(IO.Stream Stream, System.UInt16 O)
        {
            write(Stream, (System.Byte)(O % 0x100));
            write(Stream, (System.Byte)(O / 0x100));
        }

        public static void write(IO.Stream Stream, System.Int16 O)
        {
            write(Stream, (System.UInt16)O);
        }

        public static void write(IO.Stream Stream, System.UInt32 O)
        {
            write(Stream, (System.UInt16)(O % 0x10000));
            write(Stream, (System.UInt16)(O / 0x10000));
        }

        public static void write(IO.Stream Stream, System.Int32 O)
        {
            write(Stream, (System.UInt32)O);
        }

        public static void write(IO.Stream Stream, System.UInt64 O)
        {
            write(Stream, (System.UInt32)(O % 0x100000000));
            write(Stream, (System.UInt32)(O / 0x100000000));
        }

        public static void write(IO.Stream Stream, System.Int64 O)
        {
            write(Stream, (System.UInt64)O);
        }

        public static void write(IO.Stream Stream, System.Single O)
        {
            System.Byte[] Bytes = BitConverter.GetBytes(O);
            Stream.Write(Bytes, 0, Bytes.Length);
        }

        public static void write(IO.Stream Stream, object O)
        {
            System.Type Type = O.GetType();
            if (Type.IsPrimitive)
            {                
                if (Type == typeof(System.Byte))
                {
                    write(Stream, (System.Byte)O);
                }
                else if (Type == typeof(System.SByte))
                {
                    write(Stream, (System.SByte)O);
                }
                else if (Type == typeof(System.UInt16))
                {
                    write(Stream, (System.UInt16)O);
                }
                else if (Type == typeof(System.Int16))
                {
                    write(Stream, (System.Int16)O);
                }
                else if (Type == typeof(System.UInt32))
                {
                    write(Stream, (System.UInt32)O);
                }
                else if (Type == typeof(System.Int32))
                {
                    write(Stream, (System.Int32)O);
                }
                else if (Type == typeof(System.UInt64))
                {
                    write(Stream, (System.UInt64)O);
                }
                else if(Type == typeof(System.Int64))
                {
                    write(Stream, (System.Int64)O);
                }
                else if (Type == typeof(System.Single))
                {
                    write(Stream, (System.Single)O);
                }
                else
                {
                    throw new System.Exception("Unknown type");
                }
            }
            else if (Type.IsArray)
            {
                foreach (object OI in (System.Array)O)
                {                    
                    write(Stream, OI);
                }
            }
            else
            {
                foreach (Reflection.FieldInfo Field in Type.GetFields())
                {
                    object Value = Field.GetValue(O);
                    if (Field.FieldType.IsArray)
                    {
                        InteropServices.MarshalAsAttribute M =
                            (InteropServices.MarshalAsAttribute)
                            Field.GetCustomAttributes(
                                typeof(InteropServices.MarshalAsAttribute), 
                                false)[0];
                        if (((System.Array)Value).Length != M.SizeConst)
                            throw new System.Exception("wrong array size");
                    }
                    write(Stream, Value);
                }
            }
        }

        public static void read(IO.Stream Stream, ref object O)
        {
        }
         */
    }
}
