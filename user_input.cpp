#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
using namespace std;

vector<string> parseInput(string s){
    stringstream ss(s);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    return vstrings;
}

void getCommand(vector<string> s){
    if(s[0] == "SHOW"){
        cout << "SHOW" << endl;
    }else if(s[0] == "GIVE"){
        cout << "GIVE" << endl;
    }else if(s[0] == "DISCARD"){
        cout << "DISCARD" << endl;
    }else if(s[0] == "MOVE"){
        cout << "MOVE" << endl;
    }else if(s[0] == "USE"){
        cout << "USE" << endl;
    }else if(s[0] == "CRAFT"){
        cout << "CRAFT";
    }else if(s[0] == "EXPORT"){
        cout << "EXPORT";
    }
}

int main(){
    string s;
    getline(cin, s);
    vector<string> input = parseInput(s);
    getCommand(input);
    // std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n")); 
    

    return 0;
}