namespace cbear_berlios_de.stream.binary
{
    using IO = System.IO;

    public class uint32 : dynamic_implementation<System.UInt32>
    {
        public static System.UInt32 static_read(IO.Stream Stream)
        {
            @base.uint32 X;
            X.low = @uint16.static_read(Stream);
            X.high = @uint16.static_read(Stream);
            return X;
        }

        public static void static_write(IO.Stream Stream, System.UInt32 Value)
        {
            @base.uint32 X = Value;
            uint16.static_write(Stream, X.low);
            uint16.static_write(Stream, X.high);
        }

        protected override System.UInt32 read(System.IO.Stream Stream)
        {
            return static_read(Stream);
        }

        protected override void write(
            System.IO.Stream Stream, System.UInt32 Value)
        {
            static_write(Stream, Value);
        }
    }
}
