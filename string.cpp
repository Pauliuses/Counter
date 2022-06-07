#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;


string fileAvailability(){
    string fileName;
    cout << "Iveskite failo pavadinima (fileName.txt): " <<endl;
    cin >> fileName;
    bool badFile;

    do {
            try {
                std::ifstream in(fileName);
                if (!in.good())
                    throw 404;
                else {
                    in.close();
                    badFile = false;
                }
            }
            catch (int exception) {
                badFile = true;
                cout << "Duomenu failas " << fileName << " neegzistuoja. Iveskite esamo failo varda: " << endl;
                cin >> fileName;
            }
        } while (badFile);

    return fileName;
}
void counter(std::map<string, vector<int>>& words, vector<string>& links){
    
    int n = 0;
    std::ifstream in(fileAvailability());
    string row, tempWord;
    std::stringstream readableRow;

    while(std::getline(in, row)) {
        readableRow.clear();
        readableRow.str(row);
        n++;

        while(readableRow >> tempWord) {
            // ieskome http arba www.
            if(tempWord.find("http") != string::npos || tempWord.find("www.") != string::npos){
                links.push_back(tempWord);
            }
            else {
                // Naikinam nereikalingus simbolius ar skaicius
                tempWord.erase(std::remove_if(tempWord.begin(), tempWord.end(), [](char temp) {return !isalpha(temp); } ), tempWord.end());

                // Patikrinam ar liko raidziu ir pakeiciame jas i mazasias raides
                if(tempWord != "")
                std::transform(tempWord.begin(), tempWord.end(), tempWord.begin(), [](unsigned char temp) {return std::tolower(temp); });
                words[tempWord].push_back(n);
            }
        }
    }
}

void toFile(std::map<string, vector<int>>& words, vector<string>& links){
    std::ofstream fr("rezultatai.txt");

    fr << "NUORODOS" <<endl;
    fr <<endl;
    for(string c : links)
    fr << c <<endl;

    fr <<endl;

    int eil = 0;

    fr << left << setw(30) << "ZODIS" << setw(30) << "KIEKIS" << setw(30) << "VIETA";
    for(auto a : words){
        if(a.second.size() > 1){
    fr << endl;
    eil++;
    if(eil != 1){
        fr << left << setw(30) << a.first << setw(30) << a.second.size();
    for(auto b : a.second)
    fr << b << " ";
    }
    }
    }
        
}

int main() {
    vector<string> links;
    std::map<string, vector<int>> words;

    counter(words, links);
    toFile(words, links);
}