# include "query.h"


query::query() {
    vtxFound = false; // Checks if find command has been prompted at least once 
}

string query::interpret(string input, int n) {
    string firstCommand = getNthWord(input, 1);
    string secondCommand;
    string thirdCommand; 
    string fourthCommand; 

    int s = 0; 
    int d = 0; 
    int flag = 0; 

    int write_d = 0; 

    // CASE 1: FIND
    //****************************************************************

    if(firstCommand == "find") {
        secondCommand = getNthWord(input, 2); // Determines source 
        thirdCommand = getNthWord(input, 3);  // Determines destination 
        fourthCommand = getNthWord(input, 4); // Determines flag 

        
        for (int i = 0; i < secondCommand.length(); i++) {
            if (isdigit(secondCommand[i]) == false) {
                cout << "Error: invalid find query\n";
                return "";
            }
        }
        for (int i = 0; i < thirdCommand.length(); i++) {
            if (isdigit(thirdCommand[i]) == false) {
                cout << "Error: invalid find query\n";
                return "";
            }
        }
        for (int i = 0; i < fourthCommand.length(); i++) {
            if (isdigit(fourthCommand[i]) == false) {
                cout << "Error: invalid find query\n";
                return "";
            }
        }

        s = stoi(secondCommand);
        d = stoi(thirdCommand);
        flag = stoi(fourthCommand);

        // Checks if valid
        if(case1IsValid(s, d, flag, n)) { 
            return firstCommand + " " + secondCommand + " " + thirdCommand + " " + fourthCommand; //source destination flag 
        } 
        else {
            cout << "Error: invalid find query\n";
            return ""; 
        }
        

        

    }

    // CASE 2: WRITE PATH
    //****************************************************************

    else if(firstCommand == "write") {
        secondCommand = getNthWord(input, 2); // path
        thirdCommand = getNthWord(input, 3); // s 
        fourthCommand = getNthWord(input, 4); // d 

        for (int i = 0; i < thirdCommand.length(); i++) {
            if (isdigit(thirdCommand[i]) == false) {
                cout << "Error: invalid find query\n";
                return "";
            }
        }
        for (int i = 0; i < fourthCommand.length(); i++) {
            if (isdigit(fourthCommand[i]) == false) {
                cout << "Error: invalid find query\n";
                return "";
            }
        }
        write_d = stoi(fourthCommand);

        if(case2IsValid(write_d, n)) {
            return firstCommand + " " + secondCommand + " " + thirdCommand + " " + fourthCommand; //write path s d  
        }
        else {
            cout << "Error: invalid source destination pair\n";
            return "";
        }


    }
    // CASE 3: STOP
    //**************************************************************** 

    else if(firstCommand == "stop") {
        exit(0); 
    }

    // CASE 4: INVALID
    //****************************************************************

    else {
        cout << "Invalid command\n"; 
    }

    return "";
}

string query::getNthWord(string str, int n) {
    istringstream iss (str);
    while(n-- > 0 && (iss >> str));
    return str;
}

bool query::case1IsValid(int s, int d, int f, int n) {
    //s cannot be d
    if(s < 1 || s > n)
        return false; 
    if(d < 0 || d > n)
        return false; 
    if(s == d)
        return false; 
    if(f != 0 && f != 1)
        return false; 
    
    return true; 
}

bool query::case2IsValid(int d, int n) {
    if(d < 1 || d > n)
        return false; 

    return true; 
}
