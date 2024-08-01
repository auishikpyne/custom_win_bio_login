// CredentialProvider.h
#ifndef CREDENTIAL_PROVIDER_H
#define CREDENTIAL_PROVIDER_H

#include <windows.h>
#include <credentialprovider.h>
#include <winbio.h>
#include <strsafe.h>
#include <string>

class CredentialProvider : public ICredentialProvider
{
public:
    CredentialProvider();
    virtual ~CredentialProvider();

    // IUnknown
    IFACEMETHODIMP_(ULONG) AddRef();
    IFACEMETHODIMP_(ULONG) Release();
    IFACEMETHODIMP QueryInterface(REFIID riid, void** ppv);

    // ICredentialProvider
    IFACEMETHODIMP SetUsageScenario(CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus, DWORD dwFlags);
    IFACEMETHODIMP SetSerialization(const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* pcpcs);
    IFACEMETHODIMP Advise(ICredentialProviderEvents* pcpe, UINT_PTR upAdviseContext);
    IFACEMETHODIMP UnAdvise();
    IFACEMETHODIMP GetFieldDescriptorCount(DWORD* pdwCount);
    IFACEMETHODIMP GetFieldDescriptorAt(DWORD dwIndex, CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR** ppcpfd);
    IFACEMETHODIMP GetCredentialCount(DWORD* pdwCount, DWORD* pdwDefault, BOOL* pbAutoLogonWithDefault);
    IFACEMETHODIMP GetCredentialAt(DWORD dwIndex, ICredentialProviderCredential** ppcpc);

private:
    long _cRef;
};

// Utility functions
extern void LogEvent(const std::wstring& message);
extern std::wstring ToWString(long value);

#endif // CREDENTIAL_PROVIDER_H
