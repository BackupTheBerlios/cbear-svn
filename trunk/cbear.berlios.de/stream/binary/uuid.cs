namespace cbear_berlios_de.stream.binary
{
	using IO = System.IO;

	public class uuid: dynamic_implementation<System.Guid>
  {
    public static System.Guid static_read(IO.Stream Stream)
    {
			System.Byte[] Bytes = System.Guid.Empty.ToByteArray();
			Stream.Read(Bytes, 0, Bytes.Length);
			return new System.Guid(Bytes);
    }

    public static void static_write(IO.Stream Stream, System.Guid Value)
    {
			System.Byte[] Bytes = Value.ToByteArray();
			Stream.Write(Bytes, 0, Bytes.Length);
    }

    protected override System.Guid read(System.IO.Stream Stream)
    {
        return static_read(Stream);
    }

    protected override void write(
        System.IO.Stream Stream, System.Guid Value)
    {
        static_write(Stream, Value);
    }
	}
}
