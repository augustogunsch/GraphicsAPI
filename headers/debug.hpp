#pragma once

class debug {
public:
    static void queryErrors(const char* customMsg = NULL);
    static void throwError(const char* customMsg = NULL);
    static void warn(const char* msg);
    static void log(const char* msg);
};