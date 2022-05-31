//
// Created by Mason on 2022/5/11.
//
#include "config_reader.h"
#include "ConfigFile.h"
#include <iostream>


void ConfigReader::readConfigFiles() {
    try {
        ConfigFile cf(fileName);
        searchType = std::string(cf.Value("search_section", "search_type"));

        musicLoc = std::string(cf.Value("music_section", "location"));

        movieStartYear = std::string(cf.Value("movie_section", "start_year"));
        movieEndYear = std::string(cf.Value("movie_section", "end_year"));
        movieType = std::string(cf.Value("movie_section", "movie_type"));

        companyProvince = std::string(cf.Value("institution_section", "province"));
        companyType = std::string(cf.Value("institution_section", "searchType"));

        appPlatform = std::string(cf.Value("app_section", "platform"));
        appType= std::string(cf.Value("app_section", "app_type"));

        std::cout << musicLoc << std::endl;

        std::cout << movieStartYear << std::endl;
        std::cout << movieEndYear << std::endl;
        std::cout << movieType << std::endl;

        std::cout << companyProvince << std::endl;
        std::cout << companyType << std::endl;

        std::cout << stoi(searchType) << std::endl;
    } catch (const char * msg) {
        std::cerr << msg << std::endl;
    }
}

CategoryType ConfigReader::getCategory() const {
    auto typeId = std::stoi(searchType);
    CategoryType cateType;
    switch (typeId) {
        case 1:
            cateType = CategoryType::CategoryMusic;
            break;
        case 2:
            cateType = CategoryType::CategoryMovie;
            break;
        case 4:
            cateType = CategoryType::CategoryApp;
            break;
        case 5:
            cateType = CategoryType::CategoryMall;
            break;
        default:
            cateType = CategoryType::CategoryCompany;
            break;
    }
    return cateType;
}

MOVIE_INFO_TYPE ConfigReader::getMovieType() const {
    MOVIE_INFO_TYPE movieTypes;
    if (movieType == "动漫")
        movieTypes = MOVIE_INFO_TYPE::CARTOON;
    else if (movieType == "电影")
        movieTypes = MOVIE_INFO_TYPE::MOVIE;
    else if (movieType == "电视剧")
        movieTypes = MOVIE_INFO_TYPE::TV_SERIES;
    else if (movieType == "综艺")
        movieTypes = MOVIE_INFO_TYPE::TV_SHOW;
    else if (movieType == "纪录片")
        movieTypes = MOVIE_INFO_TYPE::RECORD;
    else
        movieTypes = MOVIE_INFO_TYPE::VIDEO;
    return movieTypes;
}

CompanyType ConfigReader::getCompanyType() const {
    CompanyType companyTypeEnum;
    if (companyType == "公司")
        companyTypeEnum = CompanyType::COMPANY_TYPE;
    else if (companyType == "学校")
        companyTypeEnum = CompanyType::SCHOOL_TYPE;
    else
        companyTypeEnum = CompanyType::HOSPITAL;
    return companyTypeEnum;
}

MUSIC_LOCATION ConfigReader::getMusicType() const {
    MUSIC_LOCATION musicLocation;
    if (musicLoc == "港台")
        musicLocation = MUSIC_LOCATION::HONGKONG;
    else
        musicLocation = MUSIC_LOCATION::MAINLAND;
    return musicLocation;
}