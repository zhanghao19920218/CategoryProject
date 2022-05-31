//
// Created by Mason on 2022/5/4.
//
#include "ba_request.h"
#include "request_api.h"


BARequest &BARequest::share(SEARCHTYPE search_type) {
    static BARequest instance;
    if (instance.client != nullptr) {
        instance.client = nullptr;
        delete instance.client;
    }
    switch (search_type) {
        case SEARCHTYPE::DOUBAN:
            instance.client = new httplib::Client(DOUBAN_BASE_URL);
            instance.client->enable_server_certificate_verification(false);
            instance._searchType = search_type;
            break;
        case SEARCHTYPE::MUSIC:
            instance.client = new httplib::Client("localhost", URL_PORT);
            instance.client->set_connection_timeout(5300000);
            instance.client->set_read_timeout(30, 0); // 5 seconds
            instance.client->set_write_timeout(30, 0); // 5 seconds
            instance._searchType = search_type;
            break;
        case SEARCHTYPE::APP:
        case SEARCHTYPE::MALL:
        case SEARCHTYPE::COMPANY:
            instance.client = new httplib::Client(BASE_COMPANY_URL, COMPANY_PORT);
            instance.client->set_connection_timeout(5300000);
            instance.client->set_read_timeout(30, 0); // 5 seconds
            instance.client->set_write_timeout(30, 0); // 5 seconds
            instance._searchType = search_type;
            break;
        case SEARCHTYPE::CITY_NAMES:
            instance.client = new httplib::Client(AMAP_BASE_URL);
            instance.client->enable_server_certificate_verification(false);
            instance.client->set_connection_timeout(5300000);
            instance.client->set_read_timeout(30, 0); // 5 seconds
            instance.client->set_write_timeout(30, 0); // 5 seconds
            instance._searchType = search_type;
            break;
    }
    return instance;
}
