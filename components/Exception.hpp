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
        Exception(char* type, T errorElement) {
            this.type=string(type);
            this.errorElement= errorElement;
        }
        Exception(char* type) {
            this.type=string(type);
            this.errorElement=NU;
        }
        void printMessage(){
            switch(this.type){
                case "indexOutOfBound":
                    cout << "Error: you are trying to access index " << this.errorElement[0];
                    cout << " of " << this.errorElement[1] << "!" << endl;
                case "commandNotFound":
                    cout << "Error: command " << this.errorElement[0] << " not found!" << endl;
                case "inventoryFull":
                    cout << "Error: Inventory is already full!" << endl;
                default:
                    cout << "Error!" << endl;
            }
        }
};

#endif