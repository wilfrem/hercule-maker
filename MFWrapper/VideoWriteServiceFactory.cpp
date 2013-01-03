#include "pch.h"
#include "VideoWriteServiceFactory.h"
#include "VideoWriteService.h"

using namespace Wilfrem::HerculeMaker::MFWrapper;
using namespace Platform;

VideoWriteServiceFactory::VideoWriteServiceFactory()
{
}

IVideoWriteService^ VideoWriteServiceFactory::Create(VideoProperty^ prop)
{
	IMFSinkWriter* pSinkWriter = NULL;
	DWORD streamIndex = 0;
	IMFMediaType    *pMediaTypeOut = NULL;   
    IMFMediaType    *pMediaTypeIn = NULL;   
    IMFAttributes	*pAttributes = NULL;

	//MediaFoundation������
	MediaFoundation::Instance->Init();
	//�o�͐�pByteStream��prop����쐬
	IMFByteStream* pByteStream;
	HRESULT hr = MFCreateMFByteStreamOnStreamEx((IUnknown*)prop->Output, &pByteStream);
	if(SUCCEEDED(hr)){
		hr = MFCreateAttributes(&pAttributes, 10);
	}
	if(SUCCEEDED(hr)){
		hr = pAttributes->SetUINT32(MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS, true);
	}
	//pByteStream���o�͐�Ƃ���SinkWriter���쐬
	if (SUCCEEDED(hr))
	{
		hr = MFCreateSinkWriterFromURL(L".wmv", pByteStream, pAttributes, &pSinkWriter);
	}
    // ������̐ݒ�
    if (SUCCEEDED(hr))
    {
        hr = MFCreateMediaType(&pMediaTypeOut);   
    }
    if (SUCCEEDED(hr))
    {
        hr = pMediaTypeOut->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);     
    }
    if (SUCCEEDED(hr))
    {
        hr = pMediaTypeOut->SetGUID(MF_MT_SUBTYPE, GetVideoEncodingFormat(prop->Format));   
    }
    if (SUCCEEDED(hr))
    {
        hr = pMediaTypeOut->SetUINT32(MF_MT_AVG_BITRATE, prop->BitRate);   
    }
    if (SUCCEEDED(hr))
    {
        hr = pMediaTypeOut->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);
    }
    if (SUCCEEDED(hr))
    {
        hr = MFSetAttributeSize(pMediaTypeOut, MF_MT_FRAME_SIZE, prop->Width, prop->Height);
    }
    if (SUCCEEDED(hr))
    {
        hr = MFSetAttributeRatio(pMediaTypeOut, MF_MT_FRAME_RATE, prop->FPS, 1);   
    }
    if (SUCCEEDED(hr))
    {
        hr = MFSetAttributeRatio(pMediaTypeOut, MF_MT_PIXEL_ASPECT_RATIO, 1, 1);   
    }
    if (SUCCEEDED(hr))
    {
        hr = pSinkWriter->AddStream(pMediaTypeOut, &streamIndex);   
    }

    // ���͏��̐ݒ�
    if (SUCCEEDED(hr))
    {
        hr = MFCreateMediaType(&pMediaTypeIn);   
    }
    if (SUCCEEDED(hr))
    {
        hr = pMediaTypeIn->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);   
    }
    if (SUCCEEDED(hr))
    {
        hr = pMediaTypeIn->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB32);
    }
    if (SUCCEEDED(hr))
    {
        hr = pMediaTypeIn->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);   
    }
    if (SUCCEEDED(hr))
    {
        hr = MFSetAttributeSize(pMediaTypeIn, MF_MT_FRAME_SIZE, prop->Width, prop->Height);   
    }
    if (SUCCEEDED(hr))
    {
        hr = MFSetAttributeRatio(pMediaTypeIn, MF_MT_FRAME_RATE, prop->FPS, 1);   
    }
    if (SUCCEEDED(hr))
    {
        hr = MFSetAttributeRatio(pMediaTypeIn, MF_MT_PIXEL_ASPECT_RATIO, 1, 1);   
    }
    if (SUCCEEDED(hr))
    {
        hr = pSinkWriter->SetInputMediaType(streamIndex, pMediaTypeIn, NULL);   
    }

    // sinkwriter�̏������݂��J�n�\�ɂ���
    if (SUCCEEDED(hr))
    {
        hr = pSinkWriter->BeginWriting();
    }

    SafeRelease(&pMediaTypeOut);
    SafeRelease(&pMediaTypeIn);
    // VideoWriteService���쐬���|�C���^�������n��
	if (SUCCEEDED(hr))
    {
		return ref new VideoWriteService(prop, pSinkWriter, streamIndex, pByteStream);
    }else{
		throw ref new COMException(hr);
	}
}


