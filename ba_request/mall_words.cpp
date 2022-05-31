//
// Created by Mason on 2022/5/31.
//
#include "mall_words.h"
#include "http_error.h"
#include "ba_request.h"
#include "file_io.h"
#include "amap_city_model.h"
#include "request_api.h"
#include <regex>
#include "timer_loop.h"
#include <codecvt>

/**
 *
 * @param mallType
 * @param searchName
 * @param mallNames
 * @param returnValue
 */
void request_mall_list(const MallType &mallType,
                       const std::string &searchName,
                       std::vector<std::string> &mallNames,
                       int &returnValue) {
    HTTP_STATUS status;
    std::vector<std::pair<std::string, std::string>> params{
            {"mall",     mallType == MallType::TMallType ? "tmall" : "jd"},
            {"tag_name", searchName},
    };

    std::string request_api{"/product"};
    CompanyModel ret = BARequest::share(SEARCHTYPE::MALL).post<CompanyModel>(request_api,
                                                                                status,
                                                                                params);
    if (ret.data.empty()) {
        returnValue = -1;
        return;
    }

    if (status == HTTP_STATUS::SUCCESS) {
        for (auto &appName: ret.data) {
            mallNames.push_back(appName);
        }
    }
}

void request_by_name(const std::string& searchName)
{
    std::vector<std::string> taobaoWords{};
    std::vector<std::string> jdWords{};
    int retValue = 0;
    request_mall_list(MallType::TMallType,
                      searchName,
                      taobaoWords,
                      retValue);
    write_file_by_io("taobao.txt", taobaoWords);
    request_mall_list(MallType::JDMallType,
                      searchName,
                      jdWords,
                      retValue);
    write_file_by_io("jdmall.txt", jdWords);
}

void request_malls() {
    // 获取汉字区间进行search
    const auto k_chinese_encoding_begin = 0x4E00;
    const auto k_chinese_testcase_end = k_chinese_encoding_begin + 2000;
    const auto k_chinese_encoding_end = 0x9FFF;
    for (int i = k_chinese_encoding_begin; i <= k_chinese_testcase_end; i ++) {
        uint16_t unicode = i;
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
        std::string utf8 = convert.to_bytes(unicode);
        request_by_name(utf8);
    }
}