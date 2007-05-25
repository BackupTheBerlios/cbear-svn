namespace cbear_berlios_de.@base
{
    public struct uint64
    {
        public System.UInt32 high;
        public System.UInt32 low;

        public static implicit operator System.UInt64(uint64 This)
        {
            return (System.UInt64)(
                (((System.UInt64)This.high) << 16) + This.low);
        }

        public static implicit operator uint64(System.UInt64 Value)
        {
            uint64 This;
            This.high = (System.UInt32)(Value >> 16);
            This.low = (System.UInt32)Value;
            return This;
        }
    }
}
