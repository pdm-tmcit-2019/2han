using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Text;
using WerewolfSharp;

namespace SimpleJsonReader
{
    class Program
    {
        static void Main(string[] args)
        {            
            var serializer = new DataContractJsonSerializer(typeof(JsonData));
            string FilePath = Path.GetFullPath(@"F:\GitHub\2han\WerewolfSharp\WerewolfSharp\JsonFiles\morning.jsonld");
            var json = File.ReadAllText(FilePath);

            var ms = new MemoryStream(Encoding.UTF8.GetBytes((json)));

            //シリアライズ用
            //serializer.WriteObject(ms, new Data { Name = "たくのろじぃ" });
            //Console.WriteLine(Encoding.UTF8.GetString(ms.ToArray()));

            ms.Seek(0, SeekOrigin.Begin);
            var data = serializer.ReadObject(ms) as JsonData;

            string Status = "";
            Console.WriteLine($"ID : {data.Id}");

            for (int i = 0; i < data.Context.GetLength(0); i++)
                Console.WriteLine($"context{i} : {data.Context[i].ToString()}");

            Console.WriteLine($"Token : {data.Token}");
            Console.WriteLine($"Phase : {data.Phase}");
            Console.WriteLine($"Date : {data.Date}");
            Console.WriteLine($"PhaseTimeLimit : {data.PhaseTimeLimit}");
            Console.WriteLine($"ServerTimestamp : {data.ServerTimestamp}");
            Console.WriteLine($"ClientTimestamp : {data.ClientTimestamp}");

            Console.WriteLine();

            for (int i = 0; i < data.Character.GetLength(0); i++) //キャラクター情報の表示
            {
                Console.Write($"参加者ID {data.Character[i].CharacterId} : "); //プレイヤーID
                Console.Write($"{data.Character[i].Name.Ja} ({data.Character[i].Name.En})"); // プレイヤー名

                Status = data.Character[i].Status;
                if (Status == "alive")
                {
                    Console.ForegroundColor = ConsoleColor.Green;
                    Console.WriteLine($" {data.Character[i].Status}");
                    Console.ForegroundColor = ConsoleColor.White;
                }
                else if (Status == "dead")
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine($" {data.Character[i].Status}");
                    Console.ForegroundColor = ConsoleColor.White;
                }

            }
        }
    }
}
