#include"data.cpp"
#include <map>
#include <iostream>
#include <iterator>
#include<fstream>
#include <regex>
#include <vector>

using namespace std;

ostream& operator<< (ostream& out, const User& user);
istream& operator>> (istream& in, User& user);
void Register();
void logIn();
void changePassword();
bool emailVerifier(const string&);
bool phoneVerifier(const string&);


void loadProfileData();

int main() {
    loadProfileData();
//     bool run = true;

//     while(run){
//         printf("Choose an option:\n1-Register\n2-Log In\n3-Change Password\n4-Exit\n");
//         char userInput;
//         cin >> userInput;
//         switch (userInput) {
//             case '1':
//                 Register();
//                 break;
// //            case '2':
// //                logIn();
// //                break;
// //            case '3':
// //                changePassword();
// //                break;
//             case '4':
//                 run = false;
//                 break;
//             default:
//                 cout << "Please choose a valid option.";  //needs a loop to handle the wrong input
//                 break;
//         }
//     }


}


void loadProfileData() {
    map<string, User> userMap;
    vector<User> myUsers;
    fstream dataSource;
    User newUser;

    dataSource.open("userDataSample.txt", ios::in);

    while (!dataSource.eof()) {
        dataSource >> newUser;
        myUsers.push_back(newUser);
        userMap.insert(pair<string, User>(myUsers[myUsers.size() - 1].ID, myUsers[myUsers.size() - 1]));
    }

    for (int i = 0; i < myUsers.size(); i++) {
        cout << myUsers[i];
    }

    dataSource.close();

    cout << userMap["20210544"];
}



ostream& operator<< (ostream& out, const User& user) {
    out << user.ID << ' ';
    out << user.username << ' ';
    out << user.password << ' ';
    out << user.email << ' ';
    out << user.phoneNumber << ' ';
    out << endl;
    return out;
}



istream& operator>> (istream& in, User& user) {
    in >> user.ID;
    in >> user.username;
    in >> user.password;
    in >> user.email;
    in >> user.phoneNumber;
    return in;
}



void Register(){
    User userInfo;
    cin >> userInfo;
}

bool emailVerifier(const string& email){
    string local = "[#!%$‘&+*/=?^_`.{|}~a-zA-Z0-9-]{1,62}";
    string preDot = "[a-zA-Z0-9-]{0,61}";
    string postDot = "[a-zA-Z]{2,4}";
    string domainPart = "[a-zA-Z0-9]" + preDot + "[a-zA-Z0-9]" + "[.]" + postDot;
    string localPart = "[#!%$‘&+*/=?^_`{|}~a-zA-Z0-9-]" + local + "[#!%$‘&+*/=?^_`{|}~a-zA-Z0-9-]";
    regex fullEmail((localPart + "[@]" + domainPart));
    return regex_match(email, fullEmail);

}

bool phoneVerifier(const string& phoneNum){
    regex validPhone("[0][1][0|1|2|5][0-9]{8}");
    return regex_match(phoneNum, validPhone);
}










// was a trial to open the file, read line by line, save each line in the user Cstring
// then finally create an id to compare it to the id entered in the register function in the struct User

    //    char user[151];
    //    string currentId;
    //    ifstream database("userData.sample.txt");
    //    database.getline(user, 151);
    //    while (!database.eof()) {
    //        database.getline(user, 151);
    //        for (char i : user) {
    //            if (i != 0)
    //                currentId += i;
    //            else
    //                break;
    //        }
    //        cout << currentId << endl;
    //    }
    //    database.close();

// Another way is to load the first line as a whole into the struct as parameters no idea how then compare the id











//    if (userInput == "1") {
//        //write user info to file ----> needs adjustment
//        //-----------------
//        User p1;
//        cin >> p1;
//        ofstream userlist;
//        userlist.open("userlist.txt", ios::app);
//        userlist << p1.name << endl << p1.age << endl << p1.id << endl << p1.password << endl;
//        userlist.close();
//    }
//    else if (userInput == "2") {
//        //read all users from userlist ---> needs adjustment to find specific user
//        //------------------
//        auto file = ifstream("userlist.txt");
//        vector<User> user;                                 //store users in vector.
//        for (User person; file >> person;)
//            user.push_back(person);
//        for (auto const& person : user)                     //prints each user full information
//            cout << person;
//    }