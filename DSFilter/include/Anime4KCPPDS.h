#pragma once

#include<streams.h>
#include<Dvdmedia.h>

#include"ACuids.h"
#include "ACProp.h"
#include"Anime4KCPP.h"

enum class ColorFormat
{
    YV12, IYUV, NV12, RGB24, RGB32
};

class Anime4KCPPDS :
    public CTransformFilter, ISpecifyPropertyPages, IAC
{
public:
    DECLARE_IUNKNOWN;
    static CUnknown* WINAPI CreateInstance(LPUNKNOWN punk, HRESULT* phr);
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void** ppv);

    virtual HRESULT CheckInputType(const CMediaType* mtIn);
    virtual HRESULT CheckTransform(const CMediaType* mtIn, const CMediaType* mtOut);
    virtual HRESULT DecideBufferSize(IMemAllocator* pAlloc, ALLOCATOR_PROPERTIES* pProperties);
    virtual HRESULT GetMediaType(int iPosition, CMediaType* pMediaType);
    virtual HRESULT Transform(IMediaSample* pIn, IMediaSample* pOut);

    STDMETHODIMP GetParameters(bool* HDN, bool* CNN, unsigned int* pID, unsigned int* dID, float* zoomFactor);
    STDMETHODIMP SetParameters(bool HDN, bool CNN, unsigned int pID, unsigned int dID, float zoomFactor);
    STDMETHODIMP GetGPUInfo(std::string& info);

    STDMETHODIMP GetPages(CAUUID* pPages);

private:
    Anime4KCPPDS(TCHAR* tszName, LPUNKNOWN punk, HRESULT* phr);
    BOOL IsRGB24(const CMediaType* pMediaType) const;
    BOOL IsRGB32(const CMediaType* pMediaType) const;
    BOOL IsIYUV(const CMediaType* pMediaType) const;
    BOOL IsYV12(const CMediaType* pMediaType) const;
    BOOL IsNV12(const CMediaType* pMediaType) const;
private:
    Anime4KCPP::Anime4KCreator acCreator;
    Anime4KCPP::Parameters parameters;
    unsigned int pID, dID;
    float zf;
    bool CNN;

    LONG srcH, srcW, dstH, dstW;
    LONG dstDataLength;
    ColorFormat colorFormat;
    TCHAR lpPath[MAX_PATH];
    CCritSec lock;
};
