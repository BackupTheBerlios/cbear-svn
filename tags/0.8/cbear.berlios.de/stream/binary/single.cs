namespace cbear_berlios_de.stream.binary
{
    using IO = System.IO;
    using BC = System.BitConverter;

    public class single : dynamic_implementation<System.Single>
    {
        public static System.Single static_read(IO.Stream Stream)
        {
            System.Byte[] Bytes = BC.GetBytes(new System.Single());
            Stream.Read(Bytes, 0, Bytes.Length);
            return BC.ToSingle(Bytes, 0);
        }

        public static void static_write(IO.Stream Stream, System.Single Value)
        {
            System.Byte[] Bytes = BC.GetBytes(Value);
            Stream.Write(Bytes, 0, Bytes.Length);
        }

        protected override System.Single read(System.IO.Stream Stream)
        {
            return static_read(Stream);
        }

        protected override void write(
            System.IO.Stream Stream, System.Single Value)
        {
            static_write(Stream, Value);
        }
    }
}
