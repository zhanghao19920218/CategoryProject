//
// Created by Mason on 2022/5/10.
//

#include "company_request_api.h"
#include <string>
#include "http_error.h"
#include "ba_request.h"
#include "file_io.h"
#include "amap_city_model.h"
#include "request_api.h"
#include <regex>
#include "timer_loop.h"

void request_company_list(const std::string& address,
                          std::vector<std::string>& company_names,
                          const CompanyType& companyType) {
    HTTP_STATUS status;
    std::vector<std::pair<std::string, std::string>> params{
            {"address", address}
    };

    std::string request_api{};
    switch (companyType) {
        case CompanyType::SCHOOL_TYPE:
            request_api = "/school";
            break;
        case CompanyType::HOSPITAL:
            request_api = "/hospital";
            break;
        case CompanyType::COMPANY_TYPE:
            request_api = "/company";
            break;
    }
    CompanyModel ret = BARequest::share(SEARCHTYPE::COMPANY).post<CompanyModel>(request_api,
                                                                                status,
                                                                                params);

    if (status == HTTP_STATUS::SUCCESS) {
        for (auto &company_item: ret.data) {
            company_names.push_back(company_item);
        }
    }
}

/**
 * 请求一个城市
 * @param cityName
 * @param companyType
 * @param provinceName
 */
void request_one_city(const std::string& cityName,
                      const CompanyType& companyType,
                      const std::string& provinceName)
{
    std::vector<std::string> ret;
    std::string fileName{};
    request_company_list(cityName,
                         ret,
                         companyType);
    switch(companyType){
        case CompanyType::COMPANY_TYPE:
            fileName = provinceName + "_company.txt";
            break;
        case CompanyType::HOSPITAL:
            fileName = provinceName + "_hospital.txt";
            break;
        case CompanyType::SCHOOL_TYPE:
            fileName = provinceName + "_school.txt";
            break;
    }
    write_file_by_io(fileName,
                     ret);
}

/**
 * 根据省份请求机构
 * @param provinceName 省份名称
 * @param companyType 查询数据类型
 */
void requestCityNamesBy(const std::string& provinceName,
                        const CompanyType& companyType,
                        std::vector<std::string>& addressList)
{
    HTTP_STATUS status;
    std::vector<std::pair<std::string, std::string>> params{
            {"keywords", provinceName},
            {"key", AMAP_KEY}
    };
    AMapResponseModel response = BARequest::share(SEARCHTYPE::CITY_NAMES).get<AMapResponseModel>(CITY_API ,
                                                                                                 status,
                                                                                                 params);

    if (status == HTTP_STATUS::SUCCESS) {
        auto info_count = stoi(response.count);
        if (info_count == 0 ) {
            std::cerr << "没有城市" << std::endl;
            return;
        }
        if (info_count > 1) {
            addressList.push_back(response.districts[0].name);
        } else {
            for (auto &city_item: response.districts[0].districts) {
                addressList.push_back(companyType != CompanyType::HOSPITAL ? regex_replace(city_item.name, std::regex("市"), "") : city_item.name);
            }
        }
    }

    std::cout << "=========== GET ADDRESS NAMES ===============" << std::endl;

    for (const auto & c: addressList) {
        std::cout << c << '\t';
    }
    std::cout << std::endl;
}

void requestCompanyAll(const std::string& provinceName,
                       const CompanyType& companyType)
{
    std::vector<std::string> cityNames{};
    requestCityNamesBy(provinceName,
                       companyType,
                       cityNames);
    for (const auto& city_name: cityNames)
    {
        TimeLoop timeLoop(10000, false, &request_one_city, city_name, companyType, provinceName);
    }
}