// CredentialProviderCredential.cpp
#include "pch.h" // Include the precompiled header
#include "CredentialProviderCredential.h"
#include <windows.h> // For MessageBox
#include "Logging.h" // Include the Logging header
#include "Utilities.h" // Include the Utilities header for ToWString

CredentialProviderCredential::CredentialProviderCredential() : _cRef(1)
{
    LogEvent(L"CredentialProviderCredential constructor called");
}

CredentialProviderCredential::~CredentialProviderCredential()
{
    LogEvent(L"CredentialProviderCredential destructor called");
}

IFACEMETHODIMP_(ULONG) CredentialProviderCredential::AddRef()
{
    LogEvent(L"CredentialProviderCredential::AddRef called");
    return InterlockedIncrement(&_cRef);
}

IFACEMETHODIMP_(ULONG) CredentialProviderCredential::Release()
{
    LogEvent(L"CredentialProviderCredential::Release called");
    long cRef = InterlockedDecrement(&_cRef);
    if (!cRef)
    {
        delete this;
    }
    return cRef;
}

IFACEMETHODIMP CredentialProviderCredential::QueryInterface(REFIID riid, void** ppv)
{
    LogEvent(L"CredentialProviderCredential::QueryInterface called");
    if (riid == IID_IUnknown || riid == IID_ICredentialProviderCredential)
    {
        *ppv = static_cast<ICredentialProviderCredential*>(this);
        AddRef();
        return S_OK;
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
}

IFACEMETHODIMP CredentialProviderCredential::Advise(ICredentialProviderCredentialEvents* pcpce)
{
    LogEvent(L"CredentialProviderCredential::Advise called");
    return E_NOTIMPL;
}

IFACEMETHODIMP CredentialProviderCredential::UnAdvise()
{
    LogEvent(L"CredentialProviderCredential::UnAdvise called");
    return E_NOTIMPL;
}

IFACEMETHODIMP CredentialProviderCredential::SetSelected(BOOL* pbAutoLogon)
{
    LogEvent(L"CredentialProviderCredential::SetSelected called");
    return E_NOTIMPL;
}

IFACEMETHODIMP CredentialProviderCredential::SetDeselected()
{
    LogEvent(L"CredentialProviderCredential::SetDeselected called");
    return E_NOTIMPL;
}

IFACEMETHODIMP CredentialProviderCredential::GetFieldState(DWORD dwFieldID, CREDENTIAL_PROVIDER_FIELD_STATE* pcpfs, CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE* pcpfis)
{
    LogEvent(L"CredentialProviderCredential::GetFieldState called with field ID: " + ToWString(dwFieldID));
    return E_NOTIMPL;
}

IFACEMETHODIMP CredentialProviderCredential::GetStringValue(DWORD dwFieldID, PWSTR* ppwsz)
{
    LogEvent(L"CredentialProviderCredential::GetStringValue called with field ID: " + ToWString(dwFieldID));
    return E_NOTIMPL;
}

IFACEMETHODIMP CredentialProviderCredential::GetBitmapValue(DWORD dwFieldID, HBITMAP* phbmp)
{
    LogEvent(L"CredentialProviderCredential::GetBitmapValue called with field ID: " + ToWString(dwFieldID));
    return E_NOTIMPL;
}

IFACEMETHODIMP CredentialProviderCredential::GetCheckboxValue(DWORD dwFieldID, BOOL* pbChecked, PWSTR* ppwszLabel)
{
    LogEvent(L"CredentialProviderCredential::GetCheckboxValue called with field ID: " + ToWString(dwFieldID));
    return E_NOTIMPL;
}

IFACEMETHODIMP CredentialProviderCredential::GetSubmitButtonValue(DWORD dwFieldID, DWORD* pdwAdjacentTo)
{
    LogEvent(L"CredentialProviderCredential::GetSubmitButtonValue called with field ID: " + ToWString(dwFieldID));
    return E_NOTIMPL;
}

IFACEMETHODIMP CredentialProviderCredential::GetComboBoxValueCount(DWORD dwFieldID, DWORD* pcItems, DWORD* pdwSelectedItem)
{
    LogEvent(L"CredentialProviderCredential::GetComboBoxValueCount called with field ID: " + ToWString(dwFieldID));
    return E_NOTIMPL;
}

IFACEMETHODIMP CredentialProviderCredential::GetComboBoxValueAt(DWORD dwFieldID, DWORD dwItem, PWSTR* ppwszItem)
{
    LogEvent(L"CredentialProviderCredential::GetComboBoxValueAt called with field ID: " + ToWString(dwFieldID) + L", item: " + ToWString(dwItem));
    return E_NOTIMPL;
}

IFACEMETHODIMP CredentialProviderCredential::CommandLinkClicked(DWORD dwFieldID)
{
    LogEvent(L"CredentialProviderCredential::CommandLinkClicked called with field ID: " + ToWString(dwFieldID));
    return E_NOTIMPL;
}

IFACEMETHODIMP CredentialProviderCredential::GetSerialization(
    CREDENTIAL_PROVIDER_GET_SERIALIZATION_RESPONSE* pcpgsr,
    CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* pcpcs,
    PWSTR* ppwszOptionalStatusText,
    CREDENTIAL_PROVIDER_STATUS_ICON* pcpsiOptionalStatusIcon)
{
    LogEvent(L"GetSerialization called");

    // Simulate PIN validation
    bool isPinValid = true; // Replace with actual PIN validation logic

    if (isPinValid)
    {
        LogEvent(L"PIN is valid, preparing to show message.");
        ShowMessageAfterPinEntry(L"PIN entered successfully!");
    }
    else
    {
        LogEvent(L"PIN is invalid, preparing to show message.");
        ShowMessageAfterPinEntry(L"Invalid PIN. Please try again.");
    }

    *pcpgsr = CPGSR_RETURN_NO_CREDENTIAL_FINISHED;
    return S_OK;
}

void CredentialProviderCredential::ShowMessageAfterPinEntry(const std::wstring& message)
{
    LogEvent(L"ShowMessageAfterPinEntry called");
    MessageBox(NULL, message.c_str(), L"Notification", MB_OK);
    LogEvent(L"Message box displayed");
}


