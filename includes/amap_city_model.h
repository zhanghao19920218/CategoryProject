//
// Created by Mason on 2022/5/10.
// 解析获取高德地图的Model
//

#ifndef CATEGORY_SCRIPT_AMAP_CITY_MODEL_H
#define CATEGORY_SCRIPT_AMAP_CITY_MODEL_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

// 城市详情
struct DistrictsModel {
    std::string name;
};

void from_json(const nlohmann::json& j, DistrictsModel& districtsModel);

// 省份详情
struct ProvinceDistrictsModel {
    std::vector<DistrictsModel> districts;
    std::string name;
};

void from_json(const nlohmann::json& j, ProvinceDistrictsModel& provinceDistrictsModel);

// 请求结果
struct AMapResponseModel {
    std::string status;
    std::string infocode;
    std::vector<ProvinceDistrictsModel> districts;
    std::string count;
};

void from_json(const nlohmann::json& j, AMapResponseModel& aMapResponseModel);

#endif //CATEGORY_SCRIPT_AMAP_CITY_MODEL_H
