   M S B A M L   `   `   `  ���� K  GWorewolfSharpGUI, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null3clr-namespace:WorewolfSharpGUIWorewolfSharpGUI  !    WorewolfSharpGUI.MainWindow   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     0localclr-namespace:WorewolfSharpGUI     -     � Title$(  "Werewolf Viewer (Develop-ver1.4.0)��$	��650��$
��1050��.��� .+�&   System.Windows.Controls.DataGrid  -     Name$ DataGrid��$
��Left=�$	��500��$��	27,44,0,0q�$	��Top=�$	��461��   AutoGenerateColumns .     Columns 0  *System.Windows.Controls.DataGridTextColumn  ,  &System.Windows.Controls.DataGridColumn   Header$ No��   
IsReadOnly . 1  +System.Windows.Controls.DataGridBoundColumn   Binding �� *
Players.Id+  $ 名前�� .  �� *Players.Name+  $ 役職�� .  �� *Players.Role+  $ チャット�� .  �� *
ChatText+  -   $ 
AliverGrid��$
��Left=�$	��160��$��
540,44,0,0q�$	��Top=�$	��461�� .     $	 Day�� .  �� *Day+  $ 村人�� .  �� *
Villager+  $ 	占い師�� .  �� *Seer+  $ 	霊媒師�� .  �� *Medium+  $ 狩人�� .  �� *Hunter+  $ 	共有者�� .  �� *Mason+  $ 狂人�� .  �� *Madman+  $ 人狼�� .  �� *
Werewolf+  $ ハムスター人間�� .  �� *Werehamster+  $ 	生存数�� .  �� *	Alivers+�� -   $��送信��$
��Left=�$��413,574,0,0q�$	��Top=�$��75��$��23���� -   $��Chatbox��$
��Left=�$��23��$��
27,574,0,0q� �� TextWrapping$
 Wrap=�$	��Top=�$	��381���� $$��会話ログ（チャット）��$
��Left=�$��	27,13,0,0q�$	��Top=�$	��384��$��14(��� $��生存数リスト��$
��Left=�$��
540,13,0,0q�$	��Top=�$	��384��$��14(�  -   $ 	BoardGrid��$
��Left=�$	��283��$��540,261,0,0q�$	��Top=�$	��461�� .     $ プレイヤー名�� .  �� *Name+  $ 村人�� .  �� *
Villager+  $ 	占い師�� .  �� *Seer+  $ 	霊媒師�� .  �� *Medium+  $ 狩人�� .  �� *Hunter+  $ 	共有者�� .  �� *Mason+  $ 狂人�� .  �� *Madman+  $ 人狼�� .  �� *
Werewolf+  $ ハムスター人間�� .  �� *Werehamster+�� $��	ボード��$
��Left=�$��540,227,0,0q�$	��Top=�$	��384��$��14(��� -   $��	次の日��$
��Left=�$��835,574,0,0q�$	��Top=�$��75��$��23���� -   $��書き出し��$
��Left=�$��926,574,0,0q�$	��Top=�$��75��$��23���� -	   $��C++呼び出し��$
��Left=�$��540,574,0,0q�$	��Top=�$��75��$��23��