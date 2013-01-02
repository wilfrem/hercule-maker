#pragma once
using namespace Wilfrem::HerculeMaker::MediaInterfaces;

namespace Wilfrem
{
namespace HerculeMaker
{
namespace MFWrapper
{
	public ref class VideoWriteServiceFactory sealed : IVideoWriteServiceFactory
	{
	private:
		inline GUID GetVideoEncodingFormat(VideoEncoding encoding){
			switch (encoding)
			{
			case VideoEncoding::H264:
				return MFVideoFormat_H264;
			case VideoEncoding::WindowsMediaVideo:
				return MFVideoFormat_WMV3;
			default:
				throw ref new Platform::NotImplementedException("unknown video encode");
			}
		}
	public:
		VideoWriteServiceFactory();

		virtual IVideoWriteService^ Create(VideoProperty^ prop);
		
	};
}
}
}
