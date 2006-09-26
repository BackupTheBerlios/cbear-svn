namespace cbear_berlios_de.windows
{
	using F = global::System.Windows.Forms;

	public class webbrowser
	{
		public static void wait(F.WebBrowser @this)
		{
			@this.DocumentText = null;
			F.HtmlDocument document = @this.Document;
			while (document.Body == null)
			{
				F.Application.DoEvents();
			}
		}

		public static F.HtmlElement append(F.HtmlElement parent, string tag)
		{
			F.HtmlElement element = parent.Document.CreateElement(tag);
			parent.AppendChild(element);
			return element;
		}
	}
}
