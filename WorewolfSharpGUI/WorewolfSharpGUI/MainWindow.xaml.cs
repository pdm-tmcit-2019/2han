using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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

namespace WorewolfSharpGUI
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        FirstDeserializer deserializer = new FirstDeserializer(); //デシリアライズのインスタンス
        NextDeserializer nextDeserializer = new NextDeserializer();
        Serializer serializer = new Serializer(); //シリアライズのインスタンス

        //データベース項目のインスタンス
        ObservableCollection<Database.Players> observablePlayers = new ObservableCollection<Database.Players>();
        Database.Players players = new Database.Players();

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            //Jsonデシリアライズ
            deserializer.Deserialize("morning");//朝フェーズとそのボード情報を得る
        }

        private void Button_Solve(object sender, RoutedEventArgs e)
        {
            deserializer.ChatSend();
        }

        private void Button_Next(object sender, RoutedEventArgs e)
        {
            nextDeserializer.NextDay("2", "morning");
        }

        private void Button_Write(object sender, RoutedEventArgs e)
        {
            //try
            {
                serializer.Serialze();
                MessageBox.Show("書き込みました。", "Jsonのシリアライズ", MessageBoxButton.OK, MessageBoxImage.Information);
            }
            //catch(Exception ex)
            {
                //MessageBox.Show(ex.ToString());
            }

        }
    }
}
