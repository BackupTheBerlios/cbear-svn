/*
The MIT License

Copyright (c) 2005 Sergey Shandar

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
namespace net.sourceforge.cbear.project
{
	using SWF = System.Windows.Forms;
	
	class main
	{
		class MenuItem: SWF.MenuItem
		{
			public MenuItem Add(SWF.MenuItem item)
			{
				this.MenuItems.Add(item);
				return this;
			}
		
			public MenuItem(string text): base(text) {}
			
			public MenuItem(string text, System.EventHandler handler): 
				base(text, handler)
			{
			}
		}
		
		class MainMenu: SWF.MainMenu
		{
			public MainMenu Add(MenuItem item)
			{
				this.MenuItems.Add(item);
				return this;
			}
			
			public MainMenu(SWF.Form form)
			{
				form.Menu = this;
			}
		}
		
		class Project: SWF.Panel
		{
			class TreeView: SWF.TreeView
			{
				public TreeView()
				{
					this.Dock = SWF.DockStyle.Left;
				}
			}
			
			class Splitter: SWF.Splitter
			{
				public Splitter()
				{
					this.Dock = SWF.DockStyle.Left;
				}
			}
			
			class Rt
			{
				public string text;
				
				public static Rt Tag(string tag)
				{
					return new Rt("\\" + tag + " ");
				}
				
				public static Rt Block(string tag, Rt rtf)
				{
					return new Rt("{" + Tag(tag).text + rtf.text + "}");
				}
				
				public Rt(string text)
				{
					foreach(char c in text)
					{
						switch(c)
						{
							case '\n': this.text += "\\line "; break;
							default: this.text += c.ToString(); break;
						}
					}
				}
				
				public Rt Add(Rt rtf)
				{
					this.text += rtf.text;
					return this;
				}
				
				public Rt Add(string text)
				{
					return this.Add(new Rt(text));
				}
				
				public static Rt operator+(Rt a, Rt b)
				{
					return new Rt(a.text).Add(b);
				}
				
				public static Rt operator+(Rt a, string b)
				{
					return new Rt(a.text).Add(b);
				}
			}
			
			class TabControl: SWF.TabControl
			{
				public class RichTextBox: SWF.RichTextBox
				{
					public RichTextBox()
					{
						this.Dock = SWF.DockStyle.Fill;
						this.Rtf = Rt.Block("rtf", 
							Rt.Block("fonttbl", Rt.Tag("f0") + "Courier New;")).text;
					}
				}
				
				public class View: SWF.TabPage
				{
					public class RichTextBox: TabControl.RichTextBox
					{
						public RichTextBox()
						{
							this.ReadOnly = true;
							this.Rtf = Rt.Block("rtf",
								Rt.Block("fonttbl",
									Rt.Tag("f0") +
									"Courier New;") +
								"Hello world!").text;
						}
					}
					
					public RichTextBox richTextBox = new RichTextBox();
					
					public View()
					{
						this.Text = "View";
						this.Controls.Add(this.richTextBox);
					}
				}
				
				public View view = new View();
				
				public class Source: SWF.TabPage
				{
					public RichTextBox richTextBox = new RichTextBox();
					
					public Source()
					{
						this.Text = "Source";					
						this.Controls.Add(this.richTextBox);
					}
				}
				
				public Source source = new Source();
				
				public TabControl()
				{
					this.Dock = SWF.DockStyle.Fill;
					this.TabPages.Add(this.view);
					this.TabPages.Add(this.source);
					//this.source.richTextBox.Rtf = this.view.richTextBox.Rtf;
				}
			}
			
			TabControl tabControl = new TabControl();
			
			project project = new project();
			
			public Project()
			{
				this.Dock = SWF.DockStyle.Fill;
				//
				this.Controls.Add(this.tabControl);
				//
				this.Controls.Add(new Splitter());
				//
				this.Controls.Add(new TreeView());
			}
				
			public Project Load(string fileName)
			{
				this.project.Load(fileName);
				this.tabControl.source.richTextBox.Rtf = Rt.Block("rtf",
					Rt.Block("fonttbl", Rt.Tag("f0") + "Courier New;") +
					this.project.text).text;
				this.tabControl.view.richTextBox.Rtf = this.project.rtf;
				return this;
			}
		}
		
		class Form: SWF.Form
		{	
			SWF.OpenFileDialog dialog = new SWF.OpenFileDialog();
			
			Project project;
			
			void Set(Project project)
			{
				this.Controls.Remove(this.project);
				this.Controls.Add(project);
				this.project = project;
			}
			
			void New(object O, System.EventArgs E)
			{
				this.Set(new Project());
			}

			void Open(object O, System.EventArgs E) 
			{
				if(dialog.ShowDialog(this)!=SWF.DialogResult.OK) return;
				this.Set(new Project().Load(dialog.FileName));
			}
			
			public Form()
			{
				this.WindowState = SWF.FormWindowState.Maximized;
				this.Text = "C Bear Project";
				//
				dialog.Filter = "XML File (*.xml)|*.xml";
				//
				new MainMenu(this).
					Add(new MenuItem("File").
					  Add(new MenuItem("New", new System.EventHandler(this.New))).
						Add(new MenuItem("Open", new System.EventHandler(this.Open))));
			}
		}
		
		static int Main(string[] args)
		{
			SWF.Application.Run(new Form());
			return 0;
		}
	}
}
