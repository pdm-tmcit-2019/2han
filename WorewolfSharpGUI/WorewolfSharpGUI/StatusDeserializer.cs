using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Windows;

namespace WorewolfSharpGUI
{
    public class StatusDeserializer
    {
        //データベース用接続文字列
        static string Connection = $@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=""{
                                Directory.GetCurrentDirectory() }\Database\WerewolfDatabase.mdf"";Integrated Security=True";

        //データベースコンテキストとオブザーバブルコレクション
        Database.WerewolfDataClassesDataContext Context = new Database.WerewolfDataClassesDataContext(Connection);
        ObservableCollection<Database.Players> observablePlayers = new ObservableCollection<Database.Players>();
        ObservableCollection<Database.Chat> observableChat = new ObservableCollection<Database.Chat>();
        ObservableCollection<Database.Role> observableRole = new ObservableCollection<Database.Role>();

        public void Deserialize(string Phase)
        {
            var Serializer = new DataContractJsonSerializer(typeof(JsonContract));
            string FilePath = "";

            switch (Phase)
            {
                case "morning":
                    FilePath = Path.GetFullPath("../../JsonFiles/DAY1/server2client/morning.jsonld");
                    break;

                case "noon":
                    FilePath = Path.GetFullPath("../../JsonFiles/DAY1/server2client/noon.jsonld");
                    break;

                case "night":
                    FilePath = Path.GetFullPath("../../JsonFiles/DAY1/server2client/night.jsonld");
                    break;

                case "result":
                    FilePath = Path.GetFullPath("../../JsonFiles/DAY1/server2client/result.jsonld");
                    break;
            }

            var JsonFile = File.ReadAllText(FilePath);
            var ms = new MemoryStream(Encoding.UTF8.GetBytes((JsonFile)));
            ms.Seek(0, SeekOrigin.Begin);
            var Data = Serializer.ReadObject(ms) as JsonContract; //読み込み次第JsonContractに保管される

            for (int i = 0; i < Data.Character.GetLength(0); i++)
            {
                Database.Players players = new Database.Players();

                players.Name = Data.Character[i].Name.Ja;
                players.Role = "？？？";
                players.Status = true;

                Database.Chat chat = new Database.Chat();

                Context.Players.InsertOnSubmit(players);
                Context.SubmitChanges();

                chat.PlayerID = players.Id;
                chat.ChatText = "それで、あなたは人狼が誰だと思うの？\n\n私はパメラが人狼だと思う。";
               
                Context.Chat.InsertOnSubmit(chat);
                Context.SubmitChanges();

                var mainwindow = (MainWindow)App.Current.MainWindow;
                this.observableChat.Add(chat);
                mainwindow.DataGrid.ItemsSource = this.observableChat;     

            }
        }

        public void ChatSend()
        {
            var mainwindow = (MainWindow)App.Current.MainWindow;
            Database.Players players = new Database.Players();

            players.Name = "デベロッパー";
            players.Role = "GameMaster";
            players.Status = true;

            Database.Chat chat = new Database.Chat();

            Context.Players.InsertOnSubmit(players);
            Context.SubmitChanges();

            chat.PlayerID = players.Id;
            chat.ChatText = mainwindow.Chatbox.Text;

            Context.Chat.InsertOnSubmit(chat);
            Context.SubmitChanges();

            this.observablePlayers.Add(players);
            this.observableChat.Add(chat);
            mainwindow.DataGrid.ItemsSource = this.observableChat;
        }

        public void GetAliverCount() //現在の生存者状況
        {
            JsonContract jsonContract = new JsonContract();
            Database.Role role = new Database.Role();
            role.Day = jsonContract;
        }
    }
}
