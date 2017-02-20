#include "command.h"


bool Command::execute() {
    int es;
    bool temp = true;
    string tmpStr;
    vector<string> vec ;
   // cout <<"Printing string in command.cpp" << endl;
    //cout << child->load() << endl;
    
    
    //TOKENIZING IN ORDER TO REMOVE SPACES FROM SINGLE COMMAND
    char_separator<char> sep(" "); 
    typedef tokenizer<char_separator<char> > mytok;
    typedef mytok::iterator tok_it;
    mytok tok(child->load(),sep);
    
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

    
    //cout<<"Printing string to be executed" << endl;
  //  cout << child->load();
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
        // then it is a parent so we wait
        // if (waitpid( pid,&status,0) == -1) {
        //     perror("Waitpid failed");
        //     exit(EXIT_FAILURE);
        // }
        // if(WIFEXITED(status)) {
        //  es = WEXITSTATUS(status);
        // }
        while((pid = waitpid(pid, &status,0)) == -1) {
            
            perror("Error! wait failed ");
        }      
        if(WIFEXITED(status)) {
         es = WEXITSTATUS(status);
        }
    }
    //cout << "status" << es << endl;
//make sure to delete array  
    while (!vec.empty())
         {
          vec.pop_back();
         }
        if(es > 0)
        temp = false;
         else 
        temp = true;
  // cout<< "status of temp " << temp << endl;
  return temp;

}