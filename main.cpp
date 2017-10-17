#include <iostream>
#include <vector>
#include <limits>
#include "Sports_Almanac_Lib.h"

using namespace std;

int main() {
    string quit;

    while (true) {
        string playerName;
        cout << "\nEnter player name: ";
        getline(cin, playerName);
        while (playerName.size() == 0 || !isalpha(playerName.at(0))) {
            cout << "\nInvalid entry. Enter player name: ";
            getline(cin, playerName);
        }

        playerName[0] = toupper(playerName[0]);
        char searchLetter = playerName[0];
        if (playerName.find(" ") != string::npos && playerName.find(" ") != playerName.size()-1) {
            playerName[playerName.find_last_of(" ")+1] =
            toupper(playerName[playerName.find_last_of(" ")+1]);
            searchLetter = playerName[playerName.find_last_of(" ")+1];
        }
        capAfterPunc(playerName);

        string searchLetStr = charToString(searchLetter);
        string searchURLFootball = "https://www.pro-football-reference.com/players/" + searchLetStr + "/";
        searchLetter = tolower(searchLetter);
        searchLetStr = charToString(searchLetter);
        string searchURLHockey = "https://www.hockey-reference.com/players/" + searchLetStr + "/";
        string searchURLBaseball = "https://www.baseball-reference.com/players/" + searchLetStr + "/";
        string searchURLBasketball = "https://www.basketball-reference.com/players/" + searchLetStr + "/";

        cout << "\nSearching for player " << playerName << "\n";
        vector<string> allPlayersFB = scrapeURL(searchURLFootball, "NFL");
        vector<string> allPlayersHK = scrapeURL(searchURLHockey, "NHL");
        vector<string> allPlayersBS = scrapeURL(searchURLBaseball, "MLB");
        vector<string> allPlayersBK = scrapeURL(searchURLBasketball, "NBA");

        vector<string> allPlayers;
        allPlayers.reserve(allPlayersFB.size() + allPlayersHK.size() + allPlayersBS.size() + allPlayersBK.size());
        allPlayers.insert(allPlayers.end(), allPlayersFB.begin(), allPlayersFB.end());
        allPlayers.insert(allPlayers.end(), allPlayersHK.begin(), allPlayersHK.end());
        allPlayers.insert(allPlayers.end(), allPlayersBS.begin(), allPlayersBS.end());
        allPlayers.insert(allPlayers.end(), allPlayersBK.begin(), allPlayersBK.end());

        vector<string> matchingNames;

        for (int i = 0; i < allPlayers.size(); i++) {
            allPlayers[i] = allPlayers[i].substr(allPlayers[i].find("/players"));
            takeOutJunk(allPlayers[i], "</a>", "");
            takeOutJunk(allPlayers[i], "\"", "");
            takeOutJunk(allPlayers[i], ">", " ");
            takeOutJunk(allPlayers[i], "</p>", "");
            takeOutJunk(allPlayers[i], "</b>", "");
            takeOutJunk(allPlayers[i], "</strong>", "");

            if (strToUpper(allPlayers[i]).find(strToUpper(playerName)) != string::npos) {
                matchingNames.push_back(allPlayers[i]);
            }
        }

        if (matchingNames.size() == 1) { //only one player found matching name
            takeOutJunk(matchingNames[0], "  ", " ");
            string urlExtension, name, posAndYears, league;
            setPlayerInfo(0, matchingNames, urlExtension, name, posAndYears, league);
            string searchURL, statStartStr;
            setSearchers(searchURL, statStartStr, league, searchURLFootball,
                         searchURLHockey, searchURLBaseball, searchURLBasketball);

            cout << "\nCareer Stats for " << name << " " << posAndYears << ":\n\n";
            string playerURL = searchURL + urlExtension;
            string statContent;
            getCareerStats(playerURL, statContent, statStartStr);


        } else if (matchingNames.size() > 1) { //multiple matches found for searched name
            string urlExtension, name, posAndYears, league;
            cout << "\nFound the following matches for " << playerName << ":\n\n";
            for (int i = 0; i < matchingNames.size(); i++) {
                takeOutJunk(matchingNames[i], "  ", " ");
                setPlayerInfo(i, matchingNames, urlExtension, name, posAndYears, league);
                cout << (i+1) << ". " << name << " " << posAndYears << " " << league << "\n";
            }

            cout << "\nPlease select an from the list (by number): ";
            int option;
            cin >> option;
            while (option > matchingNames.size() || option < 1) {
                cout << "\nInvalid selection: please select again. ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> option;
            }

            setPlayerInfo(option-1, matchingNames, urlExtension, name, posAndYears, league);
            string searchURL, statStartStr;
            setSearchers(searchURL, statStartStr, league, searchURLFootball,
                         searchURLHockey, searchURLBaseball, searchURLBasketball);

            cout << "\nCareer Stats for " << name << " " << posAndYears << ":\n\n";
            string playerURL = searchURL + urlExtension;
            string statContent;
            getCareerStats(playerURL, statContent, statStartStr);

        } else { //no matches found for searched name
            cout << "\nNo matches found for player " << playerName << "\n";
        }

        cout << "\nPress 'q' to quit, or type in anything else to continue: ";
        cin >> quit;
        if (quit == "q") {
            break;
        } else {
            getline(cin, quit);
        }
    }

    return 0;
}
