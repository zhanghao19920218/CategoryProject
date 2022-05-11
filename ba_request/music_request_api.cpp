//
// Created by Mason on 2022/5/6.
//

#include "music_request_api.h"
#include "file_io.h"
#include "ba_request.h"
#include "http_error.h"

using namespace std;

vector<string> request_singers_list(int pageNo,
                                    const MUSIC_LOCATION& musicLoc) {
    vector<string> singer_ids{};
    HTTP_STATUS status;
    std::string area = musicLoc == MUSIC_LOCATION::HONGKONG ? "2" : "200";
    std::vector<std::pair<std::string, std::string>> params{
            {"area",   area}, // 内地200, 港台2
            {"pageNo", to_string(pageNo)}
    };

    SingerListResponse ret = BARequest::share(SEARCHTYPE::MUSIC).get<SingerListResponse>("/singer/list",
                                                                                         status,
                                                                                         params);

    std::cout << "===============REQUEST SINGER SUCCESSFULLY==============" << std::endl;
    if (status == HTTP_STATUS::SUCCESS) {
        for (auto &singer_model: ret.data.list) {
            singer_ids.push_back(singer_model.singer_mid);
        }
    }
    std::cout << singer_ids.size() << std::endl;
    return singer_ids;
}

vector<string> request_music_by_id(const std::string &singer_id) {
    vector<string> music_names{};
    HTTP_STATUS status;
    std::vector<std::pair<std::string, std::string>> params{
            {"singermid", singer_id},
            {"page",      "1"},
            {"num",       "500"}
    };

    MusicNameList ret = BARequest::share(SEARCHTYPE::MUSIC).get<MusicNameList>("/singer/songs",
                                                                               status,
                                                                               params);

    if (status == HTTP_STATUS::SUCCESS) {
        for (auto &singer_model: ret.data.list) {
            music_names.push_back(singer_model.name);
        }
    }
    return music_names;
}

void request_music_list(std::vector<std::string> &singer_ids,
                        const MUSIC_LOCATION& musicLoc) {
    auto fileName = musicLoc == MUSIC_LOCATION::HONGKONG ? "港台.txt" : "内地.txt";
    for (const auto &singer_id: singer_ids) {
        auto ret = request_music_by_id(singer_id);
        write_file_by_io(fileName, ret);
    }
}

vector<string> request_all_singers(const MUSIC_LOCATION& musicLoc) {
    vector<string> ret{};
    for (int i = 1; i < 43; ++i) {
        auto tmp = request_singers_list(i,
                                        musicLoc);
        ret.insert(ret.cend(), tmp.cbegin(), tmp.cend());
    }
    return ret;
}

/**
 * 请求QQ音乐
 * @param musicLoc
 */
void request_qq_music(const MUSIC_LOCATION& musicLoc) {
    auto all_singers = request_all_singers(musicLoc);
    request_music_list(all_singers,
                       musicLoc);
}
