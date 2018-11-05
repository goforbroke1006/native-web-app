//
// Created by goforbroke on 06.11.18.
//

#ifndef SLIGHT_ANIMATION_FILESYSTEM_H
#define SLIGHT_ANIMATION_FILESYSTEM_H

#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <winbase.h>
#else

#include <sys/stat.h>

#endif


namespace filesystem {
    bool isFileExists(const std::string &filename) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        GetFileAttributes(filename);
        return !(
                INVALID_FILE_ATTRIBUTES == GetFileAttributes(filename)
                && ERROR_FILE_NOT_FOUND == GetLastError()
                );
#else
        struct stat buffer;
        return (stat(filename.c_str(), &buffer) == 0);
#endif
    }
}

#endif //SLIGHT_ANIMATION_FILESYSTEM_H
