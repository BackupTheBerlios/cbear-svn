namespace cbear_berlios_de.@base
{
    public struct uint32
    {
        public System.UInt16 high;
        public System.UInt16 low;

        public static implicit operator System.UInt32(uint32 This)
        {
            return (System.UInt32)(
                (((System.UInt32)This.high) << 16) + This.low);
        }

        public static implicit operator uint32(System.UInt32 Value)
        {
            uint32 This;
            This.high = (System.UInt16)(Value >> 16);
            This.low = (System.UInt16)Value;
            return This;
        }
    }
}
