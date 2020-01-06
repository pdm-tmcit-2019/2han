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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WerewolfSharp.Views
{
    /* 
     * If some events were receive from ViewModel, then please use PropertyChangedWeakEventListener and CollectionChangedWeakEventListener.
     * If you want to subscribe custome events, then you can use LivetWeakEventListener.
     * When window closing and any timing, Dispose method of LivetCompositeDisposable is useful to release subscribing events.
     *
     * Those events are managed using WeakEventListener, so it is not occurred memory leak, but you should release explicitly.
     */
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            var viewModel = this.DataContext as ViewModels.MainWindowViewModel;
            viewModel.chatVM = this.ChatView.DataContext as ViewModels.ChatMessageControlViewModel;
            MouseCursor(0); //初期位置 Uid = 0
        }

        private Models.JsonSerializer.JsonDatacontract JsonDatacontract = new Models.JsonSerializer.JsonDatacontract();

        private void Grid_MouseDown(object sender, MouseButtonEventArgs e)
        {
            //左クリックされたときのみイベント処理
            if (e.ChangedButton == MouseButton.Left) DragMove();
            else { return; }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            int buttonindex = int.Parse(((Button)e.Source).Uid);
            MouseCursor(buttonindex);
            switch (buttonindex)
            {
                case 0:
                    GridMain.Children.Clear();
                    GridMain.Children.Add(new ChatView());
                    break;
                case 1:
                    GridMain.Children.Clear();
                    GridMain.Children.Add(new AliverView());
                    break;
                case 2:
                    GridMain.Children.Clear();
                    GridMain.Children.Add(new RoleBoardView());
                    break;
            }
        }

        private void MouseCursor(int index)
        {
            TransitioningContentSlide.OnApplyTemplate();
            GridCursor.Margin = new Thickness(10 + (index * 150), 0, 0, 0);
        }

        private void WindowClose(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void WindowHide(object sender, RoutedEventArgs e)
        {
            this.WindowState = WindowState.Minimized;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            Models.JsonSerializer.Deserializer deserializer = new Models.JsonSerializer.Deserializer();
            //MessageBox.Show(JsonDatacontract.Context[0]);
        }
    }
}
