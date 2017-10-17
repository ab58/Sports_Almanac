using namespace std;

int numlines(string s);
string charToString(char c);
void capAfterPunc(string &s);
string takeOutJunk(string &s, string junk, string repl);
string strToUpper(string s);
vector<string> split(string s, string delimiter);

void setPlayerInfo(const int i, vector<string> &matchingNames, string &urlExtension,
                   string &name, string &posAndYears, string &league);
void setSearchers(string &searchURL, string &statStartStr, const string league,
                  const string suFB, const string suHK, const string suBS, const string suBK);

size_t writeData(void *ptr, size_t size, size_t nmemb, void *stream);
void getCareerStats(string playerURL, string statContent, string statStartStr);
vector<string> scrapeURL(string searchURL, string league);
