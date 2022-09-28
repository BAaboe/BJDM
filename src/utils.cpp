#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "utils.h"

using namespace std;

int getNumberOfLines(string fileName){
    int lines = 0;
    
    ifstream fm;
    fm.open(fileName);

    if(fm.is_open()){
        string line;
        while(getline(fm, line)){
            lines++;
        }
    }

    return lines;
}

string* adv_tokenizer(string s, char del, int len){
    string *l; 
    l = new string[len];
    
    stringstream ss(s);
    string word;
    int i = 0;
    while (!ss.eof()) {
        getline(ss, word, del);
        l[i] = word;
        i++;
    }
    return l;
}