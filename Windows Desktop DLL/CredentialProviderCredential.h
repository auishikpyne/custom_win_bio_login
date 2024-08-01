//credentialprovidecredential.h

#ifndef CREDENTIAL_PROVIDER_CREDENTIAL_H
#define CREDENTIAL_PROVIDER_CREDENTIAL_H

#include <windows.h>
#include <credentialprovider.h>
#include <winbio.h>
#include <strsafe.h>
#include <string> // Include this header for std::wstring

class CredentialProviderCredential : public ICredentialProviderCredential
{
public:
    CredentialProviderCredential();
    virtual ~CredentialProviderCredential();

    void ShowMessageAfterPinEntry(const std::wstring& message);
    // IUnknown
    IFACEMETHODIMP_(ULONG) AddRef();
    IFACEMETHODIMP_(ULONG) Release();
    IFACEMETHODIMP QueryInterface(REFIID riid, void** ppv);

    // ICredentialProviderCredential
    IFACEMETHODIMP Advise(ICredentialProviderCredentialEvents* pcpce);
    IFACEMETHODIMP UnAdvise();
    IFACEMETHODIMP SetSelected(BOOL* pbAutoLogon);
    IFACEMETHODIMP SetDeselected();
    IFACEMETHODIMP GetFieldState(DWORD dwFieldID, CREDENTIAL_PROVIDER_FIELD_STATE* pcpfs, CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE* pcpfis);
    IFACEMETHODIMP GetStringValue(DWORD dwFieldID, PWSTR* ppwsz);
    IFACEMETHODIMP GetBitmapValue(DWORD dwFieldID, HBITMAP* phbmp);
    IFACEMETHODIMP GetCheckboxValue(DWORD dwFieldID, BOOL* pbChecked, PWSTR* ppwszLabel);
    IFACEMETHODIMP GetSubmitButtonValue(DWORD dwFieldID, DWORD* pdwAdjacentTo);
    IFACEMETHODIMP GetComboBoxValueCount(DWORD dwFieldID, DWORD* pcItems, DWORD* pdwSelectedItem);
    IFACEMETHODIMP GetComboBoxValueAt(DWORD dwFieldID, DWORD dwItem, PWSTR* ppwszItem);
    IFACEMETHODIMP CommandLinkClicked(DWORD dwFieldID);
    IFACEMETHODIMP GetSerialization(
        CREDENTIAL_PROVIDER_GET_SERIALIZATION_RESPONSE* pcpgsr,
        CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* pcpcs,
        PWSTR* ppwszOptionalStatusText,
        CREDENTIAL_PROVIDER_STATUS_ICON* pcpsiOptionalStatusIcon);
    IFACEMETHODIMP GetFieldOptions(DWORD dwFieldID, CREDENTIAL_PROVIDER_CREDENTIAL_FIELD_OPTIONS* pcpfo);

private:
    long _cRef;

    // Add declaration for the new method
    //void ShowMessageAfterPinEntry(const std::wstring& message);
};

#endif // CREDENTIAL_PROVIDER_CREDENTIAL_H

