// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Log-In-System.cpp | main
// Last Modification Date: 12/05/2022
// Author1 and ID and Group: Yousef Kilany | 20210544 | S25
// Author2 and ID and Group: Maya Ayman Zain El-Din | 20210508 | S25
// Author3 and ID and Group: Mahmoud Adel | 20210563 | S25
// Teaching Assistant: Eng. Mahmoud Fateaha
// Purpose: Basic Login System for general use. For companies, Schools, ...etc.
// Description: It is a basic log in system to register and display the user's personal information using a username and a password


#include "CS112-203-2nd-S25-20210508-20210544-20210563-A4-LoginFunctions.h"

int main() {
    bool run = true;
    // at start load data from the file
    if (!loadProfileData()) { // if failed loadData returns zero
        cout << "Failed to load user data. Aborting...";
        return 0;
    }
    // main menu
    while(run){
        printf("Do you want to:\n1-Register\n2-Log In\n3-Change Password\n4-Exit\n");
        char userInput;
        userInput = _getch(); // to block multiple entries at once
        switch (userInput) {
            case '1':
                Register();
                break;
            case '2':
                logIn();
                break;
            case '3':
            if (logIn() == 1) {
                changePassword();
            }
            else
                printf("Invalid Log In.\n");
                break;
            case '4':
                run = false;
                break;
            default:
                cout << "Please choose a valid option.\n";
        }
    }
    // always saving before exit
    saveProfileData();
}

