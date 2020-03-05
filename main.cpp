#include <cstdlib>
#include <cstring>
#include <sys/wait.h> 
#include <iostream>
#include <unistd.h>
#include "Shell.h"
using namespace std;


int main() {
//Printing basic information about the program
    cout << "CS 433 Programming assignment 2" << endl;
    cout << "Author: Collin deKorne and Tannar Mandak" << endl;
    cout << "Date: 03/05/2020" << endl;
    cout << "Course: CS433 (Operating Systems)" << endl;
    cout << "Description : Program to implement a Unix Shell" << endl;
    cout << "=================================" << endl;
    Shell shell;
    char *args[MAX_LINE/2 + 1]; //command line arguments
    char cmdArray[MAX_LINE/2 + 1];//commands
    char saveCmd[MAX_LINE/2 + 1];//history of commands

    while(shell.should_run){
        cout << "\nosh> ";
        fflush(stdout);
        cin.getline(cmdArray, MAX_LINE);
        int j = shell.tokenize(cmdArray, args);
        

        if(shell.validUserCommand(args)){
            shell.userCommand(args);
        }
        else{
            shell.setPreviousCommand(cmdArray);
            if (shell.isAmpersand(args[j-1])) {
                args[j-1] = NULL;
                shell.shellCommand(args, true);
            } else {
                shell.shellCommand(args, false);
            }
        }
        /**
        * After reading user input, the steps are:
        * (1) fork a child process using fork()
        * (2) the child process will invoke execvp()
        * (3) parent will invoke wait() unless command included &
        */
    }


    return 0;
}
