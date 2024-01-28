//
// Created by Alex on 04.05.2023.
//
#pragma once

#ifndef A7_915_MINDRILA_MIHAIL_1_FILEEXCEPTION_H
#define A7_915_MINDRILA_MIHAIL_1_FILEEXCEPTION_H

#include <exception>
#include <string>

class FileException : public std::exception
{
protected:
    std::string message;
public:
    FileException(const std::string& new_message);
    virtual const char* what();
};


#endif //A7_915_MINDRILA_MIHAIL_1_FILEEXCEPTION_H
