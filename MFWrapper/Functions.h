#pragma once

namespace Wilfrem
{
namespace HerculeMaker
{
namespace MFWrapper
{
inline void CHK(HRESULT hr)
{
	if(FAILED(hr))
	{
		throw ref new Platform::COMException(hr);
	}
}

template <class T> void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}
template <class T> void SafeDelete(T **ppT)
{
    if (*ppT)
    {
        delete (*ppT);
        *ppT = NULL;
    }
}
}
}
}