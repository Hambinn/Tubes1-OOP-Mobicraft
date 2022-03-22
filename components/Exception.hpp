#ifndef __BASE_EXCEPTION_HPP__
#define __BASE_EXCEPTION_HPP__
#include <iostream>
#include <string>
using namespace std;

template <class T>
class Exception {
    private:
        int type;
        T errorElement;
    public:
        Exception(int type, T errorElement) {
            this->type=type;
            this->errorElement= errorElement;
        }
        Exception(int type) {
            this->type=type;
            this->errorElement="";
        }
        T getErrorElement() {
            return this->errorElement;
        }
        void printMessage(){
            switch(this->type){
                // case "indexOutOfBound":
                //     cout << "Error: you are trying to access index " << to_string(this->errorElement[0]);
                //     cout << " of " << to_string(this->errorElement[1]) << "!" << endl;
                // case "commandNotFound":
                //     cout << "Error: command " << this->getErrorElement() << " not found!" << endl;
                case 1: //inventoryFull 
                    cout << "Error: inventory is already full!" << endl;
                case 2: //itemToolNotAvailable
                    cout << "Error: item tool in I"<< this->getErrorElement() <<  " is not available!";
                case 3: //"itemNotAvailable"
                    cout << "Error: item in I" << this->getErrorElement() << " is not available!" << endl;
                case 4: //"giveQuantityNotOne":
                    cout << "Error: quantity of item tool can only = 1" << endl;
                case 5: //"quantityItemIsNotSufficient":
                    cout << "Error: quantity of item is less than "<< this->getErrorElement() << endl;
                case 6: // "itemInAnIndexIsNotAvailable":
                    cout << "Error: item in " << this->getErrorElement() << " is not available" << endl;
                case 7: // "craftInvSlotIsNotEmpty":
                    cout << "Error: craft inventory slot is not empty" << endl;
                default:
                    cout << "Error!" << endl;
            }
        }
};

#endif