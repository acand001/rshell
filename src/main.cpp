#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>


#include "base.h"
#include "and.h"
#include "cmds.h"
#include "or.h"
#include "semicolon.h"


using namespace std;
using namespace boost;


//REMOVE SEMICOLON, ||, AND && FROM STRING
void pars(string s, vector<string> &vec) {
    string tmpStr;
    //boost::split(vec, s, boost::is_any_of(";&&||"));
    
    char_separator<char> sep(";||&&");
    typedef tokenizer<char_separator<char> > mytok;
    typedef mytok::iterator tok_it;
    mytok tok(s, sep);
    
     for(tok_it i= tok.begin(); i != tok.end(); i++) {
         //keep track where # is located

        tmpStr = *i;
        
         //Trims Leading space from string
        if (tmpStr[0] == ' '){
            tmpStr.erase(0,1);    //was there supposed to be a 1 here?
        }
        
        vec.push_back(tmpStr);
    } 
}

//EXTRACT CONNECTORS
void capCon(string& input, vector<string>& cnn){
    
    string tmpStr;
    
    for(unsigned int i = 0; i < input.size(); i++){
        
        if(input[i] == '&'){
            tmpStr = "&&";
            //cout<<"peek 1"<<endl;
            //cout<<tmpStr<<endl;
            cnn.push_back(tmpStr);
            i++;
        }else if(input[i] == '|'){
            tmpStr = "||";
            //cout<<"peek 2"<<endl;
            //cout<<tmpStr<<endl;
            cnn.push_back(tmpStr);
            i++;
        }else if(input[i] == ';'){
            tmpStr = ";";
            //cout<<"peek 3"<<endl;
            //cout<<tmpStr<<endl;
            cnn.push_back(tmpStr);
            i++;
        }
        
    }
    
}


//PRINTS VECTOR OF STRINGS
void print(vector <string> s){
    for(unsigned i = 0; i<s.size();i++){
        cout<<s.at(i);
        cout<<endl;
    }
}


string deleteCommentAfterHack(string input){
        //Here we check for the first element of the 
        //string if # then step out of parsing
    string mystr = input.substr(0, input.find("#", 0));

return mystr;
}


int main(){
    
string input;
vector<string> cmds;
vector<string> cnn;

 
    // /EXTRA CREDIT $$$
    // char* login = getlogin();        //does not work on c9
    // char hostname[128];

    // if (login == NULL) 
    //     perror("getlogin() error");
    // else if (gethostname(hostname, 128) == -1)
    //     perror("gethostname() error");
    // else
    //     cout << login << "@" << hostname << "$ ";
        
        //LOOPS THROUGH CONNECTORS AND COMMANDS
        
        
    // Cmds * cmd = new Cmds("ls -l");
    // Semicolon * s = new Semicolon(cmd);
    // s->execute();
    
    
    
      while(1) {
           
       // /EXTRA CREDIT $$$
     char* login = getlogin();        //does not work on c9
     char hostname[128];

     if (login == NULL) 
         perror("getlogin() error");
     else if (gethostname(hostname, 128) == -1)
         perror("gethostname() error");
     else
        cout << login << "@" << hostname << "$ ";
        getline(cin, input);

        string get = deleteCommentAfterHack(input);
        pars(get, cmds);
        capCon(get, cnn);
        cout << endl;
        
        // cout << "Printing vector wihtin while " << endl;
        // for(unsigned i = 0; i < cmds.size(); i++) {
        //     cout << cmds[i] << " ";
        // }
    cout << endl;
      if(cmds.empty()) {
            cout <<"empty strings" << endl;
            continue;
       
      }else if(cnn.empty() && !(cmds.empty())){      //run single commands 
          //cout<<"execute single commands"<< endl;
            
            //CHECK FOR EXIT
            if(cmds.at(0) == "exit"){/*EXIT PROGRAM OR JUST PROMPT*/
                cout<<"Exiting Rshell" << endl;
                exit(0);
            }
           // print(cmds);
            //out << "printing first value "<< cmds[0] << endl; /////THIS PRINTS HELLO WORLD?
            //out << cmds[0] << endl;
            Cmds* cmds0 = new Cmds(cmds[0]);
            //cout << "printing string that was passed into CMDS " << cmds0->load() << endl;
            Semicolon* S = new Semicolon(cmds0);
            S->execute();
            delete cmds0;
            delete S;
            // delete cmds0;
            // delete S;
      }
      else{
       
            int j = 0;
            for(unsigned int i = 0; i<cnn.size(); i++){
               
                  if(cnn.at(i) == "&&"){
                        
                        //CHECK FOR EXIT
                        if(cmds.at(i) == "exit"){/*EXIT PROGRAM OR JUST PROMPT*/
                            cout <<"exiting rshell"<< endl;
                            exit(0);
                        }
                        
                        Cmds* cmds1 = new Cmds(cmds.at(j));
                        j++;
                        
                        //CHECK FOR EXIT
                        if(cmds.at(i) == "exit"){/*EXIT PROGRAM OR JUST PROMPT*/
                            cout <<"exiting rshell"<< endl;
                            exit(0);
                        }
                        
                        Cmds* cmds2 = new Cmds(cmds.at(j));
                        And* A = new And(cmds1, cmds2);
                        A->execute();
                        delete cmds1;
                        delete cmds2;
                        delete A;
                   
                  }else if(cnn.at(i) == "||"){
                        
                        //CHECK FOR EXIT
                        if(cmds.at(i) == "exit"){/*EXIT PROGRAM OR JUST PROMPT*/
                            cout <<"exiting rshell"<< endl;
                            exit(0);
                        }
                        
                        Cmds* cmds1 = new Cmds(cmds.at(j));
                        j++;
                        
                        //CHECK FOR EXIT
                        if(cmds.at(i) == "exit"){/*EXIT PROGRAM OR JUST PROMPT*/
                            cout <<"exiting rshell"<< endl;
                            exit(0);
                        }
                        
                        Cmds* cmds2 = new Cmds(cmds.at(j));
                        Or* O = new Or(cmds1, cmds2);
                        O->execute();
                        delete cmds1;
                        delete cmds2;
                        delete O;
                        
                  }else if(cnn.at(i) == ";"){
                        
                        //CHECK FOR EXIT
                        if(cmds.at(i) == "exit"){/*EXIT PROGRAM OR JUST PROMPT*/
                            cout <<"exiting rshell"<< endl;
                            exit(0);
                        }
                        
                        Cmds* cmds1 = new Cmds(cmds.at(j));
                        Semicolon* S = new Semicolon(cmds1);
                        S->execute();
                        ///THIS SHOULD CAPTURE COMMAND AFTER LAST SEMICOLON
                        if(cnn.at(i) == cnn.back()) {
                            j++;
                            
                            //CHECK FOR EXIT
                            if(cmds.at(i) == "exit"){/*EXIT PROGRAM OR JUST PROMPT*/
                                cout <<"exiting rshell"<< endl;
                            exit(0);
                            }
                            
                            Cmds* cmds1 = new Cmds(cmds.at(j));
                            Semicolon* S = new Semicolon(cmds1);
                            S->execute();
                            delete cmds1;
                            delete S;
                                          }
                  }else if(cnn.at(i) == "#"){
                      //IF WE FIND # IN THE CONNECTORS THEN EVERYTHING ELSE IS A COMMENT
                      
                     
                  }
             
            }
            //continue;
        
        }
        // cout << "printing vector after execution" << endl;
        // print(cnn);
        // print(cmds);
        //clear here within the while
        // cin.ignore(numeric_limits<streamsize>::max(),'\n');
        while (!cmds.empty())
         {
             //cout <<"popping back command vector "<<endl;
          cmds.pop_back();
         }
            while (!cnn.empty())
         {
            // cout <<"popping back connector vector "<<endl;
          cnn.pop_back();
         }
    }
    
    return 0;
}
