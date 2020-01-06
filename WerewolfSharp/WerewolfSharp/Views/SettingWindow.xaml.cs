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
    public partial class SettingWindow : Window
    {
        public SettingWindow()
        {
            InitializeComponent();
        }

        private void Grid_MouseDown(object sender, MouseButtonEventArgs e)
        {
            //左クリックされたときのみイベント処理
            if (e.ChangedButton == MouseButton.Left) DragMove();
            else { return; }
        }

        private void WindowClose(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void ColorSelect(object sender, RoutedEventArgs e)
        {
            int buttonindex = int.Parse(((Button)e.Source).Uid);
            switch (buttonindex)
            {
                case 0:
                    
                    break;
                case 1:

                    break;
                case 2:

                    break;
            }
        }
    }
}