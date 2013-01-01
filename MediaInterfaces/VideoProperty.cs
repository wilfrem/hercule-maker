using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Wilfrem.HerculeMaker.MediaInterfaces
{
    /// <summary>
    /// 動画ファイルの情報
    /// </summary>
    public sealed class VideoProperty
    {
        /// <summary>
        /// 出力ファイルストリーム
        /// </summary>
        public IOutputStream Output { get; set; }
        /// <summary>
        /// 動画サイズの幅
        /// </summary>
        public UInt32 Width { get; set; }
        /// <summary>
        /// 動画サイズの高さ
        /// </summary>
        public UInt32 Height { get; set; }
        /// <summary>
        /// ビットレート
        /// </summary>
        public UInt32 BitRate { get; set; }
        /// <summary>
        /// 動画フォーマット
        /// </summary>
        public VideoEncoding Format { get; set; }
        /// <summary>
        /// コピーを作成する
        /// </summary>
        /// <returns>コピーされたVideoProperty</returns>
        public VideoProperty Clone()
        {
            VideoProperty newobj = new VideoProperty();
            newobj.Output = Output;
            newobj.Width = Width;
            newobj.Height = Height;
            newobj.BitRate = BitRate;
            newobj.Format = Format;
            return newobj;
        }
    }
}
