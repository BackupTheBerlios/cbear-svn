namespace cbear_berlios_de.stream.binary
{
    using IO = System.IO;

    public interface dynamic
    {
        System.Type type();
        object read(IO.Stream Stream);
        void write(IO.Stream Stream, object Value);
    }
}