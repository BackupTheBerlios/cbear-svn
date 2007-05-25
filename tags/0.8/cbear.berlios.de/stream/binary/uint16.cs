namespace cbear_berlios_de.stream.binary
{
    using IO = System.IO;

    public class uint16 : dynamic_implementation<System.UInt16>
    {
        public static System.UInt16 static_read(IO.Stream Stream)
        {
            @base.uint16 X;
            X.low = @byte.static_read(Stream);
            X.high = @byte.static_read(Stream);
            return X;
        }

        public static void static_write(IO.Stream Stream, System.UInt16 Value)
        {
            @base.uint16 X = Value;
            @byte.static_write(Stream, X.low);
            @byte.static_write(Stream, X.high);
        }

        protected override System.UInt16 read(System.IO.Stream Stream)
        {
            return static_read(Stream);
        }

        protected override void write(
            System.IO.Stream Stream, System.UInt16 Value)
        {
            static_write(Stream, Value);
        }
    }
}