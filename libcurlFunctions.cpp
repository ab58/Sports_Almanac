#include <iostream>
#include <curl/curl.h>
#include <vector>
#include "Sports_Almanac_Lib.h"

using namespace std;

size_t writeData(void *ptr, size_t size, size_t nmemb, void *stream) {
    ((string*)stream)->append((char*)ptr, size*nmemb);
    return size * nmemb;
}



void getCareerStats(string playerURL, string statContent, string statStartStr) {
    CURL *curl;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, playerURL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &statContent);
    curl_easy_perform(curl);

    if (statContent.find(statStartStr) == string::npos) { statStartStr = "Yr</th>"; }

    if (statContent.find(statStartStr) == string::npos) {
        cout << "Sorry, no career stats to report on this player.\n";
        return;
    }
    int statStart = statContent.find(statStartStr);
    string cutToSS = statContent.substr(statStart);
    int statEnd = cutToSS.find("</tr>");
    string statSearchSpace = cutToSS.substr(0, statEnd);

    vector<string> statCategories = split(statSearchSpace, "<td ");
    for (int i = 1; i < statCategories.size(); i++) {
        statCategories[i] = statCategories[i].substr(0, statCategories[i].find("<"));
        if (statCategories[i].at(statCategories[i].size()-1) != '>') {
            string cat = statCategories[i].substr(statCategories[i].find("data-stat=")+11);
            cat = cat.substr(0, cat.find("\""));
            for (int j = 0; j < cat.size(); j++) {
                cat.at(j) = toupper(cat.at(j));
            }

            string statNumber = statCategories[i].substr(statCategories[i].find(">")+1);
            cout << cat << ": " << statNumber << "\n";
        }
    }
    curl_easy_cleanup(curl);
}


vector<string> scrapeURL(string searchURL, string league) {
    CURL *curl;
    CURLcode result;
    string urlContent;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, searchURL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &urlContent);
    curl_easy_perform(curl);

    vector<string> allPlayers;
    if (urlContent.find("div_players") == string::npos ||
        urlContent.find("=\"0 Players") != string::npos) {
        return allPlayers;
    }

    int playerStart = urlContent.find("div_players")+15;
    string cutToPS = urlContent.substr(playerStart);
    int playerEnd = cutToPS.find("</div");
    string playerSearchSpace = cutToPS.substr(0, playerEnd);

    if (league == "NBA") {
        playerSearchSpace = playerSearchSpace.substr(playerSearchSpace.find("<tbody>")+8);
    }

    if (numlines(playerSearchSpace) <= 2) {
        allPlayers = split(playerSearchSpace, "</p><p>");
    } else {
        allPlayers = split(playerSearchSpace, "\n");
    }

    for (int i = 0; i < allPlayers.size(); i++) {
        //for the basketball site we need more specialized string processing
        if (league == "NBA") {
            string yMin = allPlayers[i].substr(allPlayers[i].find("year_min\" >")+11);
            yMin = yMin.substr(0, yMin.find("<"));
            string yMax = allPlayers[i].substr(allPlayers[i].find("year_max\" >")+11);
            yMax = yMax.substr(0, yMax.find("<"));
            string pos = allPlayers[i].substr(allPlayers[i].find("pos\" >")+6);
            pos = pos.substr(0, pos.find("<"));

            allPlayers[i] = allPlayers[i].substr(0, allPlayers[i].find("</a>")+4);
            allPlayers[i] = allPlayers[i] + " (" + yMin + "-" + yMax + ", " + pos + ")";
        }
        allPlayers[i] = allPlayers[i] + " (" + league + ")";
    }

    curl_easy_cleanup(curl);

    return allPlayers;
}
