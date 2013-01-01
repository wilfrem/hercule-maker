#pragma once
using namespace Wilfrem::HerculeMaker::MediaInterfaces;

namespace Wilfrem
{
namespace HerculeMaker
{
namespace MFWrapper
{
	//Media Foundationを利用した動画出力サービス
	public ref class VideoWriteService sealed  : IVideoWriteService
    {
    public:
        VideoWriteService();
		//サービス利用側からの動画フレーム出力
		virtual void WriteFrame(const Platform::Array<uint32, 1>^ buffer);
		//サービス利用側からの動画出力終了のお知らせ
		virtual void Close();
    };
}
}
}