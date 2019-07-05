/****************************************************************************
 * ==> PSS_WebBrowserBase --------------------------------------------------*
 ****************************************************************************
 * Description : Basic web browser MFC dialog                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_WebBrowserBase.h"

//---------------------------------------------------------------------------
// PSS_WebBrowserBase
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_WebBrowserBase, CWnd)
//---------------------------------------------------------------------------
CLSID const& PSS_WebBrowserBase::GetClsID()
{
    static CLSID const clsID = {0x8856f961, 0x340a, 0x11d0, {0xa9, 0x6b, 0x0, 0xc0, 0x4f, 0xd7, 0x5, 0xa2}};
    return clsID;
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::Create(LPCTSTR         pClassName,
                                LPCTSTR         pWindowName,
                                DWORD           style,
                                const RECT&     rect,
                                CWnd*           pParentWnd,
                                UINT            id,
                                CCreateContext* pContext)
{
    return CreateControl(GetClsID(), pWindowName, style, rect, pParentWnd, id);
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::Create(LPCTSTR     pWindowName,
                                DWORD       style,
                                const RECT& rect,
                                CWnd*       pParentWnd,
                                UINT        id,
                                CFile*      pPersist,
                                BOOL        storage,
                                BSTR        licKey)
{
    return CreateControl(GetClsID(), pWindowName, style, rect, pParentWnd, id, pPersist, storage, licKey);
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::GoBack()
{
    InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::GoForward()
{
    InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::GoHome()
{
    InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::GoSearch()
{
    InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::Stop()
{
    InvokeHelper(0x6a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::Quit()
{
    InvokeHelper(0x12c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::Navigate(LPCTSTR  pURL,
                                  VARIANT* pFlags,
                                  VARIANT* pTargetFrameName,
                                  VARIANT* pPostData,
                                  VARIANT* pHeaders)
{
    static BYTE params[] = VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
    InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, NULL, params, pURL, pFlags, pTargetFrameName, pPostData, pHeaders);
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::Navigate(VARIANT* pURL,
                                  VARIANT* pFlags,
                                  VARIANT* pTargetFrameName,
                                  VARIANT* pPostData,
                                  VARIANT* pHeaders)
{
    static BYTE params[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
    InvokeHelper(0x1f4, DISPATCH_METHOD, VT_EMPTY, NULL, params, pURL, pFlags, pTargetFrameName, pPostData, pHeaders);
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::Refresh()
{
    InvokeHelper(DISPID_REFRESH, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::Refresh(VARIANT* pLevel)
{
    static BYTE params[] = VTS_PVARIANT;
    InvokeHelper(0x69, DISPATCH_METHOD, VT_EMPTY, NULL, params, pLevel);
}
//---------------------------------------------------------------------------
LPDISPATCH PSS_WebBrowserBase::GetApplication()
{
    LPDISPATCH result;
    InvokeHelper(0xc8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
LPDISPATCH PSS_WebBrowserBase::GetParent()
{
    LPDISPATCH result;
    InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
LPDISPATCH PSS_WebBrowserBase::GetContainer()
{
    LPDISPATCH result;
    InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
LPDISPATCH PSS_WebBrowserBase::GetDocument()
{
    LPDISPATCH result;
    InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::GetTopLevelContainer()
{
    BOOL result;
    InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
CString PSS_WebBrowserBase::GetType()
{
    CString result;
    InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
long PSS_WebBrowserBase::GetLeft()
{
    long result;
    InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetLeft(long value)
{
    static BYTE params[] = VTS_I4;
    InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
long PSS_WebBrowserBase::GetTop()
{
    long result;
    InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetTop(long value)
{
    static BYTE params[] = VTS_I4;
    InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
long PSS_WebBrowserBase::GetWidth()
{
    long result;
    InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetWidth(long value)
{
    static BYTE params[] = VTS_I4;
    InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
long PSS_WebBrowserBase::GetHeight()
{
    long result;
    InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetHeight(long value)
{
    static BYTE params[] = VTS_I4;
    InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
CString PSS_WebBrowserBase::GetLocationName()
{
    CString result;
    InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
CString PSS_WebBrowserBase::GetLocationURL()
{
    CString result;
    InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::GetBusy()
{
    BOOL result;
    InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::ClientToWindow(long* pCX, long* pCY)
{
    static BYTE params[] = VTS_PI4 VTS_PI4;
    InvokeHelper(0x12d, DISPATCH_METHOD, VT_EMPTY, NULL, params, pCX, pCY);
}
//---------------------------------------------------------------------------
VARIANT PSS_WebBrowserBase::GetProperty(LPCTSTR pProperty)
{
    static BYTE    params[] = VTS_BSTR;
           VARIANT result;
    InvokeHelper(0x12f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, params, pProperty);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetProperty(LPCTSTR pProperty, const VARIANT& value)
{
    static BYTE params[] = VTS_BSTR VTS_VARIANT;
    InvokeHelper(0x12e, DISPATCH_METHOD, VT_EMPTY, NULL, params, pProperty, &value);
}
//---------------------------------------------------------------------------
CString PSS_WebBrowserBase::GetName()
{
    CString result;
    InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
long PSS_WebBrowserBase::GetHwnd()
{
    long result;
    InvokeHelper(DISPID_HWND, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
CString PSS_WebBrowserBase::GetFullName()
{
    CString result;
    InvokeHelper(0x190, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
CString PSS_WebBrowserBase::GetPath()
{
    CString result;
    InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::GetVisible()
{
    BOOL result;
    InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetVisible(BOOL value)
{
    static BYTE params[] = VTS_BOOL;
    InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::GetStatusBar()
{
    BOOL result;
    InvokeHelper(0x193, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetStatusBar(BOOL value)
{
    static BYTE params[] = VTS_BOOL;
    InvokeHelper(0x193, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
CString PSS_WebBrowserBase::GetStatusText()
{
    CString result;
    InvokeHelper(0x194, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetStatusText(LPCTSTR pValue)
{
    static BYTE params[] = VTS_BSTR;
    InvokeHelper(0x194, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, pValue);
}
//---------------------------------------------------------------------------
long PSS_WebBrowserBase::GetToolBar()
{
    long result;
    InvokeHelper(0x195, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetToolBar(long value)
{
    static BYTE params[] = VTS_I4;
    InvokeHelper(0x195, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::GetMenuBar()
{
    BOOL result;
    InvokeHelper(0x196, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetMenuBar(BOOL value)
{
    static BYTE params[] = VTS_BOOL;
    InvokeHelper(0x196, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::GetFullScreen()
{
    BOOL result;
    InvokeHelper(0x197, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetFullScreen(BOOL value)
{
    static BYTE params[] = VTS_BOOL;
    InvokeHelper(0x197, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
long PSS_WebBrowserBase::QueryStatusWB(long cmdID)
{
    long        result;
    static BYTE params[] = VTS_I4;
    InvokeHelper(0x1f5, DISPATCH_METHOD, VT_I4, (void*)&result, params, cmdID);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::ExecWB(long cmdID, long cmdExecOpt, VARIANT* pIn, VARIANT* pOut)
{
    static BYTE params[] = VTS_I4 VTS_I4 VTS_PVARIANT VTS_PVARIANT;
    InvokeHelper(0x1f6, DISPATCH_METHOD, VT_EMPTY, NULL, params, cmdID, cmdExecOpt, pIn, pOut);
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::ShowBrowserBar(VARIANT* pClsID, VARIANT* pShow, VARIANT* pSize)
{
    static BYTE params[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
    InvokeHelper(0x1f7, DISPATCH_METHOD, VT_EMPTY, NULL, params, pClsID, pShow, pSize);
}
//---------------------------------------------------------------------------
long PSS_WebBrowserBase::GetReadyState()
{
    long result;
    InvokeHelper(DISPID_READYSTATE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::GetOffline()
{
    BOOL result;
    InvokeHelper(0x226, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetOffline(BOOL value)
{
    static BYTE params[] = VTS_BOOL;
    InvokeHelper(0x226, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::GetSilent()
{
    BOOL result;
    InvokeHelper(0x227, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetSilent(BOOL value)
{
    static BYTE params[] = VTS_BOOL;
    InvokeHelper(0x227, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::GetRegisterAsBrowser()
{
    BOOL result;
    InvokeHelper(0x228, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetRegisterAsBrowser(BOOL value)
{
    static BYTE params[] = VTS_BOOL;
    InvokeHelper(0x228, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::GetRegisterAsDropTarget()
{
    BOOL result;
    InvokeHelper(0x229, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetRegisterAsDropTarget(BOOL value)
{
    static BYTE params[] = VTS_BOOL;
    InvokeHelper(0x229, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::GetTheaterMode()
{
    BOOL result;
    InvokeHelper(0x22a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetTheaterMode(BOOL value)
{
    static BYTE params[] = VTS_BOOL;
    InvokeHelper(0x22a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::GetAddressBar()
{
    BOOL result;
    InvokeHelper(0x22b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetAddressBar(BOOL value)
{
    static BYTE params[] = VTS_BOOL;
    InvokeHelper(0x22b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
BOOL PSS_WebBrowserBase::GetResizable()
{
    BOOL result;
    InvokeHelper(0x22c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
    return result;
}
//---------------------------------------------------------------------------
void PSS_WebBrowserBase::SetResizable(BOOL value)
{
    static BYTE params[] = VTS_BOOL;
    InvokeHelper(0x22c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, value);
}
//---------------------------------------------------------------------------
