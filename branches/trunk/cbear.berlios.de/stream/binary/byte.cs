namespace cbear_berlios_de.stream.binary
{
    using IO = System.IO;

    public class @byte : dynamic_implementation<System.Byte>
    {
        public static System.Byte static_read(IO.Stream Stream)
        {
            return (System.Byte)Stream.ReadByte();
        }

        public static void static_write(IO.Stream Stream, System.Byte Value)
        {
            Stream.WriteByte(Value);
        }

        protected override System.Byte read(IO.Stream Stream)
        {
            return static_read(Stream);
        }

        protected override void write(IO.Stream Stream, System.Byte Value)
        {
            static_write(Stream, Value);
        }
    }
}