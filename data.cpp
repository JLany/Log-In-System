#include<iostream>
using namespace std;

struct User {
    int ID = 0; // should be a string to avoid unwanted changes, also not to be restricted by a limit
    string email = "email@gmail.com";
    int phoneNumber = 1; // same thing here 
    string username = "nobody";
    string password = "Nobody";
};