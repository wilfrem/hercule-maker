#include "pch.h"
#include "VideoWriteServiceFactory.h"

using namespace Wilfrem::HerculeMaker::MFWrapper;
using namespace Platform;

VideoWriteServiceFactory::VideoWriteServiceFactory()
{
}

IVideoWriteService^ VideoWriteServiceFactory::Create(VideoProperty^ prop)
{
	throw ref new NotImplementedException();
}


