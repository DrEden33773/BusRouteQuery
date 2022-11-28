/**
 * @file StrFile_NonBinary_IO_Test.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Utility/FileManager.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace Test {

void StrFile_NonBinary_IO_Test() {
    Utility::FileManager::path_init();

    using std::fstream;

    const auto& src_path = Utility::FileManager::Filename::TestSrcFile;
    fstream     src_file;
    std::string greeting_string = "你好，世界！";

    src_file.open(src_path, fstream::out | fstream::trunc);
    if (!src_file.is_open()) {
        throw std::runtime_error("cannot open file");
    }
    src_file << greeting_string;
    src_file.close();

    std::string receiver;
    src_file.open(src_path, fstream::in);
    if (!src_file.is_open()) {
        throw std::runtime_error("cannot open file");
    }
    src_file >> receiver;
    src_file.close();

    std::cout << "origin: " << greeting_string << std::endl;
    std::cout << "received: " << receiver << std::endl;

    std::cout << std::endl;
}

} // namespace Test