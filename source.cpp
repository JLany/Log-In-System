// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Log-In-System.cpp | implementation
// Last Modification Date: xx/xx/xxxx
// Author1 and ID and Group: Yousef Kilany | 20210544 | S25
// Author2 and ID and Group: xxxxx xxxxx
// Author3 and ID and Group: xxxxx xxxxx
// Teaching Assistant: Eng. Mahmoud Fateaha
// Purpose:..........


#include "source.h"

vector<User> userList;
map<string, User> userMap;

void loadProfileData() {
    fstream dataSource;
    User newUser;

    dataSource.open("userDataSample.txt", ios::in);

    while (!dataSource.eof()) {
        dataSource >> newUser;
        userList.push_back(newUser);
        userMap.insert(pair<string, User>(
            userList[userList.size() - 1].ID, userList[userList.size() - 1]
                )
            );
    }

    dataSource.close();
}


void saveProfileData() {
    fstream dataTarget;

    dataTarget.open("userDataSample.txt", ios::out);

    for (User& user : userList) {
        dataTarget << user;
    }

    dataTarget.close();
}


void saveProfileData(User& newUser) {
    fstream dataTarget;

    userList.push_back(newUser);
    userMap.insert(pair<string, User>(newUser.ID, newUser));

    dataTarget.open("userDataSample.txt", ios::out);

    for (User& user : userList) {
        dataTarget << user;
    }

    dataTarget.close();
} 



ostream& operator<< (ostream& out, const User& user) {
    out << user.ID << ' ';
    out << user.username << ' ';
    // Encryption of password may occur here
    out << user.password << ' ';
    out << user.email << ' ';
    out << user.phoneNumber << endl;
    return out;
}



istream& operator>> (istream& in, User& user) {
    // probably this overload will only be used to load from file
    // using it for registeration is not ideal
    in >> user.ID;
    in >> user.username;
    in >> user.password;
    // decryption of password may occur here
    in >> user.email;
    in >> user.phoneNumber;
    return in;
}



void Register() {
    User newUser;
    // take ID and verify it
    // take E-mail and verify its format and non-use before
    // take username and verify it
    // take mobile number and verify it
    newUser.password = takePassword();

    saveProfileData(newUser);
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


void displayPassReq() {
    cout << "Password should at least have one Capital letter, one small letter,\n";
    cout << "one digit, one symbol, and at least 8 characters long.\n";
    cout << "Allowed symbols: !#$%&*+-\n";
}


string takePassword() {
    string password, passAgain = "";
    displayPassReq();
    cout << "Password: ";
    password = hiddenInput();
    while (!isValidPass(password)) {
        cout << "Invalid Charcters used!\n";
        displayPassReq();
        cout << "Password: ";
        password = hiddenInput();
    }
    while (!isStrongPass(password)) {
        cout << "Weak Password, make sure you follow rules:\n";
        displayPassReq();
        cout << "Password: ";
        password = hiddenInput();
    }
    cout << "Repeat your Password: ";
    passAgain = hiddenInput();
    while (password != passAgain) {
        cout << "Make sure you enter the same password twice! : ";
        passAgain = hiddenInput();
    }
    return password;
}


bool isValidPass(const string& password) {
    regex validPass("[!#$%&*+a-zA-Z0-9-]{8,100}");
    return regex_match(password, validPass);
}


bool isStrongPass(string password) {
    regex strongPass("[!#$%&*+-]+[0-9]+[A-Z]+[a-z]+");
    sortStr(password);
    return regex_match(password, strongPass);
}

void sortStr(string& str) {
    for (int i = 0; i < str.length() - 1; i++) {
        for (int j = 0; j < str.length() - 1 - i; j++) {
            if (str[j] > str[j+1]) {
                swap(str[j], str[j+1]);
            }
        }
    }
}

string hiddenInput() {
	string input;
	char chr;
	while (true) { 
        chr = _getch();
        if ((int)chr == 13) { // ascii of newline
            break;
        }
		if ((int)chr == 8) { // ascii of Backsapce
            if (input.length() < 1) { // to avoid unwanted erasing
                continue;
            }
			cout << '\b' << ' ' << '\b'; // '\b' pushes the cursor 1 step back
			input.pop_back();			 // and then ' ' erases the last charcter
			continue;
		}
        input += chr;
        cout << '*';
	}
	cout << endl;

	return input;
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