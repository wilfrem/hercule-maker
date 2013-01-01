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
	public:
		VideoWriteServiceFactory();

		virtual IVideoWriteService^ Create(VideoProperty^ prop);
	};
}
}
}
