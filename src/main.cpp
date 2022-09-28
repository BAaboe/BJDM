#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include <security/_pam_types.h>

#include "login.h"

using namespace std;

int getPassword(string *password){
    struct termios tty;

    // Get current terminal settings
    if (tcgetattr(STDIN_FILENO, &tty) != 0)
        return -1;

    // Unset ECHO flag
    tty.c_lflag &= ~ECHO;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) != 0)
        return -1;


    getline(std::cin, *password);
    cout << endl;

    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);

    return 1;
}

int main(){
    string session;
    string username;
    string password;

    while(true){
        system("clear");

        //Show start message

        string welcomeMessage = "Welcome to BJDM!";
        cout << welcomeMessage << endl;

        // Get username
        cout << "User: ";
        getline(std::cin, username);
        
        //Get password
        cout << "Password: ";
        if(getPassword(&password) < 0){
            cout << "Something went wrong." << endl;
            cout << "Press enter to try again..." << endl;
            char *temp;
            cin >> temp;
            sleep(2);
            continue;
        }

        //Checks if password and username are correct
        int n = username.length();
        char usernameA[n+1];
        strcpy(usernameA, username.c_str());

        n = password.length();
        char passwordA[n+1];
        strcpy(passwordA, password.c_str());


        int ok = auth(usernameA, passwordA);


        if(ok != PAM_SUCCESS){
            cout << "Authentication failes." << endl;
            sleep(1);
        } else{
            break;
        }



    }



    return 0;
}