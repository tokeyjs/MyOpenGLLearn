using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace MyWpfLearn
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        Student stu;
        public MainWindow()
        {
            InitializeComponent();
            
            // 数据源
            stu = new Student();

            // 准备Binding
            Binding bid = new Binding();
            bid.Source = stu;
            bid.Path = new PropertyPath("Name");

            // 使用Binding连接数据源与Binding目标
            BindingOperations.SetBinding(this.textBox1, TextBox.TextProperty, bid);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            stu.Name += "Name";
        }
    }

    public class Student : System.ComponentModel.INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public string name;
        public string Name
        {
            get
            {
                return this.name;
            }
            set
            {
                this.name = value;
                if(PropertyChanged!=null)
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("Name"));
            }
        }
    }
}
