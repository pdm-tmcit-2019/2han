using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Threading.Tasks;

namespace WorewolfSharpGUI
{
    public class Serializer : JsonContract
    {
        /// <summary>
        /// Jsonファイルのシリアライズ
        /// </summary>
        public void Serialze()
        {
            DataContractJsonSerializer serializer = new DataContractJsonSerializer(typeof(JsonContract));
            JsonContract jsonContract = new JsonContract();
            //ExampleData();
            jsonContract.Day = 1;
            MemoryStream ms = new MemoryStream();
            serializer.WriteObject(ms, jsonContract);
            string JsonString = Encoding.UTF8.GetString(ms.ToArray());
            Save(JsonString);
            
        }

        /// <summary>
        /// Jsonファイルを書きだす際、どこかのディレクトリに保存
        /// </summary>
        protected void Save(string JsonString)
        {
            //ファイル保存ロジック
            var Dialog = new SaveFileDialog();
            Dialog.FileName = "serialize.jsonld"; //デフォルト名
            Dialog.Filter = "jsonldファイル (*.jsonld)|*.jsonld|全てのファイル (*.*)|*.*"; //保存形式
            if (true == Dialog.ShowDialog()) //保存が押されたとき
            {
                File.WriteAllText(Dialog.FileName, JsonString);
            }
            else { return; }
        }

        /// <summary>
        /// 書き出し用データの例
        /// </summary>
        public void ExampleData()
        {
            //@context
            Context = new string[1]; //配列要素プロパティはnewで初期化しておく

            Context[0] = "https://werewolf.world/village/context/0.3/base.jsonld";
            //Context[1] = "https://werewolf.world/village/context/0.3/votingResult.jsonld";
            //@id
            Id = "https://licos.online/state/0.3/village#3/systemMessage";
            //@token
            Token = "とーくん";
            //@phase
            Phase = "朝かもぉ";
            //@date
            Day = 1;
            //@phaseTimeLimit
            PhaseTimeLimit = 800;
            //@serverTimestamp
            ServerTimestamp = "2006-10-07T12:06:56.568+09:00";
            //@clientTimestamp
            ClientTimestamp = "2006-10-07T12:06:56.568+09:00";

            //@character[0]構造体
            /*var character = new Character[1];
            character[0].Context = "https://werewolf.world/village/context/0.3/character.jsonld";
            character[0].Id = "1";
            character[0].IsMine = true;
            character[0].Name.Ja = "たくのろじぃ";
            character[0].Name.En = "takunology";
            character[0].Image = "none";
            character[0].Id = "1";
            character[0].Status = "alive";
            character[0].Update.Id = "updateid";
            character[0].Update.Phase = "あさ";
            character[0].Update.Date = 20191210;
            character[0].IsAChoice = false;*/

            //@Role構造体
            /*var role = new Role[1];
            role[0].IsMine = false;
            role[0].Name.Ja = "げーむますたぁ！";
            role[0].Name.En = "GM";
            role[0].NumberOfPlayers = 1;*/

            /*var board = new Board[1];
            role[0].board[0].character[0].Context = "https://werewolf.world/village/context/0.3/character[0].jsonld";
            role.Board[0].character[0].Id = "1";
            role.Board[0].character[0].IsMine = true;
            role.Board[0].character[0].Name.Ja = "たくのろじぃ";
            role.Board[0].character[0].Name.En = "takunology";
            role.Board[0].character[0].Image = "none";
            role.Board[0].character[0].character[0]Id = 1;
            role.Board[0].character[0].Status = "alive";
            role.Board[0].character[0].Update.Id = "updateid";
            role.Board[0].character[0].Update.Phase = "あさ";
            role.Board[0].character[0].Update.Date = 20191210;
            role.Board[0].character[0].IsAChoice = false;
            role.Board[0].polarity = "negative";*/
        }
    }
}
