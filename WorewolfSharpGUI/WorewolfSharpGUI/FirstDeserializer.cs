using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Windows;

namespace WorewolfSharpGUI
{
    public class FirstDeserializer
    {
        //データベース用接続文字列
        static string Connection = $@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=""{
                                Directory.GetCurrentDirectory() }\Database\WerewolfDatabase.mdf"";Integrated Security=True";

        //データベースコンテキストとオブザーバブルコレクション
        Database.WerewolfDataClassesDataContext Context = new Database.WerewolfDataClassesDataContext(Connection);
        ObservableCollection<Database.Players> observablePlayers = new ObservableCollection<Database.Players>();
        ObservableCollection<Database.Chat> observableChat = new ObservableCollection<Database.Chat>();
        ObservableCollection<Database.Role> observableRole = new ObservableCollection<Database.Role>();
        ObservableCollection<Database.Board> observableBoards = new ObservableCollection<Database.Board>();

        int GamePlayersRole = 0; //プレイヤー人数の初期化

        public void Deserialize(string Phase)
        {
            observablePlayers = new ObservableCollection<Database.Players>(this.Context.Players);
            observableChat = new ObservableCollection<Database.Chat>(this.Context.Chat);
            observableRole = new ObservableCollection<Database.Role>(this.Context.Role);
            observableBoards = new ObservableCollection<Database.Board>(this.Context.Board);

            var mainwindow = (MainWindow)App.Current.MainWindow;
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
            var jsonContract = Serializer.ReadObject(ms) as JsonContract; //読み込み次第JsonContractに保管される

            for (int i = 0; i < jsonContract.Character.GetLength(0); i++)
            {
                Database.Players players = new Database.Players();

                players.Name = jsonContract.Character[i].Name.Ja;
                players.Role = "？？？";
                players.Status = true;

                Database.Chat chat = new Database.Chat();

                Context.Players.InsertOnSubmit(players);
                Context.SubmitChanges();

                chat.PlayerID = players.Id;
                chat.ChatText = "それで、あなたは人狼が誰だと思うの？\n私はパメラが人狼だと思う。";

                Context.Chat.InsertOnSubmit(chat);
                Context.SubmitChanges();

                this.observableChat.Add(chat);
                mainwindow.DataGrid.ItemsSource = this.observableChat;
            }

            //ここから下は生存数処理とボード情報の処理
            Database.Role DatabaseRole = new Database.Role();
            Database.Board DatabaseBoard = new Database.Board();
            int[] Counter = new int[9];

            for (int i = 0; i < jsonContract.Role.GetLength(0); i++)
            {
                switch (jsonContract.Role[i].Name.En)
                {
                    case "Villager":
                        for (int j = 1; j <= jsonContract.Role[i].NumberOfPlayers; j++) { Counter[0]++; }
                        for (int j = 0; j < jsonContract.Role[i].Board.GetLength(0); j++)
                        {
                            if (jsonContract.Role[i].Board[j].polarity == "positive")
                            {
                                DatabaseBoard.Name = jsonContract.Role[i].Board[j].Character.Name.Ja;
                                DatabaseBoard.Villager = "〇";
                            }
                            else { DatabaseBoard.Villager = "×"; }
                        }
                        break;

                    case "Seer":
                        for (int j = 1; j <= jsonContract.Role[i].NumberOfPlayers; j++) { Counter[1]++; }
                        for (int j = 0; j < jsonContract.Role[i].Board.GetLength(0); j++)
                        {
                            if (jsonContract.Role[i].Board[j].polarity == "positive")
                            {
                                DatabaseBoard.Name = jsonContract.Role[i].Board[j].Character.Name.Ja;
                                DatabaseBoard.Seer = "〇";
                            }
                            else { DatabaseBoard.Seer = "×"; }
                        }
                        break;

                    case "Medium":
                        for (int j = 1; j <= jsonContract.Role[i].NumberOfPlayers; j++) { Counter[2]++; }
                        for (int j = 0; j < jsonContract.Role[i].Board.GetLength(0); j++)
                        {
                            if (jsonContract.Role[i].Board[j].polarity == "positive")
                            {
                                DatabaseBoard.Name = jsonContract.Role[i].Board[j].Character.Name.Ja;
                                DatabaseBoard.Medium = "〇";
                            }
                            else { DatabaseBoard.Medium = "×"; }
                        }
                        break;

                    case "Hunter":
                        for (int j = 1; j <= jsonContract.Role[i].NumberOfPlayers; j++) { Counter[3]++; }
                        for (int j = 0; j < jsonContract.Role[i].Board.GetLength(0); j++)
                        {
                            if (jsonContract.Role[i].Board[j].polarity == "positive")
                            {
                                DatabaseBoard.Name = jsonContract.Role[i].Board[j].Character.Name.Ja;
                                DatabaseBoard.Hunter = "〇";
                            }
                            else { DatabaseBoard.Hunter = "×"; }
                        }
                        break;

                    case "Mason":
                        for (int j = 1; j <= jsonContract.Role[i].NumberOfPlayers; j++) { Counter[4]++; }
                        for (int j = 0; j < jsonContract.Role[i].Board.GetLength(0); j++)
                        {
                            if (jsonContract.Role[i].Board[j].polarity == "positive")
                            {
                                DatabaseBoard.Name = jsonContract.Role[i].Board[j].Character.Name.Ja;
                                DatabaseBoard.Mason = "〇";
                            }
                            else { DatabaseBoard.Mason = "×"; }
                        }
                        break;

                    case "Madman":
                        for (int j = 1; j <= jsonContract.Role[i].NumberOfPlayers; j++) { Counter[5]++; }
                        for (int j = 0; j < jsonContract.Role[i].Board.GetLength(0); j++)
                        {
                            if (jsonContract.Role[i].Board[j].polarity == "positive")
                            {
                                DatabaseBoard.Name = jsonContract.Role[i].Board[j].Character.Name.Ja;
                                DatabaseBoard.Madman = "〇";
                            }
                            else { DatabaseBoard.Madman = "×"; }
                        }
                        break;

                    case "Werewolf":
                        for (int j = 1; j <= jsonContract.Role[i].NumberOfPlayers; j++) { Counter[6]++; }
                        for (int j = 0; j < jsonContract.Role[i].Board.GetLength(0); j++)
                        {
                            if (jsonContract.Role[i].Board[j].polarity == "positive")
                            {
                                DatabaseBoard.Name = jsonContract.Role[i].Board[j].Character.Name.Ja;
                                DatabaseBoard.Werewolf = "〇";
                            }
                            else { DatabaseBoard.Werewolf = "×"; }
                        }
                        break;

                    case "Werehamster":
                        for (int j = 1; j <= jsonContract.Role[i].NumberOfPlayers; j++) { Counter[7]++; }
                        for (int j = 0; j < jsonContract.Role[i].Board.GetLength(0); j++)
                        {
                            if (jsonContract.Role[i].Board[j].polarity == "positive")
                            {
                                DatabaseBoard.Name = jsonContract.Role[i].Board[j].Character.Name.Ja;
                                DatabaseBoard.Werehamster = "〇";
                            }
                            else { DatabaseBoard.Werehamster = "×"; }
                        }
                        break;
                }
            }
            DatabaseRole.Villager = Counter[0];
            DatabaseRole.Seer = Counter[1];
            DatabaseRole.Medium = Counter[2];
            DatabaseRole.Hunter = Counter[3];
            DatabaseRole.Mason = Counter[4];
            DatabaseRole.Madman = Counter[5];
            DatabaseRole.Werewolf = Counter[6];
            DatabaseRole.Werehamster = Counter[7];
            
            for(int i = 0; i < Counter.GetLength(0) - 1; i++) { Counter[8] += Counter[i]; }
            DatabaseRole.Alivers = Counter[8]; 
            DatabaseRole.Day = jsonContract.Day;

            //生存者数データベースの更新
            Context.Role.InsertOnSubmit(DatabaseRole);
            Context.SubmitChanges();

            this.observableRole.Add(DatabaseRole);
            mainwindow.AliverGrid.ItemsSource = this.observableRole;
            
            //ボード情報の更新
            Context.Board.InsertOnSubmit(DatabaseBoard);
            Context.SubmitChanges();

            this.observableBoards.Add(DatabaseBoard);
            mainwindow.BoardGrid.ItemsSource = this.observableBoards;
            
        }

        //データベースに全てぶち込むべきかもしれない
        //おそらくデータコントラクトは保持されない？

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
    }
}
