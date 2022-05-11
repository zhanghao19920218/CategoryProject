//
// Created by Mason on 2022/5/5.
//

#ifndef QQ_API_SCRIPT_CONSTANT_H
#define QQ_API_SCRIPT_CONSTANT_H
#include <string>

// 请求地址
//const std::string& URL_ADDRESS = "localhost";

// 请求端口号
const unsigned URL_PORT = 3300;

const unsigned COMPANY_PORT = 9000;
// 机构地址
#define BASE_COMPANY_URL "localhost"
// 豆瓣的地址
#define DOUBAN_BASE_URL "https://movie.douban.com"

// 获取AMAPKEY
#define AMAP_KEY "312f0bd088b5a87540dec7e1e9e9fe3b"


enum MovieType {
    TV,
    Movie,
    TVShow
};

// 请求的商业类型
enum CompanyType {
    SCHOOL_TYPE,
    COMPANY_TYPE,
    HOSPITAL
};

/**
 * 音乐请求类型
 * HONGKONG, 港台
 * MAINLAND, 内地
 */
enum MUSIC_LOCATION {
    HONGKONG,
    MAINLAND
};

/**
 * 豆瓣对于的电影
 */
enum MOVIE_INFO_TYPE {
    MOVIE,
    TV_SHOW,
    TV_SERIES,
    CARTOON,
    RECORD,
    VIDEO
};

/**
 * 获取类型
 */

enum CategoryType {
    CategoryMovie,
    CategoryMusic,
    CategoryCompany
};

#endif //QQ_API_SCRIPT_CONSTANT_H
