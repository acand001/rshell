#include "semicolon.h"

bool Semicolon::execute() {
        Command* command = new Command (single);
        //cout <<"printing string to execute" << endl;
       // cout << single->load() << endl;
        //cout <<"executing  single command or after semicolon "<< endl;
        return command->execute();
}

string Semicolon::load() {
    return this->str;
}