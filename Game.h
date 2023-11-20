#include <string>
#include <map>
#include <vector>
#include "GameIter.h"
#include <iostream>
using namespace std;
class Game{
    private:
    bool (*our_wanted)(string) = [](string) {return true;};
    size_t targetWordLength = 5;
    string goodCharacter = "=";
    string wrongCharacter = "-";
    string badCharacter = " ";
    map<size_t, vector<string>> wordDictionary = {};
    string targetWord; 
    bool checkWord(char guessOfi) const;

    public:
    using iterator = GameIter;
    Game();
    Game(const Game &gametoCopy);
    Game& operator=(const Game &otherGame);
    ~Game();
    void set_length(size_t TargetLength);
    size_t get_length() const;
    string getGoodCharacter() const;
    string getWrongCharacter() const;
    string getBadCharacter() const;
    map<size_t, vector<string>> getWordDictionary() const;
    void setWordDictionary(map<size_t, vector<string>> wordDict);
    void add_dict(string path);
    void set_good(string goodChar);
    void set_wrong(string wrongChar);
    void set_bad(string badChar);
    string select_target();
    bool contains(string word);
    string feedback(string guess) const;
    void set_wanted(bool (*wanted)(string));
    iterator begin() const {
        return iterator(wordDictionary.at(targetWordLength), our_wanted, 0);
        }
    iterator end() const {
        return iterator(wordDictionary.at(targetWordLength), our_wanted);
        }



};