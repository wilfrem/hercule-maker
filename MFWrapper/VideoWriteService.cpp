// VideoWriterService.cpp
#include "pch.h"
#include "VideoWriteService.h"

using namespace Wilfrem::HerculeMaker::MFWrapper;
using namespace Platform;

VideoWriteService::VideoWriteService(VideoProperty^ prop, IMFSinkWriter* pSinkWriter, DWORD stream)
{
	m_prop = prop;
	m_pSinkWriter = pSinkWriter;
	m_stream = stream;
}
void VideoWriteService::WriteFrame(const Array<uint32,1>^ buffer){
	throw ref new NotImplementedException();
}
void VideoWriteService::Close(){
	throw ref new NotImplementedException();
}