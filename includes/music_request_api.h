//
// Created by Mason on 2022/5/6.
// This API is request for music files names

#ifndef CATEGORY_SCRIPT_MUSIC_REQUEST_API_H
#define CATEGORY_SCRIPT_MUSIC_REQUEST_API_H
#include "music_request_api.h"
#include "constant.h"

/**
 * 请求所有音乐，分成港台和内地
 * @param musicLoc 查看是哪种音乐
 */
void request_qq_music(const MUSIC_LOCATION& musicLoc);

#endif //CATEGORY_SCRIPT_MUSIC_REQUEST_API_H
