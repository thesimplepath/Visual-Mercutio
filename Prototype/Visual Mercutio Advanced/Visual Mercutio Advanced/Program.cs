using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Visual_Mercutio_2006_Advanced
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Visual_Mercutio_2006_Advanced.MainFrame.MainFrame());
        }
    }
}