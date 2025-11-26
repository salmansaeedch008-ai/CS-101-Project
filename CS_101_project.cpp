#include<iostream>    //header files
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"               // Color codes for printing colored text in the console (ANSI escape sequences)                        
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

float calculate_total(float price[], int quantity[], int n) {
    float total = 0;
    for (int i = 0; i < n; i++) {
        total += price[i] * quantity[i];
    }
    return total;
}

int main(){

    cout << BLUE << "================================" << RESET << endl;    //also giving colouring to each line
    cout << GREEN << "           LOGIN SYSTEM         " << RESET << endl;   //prints login system on screen
    cout << BLUE << "================================" << RESET << endl;

    string user_name;          //string variable to store username
    string password;           //string variable to store password

    int attempts = 3;          //giving three attempts for username and three attempts for password , if attempts becomes zero the software will be closed
    while (attempts > 0) {     //loop runs until attempts will be greater than zero
        cout << CYAN << "Enter Username : " << RESET;
        cin >> user_name;      //asking user to enter user name

        if (user_name == "admin" || user_name == "ADMIN") {
            break;              // if username will be correct it will exit the loop immediately
        } else {
            attempts--;         //if username will be incorrect it will decrease the number of attempts one by one
            cout << RED << "Wrong Username! Attempts left: " << attempts << RESET << endl;
        }
    }

    if (attempts == 0) {        //if there are 0 attempts remaining the program will end automatically
        cout << RED << "Too many wrong attempts. Program closed." << RESET << endl;
        return 0;
    }

    attempts = 3;              //giving three attempts for password
    while (attempts > 0) {     //loop runs until attempts will be greater than zero
        cout << CYAN << "Enter Password : " << RESET;
        cin >> password;        //asking user to enter password

        if (password == "1234") {
            break;              // if password will be correct it will exit the loop immediately
        } else {
            attempts--;         //if username will be incorrect it will decrease the number of attempts one by one
            cout << RED << "Wrong Password! Attempts left: " << attempts << RESET << endl;
        }
    }

    if (attempts == 0) {        //if there are 0 attempts remaining the program will end automatically
        cout << RED << "Too many wrong attempts. Program closed." << RESET << endl;
        return 0;
    }

    cout << GREEN << "\n======= LOGIN SUCCESSFUL =======" << RESET << endl << endl;   //if both username and password will be correct it will pring login successful on the screen






    return 0;
}