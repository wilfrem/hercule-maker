using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading.Tasks;

namespace Wilfrem.HerculeMaker.MediaInterfaces
{
    /// <summary>
    /// 出力ストリームインターフェイス
    /// </summary>
    public interface IOutputStream : IDisposable
    {
        /// <summary>
        /// 出力されるデータ
        /// </summary>
        /// <param name="data">データ配列</param>
        void Write([ReadOnlyArray()]byte[] data);
        /// <summary>
        /// 閉じる
        /// </summary>
        void Close();
    }
}
