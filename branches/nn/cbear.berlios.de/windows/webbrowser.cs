namespace cbear_berlios_de.windows
{
	using F = global::System.Windows.Forms;
	using C = global::System.Collections;
	using G = global::System.Collections.Generic;

	public class webbrowser
	{
		private webbrowser()
		{
		}

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

	public class treeview
	{
		private treeview()
		{
		}

		public delegate bool @predicate(F.TreeNode node);

		public static F.TreeNode find(F.TreeNodeCollection collection, @predicate d)
		{
			foreach (F.TreeNode n in collection)
			{
				if (d(n))
				{
					return n;
				}
			}
			return null;
		}

		public static void remove_all(F.TreeNodeCollection collection, @predicate d)
		{
			foreach (F.TreeNode n in collection)
			{			
				if(d(n))
				{
					collection.Remove(n);
				}
			}
		}

		public delegate void @delegate(F.TreeNode node);

		public static void all_for_each(F.TreeNodeCollection collection, @delegate d)
		{
			foreach (F.TreeNode n in collection)
			{
				d(n);
				all_for_each(n.Nodes, d);
			}
		}
	}
}
