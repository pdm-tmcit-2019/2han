using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Json;
using System.Text;

using Livet;

namespace WerewolfSharp.Models.JsonSerializer
{
    public class Deserializer : NotificationObject
    {
        private DataContractJsonSerializer serializer = new DataContractJsonSerializer(typeof(JsonDatacontract));
        private string FilePath = "../../../JSONDATA/noon.jsonld";
        
        public Deserializer()
        {
            var JsonFile = File.ReadAllText(FilePath);
            var ms = new MemoryStream(Encoding.UTF8.GetBytes((JsonFile)));
            ms.Seek(0, SeekOrigin.Begin);
            var jsonContract = serializer.ReadObject(ms) as JsonDatacontract; //読み込み次第JsonContractに保管される
        }
    }
}
