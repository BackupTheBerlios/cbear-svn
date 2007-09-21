namespace cbear_berlios_de.stream.binary
{
	using IO = System.IO;
	using BC = System.BitConverter;

	public class @double: dynamic_implementation<System.Double>
	{
		public static System.Single static_read(IO.Stream Stream)
		{
			System.Byte[] Bytes = BC.GetBytes(new System.Double());
			Stream.Read(Bytes, 0, Bytes.Length);
			return BC.ToSingle(Bytes, 0);
		}

		public static void static_write(IO.Stream Stream, System.Double Value)
		{
			System.Byte[] Bytes = BC.GetBytes(Value);
			Stream.Write(Bytes, 0, Bytes.Length);
		}

		protected override System.Double read(System.IO.Stream Stream)
		{
			return static_read(Stream);
		}

		protected override void write(
				System.IO.Stream Stream, System.Double Value)
		{
			static_write(Stream, Value);
		}
	}
}
