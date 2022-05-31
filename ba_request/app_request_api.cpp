//
// Created by Mason on 2022/5/30.
//

#include "app_request_api.h"
#include <string>
#include "http_error.h"
#include "ba_request.h"
#include "file_io.h"
#include <regex>

/**
 * 请求app列表
 * @param platform
 * @param appType
 * @param pageNo
 * @param appNames
 */
void request_app_list(const std::string& platform,
                      const std::string& appType,
                      int pageNo,
                      std::vector<std::string>& appNames,
                      int& returnValue) {
    HTTP_STATUS status;
    std::vector<std::pair<std::string, std::string>> params{
            {"platform", platform},
            {"app_type", appType},
            {"page", std::to_string(pageNo)}
    };

    std::string request_api{ "/app" };
    CompanyModel ret = BARequest::share(SEARCHTYPE::COMPANY).post<CompanyModel>(request_api,
                                                                                status,
                                                                                params);
    if (ret.data.empty()) {
        returnValue = -1;
        return;
    }

    if (status == HTTP_STATUS::SUCCESS) {
        for (auto &appName: ret.data) {
            appNames.push_back(appName);
        }
    }
}



void request_apps(const std::string& platform,
                  const std::string& appType)
{
    std::vector<std::string> appNames{};
    int retValue = 0;
    if (platform == "ios") {
        request_app_list(platform,
                         appType,
                         1,
                         appNames,
                         retValue);
        const std::string& fileName = appType == "game" ? "ios_game.txt" : "ios_app.txt";
        write_file_by_io(fileName,
                         appNames);
    } else if (platform == "android") {
        const std::string& fileName = appType == "game" ? "android_game.txt" : "android_app.txt";
        for (int i = 1; i < 50; ++i) {
            std::vector<std::string> normalNames{};
            request_app_list(platform, appType, i, normalNames, retValue);
            appNames.insert(appNames.end(), normalNames.begin(), normalNames.end());
            if (retValue == -1)
                break;
        }
        write_file_by_io(fileName, appNames);
    }
}