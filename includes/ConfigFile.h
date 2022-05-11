//
// Created by Mason on 2022/5/10.
//

#ifndef CONFIGREADER_CONFIGFILE_H
#define CONFIGREADER_CONFIGFILE_H

#include <string>
#include <map>

#include "Chamelon.h"

class ConfigFile {
private:
    std::map<std::string,Chameleon> _content;

public:
    explicit ConfigFile(const std::string & configFile);

    const Chameleon & Value(const std::string& section,
                            const std::string& entry) const;

    /**
     * Reading section elements to create file
     * @param section
     * @param entry
     * @param value
     * @return
     */
    const Chameleon & Value(const std::string& section,
                           const std::string& entry,
                           double value);

    const Chameleon & Value(const std::string& section,
                            const std::string& entry,
                            const std::string& value);
};

#endif //CONFIGREADER_CONFIGFILE_H
