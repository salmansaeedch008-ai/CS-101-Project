#include<iostream>    //header files
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include<chrono>
#include<thread>
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

    cin.ignore();
    string customer_name;
    cout << CYAN << "Enter Customer Name : " << RESET;
    getline(cin, customer_name);
    cout << endl;

    int total_number_of_products;
    do {
        cout << CYAN << "Enter total number of products : " << RESET;
        cin >> total_number_of_products;
        if (total_number_of_products < 0) {
            cout << RED << "Invalid input! please again " << RESET;
        }
    } while (total_number_of_products < 0);
    cout << endl;

    string products[total_number_of_products];
    float price[total_number_of_products];
    int quantity[total_number_of_products];

    for (int i = 0; i < total_number_of_products; i++) {
        cout << MAGENTA << "Enter name of product " << i + 1 << " : " << RESET;
        cin.ignore();
        getline(cin, products[i]);

        do {
            cout << YELLOW << "Enter price of product " << i + 1 << " : " << RESET;
            cin >> price[i];
            if (price[i] < 0) {
                cout << RED << "Invalid input! please again " << RESET;
            }
        } while (price[i] < 0);

        do {
            cout << YELLOW << "Enter quantity of product " << i + 1 << " : " << RESET;
            cin >> quantity[i];
            if (quantity[i] < 0) {
                cout << RED << "Invalid input! please again " << RESET;
            }
        } while (quantity[i] < 0);

        cout << endl;
    }

    srand(time(0));
    int bill_number = rand() % 10000;

    time_t now = time(0);
    char *dt = ctime(&now);


    return 0;
}
