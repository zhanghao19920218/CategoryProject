//
// Created by Mason on 2022/5/5.
//

#ifndef QQ_API_SCRIPT_QQ_MUSIC_MODEL_H
#define QQ_API_SCRIPT_QQ_MUSIC_MODEL_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

template<typename Base, typename T>
inline bool instanceof(const T ptr, const Base ptr2) {
    return typeid(ptr) == typeid(ptr2);
};

// 学校机构的model
struct CompanyModel {
    std::vector<std::string> data;
};

void from_json(const nlohmann::json& j,CompanyModel& companyModel);

// 豆瓣电影的Model

struct MovieSubjectModel {
    std::string title;  // 电影名称
    std::string id; // 电影id
};

void from_json(const nlohmann::json& j, MovieSubjectModel& movieSubjectModel);

struct MovieSubjectList {
    std::vector<MovieSubjectModel> data;
};

void from_json(const nlohmann::json& j, MovieSubjectList& movieSubjectList);


struct MusicNameModel {
    std::string name;
};

void from_json(const nlohmann::json& j, MusicNameModel& musicNameModel);

struct MusicNameDataModel {
    std::vector<MusicNameModel> list;
};

void from_json(const nlohmann::json& j, MusicNameDataModel& musicNameDataModel);

struct MusicNameList {
    int32_t result{};
    MusicNameDataModel data;
};

void from_json(const nlohmann::json& j,  MusicNameList& musicNameDataModel);

struct SingerListModel {
    std::string singer_mid;
    std::string singer_name;
};

void from_json(const nlohmann::json& j, SingerListModel& singerListModel);

struct SingerListData {
    std::vector<SingerListModel> list;
    int32_t total;
};

void from_json(const nlohmann::json& j, SingerListData& singerListData);

struct SingerListResponse {
    int32_t result{};
    SingerListData data;
};

void from_json(const nlohmann::json& j, SingerListResponse& singerListResponse);

struct SingerModel {
    int32_t id;
    std::string name;
    std::string title;
};

void from_json(const nlohmann::json& j, SingerModel& singerModel);

struct AlbumModel {
    int32_t id;
    std::string name;
    std::string title;
};

void from_json(const nlohmann::json& j, AlbumModel& albumModel);

struct MusicModel {
    int32_t id{};
    std::string name;
    std::string title;
    std::vector<SingerModel> singer;
    AlbumModel album;
};

void from_json(const nlohmann::json& j, MusicModel& musicModel);

struct MusicResponseData {
    std::string lan;
    std::vector<MusicModel> musicModels;
};

void from_json(const nlohmann::json& j, MusicResponseData& musicResponseData);

struct MusicResponse {
    int32_t result{};
    MusicResponseData data;
};

void from_json(const nlohmann::json& j,MusicResponse& musicResponse);

#endif //QQ_API_SCRIPT_QQ_MUSIC_MODEL_H
