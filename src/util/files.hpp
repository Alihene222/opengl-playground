#ifndef FILES_HPP
#define FILES_HPP

#include <iostream>
#include <fstream>
#include <sstream>

namespace util {
    inline std::string read_file(std::string filePath) {
        std::string text;

        std::fstream stream(filePath, std::ios::in);
        if(stream.is_open()) {
            std::stringstream string_stream;
            string_stream << stream.rdbuf();
            text = string_stream.str();
            stream.close();
        } else {
            fprintf(stderr, "Impossible to open file %s\n", filePath.c_str());
            exit(-1);
        }

        return text;
    }
}

#endif