namespace cbear_berlios_de.stream.binary
{
    using IO = System.IO;

    public class int32 : dynamic_implementation<System.Int32>
    {
        public static System.Int32 static_read(IO.Stream Stream)
        {
            return (System.Int32)uint32.static_read(Stream);
        }

        public static void static_write(IO.Stream Stream, System.Int32 Value)
        {
            uint32.static_write(Stream, (System.UInt32)Value);
        }

        protected override System.Int32 read(System.IO.Stream Stream)
        {
            return static_read(Stream);
        }

        protected override void write(
            System.IO.Stream Stream, System.Int32 Value)
        {
            static_write(Stream, Value);
        }
    }
}