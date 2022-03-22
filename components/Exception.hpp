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
                if (this->type==1){ //inventoryFull
                    cout << "Error: inventory is already full!" << endl;
                } else if (this->type==2) { //itemToolNotAvailable
                   cout << "Error: item tool in I"<< this->getErrorElement() <<  " is not available!";
                } else if (this->type==3) { //"itemNotAvailable"
                    cout << "Error: item in I" << this->getErrorElement() << " is not available!" << endl;
                } else if (this->type=4) { //"giveQuantityNotOne"
                    cout << "Error: quantity of item tool can only = 1" << endl;
                } else if (this->type==5) { //"quantityItemIsNotSufficient"
                    cout << "Error: quantity of item is less than "<< this->getErrorElement() << endl;
                } else if (this->type==6) { // "itemInAnIndexIsNotAvailable"
                    cout << "Error: item in " << this->getErrorElement() << " is not available" << endl;
                } else if (this->type==7) { // "craftInvSlotIsNotEmpty"
                    cout << "Error: craft inventory slot is not empty" << endl;
                } else if (this->type==8) { // "cannotOpenFile"
                    cout << "Error: unable to open " << this->getErrorElement() << " file" << endl;
                } else if (this->type==9) { //"indexOutOfBound"
                    cout << "Error: you are trying to access index " << this->getErrorElement();
                } else if (this->type==10) {
                    cout << "Error: unable to open " << this->getErrorElement() << " file" << endl;
                }
        }
};

#endif