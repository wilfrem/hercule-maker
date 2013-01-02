#include "pch.h"
#include "MediaFoundation.h"

using namespace Wilfrem::HerculeMaker::MFWrapper;
using namespace Platform;

MediaFoundation^ MediaFoundation::m_instance = nullptr;
void MediaFoundation::Init()
{
	HRESULT hr;
	hr = MFStartup(MF_VERSION);
    if(FAILED(hr)){
		throw ref new COMException(hr);
	}
}
MediaFoundation::~MediaFoundation()
{
	MFShutdown();
}