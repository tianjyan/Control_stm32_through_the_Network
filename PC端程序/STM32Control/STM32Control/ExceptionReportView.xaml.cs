using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace STM32Control
{
    /// <summary>
    /// ExceptionReportView.xaml 的交互逻辑
    /// </summary>
    public partial class ExceptionReportView : Window
    {
        ExceptionReportInfo reportInfo = new ExceptionReportInfo();

        public ExceptionReportView(params Exception[] e)
        {
            InitializeComponent();
            reportInfo.SetExceptions(e);   
            ShowFullDetail();
        }

        private  void  btnDetail_Click(object sender, RoutedEventArgs e)
        {
            ShowFullDetail();
        }

        private void btnEmail_Click(object sender, RoutedEventArgs e)
        {

        }

        private void ShowFullDetail()
        {
            if (tb_Error.Visibility.Equals(Visibility.Collapsed))
            {
                this.Height = 400;
                HideRow.Height = new GridLength(130);
                tb_Error.Visibility = Visibility.Visible;
                btnDetail.Template = (ControlTemplate)App.Current.Resources["btnDetail2"];
            }
            else
            {
                tb_Error.Visibility = Visibility.Collapsed;
                this.Height = 250;
                HideRow.Height = new GridLength(0);
                btnDetail.Template = (ControlTemplate)App.Current.Resources["btnDetail"];

            }
        }

        private void ShowLastReportInfot(ExceptionReportInfo reportInfo)
        {
            ShowFullDetail();
            tb_Error.Text = reportInfo.MainException.Message + "\r\n\r\n" + reportInfo.Exceptions[0].StackTrace.ToString();
        }

        private void btnClose_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
