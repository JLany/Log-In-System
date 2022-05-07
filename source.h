// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Log-In-System.cpp | header
// Last Modification Date: xx/xx/xxxx
// Author1 and ID and Group: Yousef Kilany | 20210544 | S25
// Author2 and ID and Group: xxxxx xxxxx
// Author3 and ID and Group: xxxxx xxxxx
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
    string ID; // should be a string to avoid unwanted changes, also not to be restricted by a limit
    string username; 
    string password;
    string email;
    string phoneNumber; // same thing here 
    // no need for intitalization
};

extern vector<User> userList;
extern map<string, User> userMap;




// -------------Prototypes-------------
ostream& operator<< (ostream& out, const User& user);
istream& operator>> (istream& in, User& user);
void Register();
bool logIn();
void changePassword();
bool emailVerifier(const string&);
bool phoneVerifier(const string&);

void loadProfileData();
void saveProfileData();
void saveProfileData(User&);
void displayPassReq();
string takePassword();
string hiddenInput();
bool isValidPass(const string&);
bool isStrongPass(string);
void sortStr(string&);


#endif