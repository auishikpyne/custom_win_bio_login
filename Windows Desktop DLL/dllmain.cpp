// dllmain.cpp
#include "pch.h"
#include "CredentialProvider.h"
#include "Logging.h" // Include the Logging header
#include <fstream>
#include <sstream>
#include <shlwapi.h>
#include <strsafe.h>
#include "Utilities.h"

const CLSID CLSID_CredentialProvider = { 0xfac9c154, 0xec56, 0x4f82, { 0x8a, 0xe8, 0x76, 0x61, 0x31, 0x39, 0x44, 0x54 } };

HINSTANCE g_hInst = NULL;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_hInst = hModule;
        LogEvent(L"DLL_PROCESS_ATTACH");
        DisableThreadLibraryCalls(hModule);
        break;
    case DLL_PROCESS_DETACH:
        LogEvent(L"DLL_PROCESS_DETACH");
        break;
    }
    return TRUE;
}

HRESULT CreateRegistryKey(HKEY hKeyRoot, LPCWSTR subKey, LPCWSTR valueName, LPCWSTR value)
{
    HKEY hKey;
    LONG lRes = RegCreateKeyEx(hKeyRoot, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
    if (lRes != ERROR_SUCCESS)
        return HRESULT_FROM_WIN32(lRes);

    if (valueName != NULL && value != NULL)
    {
        lRes = RegSetValueEx(hKey, valueName, 0, REG_SZ, (const BYTE*)value, (DWORD)((wcslen(value) + 1) * sizeof(wchar_t)));
        RegCloseKey(hKey);
        if (lRes != ERROR_SUCCESS)
            return HRESULT_FROM_WIN32(lRes);
    }
    else if (valueName == NULL && value != NULL)
    {
        lRes = RegSetValueEx(hKey, NULL, 0, REG_SZ, (const BYTE*)value, (DWORD)((wcslen(value) + 1) * sizeof(wchar_t)));
        RegCloseKey(hKey);
        if (lRes != ERROR_SUCCESS)
            return HRESULT_FROM_WIN32(lRes);
    }

    return S_OK;
}

HRESULT RegisterServer()
{
    LogEvent(L"RegisterServer called");

    WCHAR szModule[MAX_PATH];
    GetModuleFileName(g_hInst, szModule, ARRAYSIZE(szModule));
    LogEvent(L"GetModuleFileName called");

    WCHAR szCLSID[MAX_PATH];
    StringFromGUID2(CLSID_CredentialProvider, szCLSID, ARRAYSIZE(szCLSID));
    LogEvent(L"StringFromGUID2 called");

    WCHAR szSubKey[MAX_PATH];

    // Create the CLSID key
    StringCchPrintf(szSubKey, ARRAYSIZE(szSubKey), L"CLSID\\%s", szCLSID);
    HRESULT hr = CreateRegistryKey(HKEY_CLASSES_ROOT, szSubKey, NULL, L"CredentialProvider");
    LogEvent(L"CLSID key created");

    if (SUCCEEDED(hr))
    {
        // Create the InprocServer32 key
        StringCchPrintf(szSubKey, ARRAYSIZE(szSubKey), L"CLSID\\%s\\InprocServer32", szCLSID);
        hr = CreateRegistryKey(HKEY_CLASSES_ROOT, szSubKey, NULL, szModule);
        LogEvent(L"InprocServer32 key created");

        if (SUCCEEDED(hr))
        {
            hr = CreateRegistryKey(HKEY_CLASSES_ROOT, szSubKey, L"ThreadingModel", L"Apartment");
            LogEvent(L"ThreadingModel set to Apartment");
        }
    }

    // Register the provider in the Credential Providers key
    if (SUCCEEDED(hr))
    {
        StringCchPrintf(szSubKey, ARRAYSIZE(szSubKey), L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Authentication\\Credential Providers\\%s", szCLSID);
        hr = CreateRegistryKey(HKEY_LOCAL_MACHINE, szSubKey, NULL, szModule); // Save DLL path here
        LogEvent(L"Credential Providers key created and DLL path saved");
    }

    LogEvent(L"RegisterServer completed with result " + ToWString(hr));
    return hr;
}

HRESULT UnregisterServer()
{
    LogEvent(L"UnregisterServer called");

    WCHAR szCLSID[MAX_PATH];
    StringFromGUID2(CLSID_CredentialProvider, szCLSID, ARRAYSIZE(szCLSID));
    LogEvent(L"StringFromGUID2 called");

    WCHAR szSubKey[MAX_PATH];

    // Delete the CLSID key
    StringCchPrintf(szSubKey, ARRAYSIZE(szSubKey), L"CLSID\\%s", szCLSID);
    LONG lResult = SHDeleteKey(HKEY_CLASSES_ROOT, szSubKey);
    LogEvent(L"CLSID key deleted");

    if (lResult == ERROR_SUCCESS || lResult == ERROR_FILE_NOT_FOUND)
    {
        // Delete the provider key from Credential Providers
        StringCchPrintf(szSubKey, ARRAYSIZE(szSubKey), L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Authentication\\Credential Providers\\%s", szCLSID);
        lResult = SHDeleteKey(HKEY_LOCAL_MACHINE, szSubKey);
        LogEvent(L"Credential Providers key deleted");
    }

    LogEvent(L"UnregisterServer completed with result " + ToWString(lResult));
    return HRESULT_FROM_WIN32(lResult);
}

extern "C" HRESULT __declspec(dllexport) __stdcall DllRegisterServer()
{
    return RegisterServer();
}

extern "C" HRESULT __declspec(dllexport) __stdcall DllUnregisterServer()
{
    return UnregisterServer();
}
