#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
using namespace std;

class Command{
    private:
        string s;
        vector<string> v;
    public:
        Command(string s){
            this->s = s;
            this->v = parseCommand();
        }
        Command(Command& c){
            this->s = c.s;
            this->v = c.v;
        }
        vector<string> parseCommand(){
            this->s;
            stringstream ss(s);
            istream_iterator<string> begin(ss);
            istream_iterator<string> end;
            vector<string> vstrings(begin, end);
            return vstrings;
        }
        void giveCommand(){
            if(this->v[0] == "SHOW"){
                cout << "SHOW" << endl;
            }else if(this->v[0] == "GIVE"){
                cout << "GIVE" << endl;
            }else if(this->v[0] == "DISCARD"){
                cout << "DISCARD" << endl;
            }else if(this->v[0] == "MOVE"){
                cout << "MOVE" << endl;
            }else if(this->v[0] == "USE"){
                cout << "USE" << endl;
            }else if(this->v[0] == "CRAFT"){
                cout << "CRAFT" << endl;
            }else if(this->v[0] == "EXPORT"){
                cout << "EXPORT" << endl;
            }
        }
};

int main(){
    string s;
    cin >> s;
    Command c(s);
    c.parseCommand();
    c.giveCommand();
    
    return 0;
}
