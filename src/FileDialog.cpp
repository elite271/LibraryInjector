#include "FileDialog.h"

FileDialog::FileDialog()
{
}

FileDialog::~FileDialog()
{
    CoTaskMemFree(pszFilePath);

    pItem->Release();

    pFileOpen->Release();

    CoUninitialize();
}

bool FileDialog::Init()
{
    hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    if (SUCCEEDED(hr))
    {
        hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL,
            IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        return true;
    }
    else
    {
        return false;
    }
}

void FileDialog::Show()
{
    if (SUCCEEDED(hr))
    {
        hr = pFileOpen->Show(nullptr);

        if (SUCCEEDED(hr))
        {
            hr = pFileOpen->GetResult(&pItem);

            if (SUCCEEDED(hr))
            {
                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                if (SUCCEEDED(hr))
                {
                    this->selectedPath = NormalizePath(pszFilePath);
                    //std::wcout << selectedPath << std::endl;
                }
            }
        }
    }
}
