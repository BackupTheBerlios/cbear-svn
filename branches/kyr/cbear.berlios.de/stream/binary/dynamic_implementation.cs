namespace cbear_berlios_de.stream.binary
{
    using IO = System.IO;

    public abstract class dynamic_implementation<T> : dynamic
    {
        #region dynamic Members

        System.Type dynamic.type() { return typeof(T); }

        object dynamic.read(IO.Stream Stream)
        {
            return (object)this.read(Stream);
        }

        void dynamic.write(IO.Stream Stream, object Value)
        {
            this.write(Stream, (T)Value);
        }

        #endregion

        protected abstract T read(IO.Stream Stream);
        protected abstract void write(IO.Stream Stream, T Value);
    }
}