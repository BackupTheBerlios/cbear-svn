namespace cbear_berlios_de.stream.binary
{
    using IO = System.IO;

    public class int16 : dynamic_implementation<System.Int16>
    {
        public static System.Int16 static_read(IO.Stream Stream)
        {
            return (System.Int16)uint16.static_read(Stream);
        }

        public static void static_write(IO.Stream Stream, System.Int16 Value)
        {
            uint16.static_write(Stream, (System.UInt16)Value);
        }

        protected override System.Int16 read(System.IO.Stream Stream)
        {
            return static_read(Stream);
        }

        protected override void write(
            System.IO.Stream Stream, System.Int16 Value)
        {
            static_write(Stream, Value);
        }
    }
}