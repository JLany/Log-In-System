#include "source.h"

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



ostream& operator<< (ostream& out, const User& user) {
    // Encryption of password may occur here
    out << user.ID << ' ';
    out << user.username << ' ';
    out << user.password << ' ';
    out << user.email << ' ';
    out << user.phoneNumber << ' ';
    out << endl;
    return out;
}



istream& operator>> (istream& in, User& user) {
    // probably this overload will only be used to load from file
    // using it for registeration is not ideal
    in >> user.ID;
    in >> user.username;
    in >> user.password;
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
    // take password and verify: {Strength, repeat it, using allowed charcters}

    // saveProfileData(newUser.ID, newUser);
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
    
}


string takePassword() {
    string password, passAgain = "";
    cout << "Password: ";
    cin >> password;
    cout << "Repeat your Password: ";
    cin >> passAgain;
    while (password != passAgain) {
        cout << "Make sure you enter the same password twice! : ";
        cin >> passAgain;
    }
    return password;
}


string hiddenInput() {
	string input;
	char chr;
	chr = _getch();
	while ((int)chr != 13) { // ascii of newline
		if ((int)chr == 8) { // ascii of Backsapce
			cout << '\b' << ' ' << '\b'; // '\b' pushs the cursor 1 step back
			input.pop_back();			 // and then ' ' erases the last charcter
			chr = _getch();
			continue;
		}
		else {
			input += chr;
			cout << '*';
		}
		chr = _getch();
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