namespace cbear_berlios_de.windows.com
{
    using IO = System.IO;
    using Reflection = System.Reflection;
    using BitConverter = System.BitConverter;
    using InteropServices = System.Runtime.InteropServices;

    public class @struct
    {
        /*
        private static System.UInt16 make(System.Byte H, System.Byte L)
        {
            return (System.UInt16)(
                ((System.UInt16)H << 8) + (System.UInt16)L);
        }

        private static System.UInt32 make(System.UInt16 H, System.UInt16 L)
        {
            return (System.UInt32)(
                ((System.UInt32)H << 16) + (System.UInt32)L);
        }

        private static System.UInt64 make(System.UInt32 H, System.UInt32 L)
        {
            return (System.UInt64)(
                ((System.UInt64)H << 32) + (System.UInt64)L);
        }

        private static System.Byte hi(System.UInt16 X) 
        { 
            return (System.Byte)(X >> 8); 
        }

        private static System.Byte lo(System.UInt16 X) 
        { 
            return (System.Byte)X; 
        }

        private static System.UInt16 hi(System.UInt32 X) 
        { 
            return (System.UInt16)(X >> 16); 
        }

        private static System.UInt16 lo(System.UInt32 X) 
        {
            return (System.UInt16)X; 
        }

        private static System.UInt32 hi(System.UInt64 X) 
        {
            return (System.UInt32)(X >> 32); 
        }

        private static System.UInt32 lo(System.UInt64 X) 
        {
            return (System.UInt32)X;
        }

        private abstract class io_implementation<T> : io_base
        {
            #region io_base Members

            System.Type io_base.type() { return typeof(T); }

            object io_base.read(IO.Stream Stream)
            {
                return (object)this.read(Stream);
            }

            void io_base.write(IO.Stream Stream, object t)
            {
                this.write(Stream, (T)t);
            }

            #endregion

            protected abstract T read(IO.Stream Stream);
            protected abstract void write(IO.Stream Stream, T t);
        }

        private static System.Byte read8(IO.Stream Stream)
        {
            return (System.Byte)Stream.ReadByte();
        }

        private static void write8(IO.Stream Stream, System.Byte X)
        {
            Stream.WriteByte(X);
        }

        private class io_byte: io_implementation<System.Byte>
        {
            protected override System.Byte read(System.IO.Stream Stream)
            {
                return read8(Stream);
            }

            protected override void write(
                System.IO.Stream Stream, System.Byte X)
            {
                write8(Stream, X);
            }
        }

        private class io_sbyte : io_implementation<System.SByte>
        {

            protected override System.SByte read(System.IO.Stream Stream)
            {
                return (System.SByte)read8(Stream);
            }

            protected override void write(System.IO.Stream Stream, System.SByte X)
            {
                write8(Stream, (System.Byte)X);
            }
        }

        private static System.UInt16 read16(IO.Stream Stream)
        {
            System.Byte L = read8(Stream);
            System.Byte H = read8(Stream);
            return make(H, L);
        }

        private static void write16(IO.Stream Stream, System.UInt16 X)
        {
            write8(Stream, lo(X));
            write8(Stream, hi(X));
        }

        private class io_uint16 : io_implementation<System.UInt16>
        {
            protected override System.UInt16 read(System.IO.Stream Stream)
            {
                return read16(Stream);
            }

            protected override void write(
                System.IO.Stream Stream, System.UInt16 X)
            {
                write16(Stream, X);
            }
        }

        private class io_int16 : io_implementation<System.Int16>
        {
            protected override System.Int16 read(System.IO.Stream Stream)
            {
                return (System.Int16)read16(Stream);
            }

            protected override void write(
                System.IO.Stream Stream, System.Int16 X)
            {
                write16(Stream, (System.UInt16)X);
            }
        }
        */

        private static T GetCustomAttribute<T>(
            Reflection.FieldInfo Field, bool Inherit, int I)
        {
            return (T)Field.GetCustomAttributes(typeof(T), Inherit)[I];
        }

        public static object @new(System.Type T, object[] A)
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
                    RA.SetValue(@new(T.GetElementType(), null), I);
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

        public static object @new(System.Type T)
        {
            return @new(T, null);
        }

        public static T @new<T>() { return (T)@new(typeof(T)); }

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
    }
}
