//
// Created by Mason on 2022/5/5.
//

#ifndef QQ_API_SCRIPT_FILE_IO_H
#define QQ_API_SCRIPT_FILE_IO_H
#include "qq_music_model.h"
#include <fstream>
#include <iostream>
#include <vector>

inline void write_file_by_io(const std::string& file_name,
                      std::vector<std::string>& lines)
{
    std::ofstream input_file;
    input_file.open("./outputs/" + file_name, std::fstream::app);
    if (input_file.is_open()) {
        for(auto& musicItem: lines)
        {
            input_file << musicItem << std::endl;
        }
    } else {
        std::cerr << "Unable to open file";
    }
}


#endif //QQ_API_SCRIPT_FILE_IO_H
