//
// Created by Mason on 2022/5/9.
//

#include "movie_request_api.h"
#include "http_error.h"
#include "ba_request.h"
#include "qq_music_model.h"
#include <vector>
#include "douban_api.h"
#include "timer_loop.h"
#include "file_io.h"
#include <string>

/**
 * 根据请求的开始文件目录进行获取影视结果
 * @param pageStart 开始请求的列表数目
 * @param tag 推荐类型
 * @param pageLimit 页面限制
 * @param movieType 电影类型
 * @param endYear 结束年代
 */
std::vector<std::string> request_movie_times(unsigned pageStart,
                                             const std::string &tag,
                                             const std::string &year,
                                             const std::string &endYear) {
    auto year_range = year + "," + endYear;
    std::vector<std::string> ret{};
    HTTP_STATUS status;
    std::string type;
    std::vector<std::pair<std::string, std::string>> params{
            {"sort",       "U"},
            {"range",      "0,10"},
            {"tags",       tag},
            {"start",      std::to_string(pageStart)},
            {"year_range", year_range}
    };

    MovieSubjectList tmp = BARequest::share(SEARCHTYPE::DOUBAN).get<MovieSubjectList>("/j/new_search_subjects",
                                                                                      status,
                                                                                      params);
    for (const auto &movieItem: tmp.data) {
        ret.push_back(movieItem.title);
    }

    if (status == HTTP_STATUS::SUCCESS) {
        std::cout << "当前抓取的文件长度:" << pageStart << std::endl;
    }
    return ret;
}

// 定时器获取请求
void write_file_movie(unsigned pageStart,
                      const MOVIE_INFO_TYPE& movieInfoType,
                      const std::string& startYear,
                      const std::string& endYear) {
    std::string typeName{};
    switch (movieInfoType) {
        case MOVIE_INFO_TYPE::CARTOON:
            typeName = "动漫";
            break;
        case MOVIE_INFO_TYPE::MOVIE:
            typeName = "电影";
            break;
        case MOVIE_INFO_TYPE::TV_SERIES:
            typeName = "电视剧";
            break;
        case MOVIE_INFO_TYPE::TV_SHOW:
            typeName = "综艺";
            break;
        case MOVIE_INFO_TYPE::RECORD:
            typeName = "纪录片";
            break;
        case MOVIE_INFO_TYPE::VIDEO:
            typeName = "短片";
            break;
    }
    auto ret = request_movie_times(pageStart,
                                   typeName,
                                   startYear,
                                   endYear);
    write_file_by_io(typeName + startYear + "_" + endYear + ".txt", ret);
}

void request_movies(const std::string& startYear,
                    const std::string& endYear,
                    const MOVIE_INFO_TYPE& movieInfoType) {
    unsigned startPage = 0;
    unsigned pageNum = 20;
    for (int i = 1; i < 1000; ++i) {
        TimeLoop timeLoop(10000, false, &write_file_movie, startPage, movieInfoType, startYear, endYear);
        startPage = startPage + pageNum;
    }
}