using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

using Livet;

namespace WerewolfSharp.Models.JsonSerializer
{
    [DataContract]
    public class JsonDatacontract : NotificationObject
    {
        //ViewModels.MainWindowViewModel MainWindowViewModel = new ViewModels.MainWindowViewModel();
        //Json先頭読み込み部分
        [DataMember(Name = "@context")]
        public string[] Context { get; set; }
    }
}
