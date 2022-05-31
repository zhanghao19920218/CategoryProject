//
// Created by Mason on 2022/5/11.
//

#ifndef CATEGORY_SCRIPT_CONFIG_READER_H
#define CATEGORY_SCRIPT_CONFIG_READER_H
#include <string>
#include <utility>
#include "constant.h"

class ConfigReader {
public:
    explicit ConfigReader(std::string  fileName): fileName(std::move(fileName)) {
        readConfigFiles();
    };
    CategoryType getCategory() const;
    MOVIE_INFO_TYPE getMovieType() const;
    CompanyType getCompanyType() const;
    MUSIC_LOCATION getMusicType() const;
public:
    std::string movieStartYear;
    std::string movieEndYear;
    std::string companyProvince;
    std::string appPlatform;
    std::string appType;
private:
    void readConfigFiles();
private:
    std::string fileName;
    std::string searchType;
    std::string movieType;
    std::string musicLoc;
    std::string companyType;
};

#endif //CATEGORY_SCRIPT_CONFIG_READER_H
