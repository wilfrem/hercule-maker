#pragma once
#include <math.h>

namespace Wilfrem
{
namespace HerculeMaker
{
namespace MFWrapper
{
namespace Video
{
class VideoMath{
public:
	static inline DWORD CalcFrameDulation(unsigned int fps){
		switch (fps)
		{
		case 60:
			return 166667;
		case 30:
			return 333333;
		case 50:
			return 200000;
		case 25:
			return 400000;
		case 24:
			return 416667;
		default:
			return (DWORD)floor(10000000.0 / (double)fps + 0.5);
		}
	}
	static inline const LPCWSTR GetFileExt(Wilfrem::HerculeMaker::MediaInterfaces::VideoEncoding encoding)
	{
		switch(encoding)
		{
		case Wilfrem::HerculeMaker::MediaInterfaces::VideoEncoding::H264:
			return L".mp4";
		case Wilfrem::HerculeMaker::MediaInterfaces::VideoEncoding::WindowsMediaVideo:
			return L".wmv";
		default:
			throw ref new Platform::NotImplementedException();
		}
	}
};
}
}
}
}