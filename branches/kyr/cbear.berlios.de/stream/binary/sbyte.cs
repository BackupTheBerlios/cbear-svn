namespace cbear_berlios_de.stream.binary
{
    using IO = System.IO;

    public class @sbyte : dynamic_implementation<System.SByte>
    {
        public static System.SByte static_read(IO.Stream Stream)
        {
            return (System.SByte)@byte.static_read(Stream);
        }

        public static void static_write(IO.Stream Stream, System.SByte Value)
        {
            @byte.static_write(Stream, (System.Byte)Value);
        }

        protected override System.SByte read(System.IO.Stream Stream)
        {
            return static_read(Stream);
        }

        protected override void write(
            System.IO.Stream Stream, System.SByte Value)
        {
            static_write(Stream, Value);
        }
    }
}