namespace cbear_berlios_de.windows
{
	using F = global::System.Windows.Forms;

	public class webbrowser
	{
		public static void wait(F.WebBrowser webBrowser)
		{
			webBrowser.DocumentText = null;
			F.HtmlDocument document = webBrowser.Document;
			while (document.Body == null)
			{
				F.Application.DoEvents();
			}
		}
	}
}
