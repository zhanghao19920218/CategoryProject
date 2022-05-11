//
// Created by Mason on 2022/5/9.
//

#ifndef CATEGORY_SCRIPT_MOVIE_REQUEST_API_H
#define CATEGORY_SCRIPT_MOVIE_REQUEST_API_H
#include "constant.h"

/**
 * 请求电影接口
 * @param startYear 开始年份
 * @param endYear 结束年份
 * @param movieInfoType 电影信息类型
 */
void request_movies(const std::string& startYear,
                    const std::string& endYear,
                    const MOVIE_INFO_TYPE& movieInfoType);

#endif //CATEGORY_SCRIPT_MOVIE_REQUEST_API_H
