#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shobjidl.h>
#include <iostream>
#include <algorithm>
#include <string>


inline std::wstring NormalizePath(std::wstring path)
{
	std::replace(path.begin(), path.end(), L'\\', L'/');
	return path;
}

class FileDialog
{
public:
	FileDialog();
	~FileDialog();

	bool Init();
	void Show();

	const std::wstring& GetSelectedPath() const { return selectedPath;  }

private:
	HRESULT hr;
	IFileOpenDialog* pFileOpen = nullptr;
	IShellItem* pItem = nullptr;
	PWSTR pszFilePath = nullptr;
	std::wstring selectedPath;
};
