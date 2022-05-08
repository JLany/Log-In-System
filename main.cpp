// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Log-In-System.cpp | main
// Last Modification Date: xx/xx/xxxx
// Author1 and ID and Group: Yousef Kilany | 20210544 | S25
// Author2 and ID and Group: Maya Ayman Zain El-Din | 20210508 | S25
// Author3 and ID and Group: xxxxx xxxxx
// Teaching Assistant: Eng. Mahmoud Fateaha
// Purpose:..........


#include "source.h"

int main() {
     loadProfileData();
     bool run = true;

     while(run){
         printf("Do you want to:\n1-Register\n2-Log In\n3-Change Password\n4-Exit\n");
         char userInput;
         cin >> userInput;
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
                return main();
         }
     }
     return 0;
}

