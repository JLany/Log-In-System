#include<iostream>
using namespace std;

struct User {
    string ID = ""; // should be a string to avoid unwanted changes, also not to be restricted by a limit
    string email = "email@gmail.com";
    string phoneNumber = ""; // same thing here 
    string username = "nobody";
    string password = "Nobody";
};