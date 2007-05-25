namespace cbear_berlios_de.@base
{
	public class compare<T>
		where T : global::System.IComparable<T>
	{
		public static T min(T a, T b)
		{
			return a.CompareTo(b) < 0 ? a : b;
		}

		public static T max(T a, T b)
		{
			return a.CompareTo(b) > 0 ? a : b;
		}
	}
}
