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
        public Deserializer deserializer = new Deserializer(); //デシリアライズのインスタンス
        public ObservableCollection<Database.Players> observablePlayers = new ObservableCollection<Database.Players>();
        public Database.Players players = new Database.Players();
        Database.Chat chat = new Database.Chat();

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            //Jsonデシリアライズ
            deserializer.Deserialize("morning");

            //データベース処理とGUIへ反映
            this.observablePlayers.Add(players);
            this.DataGrid.ItemsSource = observablePlayers;

        }
    }
}
