using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows;
using System.Windows.Forms;
using Application = System.Windows.Application;

namespace STM32Control
{
    /// <summary>
    /// App.xaml 的交互逻辑
    /// </summary>
    public partial class App : Application
    {
        private static NotifyIcon trayIcon;

        private void ApplicationStartup(object sender, StartupEventArgs e)
        {
            RemoveTrayIcon();
            AddTrayIcon();
        }

        //protected override void OnStartup(StartupEventArgs e)
        //{
        //    base.OnStartup(e);
        //    InitializeComponent();
        //    RemoveTrayIcon();
        //    AddTrayIcon();
        //}

        //[DllImport("user32", CharSet = CharSet.Unicode)]
        //static extern IntPtr FindWindows(string cls, string win);
        //[DllImport("user32")]
        //static extern bool IsIconic(IntPtr hwnd);
        //[DllImport("user32")]
        //static extern bool OpenIcon(IntPtr hwnd);
        //[DllImport("user32")]
        //static extern IntPtr SetForegroundWindow(IntPtr hwnd);
        //protected override void OnStartup(StartupEventArgs e)
        //{
        //    bool isNew;
        //    var mutex = new Mutex(true, "STM32Control", out isNew);
        //    if (!isNew)
        //    {
        //        ActivateOtherWindow();
        //        Application.Current.Shutdown();
        //        return;
        //    }
        //    base.OnStartup(e);
        //}

        //private void ActivateOtherWindow()
        //{
        //    var other = FindWindows(null, "MainWindow");
        //    if (other != IntPtr.Zero)
        //    {
        //        SetForegroundWindow(other);
        //        if (IsIconic(other)) OpenIcon(other);
        //    }
        //}

        private void AddTrayIcon()
        {
            if (trayIcon != null)
            {
                return;
            }
            trayIcon = new NotifyIcon
            {
                Icon = new System.Drawing.Icon("logo.ico"),
                Text = "STM32Control"
            };
            trayIcon.Click += trayIcon_Click;
            trayIcon.Visible = true;

            ContextMenu menu = new ContextMenu();

            MenuItem closeItem = new MenuItem();
            closeItem.Text = "退出";
            closeItem.Click += new EventHandler(delegate { this.Shutdown(); });
            MenuItem showItem = new MenuItem();
            showItem.Text = "显示界面";
            showItem.Click += new EventHandler(delegate { this.trayIcon_Click(null,null); });
            menu.MenuItems.Add(showItem);
            menu.MenuItems.Add(closeItem);

            trayIcon.ContextMenu = menu;    //设置NotifyIcon的右键弹出菜单
        }

        void trayIcon_Click(object sender, EventArgs e)
        {
            MainWindow.Visibility = Visibility.Visible;
            MainWindow.Focus();
        }

        private void RemoveTrayIcon()
        {
            if (trayIcon != null)
            {
                trayIcon.Visible = false;
                trayIcon.Dispose();
                trayIcon = null;
            }
        }

        private void ApplicationExit(object sender, ExitEventArgs e)
        {
            RemoveTrayIcon();
        }

        //internal void TryActive()
        //{
        //    MainWindow mw = GetMainWindow();
        //    if (mw != null)
        //    {
        //        mw.WindowState = WindowState.Minimized;
        //        mw.WindowState = WindowState.Normal;
        //        mw.Activate();
        //    }
        //}

        //public MainWindow GetMainWindow()
        //{
        //    if (this.MainWindow is MainWindow)
        //        return (MainWindow)this.MainWindow;
        //    else
        //        return null;
        //}
    }
}
