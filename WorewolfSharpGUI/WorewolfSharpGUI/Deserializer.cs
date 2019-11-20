using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Windows;

namespace WorewolfSharpGUI
{
    public class Deserializer
    {

        static string Connection = $@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=""{
                                Directory.GetCurrentDirectory() }\Database\WerewolfDatabase.mdf"";Integrated Security=True";

        Database.WerewolfDataClassesDataContext Context = new Database.WerewolfDataClassesDataContext(Connection);

        Database.Players players = new Database.Players();
        Database.Chat chat = new Database.Chat();

        public void Deserialize(string Phase)
        {
            var Serializer = new DataContractJsonSerializer(typeof(JsonContract));
            string FilePath = "";

            switch (Phase)
            {
                case "morning":
                    FilePath = Path.GetFullPath("../../JsonFiles/DAY1/server2client/morning.jsonld");
                    break;
            }

            var JsonFile = File.ReadAllText(FilePath);
            var ms = new MemoryStream(Encoding.UTF8.GetBytes((JsonFile)));
            ms.Seek(0, SeekOrigin.Begin);
            var Data = Serializer.ReadObject(ms) as JsonContract; //読み込み次第JsonContractに保管される


            players.Name = Data.Character[0].Name.Ja;
            chat.PlayerID = players.Id;

            Context.Players.InsertOnSubmit(players);
            Context.SubmitChanges();


        }
    }
}
