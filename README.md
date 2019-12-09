# WerewolfSharpGUI
Werewolf world の Json ファイルデータをGUIで表示するためのツールです。

# 更新状況 (Develop-ver1.4.0)
書き出し機能を実装してサーバへ送信するためのJsonファイルを生成できるようにしました。</br>

## 実装されている機能

- 会話ログの表示 💬
- 会話の送信（データベースへの保存のみ）👨
- 生存者数の数え上げと表示 👬
- そのフェーズで分かっている役職ボードの表示 🐺
- Jsonldファイルの書き出し <font color="Red"> ← New!!</font>

"書き出し"ボタンが追加されました。

![screenshot](Images/ver1_4(1).png "screenshot")

"書き出し"をクリックすると保存ダイアログが出てきます。

![screenshot](Images/ver1_4(2).png "screenshot")

保存ができるとメッセージが表示されます。

![screenshot](Images/ver1_4(3).png "screenshot")

保存されたJsonldファイルです。今の段階では構造体や配列に入っていないデータの書き込みだけできるので、タイムスタンプやフェーズなどが書かれています。なぜかNULLになってますが...。</br>
インデントや改行がされていませんが、サーバに読ませるなら問題ないと思うのでこのままにしておきます。

![screenshot](Images/ver1_4(4).png "screenshot")

## 現時点での問題点

- データベースの更新に伴い、履歴にあったデータの表示が〇から？になってしまう問題
- 配列要素をもつデータ構造のシリアライズで例外が発生する（おそらくNULL）

</br>
takunology (2019/12/10) 更新</br> </br> </br> </br> </br>


# 更新状況(Develop-ver1.3.0)
Json で読み込んだプレイヤー情報とゲーム情報を LocalDB に保持して DataGrid で表示できるようにしました。動作環境は .NET Framework 4.7.3 なので Windows で動作します。また、データベースは Microsoft SQL Server 2016 以上を使用しています。

</br>
takunology (2019/11/27) 更新