#include <iostream>
#include "music_request_api.h"
#include "movie_request_api.h"
#include "company_request_api.h"
#include "config_reader.h"
#include "music_lysic_request_api.h"

using namespace std;

void printInfo(const std::string& msg)
{
    cout << "===========" << msg << "===============" << endl;
}

void runShell()
{
    auto reader = ConfigReader("./config/config.ini");
    CategoryType categoryType = reader.getCategory();
    switch (categoryType) {
        case CategoryType::CategoryMovie:
            printInfo("搜索电影");
            request_movies(reader.movieStartYear,
                           reader.movieEndYear,
                           reader.getMovieType());
            break;
        case CategoryType::CategoryCompany:
            printInfo("搜索机构");
            requestCompanyAll(reader.companyProvince,
                              reader.getCompanyType());
            break;
        case CategoryType::CategoryMusic:
            printInfo("搜索音乐");
            request_qq_music(reader.getMusicType());
            break;
    }
}

int main() {
//    runShell();
    requestAllMusic();
    return EXIT_SUCCESS;
}
