using System;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.Text;

namespace WorewolfSharpGUI
{
    [DataContract]
    public class JsonContract
    {
        //Json先頭読み込み部分
        [DataMember(Name = "@context")]
        public string[] Context { get; set; }

        [DataMember(Name = "@id")]
        public string Id { get; set; }

        [DataMember(Name = "token")]
        public string Token { get; set; }

        [DataMember(Name = "phase")]
        public string Phase { get; set; }

        [DataMember(Name = "date")]
        public int Date { get; set; }

        [DataMember(Name = "phaseTimeLimit")]
        public int PhaseTimeLimit { get; set; }

        [DataMember(Name = "serverTimestamp")]
        public string ServerTimestamp { get; set; }

        [DataMember(Name = "clientTimestamp")]
        public string ClientTimestamp { get; set; }

        [DataMember(Name = "character")]
        public Character[] Character { get; set; }
    }

    [DataContract]
    public partial class Character
    {
        //Json　Character配列
        [DataMember(Name = "@context")]
        public Uri Context { get; set; }

        [DataMember(Name = "@id")]
        public Uri Id { get; set; }

        [DataMember(Name = "isMine")]
        public bool IsMine { get; set; }

        //Name構造体
        [DataMember(Name = "name")]
        public Name Name { get; set; }

        [DataMember(Name = "image")]
        public Uri Image { get; set; }

        [DataMember(Name = "id")]
        public int CharacterId { get; set; }

        [DataMember(Name = "status")]
        public string Status { get; set; }

        //Update構造体
        [DataMember(Name = "update")]
        public Update Update { get; set; }

        [DataMember(Name = "isAChoice")]
        public bool IsAChoice { get; set; }
    }

    [DataContract]
    public partial class Name
    {
        [DataMember(Name = "en")]
        public string En { get; set; }

        [DataMember(Name = "ja")]
        public string Ja { get; set; }
    }

    [DataContract]
    public partial class Update
    {
        [DataMember(Name = "@id")]
        public Uri Id { get; set; }

        [DataMember(Name = "phase")]
        public string Phase { get; set; }

        [DataMember(Name = "date")]
        public long Date { get; set; }
    }
}
