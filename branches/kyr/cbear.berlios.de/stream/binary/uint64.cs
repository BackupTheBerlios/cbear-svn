namespace cbear_berlios_de.stream.binary
{
    using IO = System.IO;

    public class uint64 : dynamic_implementation<System.UInt64>
    {
        public static System.UInt64 static_read(IO.Stream Stream)
        {
            @base.uint64 X;
            X.low = @uint32.static_read(Stream);
            X.high = @uint32.static_read(Stream);
            return X;
        }

        public static void static_write(IO.Stream Stream, System.UInt64 Value)
        {
            @base.uint64 X = Value;
            uint32.static_write(Stream, X.low);
            uint32.static_write(Stream, X.high);
        }

        protected override System.UInt64 read(System.IO.Stream Stream)
        {
            return static_read(Stream);
        }

        protected override void write(
            System.IO.Stream Stream, System.UInt64 Value)
        {
            static_write(Stream, Value);
        }
    }
}
