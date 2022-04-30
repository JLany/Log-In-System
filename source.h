#ifndef SOURCE_H
#define SOURCE_H

#include<iostream>
#include <map>
#include <iostream>
#include <iterator>
#include<fstream>
#include <regex>
#include <vector>

using namespace std;

struct User {
    string ID = ""; // should be a string to avoid unwanted changes, also not to be restricted by a limit
    string email = "email@gmail.com";
    string phoneNumber = ""; // same thing here 
    string username = "nobody"; 
    string password = "Nobody";
    // no need for intitalization
};

ostream& operator<< (ostream& out, const User& user);
istream& operator>> (istream& in, User& user);
void Register();
void logIn();
void changePassword();
bool emailVerifier(const string&);
bool phoneVerifier(const string&);


void loadProfileData(); // testing function


#endif