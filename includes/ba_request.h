//
// Created by Mason on 2022/5/4.
//

#ifndef QQ_API_SCRIPT_BA_REQUEST_H
#define QQ_API_SCRIPT_BA_REQUEST_H

#include <string>
#include "http_error.h"
#include "httplib.h"
#include "constant.h"
#include <map>
#include <nlohmann/json.hpp>
#include "qq_music_model.h"
#include "douban_api.h"

const std::vector<std::map<std::string, std::string>> proxy_urls {
        {{"host", "106.54.128.253"}, {"port", "999"}},
        {{"host", "61.216.185.88"}, {"port", "60808"}},
        {{"host", "183.247.215.218"}, {"port", "30001"}},
        {{"host", "103.37.141.69"}, {"port", "80"}},
        {{"host", "152.136.62.181"}, {"port", "9999"}},
        {{"host", "113.88.208.112"}, {"port", "8118"}},
        {{"host", "183.236.123.242"}, {"port", "8060"}},
        {{"host", "183.64.239.19"}, {"port", "8060"}},
        {{"host", "202.55.5.209"}, {"port", "8090"}},
        {{"host", "223.215.7.119"}, {"port", "8118"}}
};

class BARequest {
private:
    BARequest() {
        client = new httplib::Client{"localhost", URL_PORT};
    }

    ~BARequest() {
        if (this->client != nullptr) {
            client = nullptr;
            delete client;
        }
    }

    BARequest(const BARequest &);

    BARequest &operator=(const BARequest &);

public:
    /**
     * get the instance of ba request
     * @return
     */
    static BARequest &share(SEARCHTYPE search_type);

    /**
     *
     * @param url_param
     * @param request_params the params to get
     * @param ret_value the return type to confirm success
     * @return
     */
    template<typename T>
    T get(const std::string &url_param,
          HTTP_STATUS &ret_value,
          const std::vector<std::pair<std::string, std::string>> &request_params)
    {
        T response;
        std::size_t len = request_params.size();
        std::string request_url = url_param;
        if (len > 0) {
            request_url = request_url + "?";
            for (const auto & request_param : request_params) {
                request_url += (request_param.first) + "=" + (request_param.second) + "&";  // 豆瓣搜索需要按顺序，不能用for (auto c: item}
            }
        }
        try {
            httplib::Headers headers{};
            // 如果是豆瓣就需要增加headers
            if (_searchType == SEARCHTYPE::DOUBAN) {
                headers.insert(headers.cend(), {"Host",       "movie.douban.com"});
                // 随机设置代理地址
                auto random_proxy_index = random() % proxy_urls.size();
                std::map<std::string, std::string> random_proxy = proxy_urls[random_proxy_index];
                client->set_proxy(random_proxy["proxy"].c_str(), std::stoi(random_proxy["port"]));
            } else if (_searchType == SEARCHTYPE::CITY_NAMES) {
                headers.insert(headers.cend(), {"Host",       "restapi.amap.com"});
            }
            httplib::Result res = client->Get(request_url.c_str(), headers);
            if (res == nullptr) {
                std::cerr << "=========== request error ========" << std::endl;
                std::cerr << request_url << std::endl;
                ret_value = HTTP_STATUS::OTHER_ERROR;
            } else {
                auto ret = res->status;
                // 判断返回值是否是正常，不是就报错
                ret_value = static_cast<HTTP_STATUS>(ret);
                if (ret_value == HTTP_STATUS::SUCCESS) {
                    nlohmann::json j = nlohmann::json::parse(res->body);
                    from_json(j, response);
                    return response;
                } else {
                    return response;
                }
            }
        } catch (httplib::Error error) {
            ret_value = HTTP_STATUS::OTHER_ERROR;
        }
        return response;
    }

    /**
     * post请求接口
     * @tparam T
     * @param url_param
     * @param ret_value
     * @param request_params
     * @return
     */
    template<typename T>
    T post(const std::string &url_param,
          HTTP_STATUS &ret_value,
          const std::vector<std::pair<std::string, std::string>> &request_params)
    {
        T response;
        std::size_t len = request_params.size();
        std::string formData{};
        nlohmann::json formJson;
        if (len > 0) {
            for (const auto & request_param : request_params) {
                formJson[request_param.first] = request_param.second;  // 拼装元素data
            }
            formData = formJson.dump();
        }
        try {
            httplib::Result res = client->Post(url_param.c_str(), formData, "application/json");
            auto ret = res->status;
            // 判断返回值是否是正常，不是就报错
            ret_value = static_cast<HTTP_STATUS>(ret);
            if (ret_value == HTTP_STATUS::SUCCESS) {
                nlohmann::json j = nlohmann::json::parse(res->body);
                from_json(j, response);
                return response;
            } else {
                return response;
            }
        } catch (httplib::Error error) {
            ret_value = HTTP_STATUS::OTHER_ERROR;
        }
        return response;
    }

    template<typename T>
    T post(const std::string& url_param,
           HTTP_STATUS &ret_value)
    {
        return this->get<T>(url_param,
                            ret_value,
                            std::vector<std::pair<std::string, std::string>>{});
    }

    /**
     * get without params
     * @param url_param
     * @param ret_value
     * @return
     */
    template<typename T>
    T get(const std::string &url_param,
                    HTTP_STATUS &ret_value)
    {
        return this->get<T>(url_param,
                            ret_value,
                            std::vector<std::pair<std::string, std::string>>{});
    }

private:
    // 请求的服务端
    httplib::Client* client = nullptr;

    // 请求类型
    SEARCHTYPE _searchType;
};

#endif //QQ_API_SCRIPT_BA_REQUEST_H
