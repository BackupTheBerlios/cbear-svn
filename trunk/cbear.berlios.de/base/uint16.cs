namespace cbear_berlios_de.@base.integer
{
    public struct uint16
    {
        public System.Byte high;
        public System.Byte low;

        public static implicit operator System.UInt16(uint16 This)
        {
            return (System.UInt16)(
                (((System.UInt16)This.high) << 8) + This.low);
        }

        public static implicit operator uint16(System.UInt16 Value)
        {
            uint16 This;
            This.high = (System.Byte)(Value >> 8);
            This.low = (System.Byte)Value;
            return This;
        }
    }
}
