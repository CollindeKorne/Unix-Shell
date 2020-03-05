#include <cstdlib>
#include <cstring>
#include<sys/wait.h> 
#include <iostream>
#include <unistd.h>
#include "Shell.h"
using namespace std;

Shell::Shell(){
    should_run = true;
}

int Shell::tokenize(char cmd[], char* args[]) {
    char *token;
    int i = 0;

    token = strtok(cmd, " ");
    while (token != NULL){
        cout << "TOKEN: " << token << endl;
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
    return i;
}

bool Shell::isAmpersand(char token[]){
    if(token[0] == '&'){
        return true;
    }
    return false;
}

void Shell::shellCommand(char* cmd[], bool async){
    int size = strlen(*cmd);
    cout << "Size: " << size << endl;
    pid_t pid;
    pid = fork();
    if(pid < 0){
        fprintf(stderr, "Fork Failed");
        exit(1);
    }
    else if(pid == 0){
        execvp(cmd[0], cmd);
        printf("Command %s not found(execvp)\n", *cmd);//will print if execvp doesnt work
        exit(1);
    }
    else{
        if(!async)
            wait(NULL);
    }
}

void Shell::setPreviousCommand(char saveCmd[]){
    strcpy(history, saveCmd);
}

bool Shell::validUserCommand(char* cmd[]){
    if(strcmp("exit",cmd[0]) == 0 || strcmp("!!",cmd[0]) == 0){
        return true;
    }
    return false;
}

void Shell::userCommand(char* cmd[]){
    if(strcmp("exit", cmd[0]) == 0){
        should_run = false;
    }
    else if (strcmp("!!", cmd[0]) == 0){
        if(history[0] == '\0'){
            printf("No previous commands!\n");
        }
        else{
            tokenize(history, cmd);
            shellCommand(cmd, false);
        }
    }
}