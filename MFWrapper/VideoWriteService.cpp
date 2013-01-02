// VideoWriterService.cpp
#include "pch.h"
#include "VideoWriteService.h"
#include "video/VideoMath.h"

using namespace Wilfrem::HerculeMaker::MFWrapper;
using namespace Platform;
using namespace Wilfrem::HerculeMaker::MFWrapper::Video;

VideoWriteService::VideoWriteService(VideoProperty^ prop, IMFSinkWriter* pSinkWriter, DWORD stream, IMFByteStream* pByteStream)
{
	m_prop = prop;
	m_pSinkWriter = pSinkWriter;
	m_stream = stream;
	m_start = 0;
	m_FrameDuration = VideoMath::CalcFrameDulation(prop->FPS);
	m_pByteStream = pByteStream;
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
	//バッファが書き込みサイズと一致しているかチェック
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
	//バッファに画像をコピーする
    if (SUCCEEDED(hr))
    {
        hr = MFCopyImage(
            pData,                      // 書き込み先バッファ.
            cbWidth,                    // 書き込み先のstride.
            (BYTE*)buffer->Data,        // 書き込みを行う画像データ.
            cbWidth,                    // 書き込みデータのstide.
            cbWidth,                    // バイト換算の画像幅.
            m_prop->Height              // 画像高さ(pixel).
            );
    }
	//バッファをアンロックする
    if (pBuffer)
    {
        pBuffer->Unlock();
    }

    // バッファ長を設定する
    if (SUCCEEDED(hr))
    {
        hr = pBuffer->SetCurrentLength(cbBuffer);
    }

    // media sampleを作成し、bufferに入れる
    if (SUCCEEDED(hr))
    {
        hr = MFCreateSample(&pSample);
    }
    if (SUCCEEDED(hr))
    {
        hr = pSample->AddBuffer(pBuffer);
    }

    // 書き込んだフレームのタイムスタンプと長さを指定
    if (SUCCEEDED(hr))
    {
        hr = pSample->SetSampleTime(m_start);
    }
    if (SUCCEEDED(hr))
    {
        hr = pSample->SetSampleDuration(m_FrameDuration);
    }

    // サンプルをSinkWriterに書き込み
    if (SUCCEEDED(hr))
    {
        hr = m_pSinkWriter->WriteSample(m_stream, pSample);
    }
	//開放
    SafeRelease(&pSample);
    SafeRelease(&pBuffer);
	//失敗を検知した場合はCOMExceptionを投げる
    if (FAILED(hr))
    {
		throw ref new COMException(hr);
    }
	//書き込んだ分だけ書き込み位置をすすめる
	m_start += m_FrameDuration;
}
void VideoWriteService::Close(){
	if(m_pSinkWriter != NULL){
		m_pSinkWriter->Finalize();
	}
    SafeRelease(&m_pSinkWriter);
	SafeRelease(&m_pByteStream);
}