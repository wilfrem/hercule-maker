using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Wilfrem.HerculeMaker.MediaInterfaces;
using Windows.Storage;

namespace Wilfrem.HerculeMaker.Front.Files
{
    /// <summary>
    /// 動画出力ストリーム
    /// </summary>
    class VideoOutputStream : IOutputStream
    {
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="file">出力ファイル</param>
        public VideoOutputStream(StorageFile file)
        {
            throw new NotImplementedException();
        }
        /// <summary>
        /// 追記で書き込むバイナリデータ
        /// </summary>
        /// <param name="data">バイナリ</param>
        public void Write(byte[] data)
        {
            throw new NotImplementedException();
        }
        /// <summary>
        /// 書き込み終了時に呼ばれる
        /// </summary>
        public void Close()
        {
            throw new NotImplementedException();
        }

    }
}
