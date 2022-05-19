//
// Created by Mason on 2022/5/19.
//
#include "music_lysic_request_api.h"
#include <vector>
#include "http_error.h"
#include "qq_music_model.h"
#include "ba_request.h"

std::string request_singers_list(const std::string& musicName) {
    std::vector<std::string> songs_mids{};
    HTTP_STATUS status;
    std::vector<std::pair<std::string, std::string>> params{
            {"key",   musicName}, // 内地200, 港台2
    };

    MusicLysicSongResponse ret = BARequest::share(SEARCHTYPE::MUSIC).get<MusicLysicSongResponse>("/search",
                                                                                         status,
                                                                                         params);

    std::cout << "===============REQUEST SONGS SUCCESSFULLY==============" << std::endl;
    if (status == HTTP_STATUS::SUCCESS) {
        for (auto &song_model: ret.data.list) {
            songs_mids.push_back(song_model.songmid);
        }
    }
    std::cout << songs_mids.size() << std::endl;
    if (!songs_mids.empty()) {
        return songs_mids[0];
    }
    return "";
}

std::string request_lysic_content(const std::string& song_mid,
                                  const std::string& song_name)
{
    std::string lysic_content;
    HTTP_STATUS status;
    std::vector<std::pair<std::string, std::string>> params{
            {"songmid",   song_mid}, // 内地200, 港台2
    };

    MusicLysicResponse ret = BARequest::share(SEARCHTYPE::MUSIC).get<MusicLysicResponse>("/lyric",
                                                                                         status,
                                                                                         params);

    std::cout << "===============REQUEST SONGS SUCCESSFULLY==============" << std::endl;
    if (status == HTTP_STATUS::SUCCESS) {
        lysic_content = ret.data.lysic;
    }
    return lysic_content;
}

void requestAllMusic()
{
    std::string musicId = request_singers_list("孤勇者");
    std::string response = request_lysic_content(musicId, "孤勇者");
}