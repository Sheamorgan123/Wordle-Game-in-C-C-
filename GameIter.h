#include <string>
#include <iostream>
using namespace std;
class GameIter{
   public:
   size_t index;
   vector<string> listtoIter;
   bool (*wanted)(string);

   GameIter(vector<string> wordlist, bool (*our_wanted)(string), size_t j = string::npos){
        for(size_t i = 0; i < wordlist.size(); i++){
            string wordtoCheck = wordlist[i];
            //cout << "always: " << wordtoCheck << '\n';
            if(our_wanted(wordtoCheck) == true){
                //cout << "only if: " << wordtoCheck << '\n';
                listtoIter.emplace_back(wordtoCheck);
            }
        }
        if(j >= listtoIter.size()){
            index = listtoIter.size();
        }else{
        index = j;
        }
    }
    //++it
    GameIter operator++(){
        index++;
        return *this;
    }
    //it++
    GameIter operator++(int ){
        GameIter temp(*this);
        index++;
        return temp;
    }
    string operator*() const{
        return listtoIter[index];
    }
    
    bool operator==(const GameIter & otherGameIter) const{
        if(index == otherGameIter.index){
            return true;

        }
        return false;
    }
    bool operator!=(const GameIter & otherGameIter2) const{
        if(index != otherGameIter2.index){
            return true;

        }
        return false;

    }
    GameIter(const GameIter & itertocopy){
        wanted = itertocopy.wanted;
        index = itertocopy.index;
        listtoIter.clear();
        for(size_t i = 0; i < itertocopy.listtoIter.size(); i++){
            listtoIter.emplace_back(itertocopy.listtoIter[i]);
        }
    }
    GameIter operator=(const GameIter & otherGameiter){
        wanted = otherGameiter.wanted;
        index = otherGameiter.index;
        listtoIter.clear();
        for(size_t i = 0; i < otherGameiter.listtoIter.size(); i++){
            listtoIter.emplace_back(otherGameiter.listtoIter[i]);
        }
        return *this;
    }

    


};