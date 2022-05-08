// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Log-In-System.cpp | implementation
// Last Modification Date: xx/xx/xxxx
// Author1 and ID and Group: Yousef Kilany | 20210544 | S25
// Author2 and ID and Group: Maya Ayman Zain El-Din | 20210508 | S25
// Author3 and ID and Group: xxxxx xxxxx
// Teaching Assistant: Eng. Mahmoud Fateaha
// Purpose:..........


#include "source.h"

map<string, User> userMap;

void loadProfileData() {
    fstream dataSource;
    User newUser;

    dataSource.open("userDataSample.txt", ios::in);

    while (!dataSource.eof()) {
        dataSource >> newUser;
        userMap.insert(pair<string, User>(
            newUser.username, newUser
            )
        );
    }

    dataSource.close();
}


void saveProfileData() {
    fstream dataTarget;

    dataTarget.open("userDataSample.txt", ios::out);

    for (pair<string, User> user : userMap) {
        dataTarget << user.second;
    }

    dataTarget.close();
}


void saveProfileData(User& newUser) {
    fstream dataTarget;

    userMap.insert(pair<string, User>(newUser.username, newUser));

    dataTarget.open("userDataSample.txt", ios::out);

    for (pair<string, User> user : userMap) {
        dataTarget << user.second;
    }

    dataTarget.close();
} 



ostream& operator<< (ostream& out, const User& user) {
    out << user.username << ' ';
    out << user.fullName << ' ';
    // Encryption of password may occur here
    out << user.password << ' ';
    out << user.email << ' ';
    out << user.phoneNumber << endl;
    return out;
}



istream& operator>> (istream& in, User& user) {
    // probably this overload will only be used to load from file
    // using it for registration is not ideal
    in >> user.username;
    in >> user.fullName;
    in >> user.password;
    // decryption of password may occur here
    in >> user.email;
    in >> user.phoneNumber;
    return in;
}



void Register() {
    User newUser;
    cout << "Username:\n";
    cin >> newUser.username;
    while(!usernameVerifier(newUser.username)){
        cout << "Please enter a proper username including letters and '-' ONLY." << endl;
        cin >> newUser.username;
    }

    cout << "Email:\n";
    cin >> newUser.email;
    while(!emailVerifier(newUser.email)){
        cout << "Please enter a valid email." << endl;
        cin >> newUser.email;
    }

    cout << "Phone Number:\n";
    cin >> newUser.phoneNumber;
    while(!phoneVerifier(newUser.phoneNumber)){
        cout << "Please enter a valid phone number." << endl;
        cin >> newUser.phoneNumber;
    }

    newUser.password = takePassword();

    if (validateRegistration(userMap, newUser))
    {
        cout << "You have registered successfully!" << endl;
        saveProfileData(newUser);
    }
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


bool validateRegistration(map<string, User> myUsers, User& newUser){
    bool validUsername = false, validEmail = false;
    map<string, User>::iterator ptr; // pointer to map
    for (ptr = myUsers.begin(); ptr != myUsers.end(); ++ptr) {
        while (newUser.email == ptr -> first) { // (first) refers to key
            cout << "This Email is already registered!\nPlease enter a new Email account:\n";
            cin >> newUser.email;
        }
        validEmail = true;
        while (newUser.username == (ptr -> second).username) { // (second) refers to value
            cout << "Username has been taken!\nPlease enter a different username:\n";
            cin >> newUser.username;
            while(!usernameVerifier(newUser.username)){
                cout << "Please enter a proper username including letters and '-' ONLY." << endl;
                cin >> newUser.username;
            }
        }
        validUsername = true;
        // there is no point in telling the user the password exists, we are violating other users' info if so!
    }
    if(validUsername && validEmail)
        return true;
    else
        return false;
}



bool phoneVerifier(const string& phoneNum){
    regex validPhone("[0][1][0|1|2|5][0-9]{8}");
    return regex_match(phoneNum, validPhone);
}


bool usernameVerifier(const string& username){
    regex validUsername("[a-zA-Z-]+");
    return regex_match(username, validUsername);
}


void displayPassReq() {
    cout << "Password should at least have one Capital letter, one small letter,\n";
    cout << "one digit, one symbol, and at least 8 characters long.\n";
    cout << "Allowed symbols: !#$%&*+-\n";
}


string takePassword() {
    string password, passAgain = "";
    displayPassReq();
    cout << "Password:\n";
    password = hiddenInput();
    while (!isValidPass(password)) {
        cout << "Invalid Password!\n";
        displayPassReq();
        cout << "Password:\n";
        password = hiddenInput();
    }
    while (!isStrongPass(password)) {
        cout << "Weak Password! Make sure you follow rules:\n";
        displayPassReq();
        cout << "Password:\n";
        password = hiddenInput();
    }
    cout << "Repeat your Password:\n";
    passAgain = hiddenInput();
    while (password != passAgain) {
        cout << "Make sure you enter the same password twice!:\n";
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
		if ((int)chr == 8) { // ascii of Backspace
            if (input.length() < 1) { // to avoid unwanted erasing
                continue;
            }
			cout << '\b' << ' ' << '\b'; // '\b' pushes the cursor 1 step back
			input.pop_back();			 // and then ' ' erases the last character
			continue;
		}
        input += chr;
        cout << '*';
	}
	cout << endl;

	return input;
}


string id;
bool logIn() {
    int trials = 3;
    while (trials--) {
        printf("Enter username:\n");
        cin >> id;
        printf("Enter Password:\n");
        string pass = hiddenInput();
        if (auto itr = userMap.find(id) != userMap.end()) {         // find position of the entered username
            User user = userMap[id];                                //if found stores the data in struct to check pass and display results
            if (user.password == pass) {
                printf("Log in successful\nWelcome ");
                cout << user.fullName << '\n';
                return 1;
                //cout << user;           //display all userinfo after successful login
            }
            else {
                printf("Invalid username or Password. Please try again\n");       // password error
            }
        }
        else {
            printf("Invalid username or Password. Please try again\n");       //username error
        }
    }
    printf("Access Denied.\n");
    return 0;
}


void changePassword() {
    printf("Enter old Password:\n");
    string oldpass = hiddenInput();
    if (oldpass != userMap[id].password) {      //check if old pass is entered correctly
        printf("Old password does not match.\n");
        return changePassword();
    }

    while (true) {              //loop till a new password is entered correctly
        printf("Enter new Password.\n");
        string npass = takePassword();
        if (npass == oldpass) {     //check if new pass is different from old pass
            printf("New Password must not be the same as Old Password.\n");
        }
        else {
            printf("Password changed successfully.\n");
            userMap[id].password = npass;       //overwrite password
            break;
        }
    }
    saveProfileData();
}
