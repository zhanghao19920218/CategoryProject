//
// Created by Mason on 2022/5/5.
//
#include "qq_music_model.h"

void from_json(const nlohmann::json& j,MusicLysicModel& musicLysicModel)
{
    j.at("lyric").get_to<std::string>(musicLysicModel.lysic);
}

void from_json(const nlohmann::json& j,MusicLysicResponse& musicLysicResponse)
{
    j.at("data").get_to<MusicLysicModel>(musicLysicResponse.data);
}

void from_json(const nlohmann::json& j,MusicLysicSongIdModel& musicLysicSongIdModel)
{
    j.at("lyric").get_to<std::string>(musicLysicSongIdModel.lyric);
    j.at("songmid").get_to<std::string>(musicLysicSongIdModel.songmid);
}

void from_json(const nlohmann::json& j,MusicLysicSongModel& musicLysicSongModel)
{
    j.at("list").get_to<std::vector<MusicLysicSongIdModel>>(musicLysicSongModel.list);
}

void from_json(const nlohmann::json& j,MusicLysicSongResponse& musicLysicSongResponse)
{
    j.at("data").get_to<MusicLysicSongModel>(musicLysicSongResponse.data);
}

void from_json(const nlohmann::json& j,CompanyModel& companyModel)
{
    j.at("data").get_to<std::vector<std::string>>(companyModel.data);
}

void from_json(const nlohmann::json& j, MovieSubjectModel& movieSubjectModel)
{
    j.at("title").get_to<std::string>(movieSubjectModel.title);
    j.at("id").get_to<std::string>(movieSubjectModel.id);
}

void from_json(const nlohmann::json& j, MovieSubjectList& movieSubjectList)
{
    j.at("data").get_to<std::vector<MovieSubjectModel>>(movieSubjectList.data);
}

void from_json(const nlohmann::json& j, MusicNameModel& musicNameModel)
{
    j.at("name").get_to<std::string>(musicNameModel.name);
}

void from_json(const nlohmann::json& j, MusicNameDataModel& musicNameDataModel)
{
    j.at("list").get_to<std::vector<MusicNameModel>>(musicNameDataModel.list);
}

void from_json(const nlohmann::json& j,  MusicNameList& musicNameDataModel)
{
    j.at("data").get_to<MusicNameDataModel>(musicNameDataModel.data);
    j.at("result").get_to<int32_t>(musicNameDataModel.result);
}

void from_json(const nlohmann::json& j, SingerListModel& singerListModel)
{
    j.at("singer_mid").get_to<std::string>(singerListModel.singer_mid);
    j.at("singer_name").get_to<std::string>(singerListModel.singer_name);
}

void from_json(const nlohmann::json& j, SingerListData& singerListData)
{
    j.at("list").get_to<std::vector<SingerListModel>>(singerListData.list);
    j.at("total").get_to<int32_t>(singerListData.total);
}

void from_json(const nlohmann::json& j, SingerListResponse& singerListResponse)
{
    j.at("result").get_to<int>(singerListResponse.result);
    j.at("data").get_to<SingerListData>(singerListResponse.data);
}

void from_json(const nlohmann::json& j, SingerModel& singerModel)
{
    j.at("id").get_to<int>(singerModel.id);
    j.at("name").get_to<std::string>(singerModel.name);
    j.at("title").get_to<std::string>(singerModel.title);
}

void from_json(const nlohmann::json& j, AlbumModel& albumModel)
{
    j.at("id").get_to<int>(albumModel.id);
    j.at("name").get_to<std::string>(albumModel.name);
    j.at("title").get_to<std::string>(albumModel.title);
}

void from_json(const nlohmann::json& j, MusicModel& musicModel)
{
    j.at("id").get_to<int>(musicModel.id);
    j.at("name").get_to<std::string>(musicModel.name);
    j.at("title").get_to<std::string>(musicModel.title);
    j.at("singer").get_to<std::vector<SingerModel>>(musicModel.singer);
    j.at("album").get_to<AlbumModel>(musicModel.album);
}

void from_json(const nlohmann::json& j, MusicResponseData& musicResponseData)
{
    musicResponseData.musicModels = j.at("list").get<std::vector<MusicModel>>();
    musicResponseData.lan = j.at("lan").get<std::string>();
}

void from_json(const nlohmann::json& j,MusicResponse& musicResponse) {
    j.at("result").get_to(musicResponse.result);
    j.at("data").get_to(musicResponse.data);
}