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

namespace WerewolfSharp.ViewModels
{
    public class ChatMessageControlViewModel : ViewModel
    {
        Views.MainWindow mainWindow = new Views.MainWindow();
        
        public string Date { get; set; } = "2019/04/01";
        private string _date = "2019/04/01";
        public string SubmitDate
        {
            get { return _date; }
            set
            {
                if(_date != value)
                {
                    _date = value;
                    RaisePropertyChanged("SubmitDate");
                }
            }
        }
        // Some useful code snippets for ViewModel are defined as l*(llcom, llcomn, lvcomm, lsprop, etc...).

        // This method would be called from View, when ContentRendered event was raised.
        public void Initialize()
        {
            
        }
    }
}
