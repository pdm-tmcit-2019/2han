﻿using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Runtime.InteropServices;
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

        //C++で作ったコードの呼び出し / プロトタイプ宣言？
        [DllImport("ExampleCPP.dll")]
        static extern int Test(int a, int b);

        [DllImport("mecabReply.dll", CharSet = CharSet.Ansi)]
        static extern void mystrcpy(string dest);

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

        private void Button_CppCall(object sender, RoutedEventArgs e)
        {
            //C++の文字列を読み込む
            MessageBox.Show(Test(3, 2).ToString());
        }

        private void Button_OTACall(object sender, RoutedEventArgs e)
        {
            //セリフ1
            string dest = "こんにちは";
            mystrcpy(dest);
            MessageBox.Show(dest.ToString(), "パターン1");
            
            //セリフ2
            dest = "お前たちの平成って醜くないか？";
            mystrcpy(dest);
            MessageBox.Show(dest.ToString(), "パターン2");

            //セリフ3
            dest = "end";
            mystrcpy(dest);
            MessageBox.Show(dest.ToString(), "パターン3");
        }
    }
}
