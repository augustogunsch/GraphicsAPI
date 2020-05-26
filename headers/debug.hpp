#pragma once

class debug {
public:
    static void queryErrors(const char* customMsg = 0);
    static void throwError(const char* customMsg = 0);
    static void warn(const char* msg);
    static void log(const char* msg);
};