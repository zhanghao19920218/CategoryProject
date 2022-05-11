//
// Created by Mason on 2022/5/10.
//

#include "ConfigFile.h"
#include <fstream>

std::string trim(const std::string &source,
                 const char *delims = " \t\r\n") {
    std::string result(source);
    // 查找尾部
    std::string::size_type index = result.find_last_not_of(delims);
    if(index != std::string::npos)
        result.erase(++index);

    index = result.find_first_not_of(delims);
    // 查找头部
    if(index != std::string::npos)
        result.erase(0, index);
    else
        result.erase();
    return result;
}

ConfigFile::ConfigFile(const std::string &configFile) {
    std::ifstream file(configFile);

    std::string line;
    std::string name;
    std::string value;
    std::string inSection;
    unsigned posEqual;
    while (std::getline(file, line)) {

        if (!line.length()) continue;

        if (line[0] == '#') continue;
        if (line[0] == ';') continue;

        if (line[0] == '[') {
            inSection = trim(line.substr(1,
                                         line.find(']') - 1));
            continue;
        }

        posEqual = line.find('=');
        name = trim(line.substr(0, posEqual));
        value = trim(line.substr(posEqual + 1));

        auto tempKey = inSection + "/" + name;
        _content[tempKey] = Chameleon(value);

    }
}

const Chameleon &ConfigFile::Value(const std::string &section, const std::string &entry) const {
    auto tempKey = section + "/" + entry;
    auto ci = _content.find(tempKey);

    if (ci == _content.end()) throw "does not exist";

    return ci->second;
}

const Chameleon &ConfigFile::Value(const std::string &section, const std::string &entry, double value) {
    try {
        return Value(section, entry);
    } catch (const char *) {
        return _content.insert(std::make_pair(section + '/' + entry, Chameleon(value))).first->second;
    }
}

const Chameleon &
ConfigFile::Value(const std::string &section, const std::string &entry, const std::string &value) {
    try {
        return Value(section, entry);
    } catch (const char *) {
        return _content.insert(std::make_pair(section + '/' + entry, Chameleon(value))).first->second;
    }
}
