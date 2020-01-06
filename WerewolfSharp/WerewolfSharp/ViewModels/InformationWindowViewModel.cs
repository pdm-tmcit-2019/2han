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
    public class InformationWindowViewModel : ViewModel
    {
        public string AppName { get; set; } = Properties.Settings.Default.AppName;
        public string AppVersion { get; set; } = Properties.Settings.Default.AppVersion;
        public string AppAuthor { get; set; } = Properties.Settings.Default.AppAuthor;
        public string Organization { get; set; } = Properties.Settings.Default.Organization;

        // Some useful code snippets for ViewModel are defined as l*(llcom, llcomn, lvcomm, lsprop, etc...).

        // This method would be called from View, when ContentRendered event was raised.

        public void Initialize()
        {
        }
    }
}
