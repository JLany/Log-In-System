// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Log-In-System.cpp | header
// Last Modification Date: 12/05/2022
// Author1 and ID and Group: Yousef Kilany | 20210544 | S25
// Author2 and ID and Group: Maya Ayman Zain El-Din | 20210508 | S25
// Author3 and ID and Group: Mahmoud Adel | 20210563 | S25
// Teaching Assistant: Eng. Mahmoud Fateaha
// Purpose: Basic Login System for general use. For companies, Schools, ...etc.
// Description: It is a basic log in system to register and display the user's personal information using a username and a password


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
    string username;
    string name;
    string password;
    string email;
    string phoneNumber;
};

extern map<string, User> userMap;
extern string currentUserId;




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
int loadProfileData();
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