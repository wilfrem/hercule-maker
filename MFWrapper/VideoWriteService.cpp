// VideoWriterService.cpp
#include "pch.h"
#include "VideoWriteService.h"
#include "video/VideoMath.h"

using namespace Wilfrem::HerculeMaker::MFWrapper;
using namespace Platform;
using namespace Wilfrem::HerculeMaker::MFWrapper::Video;

VideoWriteService::VideoWriteService(VideoProperty^ prop, IMFSinkWriter* pSinkWriter, DWORD stream)
{
	m_prop = prop;
	m_pSinkWriter = pSinkWriter;
	m_stream = stream;
	m_start = 0;
	m_FrameDuration = VideoMath::CalcFrameDulation(prop->FPS);
	if(prop->Width == 0 || prop->Height == 0){
		throw ref new InvalidArgumentException("VideoProperty::Width/Height cannot be 0");
	}
}
VideoWriteService::~VideoWriteService()
{
}

void VideoWriteService::WriteFrame(const Array<uint32,1>^ buffer){
    IMFSample *pSample = NULL;
    IMFMediaBuffer *pBuffer = NULL;

    const LONG cbWidth = 4 * m_prop->Width;
    const DWORD cbBuffer = cbWidth * m_prop->Height;

    BYTE *pData = NULL;
	//バッファが書き込みサイズと一致しているかチェッk
	if(buffer->Length == m_prop->Width * m_prop->Height)
	{
		throw ref new InvalidArgumentException("buffer size shuld equal to Width * Height");
	}
	
    //メモリ上にMedia Foundationのバッファを作成
    HRESULT hr = MFCreateMemoryBuffer(cbBuffer, &pBuffer);

    //バッファを一時的にロックする
    if (SUCCEEDED(hr))
    {
        hr = pBuffer->Lock(&pData, NULL, NULL);
    }
    if (SUCCEEDED(hr))
    {
        hr = MFCopyImage(
            pData,                      // Destination buffer.
            cbWidth,                    // Destination stride.
            (BYTE*)buffer->Data,        // First row in source image.
            cbWidth,                    // Source stride.
            cbWidth,                    // Image width in bytes.
            m_prop->Height              // Image height in pixels.
            );
    }
    if (pBuffer)
    {
        pBuffer->Unlock();
    }

    // Set the data length of the buffer.
    if (SUCCEEDED(hr))
    {
        hr = pBuffer->SetCurrentLength(cbBuffer);
    }

    // Create a media sample and add the buffer to the sample.
    if (SUCCEEDED(hr))
    {
        hr = MFCreateSample(&pSample);
    }
    if (SUCCEEDED(hr))
    {
        hr = pSample->AddBuffer(pBuffer);
    }

    // Set the time stamp and the duration.
    if (SUCCEEDED(hr))
    {
        hr = pSample->SetSampleTime(m_start);
    }
    if (SUCCEEDED(hr))
    {
        hr = pSample->SetSampleDuration(m_FrameDuration);
    }

    // Send the sample to the Sink Writer.
    if (SUCCEEDED(hr))
    {
        hr = m_pSinkWriter->WriteSample(m_stream, pSample);
    }

    SafeRelease(&pSample);
    SafeRelease(&pBuffer);
    if (FAILED(hr))
    {
		throw ref new COMException(hr);
    }
	m_start += m_FrameDuration;
}
void VideoWriteService::Close(){
	throw ref new NotImplementedException();
}