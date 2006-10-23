namespace cbear_berlios_de.@base
{
	public struct uint8: inumeric<uint8>
	{

		private global::System.Byte value;

		public uint8(global::System.Byte value)
		{
			this.value = value;
		}

		public static implicit operator uint8(global::System.Byte value)
		{
			return new uint8(value);
		}

		#region inumeric<uint8> Members

		void inumeric<uint8>.add(uint8 b)
		{
			this.value += b.value;
		}

		void inumeric<uint8>.sub(uint8 b)
		{
			this.value -= b.value;
		}

		#endregion

		#region IComparable<uint8> Members

		int System.IComparable<uint8>.CompareTo(uint8 other)
		{
			return this.value.CompareTo(other.value);
		}

		#endregion

		public override global::System.String ToString()
		{
			return this.value.ToString();
		}
	}
}
