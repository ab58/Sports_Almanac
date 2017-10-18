#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

int numlines(string s) {
    int lines = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) == '\n') {
            lines++;
        }
    }
    return lines;
}

string charToString(char c) {
    stringstream ss; string s;
    ss << c; ss >> s;
    return s;
}

void capAfterPunc(string &s)
{
    for (int i = 1; i < s.size(); i++) {
        if (ispunct(s.at(i-1))) {
            s.at(i) = toupper(s.at(i));
        }
    }
}

string takeOutJunk(string &s, string junk, string repl) {
    if (s.find(junk) != string::npos) {
        s = s.replace(s.find(junk), junk.size(), repl);
    }
    return s;
}

string strToUpper(string s) {
    for (int i = 0; i < s.size(); i++) {
        s.at(i) = toupper(s.at(i));
    }
    return s;
}

vector<string> split(string s, string delimiter) {
    vector<string> tokens;
    while (s.find(delimiter) != string::npos && s.size() > 0) {
        string tok = s.substr(0, s.find(delimiter));
        if (tok.size() == 0) {
            s = tok;
            break;
        }
        tokens.push_back(tok);
        s = s.substr(s.find(delimiter) + delimiter.size());
    }
    if (s.size() > 0) {
        tokens.push_back(s);
    }
    return tokens;
}

void setPlayerInfo(const int i, vector<string> &matchingNames, string &urlExtension,
                   string &name, string &posAndYears, string &league) {
    vector<string> playerInfo = split(matchingNames[i], " ");
    urlExtension = playerInfo[0].substr(playerInfo[0].find_last_of("/")+1);
    name = playerInfo[1] + " " + playerInfo[2];
    int pyi = 3;
    if (isalpha(playerInfo[3].at(0))) {
        name = name + " " + playerInfo[3];
        pyi++;
    }
    posAndYears = playerInfo[pyi];
    if (playerInfo.size() > pyi+2) {
        posAndYears = posAndYears + " " + playerInfo[pyi+1];
    }
    league = playerInfo[playerInfo.size()-1];
}

void setSearchers(string &searchURL, string &statStartStr, const string league,
                  const string suFB, const string suHK, const string suBS, const string suBK) {
    if (league == "(NFL)") {
        searchURL = suFB;
        statStartStr = "Career</th>";
    } else if (league == "(NHL)") {
        searchURL = suHK;
        statStartStr = "Career</th>";
    } else if (league == "(MLB)") {
        searchURL = suBS;
        statStartStr = "Yrs</th>";
    } else if (league == "(NBA)") {
        searchURL = suBK;
        statStartStr = "Career</th>";
    }
}
