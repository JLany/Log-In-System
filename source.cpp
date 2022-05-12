// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Log-In-System.cpp | implementation
// Last Modification Date: xx/xx/xxxx
// Author1 and ID and Group: Yousef Kilany | 20210544 | S25
// Author2 and ID and Group: Maya Ayman Zain El-Din | 20210508 | S25
// Author3 and ID and Group: Mahmoud Adel | 20210563 | S25
// Teaching Assistant: Eng. Mahmoud Fateaha
// Purpose: Basic Login System for general use. For companies, Schools, ...etc.


#include "source.h"

map<string, User> userMap;
string currentUserId;

int loadProfileData() { // int return type to ensure data was
    fstream dataSource; // loaded correctly
    User user;

    dataSource.open("UserData.txt", ios::in);

    if (dataSource.fail()) {
        return 0;
    }

    while (!dataSource.eof()) { // loading profile data into a map
        dataSource >> user;     // overloaded to read userdata line by line
        user.password = decryption(user.password); // decrypt password before inserting
        userMap.insert(pair<string, User>(
            user.username, user // using pair, insert (user.username, actual object: user)
            )
        );
    }

    dataSource.close();
    return 1; // loading successful
}


void saveProfileData() { // to save after changes
    fstream dataTarget;

    dataTarget.open("UserData.txt", ios::out);
    
    for (pair<string, User> user : userMap) { // loop on userMap 
        user.second.password = encryption(user.second.password); // enctypt pass before storing
        dataTarget << user.second; // overloaded to write        // in the file
    }                              // object attributes 
                                   // in one line
    dataTarget.close();
}


void saveProfileData(User& newUser) { // overloaded to add a new user 
    fstream dataTarget;               // to the file

    userMap.insert(pair<string, User>(newUser.username, newUser));
    
    dataTarget.open("UserData.txt", ios::out);

    for (pair<string, User> user : userMap) {
        user.second.password = encryption(user.second.password);
        dataTarget << user.second;
    }

    dataTarget.close();
} 



ostream& operator<< (ostream& out, const User& user) {
    out << user.username << ' ';
    out << user.name << ' ';
    out << user.password << ' ';
    out << user.email << ' ';
    out << user.phoneNumber << endl;
    return out;
}   // each object is written in a separate line



istream& operator>> (istream& in, User& user) {
    in >> user.username;
    in >> user.name;
    in >> user.password;
    in >> user.email;
    in >> user.phoneNumber;
    return in;
}   // assumes that each object is on a separate line



void Register() {
    User newUser;
    cout << "Username (alphabet letters and '-' are only allowed):\n";
    cin >> newUser.username;
    while(!usernameVerifier(newUser.username)){
        cout << "Please enter a proper username including letters and '-' ONLY." << endl;
        cin >> newUser.username;
    }

    cout << "Name:\n";
    cin >> newUser.name;

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


bool emailVerifier(const string& email) {
    string local = "[#!%$‘&+*/=?^_`.{|}~a-zA-Z0-9-]{1,62}";
    string preDot = "[a-zA-Z0-9-]{0,61}";
    string postDot = "[a-zA-Z]{2,4}";
    string domainPart = "[a-zA-Z0-9]" + preDot + "[a-zA-Z0-9]" + "[.]" + postDot;
    string localPart = "[#!%$‘&+*/=?^_`{|}~a-zA-Z0-9-]" + local + "[#!%$‘&+*/=?^_`{|}~a-zA-Z0-9-]";
    regex fullEmail((localPart + "[@]" + domainPart));
    return regex_match(email, fullEmail);

}


bool validateRegistration(map<string, User> myUsers, User& newUser){ // ambigeous function @_@
    map<string, User>::iterator ptr; // pointer to map
    for (ptr = myUsers.begin(); ptr != myUsers.end(); ++ptr) {
        if (emailRepeated(newUser.email, newUser)){
            cout << "This Email is already registered!\nPlease enter a new Email account:\n";
            cin >> newUser.email;
            while(!emailVerifier(newUser.email)){
                cout << "Please enter a valid email." << endl;
                cin >> newUser.email;
            }
            return validateRegistration(userMap, newUser);
        }

        if (usernameRepeated(newUser.username, newUser)){
            cout << "This username has been taken!\nPlease enter a new username:\n";
            cin >> newUser.username;
            while(!usernameVerifier(newUser.username)){
                cout << "Please enter a proper username including letters and '-' ONLY." << endl;
                cin >> newUser.username;
            }
            return validateRegistration(userMap, newUser);
        }

    }

    return 1;
}


bool phoneVerifier(const string& phoneNum){
    regex validPhone("[0][1][0|1|2|5][0-9]{8}");
    return regex_match(phoneNum, validPhone);
}


bool usernameVerifier(const string& username){
    regex validUsername("[a-zA-Z-]+");
    return regex_match(username, validUsername);
}


void displayPassReq() { // Display Passowrd Requirments
    cout << "Password should at least have one Capital letter, one small letter,\n";
    cout << "one digit, one symbol, and at least 8 characters long.\n";
    cout << "Allowed symbols: !#$%&*+-\n";
}


bool emailRepeated(const string& email, User& nUser){
    for (auto& username : userMap) {
        if (nUser.email == username.second.email){
            return true;
        }
    }
    return false;
}


bool usernameRepeated(const string&, User& nUser){
    for (auto& username : userMap) {
        if (nUser.username == username.second.username){
            return true;
        }
    }
    return false;
}


string takePassword() { // takes a password from user and return it
    string password, passAgain;
    displayPassReq();
    cout << "Password:\n";
    password = hiddenInput(); 
    while (!isValidPass(password)) { // re-ask for password until it's valid
        cout << "Invalid Password!\n";
        displayPassReq();
        cout << "Password:\n";
        password = hiddenInput();
    }
    while (!isStrongPass(password)) { // re-ask for password until it's strong
        cout << "Weak Password! Make sure you follow rules:\n";
        displayPassReq();
        cout << "Password:\n";
        password = hiddenInput();
    }
    cout << "Repeat your Password:\n";
    passAgain = hiddenInput();
    while (password != passAgain) { // re-ask to repeat password until same as first one
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
    sortStr(password); // sort pass, because the regex assumes that 
                       // the password is sorted from smallest ascii to largest
    return regex_match(password, strongPass);
}

void sortStr(string& str) { // poor sorting algorithm
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
	while (true) { // keep taking charcters until break
        chr = (char)_getch();
        if ((int)chr == 13) { // ascii of newline
            break;            // break on <Enter>
        }
		if ((int)chr == 8) { // ascii of Backspace
            if (input.length() < 1) { 
                continue; // to avoid unwanted erasing
            }                            
			cout << '\b' << ' ' << '\b'; // '\b' pushes the cursor 1 step back
                                         // and then ' ' erases the last character

            input.pop_back(); // erase from actual input
            continue;
		}
        input += chr;
        cout << '*';
	}
	cout << endl; // after hitting <Enter>

	return input;
}


bool logIn() { 
    int trials = 3;
    while (trials--) { 
        printf("Enter username:\n");
        cin >> currentUserId;
        printf("Enter Password:\n");
        string pass = hiddenInput();
        if (auto itr = userMap.find(currentUserId) != userMap.end()) { // find position of the entered username
            if (userMap[currentUserId].password == pass) {             // if found stores the data in struct to 
                printf("Log in successful\nWelcome ");                 // check pass and display results
                cout << userMap[currentUserId].name << '\n';
                //cout << user;           //display all userinfo after successful login
                return 1;
                
            }
            else {
                printf("Invalid username or Password. Please try again\n"); // password error
            }
        }
        else {
            printf("Invalid username or Password. Please try again\n"); //username error
        }
    }
    printf("Access Denied.\n");
    
    return 0;
}


void changePassword() {
    printf("Enter old Password:\n");
    string oldpass = hiddenInput();
    if (oldpass != userMap[currentUserId].password) {      //check if old pass is entered correctly
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
            userMap[currentUserId].password = npass;       //overwrite password
            break;
        }
    }
    saveProfileData();
}

string encryption(string msg) {
	int lenm = msg.length();
	string keyword = "PointerDebuggerRecursionLadyClion";					
	int lenk = keyword.length();                    
	for (int i = 0, j = 0; i < lenm; i++, j++) {
		unsigned char m = msg[i];
		if (j >= lenk) j = 0;
		if (isupper(m)) {
			m = m + (keyword[j] - 'a');
			if (m > 90)
				m -= 26;
		}
		if (islower(m)) {
			m = m + (keyword[j] - 'a');
			if (m > 122)
				m = m - 26;
		}
		msg[i] = m;
	}
	return msg;
}

string decryption(string msg) {
	int lenm = msg.length();
	string keyword = "PointerDebuggerRecursionLadyClion";
	int lenk = keyword.length();
	for (int i = 0, j = 0; i < lenm; i++, j++) {
		if (j >= lenk) j = 0;
		if (isupper(msg[i])) {
			msg[i] = msg[i] - (keyword[j] - 'a');
			if (msg[i] < 65)
				msg[i] += 26;
		}
		if (islower(msg[i])) {
			msg[i] = msg[i] - (keyword[j] - 'a');
			if (msg[i] < 97)
				msg[i] += 26;
		}
	}
	return msg;
}


void cleanStream(istream& stream) { // if someone fancy using it, 
    string garbage;                 // here it is
    while (!stream.fail()) {
        stream >> garbage;
    }
}
