#include <windows.h>
#include <commdlg.h>
#include <shellapi.h>
#include <shobjidl.h>
#include <string>
#include "folderOpen.h"

std::string OpenFolder(HWND hWndParent)
{
    // Initialize COM
    CoInitialize(NULL);
    // Create a Common Item Dialog
    IFileDialog *pfd;
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));

    if (SUCCEEDED(hr))
    {
        // Set options for folder selection
        DWORD dwFlags;
        hr = pfd->GetOptions(&dwFlags);
        hr = pfd->SetOptions(dwFlags | FOS_PICKFOLDERS);

        // Show the dialog
        hr = pfd->Show(hWndParent);

        if (SUCCEEDED(hr))
        {
            // Get the selected folder
            IShellItem *psi;
            hr = pfd->GetResult(&psi);

            if (SUCCEEDED(hr))
            {
                // Get the folder path
                LPWSTR pszPath;
                hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);
                std::wstring folderPath(pszPath);
                std::string fp(folderPath.begin(), folderPath.end());
                if (SUCCEEDED(hr))
                {
                    CoTaskMemFree(pszPath);
                }

                psi->Release();
                return fp; // Folder opened successfully
            }
        }

        pfd->Release();
    }

    CoUninitialize();
    return ""; // Folder not opened
}