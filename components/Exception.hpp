#ifndef __BASE_EXCEPTION_HPP__
#define __BASE_EXCEPTION_HPP__
#include <iostream>
#include <string>
using namespace std;

template <class T>
class Exception {
    private:
        string type;
        T errorElement;
    public:
        Exception(string type, T errorElement) {
            this.type=type;
            this.errorElement= errorElement;
        }
        Exception(string type) {
            this.type=type;
            this.errorElement=null;
        }
        void printMessage(){
            switch(this.type){
                case "indexOutOfBound":
                    cout << "Error: you are trying to access index " << this.errorElement[0];
                    cout << " of " << this.errorElement[1] << "!" << endl;
                case "commandNotFound":
                    cout << "Error: command " << this.errorElement[0] << " not found!" << endl;
                case: 
                default:
                    cout << "Error!" << endl;
            }
        }
};

#endif