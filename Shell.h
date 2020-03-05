#pragma once

#define MAX_LINE 80 // The maximum length command

class Shell {
    private:
    char history[MAX_LINE/2 + 1];

    public:
    bool should_run; //flag to determine when to exit program
    Shell();
    void setPreviousCommand(char []);
    bool validUserCommand(char*[]);
    int tokenize(char[], char*[]);
    bool isAmpersand(char[]);
    void shellCommand(char*[], bool);
    void userCommand(char*[]);
};