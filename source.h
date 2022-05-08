// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Log-In-System.cpp | header
// Last Modification Date: xx/xx/xxxx
// Author1 and ID and Group: Yousef Kilany | 20210544 | S25
// Author2 and ID and Group: Maya Ayman Zain El-Din | 20210508 | S25
// Author3 and ID and Group: Mahmoud Adel | 20210563 | S25
// Teaching Assistant: Eng. Mahmoud Fateaha
// Purpose:..........


#ifndef SOURCE_H
#define SOURCE_H


// -------------Includes-------------
#include <iostream>
#include <map>
#include <iostream>
#include <iterator>
#include <fstream>
#include <regex>
#include <vector>
#include <conio.h>


using namespace std;


// -------------Declarations-------------
struct User {
    string username; // should be a string to avoid unwanted changes, also not to be restricted by a limit
    string name;
    string password;
    string email;
    string phoneNumber;
};

extern map<string, User> userMap;




// -------------Prototypes-------------
ostream& operator<< (ostream&, const User&);
istream& operator>> (istream&, User&);
void Register();
bool logIn();
void changePassword();

bool emailVerifier(const string&);
bool phoneVerifier(const string&);
bool usernameVerifier(const string&);
bool validateRegistration(map<string, User>, User&);
bool emailRepeated(const string&, User&);
bool usernameRepeated(const string&, User&);
void loadProfileData();
void saveProfileData();
void saveProfileData(User&);
void displayPassReq();
string takePassword();
string hiddenInput();
bool isValidPass(const string&);
bool isStrongPass(string);
void sortStr(string&);

string encryption(string);
string decryption(string);


void cleanStream(istream&);
#endif