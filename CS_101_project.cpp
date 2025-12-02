#include<iostream>    
#include <string>
#include <ctime>
#include <cstdlib>                        //Header Files
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

    cin.ignore();              //ignoring previous input so there is no mixing with coming input
    string customer_name;
    cout << CYAN << "Enter Customer Name : " << RESET;   //input customer name
    getline(cin, customer_name);           //using getline to also read name if there are two words in a name
    cout << endl;

    int total_number_of_products;
    cout << CYAN << "Enter total number of products : " << RESET;
    do {
        cin >> total_number_of_products;  //input total number of products
        if (total_number_of_products < 0) {
            cout << RED << "Invalid input! please again enter total number of products : " << RESET;
        }
    } while (total_number_of_products < 0);   //asking user again to enter total products if entered less than 1 products previously
    cout << endl;

    string products[total_number_of_products];    //storing products name in array as entered by cashier
    float price[total_number_of_products];        //storing price of each product in an array entered by cashier
    int quantity[total_number_of_products];       //storing quantity of each product in an array entered by cashier

    for (int i = 0; i < total_number_of_products; i++) {
        cout << MAGENTA << "Enter name of product " << i + 1 << " : " << RESET;
        cin.ignore();                      //ignoring previous input so there is no mixing with coming input
        getline(cin, products[i]);         //input names of product

        cout << YELLOW << "Enter price of product " << i + 1 << " : " << RESET;
        do {
            cin >> price[i];             //input price of product
            if (price[i] < 0) {
                cout << RED << "Invalid input! please again enter price of product : " << RESET;
            }
        } while (price[i] < 0);     //asking again for price if user enters less than 0 price

        cout << YELLOW << "Enter quantity of product " << i + 1 << " : " << RESET;
        do {
            cin >> quantity[i];    //input quantity of each product
            if (quantity[i] < 0) {
                cout << RED << "Invalid input! please again enter quantity of product :  " << RESET;
            }
        } while (quantity[i] < 0);        //asking again for quantity if user enters less than 0 quantity

        cout << endl;
    }

    srand(time(0));
    int bill_number = rand() % 10000;         //random bill generator in the range of 10000

    time_t now = time(0); 
    char *dt = ctime(&now);                  //printing current date and time

    this_thread::sleep_for(chrono::seconds(2));

    cout << BLUE << "==================================================" << RESET << endl;
    cout << GREEN << "                   BILL RECEIPT                 " << RESET << endl;
    cout << BLUE << "==================================================" << RESET << endl;

    cout << CYAN << "\nCustomer name : " << RESET << customer_name << endl;
    cout << CYAN << "Bill number   : " << RESET << bill_number << endl;
    cout << CYAN << "Date and Time : " << RESET << dt;
    cout << BLUE << "--------------------------------------------------" << RESET << endl;

    cout << left
         << YELLOW << setw(15) << "Products"
         << setw(10) << "Price"
         << setw(12) << "Quantity"
         << setw(10) << "Total(Rs.)" << RESET << endl;

    cout << BLUE << "--------------------------------------------------" << RESET << endl;

    for (int i = 0; i < total_number_of_products; i++) {
        cout << left
             << WHITE << setw(16) << products[i]
             << setw(12) << price[i]
             << setw(10) << quantity[i]
             << GREEN << price[i] * quantity[i] << " Rs." << RESET << endl;

        cout << BLUE << "--------------------------------------------------" << RESET << endl;
    }

    float total_bill = calculate_total(price, quantity, total_number_of_products);
    cout << CYAN << "\n              Total Bill : " << GREEN << total_bill << " Rs." << RESET << endl;

    float discount = 0;
    if (total_bill > 1000) {
        discount = 0.10 * total_bill;
        cout << CYAN << "                 Discount : " << GREEN << discount << " Rs." << RESET << endl;
    }

    float tax = (0.05 * total_bill);
    cout << CYAN << "                     Tax : " << GREEN << tax << " Rs." << RESET << endl << endl;

    cout << BLUE << "--------------------------------------------------" << RESET << endl << endl;

    float sub_total = ((total_bill - discount) + tax);
    cout << CYAN << "               Sub Total : " << GREEN << sub_total << " Rs." << RESET << endl << endl;

    cout << BLUE << "--------------------------------------------------" << RESET << endl << endl;

    return 0;
}
