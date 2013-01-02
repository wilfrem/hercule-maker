#pragma once
using namespace Wilfrem::HerculeMaker::MediaInterfaces;

namespace Wilfrem
{
namespace HerculeMaker
{
namespace MFWrapper
{
	//Media Foundationを利用した動画出力サービス
	ref class VideoWriteService sealed  : IVideoWriteService
    {
	private:
		//動画情報
		VideoProperty^ m_prop;
		//出力に利用するMedia Foundationオブジェクト
		IMFSinkWriter* m_pSinkWriter;
		//チャンネル情報
		DWORD m_stream;
		//書き出し位置
		LONGLONG m_start;
		//1フレームあたりの長さ
		DWORD m_FrameDuration;
		//書き出し用のクラスを格納したオブジェクト
		IMFByteStream* m_pByteStream;
	internal:
		//コンストラクタ。生成済みのpSynkWriterとstreamを指定する
        VideoWriteService(VideoProperty^ prop, IMFSinkWriter* pSinkWriter, DWORD stream, IMFByteStream* pByteStream);
    public:
		//サービス利用側からの動画フレーム出力
		virtual void WriteFrame(const Platform::Array<uint32, 1>^ buffer);
		//サービス利用側からの動画出力終了のお知らせ
		virtual void Close();

		virtual ~VideoWriteService();
    };
}
}
}