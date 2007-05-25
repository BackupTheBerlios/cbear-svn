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
            new single(),
        };

        public class unknown_type : System.Exception
        {
            public unknown_type(System.Type type)
            {
                this.type = type;
            }

            public System.Type type;
        }

        public static object read(IO.Stream Stream, System.Type T)
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
            throw new unknown_type(T);
        }

        public static T read<T>(IO.Stream Stream)
        {
            return (T)read(Stream, typeof(T));
        }

        public static void write(IO.Stream Stream, object Value)
        {
            System.Type T = Value.GetType();
            foreach (
                stream.binary.dynamic D in
                stream.binary.primitive_type.list)
            {
                if (D.type() == T)
                {
                    D.write(Stream, Value);
                    return;
                }
            }
            throw new unknown_type(T);
        }

        public static void write<T>(IO.Stream Stream, T Value)
        {
            write(Stream, (object)Value);
        }
    }
}

