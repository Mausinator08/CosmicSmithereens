#include "stdafx.h"

#include "FSPlatform.h"
#include "windows.h"
#include "sys/stat.h"
#include "Functions/Strings.h"

PathStylesEnum PathStyle()
{
    switch (cwk_path_get_style())
    {
    case cwk_path_style::CWK_STYLE_WINDOWS:
    {
        return PathStylesEnum::WINDOWS;
    }
    break;
    case cwk_path_style::CWK_STYLE_UNIX:
    {
        return PathStylesEnum::UNIX;
    }
    default:
    {
        return PathStylesEnum::UNKNOWN;
    }
    break;
    }
}

const std::wstring ConvertToPathStyle(const std::wstring path)
{
    switch (PathStyle())
    {
    case PathStylesEnum::WINDOWS:
    {
        return s2ws(std::regex_replace(ws2s(path), std::regex("/"), "\\"));
    }
    break;
    case PathStylesEnum::UNIX:
    {
        return s2ws(std::regex_replace(ws2s(path), std::regex("\\"), "/"));
    }
    break;
    default:
    {
        return NULL;
    }
    break;
    }
}

bool MakeDirectory(const std::wstring path)
{
    std::wstring finalPath = ConvertToPathStyle(path);

    switch (PathStyle())
    {
    case PathStylesEnum::WINDOWS:
    {
        return CreateDirectoryW(finalPath.c_str(), NULL) != 0 ? true : (GetLastError() == ERROR_ALREADY_EXISTS ? true : false);
    }
    break;
    case PathStylesEnum::UNIX:
    {
        return mkdir(ws2s(finalPath).c_str()) != -1 ? true : (errno == EEXIST ? true : false);
    }
    break;
    default:
    {
        return false;
    }
    break;
    }
}
