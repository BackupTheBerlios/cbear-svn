using SX = System.Xml;
using SXS = System.Xml.Schema;

namespace net.sourceforge.cbear.xsd
{
	/// <summary>
	/// Summary description for 'xsd'.
	/// </summary>
	class main
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[System.STAThread]
		static void Main(string[] args)
		{
			//
			// TODO: Add code to start application here
			//
			try
			{
				if(args.Length!=1)
				{
					System.Console.WriteLine("Usage: xsd.exe source-uri");
					return;
				}
				SX.XmlTextReader reader = new SX.XmlTextReader(args[0]);
				SX.XmlValidatingReader validatingReader = 
					new SX.XmlValidatingReader(reader);
				while(validatingReader.Read());
			}
			catch(System.Exception e)
			{
				System.Console.WriteLine(e.ToString());
			}
		}
	}
}
