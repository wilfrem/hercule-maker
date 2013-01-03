#include "pch.h"
#include "VideoWriteServiceFactory.h"
#include "VideoWriteService.h"
#include "video/VideoMath.h"

using namespace Wilfrem::HerculeMaker::MFWrapper;
using namespace Platform;
using namespace Wilfrem::HerculeMaker::MFWrapper::Video;
using namespace Microsoft::WRL;

VideoWriteServiceFactory::VideoWriteServiceFactory()
{
}

IVideoWriteService^ VideoWriteServiceFactory::Create(VideoProperty^ prop)
{
	IMFSinkWriter* pSinkWriter = NULL;
	DWORD streamIndex = 0;
	ComPtr<IMFMediaType>    pMediaTypeOut;   
    ComPtr<IMFMediaType>    pMediaTypeIn;   
    IMFAttributes	*pAttributes = NULL;
	

	//MediaFoundation初期化
	MediaFoundation::Instance->Init();
	//出力先pByteStreamをpropから作成
	IMFByteStream* pByteStream;
	CHK(MFCreateMFByteStreamOnStreamEx((IUnknown*)prop->Output, &pByteStream));
	CHK(MFCreateAttributes(&pAttributes, 10));
	CHK(pAttributes->SetUINT32(MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS, true));
	//pByteStreamを出力先としたSinkWriterを作成
	CHK(MFCreateSinkWriterFromURL(VideoMath::GetFileExt(prop->Format), pByteStream, pAttributes, &pSinkWriter));
    // 動画の出力情報の設定
    CHK(MFCreateMediaType(&pMediaTypeOut));   
    CHK(pMediaTypeOut->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video));
    CHK(pMediaTypeOut->SetGUID(MF_MT_SUBTYPE, GetVideoEncodingFormat(prop->Format)));
    CHK(pMediaTypeOut->SetUINT32(MF_MT_AVG_BITRATE, prop->BitRate));
    CHK(pMediaTypeOut->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive));
    CHK(MFSetAttributeSize(pMediaTypeOut.Get(), MF_MT_FRAME_SIZE, prop->Width, prop->Height));
    CHK(MFSetAttributeRatio(pMediaTypeOut.Get(), MF_MT_FRAME_RATE, prop->FPS, 1));
    CHK(MFSetAttributeRatio(pMediaTypeOut.Get(), MF_MT_PIXEL_ASPECT_RATIO, 1, 1));
    CHK(pSinkWriter->AddStream(pMediaTypeOut.Get(), &streamIndex));
	//動画の入力情報の設定
    CHK(MFCreateMediaType(&pMediaTypeIn));
    CHK(pMediaTypeIn->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video));
    CHK(pMediaTypeIn->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB32));
    CHK(pMediaTypeIn->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive));
    CHK(MFSetAttributeSize(pMediaTypeIn.Get(), MF_MT_FRAME_SIZE, prop->Width, prop->Height));
    CHK(MFSetAttributeRatio(pMediaTypeIn.Get(), MF_MT_FRAME_RATE, prop->FPS, 1));
    CHK(MFSetAttributeRatio(pMediaTypeIn.Get(), MF_MT_PIXEL_ASPECT_RATIO, 1, 1));
    CHK(pSinkWriter->SetInputMediaType(streamIndex, pMediaTypeIn.Get(), NULL));

    // sinkwriterの書き込みを開始可能にする
    CHK(pSinkWriter->BeginWriting());

    // VideoWriteServiceを作成しポインタを引き渡す
	return ref new VideoWriteService(prop, pSinkWriter, streamIndex, pByteStream);
}


