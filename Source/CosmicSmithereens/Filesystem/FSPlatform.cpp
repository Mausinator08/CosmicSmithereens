#include "stdafx.h"

#include "FSPlatform.h"
#include "windows.h"
#include "sys/stat.h"

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

const std::string ConvertToPathStyle(const std::string path)
{
    switch (PathStyle())
    {
    case PathStylesEnum::WINDOWS:
    {
        return std::regex_replace(path, std::regex("/"), "\\");
    }
    break;
    case PathStylesEnum::UNIX:
    {
        return std::regex_replace(path, std::regex("\\"), "/");
    }
    break;
    default:
    {
        return NULL;
    }
    break;
    }
}

bool MakeDirectory(const std::string path)
{
    std::string finalPath = ConvertToPathStyle(path);

    switch (PathStyle())
    {
    case PathStylesEnum::WINDOWS:
    {
        return CreateDirectoryA(finalPath.c_str(), NULL) != 0 ? true : (GetLastError() == ERROR_ALREADY_EXISTS ? true : false);
    }
    break;
    case PathStylesEnum::UNIX:
    {
        return mkdir(finalPath.c_str()) != -1 ? true : (errno == EEXIST ? true : false);
    }
    break;
    default:
    {
        return false;
    }
    break;
    }
}
