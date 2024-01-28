//
// Created by Alex on 04.05.2023.
//

#include "../../include/Repositories/FileException.h"

FileException::FileException(const std::string &new_message) : message(new_message)
{

}

const char *FileException::what()
{
    return message.c_str();
}
