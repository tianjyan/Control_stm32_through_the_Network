using Microsoft.VisualBasic.ApplicationServices;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows;

namespace STM32Control
{
    public class Startup
    {
        [STAThread]
        public static void Main(string[] args)
        {
            SingleApp sa = new SingleApp();
            //string[] s = { "STM32Control" };
            sa.Run(args);
        }
    }

    public class SingleApp : WindowsFormsApplicationBase
    {
        public SingleApp()
        {
            this.IsSingleInstance = true;
        }

        private STM32Control.App app;
        protected override bool OnStartup(Microsoft.VisualBasic.ApplicationServices.StartupEventArgs eventArgs)
        {
            app = new App();
            //app.InitializeComponent();
            app.Run();
            return false;
        }

        protected override void OnStartupNextInstance(StartupNextInstanceEventArgs eventArgs)
        {
            //app.TryActive();
            foreach (Window win in app.Windows)
            {
                if (win.Visibility != Visibility.Visible)
                {
                    win.Activate();
                }
            }
        }

    }
}
