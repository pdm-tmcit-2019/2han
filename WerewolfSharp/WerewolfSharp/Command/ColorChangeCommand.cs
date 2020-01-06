using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace WerewolfSharp.Command
{
    public class ColorChangeCommand : ICommand
    {
        private Action _action;

        public ColorChangeCommand(Action action)
        {
            _action = action;            
        }

        public event EventHandler CanExecuteChanged;

        //利用状態を確認する
        public bool CanExecute(object parameter)
        {
            return _action != null;
        }

        //実行するコマンド
        public void Execute(object parameter)
        {
            //引数無しで実行
            _action?.Invoke();
        }
    }
}
