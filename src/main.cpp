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
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <queue>
#include <stack>
#include <list>


using namespace std;
using namespace boost;

queue<string> insideQ;
list<string> connectors;

vector<string> temp;
vector<string> tempDos;
queue<string> outsideQ;
stack<bool> myBools;
stack<string> tempContainer;
queue<string> connectorsBetweenParenthesis;

bool boolean = false;

///TEST CHECK FUNCTION
bool chkForTest( string& input,  vector<string>& temp ){
    
    string tmpStr;
    //bool testForBool = false;
    char_separator<char> sep(" ");
    typedef tokenizer<char_separator<char> > mytok;
    typedef mytok::iterator tok_it;
    mytok tok(input, sep);
      for(tok_it i= tok.begin(); i != tok.end(); i++) {
        tmpStr = *i;
        
         //Trims Leading space from string
        if (tmpStr[0] == ' '){
            tmpStr.erase(0,1);  
        }
        temp.push_back(tmpStr);
      }
        tmpStr = "";
        //cout << endl;
        
        //cout << " printing whats inside vector after parsing for test " << endl;
        // for(unsigned i = 0; i< temp.size(); i++) {
        //     cout << temp[i] << endl;
        // }
        //bool checkForBracket = false;
        //cout << endl;
        //unsigned i = 0;
        unsigned counter = 0;
        unsigned bracketCounter = 0;
        struct stat sb;
        for( unsigned i = 0; i < temp.size(); i++) {     
             counter = 0;
             if(temp[counter] == "test" || temp[counter] == "["){
                 if(temp.at(counter) == "[") {
                     //cout << "found bracket" << endl;
                    vector<string>::iterator it = temp.begin ();
                    //cout << "setup iterator"<< endl;
                    while(it != temp.end()) {
                        if(*it == "]")  {
                        //cout << *it << "found closing bracket " << "counter:  " << bracketCounter<<endl;
                        //  temp.erase(temp.begin());
                        //  temp.erase(temp.begin()+bracketCounter);
                        break;
                      }
                        
                        else if(it == temp.end()) {
                            //cout << "did not find closing bracket! " << endl;
                            return false;
                        }
                        else
                        {
                        it++;
                        bracketCounter++;
                    }
                  }
                  
                } 
                 counter++;
                 //cout << "printing string" << temp.at(counter)<<endl;
                 //checking for out of bands incase user omitted path 
                try {
                    if(temp.at(counter) == "\0"); 
                    }
                catch(const out_of_range& e) {
                    cout << "(False)"<< endl;
                    return false;
                }
                if( ( temp[counter] == "-d" ) || ( temp[counter] == "-e" ) || ( temp[counter] == "-f" ) ) {
                    counter++;
                    //checking for out of bounds incase user omitted path after entering flag
                    try {
                        if(temp.at(counter) == "\0");
                        }
                        catch (const out_of_range& e) {
                            cout << "(False)"<<endl;
                            return false;
                    }
                 }
                if(stat(temp[counter].c_str(), &sb) == -1 )  {
                    perror("stat");
                    cout << "(False)"<<endl;
                    return false;
                }
                // //  //checks for -e flag 
                else if ( temp.at(counter-1) == "-e") {
                    if( (sb.st_mode & S_IFDIR) || ( sb.st_mode & S_IFREG )  ) {
                        //cout << "checking for -e flag " << endl;
                        cout << "(True)"<<endl;
                        return true;
                    }
                    else {
                        cout << "(False)"<<endl;
                        return false;
                    }
                }
                else if ( temp.at(counter-1) == "-f" ) {
                    if (sb.st_mode & S_IFREG) {
                        //cout << "-F FLAG "<< endl;
                        cout << "(True)"<<endl;
                        return true;
                    }
                    else {
                        cout << "(False)"<<endl;
                        return false;
                    }
                }
                // // //This will check for -d flag 
                else if( temp.at(counter-1) == "-d") {
                    if (sb.st_mode & S_IFDIR)  { 
                    //cout << "CHECKING for -d flag" << endl;
                        cout << "(True)"<<endl;
                         return  true;
                    }
                    else {
                        cout <<"(False)"<<endl;
                        return false;
                    }
                }
                else {
                    if( (sb.st_mode & S_IFDIR) || ( sb.st_mode & S_IFREG )  ) {
                        cout <<"(True)"<<endl;
                        return true;
                    }
                    else {
                        cout <<"(False)"<<endl;
                        return false;
                    }
                }
         
             }
    }

    return false; ///ADDED THIS BECASE OF COMPILING ERROR -VM 
}


//EXIT FUNCTION | CHECKS FOR EXIT IN COMMANDS
void chkExit(string& cmds){

    if(cmds == "exit"){
        cout <<"Exiting Rshell..."<<endl;
        exit(0);
    }
}


//DELETES COMMENTS AFTER # <===== THIS MIGHT NEED SOME WORK!!!
string deleteCommentAfterHack(string input){
        //Here we check for the first element of the 
        //string if # then step out of parsing
    string mystr = input.substr(0, input.find("#", 0));

    return mystr;

}

//REMOVE SEMICOLON, ||, AND && FROM STRING
void parsQ(string s, queue<string>& cmds){   
    string tmpStr;
    
    char_separator<char> sep(";||&&");
    typedef tokenizer<char_separator<char> > mytok;
    typedef mytok::iterator tok_it;
    mytok tok(s, sep);
    
     for(tok_it i= tok.begin(); i != tok.end(); i++) {
    
        tmpStr = *i;
        
        //CHECKS IF STRING IS EMPTY
        if(tmpStr == " "){
            continue;
        }
        
        
         //Trims Leading space from string
        if (tmpStr[0] == ' '){
            tmpStr.erase(0,1);  
        }
        
        chkExit(tmpStr);//CHECKING FOR EXIT
        deleteCommentAfterHack(tmpStr);//CHECK COMMENT HASH #
        
        cmds.push(tmpStr);
        
    }
    
    tmpStr = "";
    
}

//EXTRACT CONNECTORS
void capConQ(string& s, list<string>& cnn){
    
    string tmpStr2;
    
        for(unsigned int i = 0; i < s.size(); i++){
            
            if(s[i] == '&'){
                tmpStr2 = "&&";
                //cout<<"peek 1"<<endl;
                //cout<<tmpStr<<endl;
                cnn.push_back(tmpStr2);
                i++;
            }else if(s[i] == '|'){
                tmpStr2 = "||";
                //cout<<"peek 2"<<endl;
                //cout<<tmpStr<<endl;
                cnn.push_back(tmpStr2);
                i++;
            }else if(s[i] == ';'){
                tmpStr2 = ";";
                //cout<<"peek 3"<<endl;
                //cout<<tmpStr<<endl;
                cnn.push_back(tmpStr2);
            }
        
    }
}


///BOOL EXECUTE FUNCTION + EXECVP
bool execute(string str ) {
    int es;
    bool temp = true;
    string tmpStr;
    vector<string> vec ;
 
    //TOKENIZING IN ORDER TO REMOVE SPACES FROM SINGLE COMMAND
    char_separator<char> sep(" "); 
    typedef tokenizer<char_separator<char> > mytok;
    typedef mytok::iterator tok_it;
    mytok tok(str,sep);
    
    for(tok_it i= tok.begin(); i != tok.end(); i++) {
        tmpStr = *i;
        vec.push_back(tmpStr);
    }
    
    //CONVERTING TO CHAR**
    char **ex = new char*[vec.size()+1];
    size_t k = 0;
    for(size_t i = 0; i < vec.size(); i++) {
        string temp = vec[i];
        ex[k] = new char[vec.size()+1];
        strcpy(ex[k], temp.c_str());
        k++;
    }
        
        ex[k] = 0;

    ///EXECVP FROM THIS POINT DOWN
    pid_t pid = fork();
    int status;
    if(pid < 0) {
        //error failed to fork()
        perror(" Error, forking child process failed! ");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        //then it is a child process
        (execvp(ex[0],ex)==-1);
        perror(" excevp failed! ");
        //if the cout prints then error, exit program 
        exit(EXIT_FAILURE);
    }
    else {
        while((pid = waitpid(pid, &status,0)) == -1) {
            
            perror("Error! wait failed ");
        }      
        if(WIFEXITED(status)) {
         es = WEXITSTATUS(status);
        }
    }
    //make sure to delete array  
    while (!vec.empty())
         {
          vec.pop_back();
         }
        if(es > 0)
        temp = false;
         else 
        temp = true;

  return temp;

}

///BOOL CHECK FUNCTION
void boolChk(list<string>& connectors, queue<string>& insideQ){
    
    boolean = execute(insideQ.front());
    insideQ.pop();
    myBools.push(boolean);
    
    while(!connectors.empty()){    
        if(myBools.top() && (connectors.front() == "&&")) {
            //can add another if here for exit
            boolean = execute(insideQ.front());
            myBools.push(boolean);
            connectors.pop_front();
            insideQ.pop();
        }
        else if(!myBools.top() && (connectors.front() == "||")) {
            //can add another if here for exit
            //myBools.pop();
            boolean = execute(insideQ.front());
            myBools.push(boolean);
            connectors.pop_front();
            insideQ.pop();
            
        }    
        
        else if(connectors.front() == ";" ) {
            //can add another if here for exit
            //myBools.pop();
            boolean = execute(insideQ.front());
            myBools.push(boolean);
            connectors.pop_front();
            insideQ.pop();

        }
        else 
        {
           insideQ.pop();
            connectors.pop_front();
        }
    }
     
}


///TRIMS OUTER SPACES
string trim(string& str){
    
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first){
        return str;
    }
    
    size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
}



///CLEANS UP VECTOR AND PREPS IT FOR QUEUE
void vecCleanUp(vector<string>& temp, vector<string>& tempDos, queue<string>& newQ){     

        string s;
        //int last = s.length()-1;
        ////CLEAN-UP VECTOR AND CONVERT TO QUEUES
        for(unsigned i = 1; i < temp.size(); i++){
            s = temp.at(i); 
                    
            if(s == ""){
                continue;
                
                
            }else{
                
                tempDos.push_back(trim(s));
                
            }    
            
        }
                temp.clear();

        for(unsigned i = 0; i < tempDos.size(); i++){
   
            if(tempDos.at(i) == ""){
                continue;
            }else{
                
            newQ.push(tempDos.at(i));
            }
            
        }
        
        
   }

//PRINTS STACK CONTENTS
void printS(stack<string> s){
    int i = 0;
    while(!s.empty()){
    cout<<i<<": "<<s.top()<<endl;
    s.pop();
    i++;
    }
}


//PRINTS VECTOR CONTENTS
void printVec(vector<string> v){
   for(unsigned i = 0; i < v.size(); i++){
       cout<<i<<": "<<v.at(i)<<endl;
   }
}


//PRINTS QUEUE CONTENTS
void printQ(queue<string> q){
    int i = 0;
    while(!q.empty()){
    cout<<i<<": "<<q.front()<<endl;
    q.pop();
    i++;
    }
}

void analyze(string& input){
        string tString;
         
        if(input.find("(") != string::npos && input[0] != '(' && input[input.length()-1] == ')' ){
            ///IF "(" IS NOT THE FIRST POSITION
            string noParStr;
            int pos;
           
            split(temp, input, is_any_of("()"));
            
                for(unsigned i = 0; i < input.size(); i++){
                    if(input[i] == '('){
                        pos = i;
                    }
                }
                    noParStr = input.substr(0, pos);
                    temp.push_back(noParStr);
                    
            vecCleanUp(temp, tempDos, outsideQ);
            ///outsideQ WILL BE THE QUEUE OF STRINGS WHICH HAVE BEEN BROKEN DOWN BY PRECEDENCE
            
            
            while(!outsideQ.empty()){
                tempContainer.push(outsideQ.front());
                outsideQ.pop();
            }
                
            
            while(!tempContainer.empty()){
                outsideQ.push(tempContainer.top());
                tempContainer.pop();
            }
                
                unsigned counter  = 0;
                counter = outsideQ.size();
                
                while(counter > 0){

                    tString = outsideQ.front();
                             parsQ(tString, insideQ);
                             capConQ(tString, connectors);
                             
                            connectorsBetweenParenthesis.push(tString); 
                            outsideQ.pop();
                            tString = outsideQ.front();
                            counter--;
                            parsQ(tString, insideQ);
                            capConQ(tString, connectors);
                            
                             boolChk(connectors, insideQ);

                             outsideQ.pop();
                             
                             
                             counter--;
                             
                } 
                    
         } else if(input.find("(") != string::npos && input[0] == '(' && input[input.length()-1] == ')'){
            
            ///FROM BOOST EXTRACTS EVERYTHING WITHING PARANTHESIS
            split(temp, input, is_any_of("()")); 

            vecCleanUp(temp, tempDos, outsideQ);
            ///outsideQ WILL BE THE QUEUE OF STRINGS WHICH HAVE BEEN BROKEN DOWN BY PRECEDENCE
     
  
          char OR[] = "||";
          char AND[] = "&&";
          char SEMI[] = ";";
                
                unsigned counter  = 0;
                counter = outsideQ.size();
                while(counter > 0){

                             tString = outsideQ.front();
                             parsQ(tString, insideQ);
                             capConQ(tString, connectors);
                             boolChk(connectors, insideQ);
                             outsideQ.pop();
                            tString = outsideQ.front();
                      if(tString == OR || tString == AND || tString == SEMI) {

                            connectorsBetweenParenthesis.push(tString); 
                            outsideQ.pop();

                            tString = outsideQ.front();
                            counter--;
                            
                            if(myBools.top() && connectorsBetweenParenthesis.front() == "&&") {
                               
                                parsQ(tString, insideQ);
                                capConQ(tString, connectors);
                                boolChk(connectors, insideQ);
                                 outsideQ.pop();
                                 counter--;
                                    }
                            else if(!myBools.top() && connectorsBetweenParenthesis.front() == "||") {
                                
                                parsQ(tString, insideQ);
                                capConQ(tString, connectors);
                                boolChk(connectors, insideQ);
                                outsideQ.pop();
                                counter--;
        
                            }
                            else if(connectorsBetweenParenthesis.front() == ";") {
                             
                                parsQ(tString, insideQ);
                                capConQ(tString, connectors);
                                boolChk(connectors, insideQ);
                                outsideQ.pop();
                                counter--;
                            }
                            else {
                               
                                counter--;
                            }
                                
                    }
                    
                    counter--;
                } 
            
        }else if(input.find("(") != string::npos && input[0] == '(' && input[input.length()-1] != ')'){

             ///IF "(" IS NOT THE FIRST POSITION
            string noParStr;
            int pos;
           
            split(temp, input, is_any_of("()"));
            
                for(unsigned i = 0; i < input.size(); i++){
                    if(input[i] == ')'){
                        pos = i;
                    }
                }
                    noParStr = input.substr(pos+1, input.length()-1);
                    
                    
            vecCleanUp(temp, tempDos, outsideQ);
            ///outsideQ WILL BE THE QUEUE OF STRINGS WHICH HAVE BEEN BROKEN DOWN BY PRECEDENCE
            
                //printVec(tempDos);

                unsigned counter  = 0;
                counter = outsideQ.size();
                
                while(counter > 0){
                    tString = outsideQ.front();
                   
                             parsQ(tString, insideQ);
                             capConQ(tString, connectors);
                             
                            connectorsBetweenParenthesis.push(tString); 
                            outsideQ.pop();
                            tString = outsideQ.front();
                            counter--;
                            parsQ(tString, insideQ);
                            capConQ(tString, connectors);
                            boolChk(connectors, insideQ);
 
                             outsideQ.pop();
                             
                             
                             counter--;
                             
                } 

        }else{
            
        ///ELSE REGULAR INPUT WITHOUT ANY PARANTHESIS
                    parsQ(input, insideQ);
                    capConQ(input, connectors);
                    boolChk(connectors, insideQ);    
            
        }
        

            ///CLEANING UP ALL QUEUES/STACKS/VECTORS/LISTS
            while(!insideQ.empty()){insideQ.pop();}
            while(!connectors.empty()){connectors.clear();}            
            while(!temp.empty()){temp.clear();}    
            while(!tempDos.empty()){tempDos.clear();} 
            while(!outsideQ.empty()){outsideQ.pop();}            
            while(!myBools.empty()){myBools.pop();} 
            while(!tempContainer.empty()){tempContainer.pop();}            
            while(!connectorsBetweenParenthesis.empty()){connectorsBetweenParenthesis.pop();}

}


/////TEST COMMAND FUNCTION
bool testCmd(string& input, queue<string>& tmpQ){

     string tmpStr;
     parsQ(input, tmpQ);
     tmpStr = tmpQ.front();
     cout<<tmpStr<<endl;
     //HERE WE CAN TAKE THE STRING WITH TEST COMMANDS AND DO WHAT WE NEED TO DO.
    
    return true;
}

int main(){

//VARIABLE DECLERATION    
string input;

        while(1){
        
            cout<<"$ ";
            getline(cin, input);
            
            //REMOVE ALL COMMENTS FOLLOWED BY AND INCLUDING #
            string newInput = deleteCommentAfterHack(input);
            
            //CHECK FOR TEST COMMAND
            chkForTest(input, temp);

            //PROCEED TO ANALYZE INPUT
            analyze(input);
            
            
        }
       
    return 0;
}