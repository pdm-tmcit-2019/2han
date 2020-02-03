#Jsonファイルの読み込み
#読み込んだ文字列を表示していく
#発言したいタイミングを適当に決める
#発言する場合、1つ前の文字を形態素解析にかける
#DLL呼び出しからの文字受け取り、表示

import json
import random
from ctypes import *
import ctypes

filesCount = 33 #Jsonファイル数
Textlist = [] #Jsonから読み込んだテキストデータを格納する
Chara = [] #発言したキャラクタの取得
rndnum = 0 #割り込みたい番号
Player = 'たくのろじぃ' #割り込みするプレイヤー名
SayCount = 0 #割り込み発言回数

for i in range(filesCount + 1): #発言読み込み処理
    f = open('JSONDATA/TheirMessages/theirMessageOnChat('+ str(i) +').jsonld', 'r', encoding="utf-8")
    json_dict = json.load(f)
    Textlist.append(json_dict['text']['@value'])
    Chara.append(json_dict['character']['name']['ja'])

for i in range(filesCount + SayCount + 1): #出力（発言のタイミングを決めてから発言する）
    print(str(i) + ' ' + Chara[i] + ' : ' + Textlist[i])

for i in range(random.randint(1, 5)): #1フェーズあたり10回まで発言できるが、一応5回に制限
    dll = cdll.LoadLibrary("mecabReply.dll") #形態素解析DLL読み込み
    rndnum = random.randint(1, filesCount) #ここで乱数生成して何番目に発言を割り込むかを指定する
    #msg = ctypes.create_string_buffer(32)
    NextText = dll.FromPy(str(Textlist[rndnum - 1]).encode("mbcs")) #1つ前の発言を参考に形態素解析
    #dll.MainPy() #テスト用
    #NextText = dll.TestPy(5) #テスト用
    Chara.insert(rndnum, Player) #プレイヤ名
    Textlist.insert(rndnum, str(NextText)) #形態素解析による発言
    SayCount = i

for i in range(filesCount + SayCount + 1): #出力（発言のタイミングを決めてから発言する）
    print(str(i) + ' ' + Chara[i] + ' : ' + Textlist[i])