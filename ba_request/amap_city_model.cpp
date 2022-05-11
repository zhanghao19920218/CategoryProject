//
// Created by Mason on 2022/5/10.
//

#include "amap_city_model.h"

void from_json(const nlohmann::json& j, DistrictsModel& districtsModel)
{
    j.at("name").get_to<std::string>(districtsModel.name);
}

void from_json(const nlohmann::json& j, ProvinceDistrictsModel& provinceDistrictsModel)
{
    j.at("districts").get_to<std::vector<DistrictsModel>>(provinceDistrictsModel.districts);
    j.at("name").get_to<std::string>(provinceDistrictsModel.name);
}

void from_json(const nlohmann::json& j, AMapResponseModel& aMapResponseModel)
{
    j.at("status").get_to<std::string>(aMapResponseModel.status);
    j.at("infocode").get_to<std::string>(aMapResponseModel.infocode);
    j.at("districts").get_to<std::vector<ProvinceDistrictsModel>>(aMapResponseModel.districts);
    j.at("count").get_to<std::string>(aMapResponseModel.count);
}