/*****************************************************************************
 * ==> Class Program --------------------------------------------------------*
 * ***************************************************************************
 * Description : Main program entry point.                                   *
 * Version     : 1.0                                                         *
 * Developper  : Jean-Milost Reymond                                         *
 *****************************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Visual_Mercutio_Reports_Manager
{
	static class Program
	{
		/// <summary>
		/// Point d'entrée principal de l'application.
		/// </summary>
		[STAThread]
		static void Main()
		{
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault( false );
			Application.Run( new MainFrame() );
		}
	}
}
