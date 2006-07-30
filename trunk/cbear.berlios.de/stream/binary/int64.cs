namespace cbear_berlios_de.stream.binary
{
    using IO = System.IO;

    public class int64 : dynamic_implementation<System.Int64>
    {
        public static System.Int64 static_read(IO.Stream Stream)
        {
            return (System.Int64)uint64.static_read(Stream);
        }

        public static void static_write(IO.Stream Stream, System.Int64 Value)
        {
            uint64.static_write(Stream, (System.UInt64)Value);
        }

        protected override System.Int64 read(System.IO.Stream Stream)
        {
            return static_read(Stream);
        }

        protected override void write(
            System.IO.Stream Stream, System.Int64 Value)
        {
            static_write(Stream, Value);
        }
    }
}
