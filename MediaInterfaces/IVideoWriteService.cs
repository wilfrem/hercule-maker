using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading.Tasks;

namespace Wilfrem.HerculeMaker.MediaInterfaces
{
    /// <summary>
    /// 動画を出力するサービスのインターフェイス
    /// </summary>
    public interface IVideoWriteService : IDisposable
    {
        /// <summary>
        /// フレームを書き出す
        /// </summary>
        /// <param name="buffer">書き出すフレームデータ。ARGB情報</param>
        void WriteFrame([ReadOnlyArray()]UInt32[] buffer);
        /// <summary>
        /// 出力を閉じる
        /// </summary>
        void Close();
    }
}
