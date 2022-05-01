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
void logIn();
void changePassword();
bool emailVerifier(const string&);
bool phoneVerifier(const string&);

void displayPassReq();
string takePassword();
void loadProfileData();
void saveProfileData();
void saveProfileData(User&);
string hiddenInput();
bool isValidPass(const string&);
bool isStrongPass(const string&);


#endif