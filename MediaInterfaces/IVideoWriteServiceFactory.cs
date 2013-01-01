using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Wilfrem.HerculeMaker.MediaInterfaces
{
    /// <summary>
    /// 動画出力サービスを作成するファクトリ
    /// </summary>
    public interface IVideoWriteServiceFactory
    {
        /// <summary>
        /// 指定された動画フォーマット情報をもとに動画出力サービスを作成する
        /// </summary>
        /// <param name="prop">動画フォーマット。このpropertyは実装側でcloneしてサービス作成後に値を変更できなくするべき</param>
        /// <returns>動画出力サービス</returns>
        IVideoWriteService Create(VideoProperty prop);
    }
}
