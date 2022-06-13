#pragma once

enum class PathStylesEnum
{
    UNKNOWN,
    WINDOWS,
    UNIX
};

/**
     * @brief Detect OS path seperator.
     * @return WINDOWS, UNIX or UNKNOWN
     */
PathStylesEnum PathStyle();

/**
     * @brief Converts path to OS path style.
     * @param path The path to convert.
     * @return The resulting path.
     */
const std::wstring ConvertToPathStyle(const std::wstring path);

/**
     * @brief Creates a directory or directories if path contains multiple new directories.
     * @param path The path to the new directory or directories.
     * @return true if successful, false if unsuccessful.
     */
bool MakeDirectory(const std::wstring path);
