#include "Game.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>
using namespace std;
Game::Game(){

}
Game::Game(const Game &gametoCopy){
    this->set_length(gametoCopy.get_length());
    this->set_good(gametoCopy.getGoodCharacter());
    this->set_wrong(gametoCopy.getWrongCharacter());
    this->set_bad(gametoCopy.getBadCharacter());
    this->setWordDictionary(gametoCopy.getWordDictionary());
    this->our_wanted = gametoCopy.our_wanted;

}
Game& Game::operator=(const Game &otherGame){
    this->set_length(otherGame.get_length());
    this->set_good(otherGame.getGoodCharacter());
    this->set_wrong(otherGame.getWrongCharacter());
    this->set_bad(otherGame.getBadCharacter());
    this->setWordDictionary(otherGame.getWordDictionary());
    this->our_wanted = otherGame.our_wanted;
    return *this;
}

Game::~Game(){

}
size_t Game::get_length() const{
    return targetWordLength;
}
string Game::getGoodCharacter() const{
    return goodCharacter;

}
string Game::getWrongCharacter() const{
    return wrongCharacter;

}
string Game::getBadCharacter() const{
    return badCharacter;

}
map<size_t, vector<string>> Game::getWordDictionary() const{
    return wordDictionary;

}
void Game::setWordDictionary(map<size_t, vector<string>> wordDict){
    this->wordDictionary = wordDict;

}
void Game::set_length(size_t TargetLength){
    this->targetWordLength = TargetLength;

}
void Game::add_dict(string path){
    ifstream file(path);
    if(file.is_open()){
        for(string word; getline(file, word);){
            size_t wordlength = word.size();
            /*
            {0, }
            {1, }
            {2, }
            {3, }

            --------
            {0, []}
            {1, }
            {2, ["at"]}
            {3, }
            */
           if(wordDictionary.count(wordlength) == 0){
                //pair<size_t, string> p = {leftPairObj, rightPairObj};
                //pair<size_t, vector<string>> p = {wordlength, {word}}
                //wordDictionar.insert(p);
                vector<string> ws = {word};
                wordDictionary.insert(make_pair(wordlength, ws));
           }else{
               wordDictionary[wordlength].emplace_back(word);
           }

        }
                    
    }else{
        throw invalid_argument("Failed to open " + path + " for reading.");
    }
}
void Game::set_good(string goodChar){
    this->goodCharacter = goodChar;


}
void Game::set_wrong(string wrongChar){
    this->wrongCharacter = wrongChar;

}
void Game::set_bad(string badChar){
    this->badCharacter = badChar;

}
string Game::select_target(){
    if(wordDictionary.count(targetWordLength) == 0){
        throw length_error("No words of length " + to_string(targetWordLength) + " exist.");
    
    }else{
        vector<string> words = wordDictionary[targetWordLength];
        random_device rd;
        targetWord = words[rd() % words.size()];
        return targetWord;
    }
    

}
bool Game::contains(string wordToFind){
    size_t wordsize = wordToFind.size();
    if(wordDictionary.count(wordsize) != 0){
        vector<string> words = wordDictionary[wordsize];
        for(size_t i = 0; i < words.size(); i++){
            if(wordToFind == words[i]){
                return true;
            }
        }
    }
    return false;
}
bool Game::checkWord(char guessOfi) const{
    for(size_t i = 0; i < targetWordLength; i++){ 
        if(guessOfi == targetWord[i]){
            return true;
        }

    }
    return false;
}

string Game::feedback(string guess) const{
    ostringstream feedback;
    if(targetWord.empty()){
        cerr << "no target word selected  " << '\n';
    }else{
    for(size_t i = 0; i < guess.length(); i++){
        if(guess[i] == targetWord[i]){
            feedback << goodCharacter;
        }else if(checkWord(guess[i])){
            feedback << wrongCharacter;
            
        }else{
            feedback << badCharacter;
            
        }
    }
    }
    return feedback.str();

}

void Game::set_wanted(bool(*wanted)(string)){
    our_wanted = wanted;

}


