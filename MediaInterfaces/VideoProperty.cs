using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Windows.Storage.Streams;

namespace Wilfrem.HerculeMaker.MediaInterfaces
{
    /// <summary>
    /// 動画ファイルの情報
    /// </summary>
    public sealed class VideoProperty
    {
#if NETFX_CORE
        /// <summary>
        /// 出力ファイルストリーム
        /// </summary>
        public IRandomAccessStream Output { get; set; }
#else
        /// <summary>
        /// 出力ファイル名
        /// </summary>
        public string Output { get; set; }
#endif
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
        /// FPS
        /// </summary>
        public uint FPS { get; set; }
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
            newobj.FPS = FPS;
            return newobj;
        }
    }
}
