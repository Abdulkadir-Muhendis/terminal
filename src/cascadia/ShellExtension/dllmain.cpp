// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "pch.h"
#include "OpenTerminalHere.h"
// NOTE: All this file is pretty egregiously taken from PowerToys's PowerRename,
// specifically:
//
// https://github.com/microsoft/PowerToys/blob/master/
//   src/modules/powerrename/dll/dllmain.cpp
//
// I'm not positive how much of it we need, but we definitely need:
// * a ClassFactory that can create our implementation of IExplorerCommand
// * a DllGetClassObject that will return the aforementioned class factory.

// std::atomic<DWORD> g_dwModuleRefCount = 0;
// HINSTANCE g_hInst = 0;

// extern "C" IMAGE_DOS_HEADER __ImageBase;
// void ModuleAddRef()
// {
//     g_dwModuleRefCount++;
// }

// void ModuleRelease()
// {
//     g_dwModuleRefCount--;
// }

// struct ShellExtClassFactory : winrt::implements<ShellExtClassFactory, IClassFactory>
// {
// public:
//     ShellExtClassFactory(_In_ REFCLSID clsid) :
//         m_clsid{ clsid } {};

//     // IClassFactory methods
//     IFACEMETHODIMP CreateInstance(_In_opt_ IUnknown* punkOuter,
//                                   _In_ REFIID riid,
//                                   _Outptr_ void** ppv)
//     {
//         *ppv = NULL;
//         HRESULT hr;
//         if (punkOuter)
//         {
//             hr = CLASS_E_NOAGGREGATION;
//         }
//         else if (m_clsid == __uuidof(OpenTerminalHere))
//         {
//             hr = winrt::make<OpenTerminalHere>()->QueryInterface(riid, ppv);
//         }
//         else
//         {
//             hr = CLASS_E_CLASSNOTAVAILABLE;
//         }
//         return hr;
//     }

//     IFACEMETHODIMP LockServer(BOOL bLock)
//     {
//         if (bLock)
//         {
//             ModuleAddRef();
//         }
//         else
//         {
//             ModuleRelease();
//         }
//         return S_OK;
//     }

// private:
//     CLSID m_clsid;
// };

// // !IMPORTANT! Make sure that DllGetClassObject is exported in <dllName>.def!
// HRESULT __stdcall DllGetClassObject(GUID const& clsid, GUID const& iid, void** result)
// {
//     *result = nullptr;
//     // !IMPORTANT! Explorer is going to call DllGetClassObject with the clsid of
//     // the class it wants to create, and the iid of IClassFactory. First we must
//     // return the ClassFactory here - later on, the ClassFactory will have
//     // CreateInstance called, where we can actually create the thing it
//     // requested in clsid.
//     auto pClassFactory = winrt::make<ShellExtClassFactory>(clsid);
//     return pClassFactory->QueryInterface(iid, result);
// }

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, _COM_Outptr_ void** ppv)
{
    // DebugBreak();
    auto& m = Microsoft::WRL::Module<Microsoft::WRL::InProc>::GetModule();

    auto result = m.GetClassObject(rclsid, riid, ppv);
    return result;
}

// STDAPI DllCanUnloadNow()
// {
//     return Microsoft::WRL::Module<Microsoft::WRL::InProc>::GetModule().Terminate() ? S_OK : S_FALSE;
// }

STDAPI_(BOOL)
DllMain(_In_opt_ HINSTANCE hinst, DWORD reason, _In_opt_ void*)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinst);
    }
    return TRUE;
}
