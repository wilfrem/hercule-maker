#pragma once
namespace Wilfrem
{
namespace HerculeMaker
{
namespace MFWrapper
{

template <class T> void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}
}
}
}