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
	

	//MediaFoundation������
	MediaFoundation::Instance->Init();
	//�o�͐�pByteStream��prop����쐬
	IMFByteStream* pByteStream;
	CHK(MFCreateMFByteStreamOnStreamEx((IUnknown*)prop->Output, &pByteStream));
	CHK(MFCreateAttributes(&pAttributes, 10));
	CHK(pAttributes->SetUINT32(MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS, true));
	//pByteStream���o�͐�Ƃ���SinkWriter���쐬
	CHK(MFCreateSinkWriterFromURL(VideoMath::GetFileExt(prop->Format), pByteStream, pAttributes, &pSinkWriter));
    // ����̏o�͏��̐ݒ�
    CHK(MFCreateMediaType(&pMediaTypeOut));   
    CHK(pMediaTypeOut->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video));
    CHK(pMediaTypeOut->SetGUID(MF_MT_SUBTYPE, GetVideoEncodingFormat(prop->Format)));
    CHK(pMediaTypeOut->SetUINT32(MF_MT_AVG_BITRATE, prop->BitRate));
    CHK(pMediaTypeOut->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive));
    CHK(MFSetAttributeSize(pMediaTypeOut.Get(), MF_MT_FRAME_SIZE, prop->Width, prop->Height));
    CHK(MFSetAttributeRatio(pMediaTypeOut.Get(), MF_MT_FRAME_RATE, prop->FPS, 1));
    CHK(MFSetAttributeRatio(pMediaTypeOut.Get(), MF_MT_PIXEL_ASPECT_RATIO, 1, 1));
    CHK(pSinkWriter->AddStream(pMediaTypeOut.Get(), &streamIndex));
	//����̓��͏��̐ݒ�
    CHK(MFCreateMediaType(&pMediaTypeIn));
    CHK(pMediaTypeIn->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video));
    CHK(pMediaTypeIn->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB32));
    CHK(pMediaTypeIn->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive));
    CHK(MFSetAttributeSize(pMediaTypeIn.Get(), MF_MT_FRAME_SIZE, prop->Width, prop->Height));
    CHK(MFSetAttributeRatio(pMediaTypeIn.Get(), MF_MT_FRAME_RATE, prop->FPS, 1));
    CHK(MFSetAttributeRatio(pMediaTypeIn.Get(), MF_MT_PIXEL_ASPECT_RATIO, 1, 1));
    CHK(pSinkWriter->SetInputMediaType(streamIndex, pMediaTypeIn.Get(), NULL));

    // sinkwriter�̏������݂��J�n�\�ɂ���
    CHK(pSinkWriter->BeginWriting());

    // VideoWriteService���쐬���|�C���^�������n��
	return ref new VideoWriteService(prop, pSinkWriter, streamIndex, pByteStream);
}


