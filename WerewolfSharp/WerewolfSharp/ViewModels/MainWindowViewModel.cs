using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

using Livet;
using Livet.Commands;
using Livet.Messaging;
using Livet.Messaging.IO;
using Livet.EventListeners;
using Livet.Messaging.Windows;

using WerewolfSharp.Models;
using System.Windows;

namespace WerewolfSharp.ViewModels
{
    public class MainWindowViewModel : ViewModel
    {

        private Command.InformationOpenCommand _informationCommand;
        private Command.SettingOpenCommand _settingCommand;
        private ChatMessageControlViewModel _chatVM;

        public string WindowTitle { get; set; } = $"{Properties.Settings.Default.AppName} {Properties.Settings.Default.AppVersion}";

        // Some useful code snippets for ViewModel are defined as l*(llcom, llcomn, lvcomm, lsprop, etc...).
        public void Initialize()
        {
            
        }

        // MainWindow -> ChatControl への databinding
        public ChatMessageControlViewModel chatVM
        {
            get { return _chatVM; }
            set
            {
                if(_chatVM != value)
                {
                    _chatVM = value;
                    RaisePropertyChanged("chatVM");
                }
            }
        }

        public Command.InformationOpenCommand informationCommand //Open Information Window
        {
            get
            {
                return _informationCommand ?? (_informationCommand = new Command.InformationOpenCommand(() =>
                  {
                      Views.InformationWindow informationWindow = new Views.InformationWindow();
                      informationWindow.Show();
                  }));
            }
        }

        public Command.SettingOpenCommand SettingCommand // Open Setting Window
        {
            get
            {
                return _settingCommand ?? (_settingCommand = new Command.SettingOpenCommand(() =>
                {
                    Views.SettingWindow settingWindow = new Views.SettingWindow();
                    settingWindow.Show();
                }));
            }
        }
    }
}
