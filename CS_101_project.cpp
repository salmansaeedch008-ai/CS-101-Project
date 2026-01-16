#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <limits>   

using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

int choice;

double calculate_total(double price[], int quantity[], int n)
{
    double total = 0;
    for (int i = 0; i < n; i++)
    {
        total += price[i] * quantity[i];
    }
    return total;
}

static bool read_int(int &x)
{
    if (!(cin >> x))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

static bool read_double(double &x)
{
    if (!(cin >> x))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

bool login()
{
    string username, password, file_user, file_pass;

    while (true)
    {
        cout << BLUE << "========================================" << RESET << endl;
        cout << GREEN << "       ADMINISTRATION PORTAL            " << RESET << endl;
        cout << BLUE << "========================================" << RESET << endl;
        cout << CYAN << "1. Admin Login (Go to Dashboard)" << RESET << endl;
        cout << CYAN << "2. Register New Admin" << RESET << endl;
        cout << CYAN << "3. Exit System" << RESET << endl;
        cout << YELLOW << "\nSelect an option: " << RESET;

        // FIX: handle non-numeric menu input
        if (!read_int(choice))
        {
            cout << RED << "Invalid input! Please enter a number (1 to 3).\n" << RESET;
            continue;
        }

        if (choice == 1)
        {
            int attempts = 3;

            while (attempts > 0)
            {
                cout << "\n" << CYAN << "Enter Admin Username: " << RESET;
                cin >> username;
                cout << CYAN << "Enter Admin Password: " << RESET;
                cin >> password;

                ifstream read("users.txt");
                bool found = false;

                if (read.is_open())
                {
                    while (read >> file_user >> file_pass)
                    {
                        if (file_user == username && file_pass == password)
                        {
                            found = true;
                            break;
                        }
                    }
                    read.close();
                }
                else
                {
                    cout << RED << "No admins registered! Please register first." << RESET << endl;
                    break;
                }

                if (found)
                {
                    cout << GREEN << "\n Verifying credentials...Access Granted. " << RESET << endl << endl;
                    cout << BLUE << "========================================" << RESET << endl;
                    cout << GREEN << "      WELCOME TO ADMIN DASHBOARD        " << RESET << endl;
                    cout << BLUE << "========================================" << RESET << endl << endl;
                    return true;
                }
                else
                {
                    attempts--;
                    cout << RED << "Invalid Credentials! Attempts left: " << attempts << RESET << endl;
                }
            }

            if (attempts == 0)
            {
                cout << RED << "Security Alert: Too many failed attempts. System Locked." << RESET << endl;
                return false;
            }
        }
        else if (choice == 2)
        {
            cout << "\n" << MAGENTA << "Enter New Admin Username: " << RESET;
            cin >> username;
            cout << MAGENTA << "Enter New Admin Password: " << RESET;
            cin >> password;

            ofstream file("users.txt", ios::app);
            // FIX: check file open
            if (!file.is_open())
            {
                cout << RED << "Error: Unable to open users.txt for writing." << RESET << endl;
            }
            else
            {
                file << username << " " << password << endl;
                file.close();
                cout << GREEN << "New Admin Registered Successfully!\n" << RESET << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "Exiting system..." << endl;
            return false;
        }
        else
        {
            cout << RED << "Invalid Choice! Try again.\n" << RESET;
        }
    }
}

void save_and_print_summary(string customer_name, int bill_number, const char *dt,
                            string products[], double price[], int quantity[],
                            int total_items, double total_bill, double discount, double tax, double sub_total)
{
    ofstream file("bill_summary.txt", ios::app);

    cout << "\n\n======= BILL SUMMARY =======\n";
    if (file.is_open()) file << "======= BILL SUMMARY =======\n";

    cout << "Customer Name : " << customer_name << endl;
    if (file.is_open()) file << "Customer Name : " << customer_name << endl;

    cout << "Bill Number   : " << bill_number << endl;
    if (file.is_open()) file << "Bill Number   : " << bill_number << endl;

    cout << "Date & Time   : " << dt;
    if (file.is_open()) file << "Date & Time   : " << dt;

    cout << "---------------------------------------\n";
    if (file.is_open()) file << "---------------------------------------\n";

    cout << left << setw(15) << "Product"
         << setw(10) << "Price"
         << setw(10) << "Qty"
         << "Total\n";

    if (file.is_open())
    {
        file << left << setw(15) << "Product"
             << setw(10) << "Price"
             << setw(10) << "Qty"
             << "Total\n";
    }

    cout << "---------------------------------------\n";
    if (file.is_open()) file << "---------------------------------------\n";

    for (int i = 0; i < total_items; i++)
    {
        double product_total = price[i] * quantity[i];

        cout << left << setw(15) << products[i]
             << setw(10) << price[i]
             << setw(10) << quantity[i]
             << product_total << endl;

        if (file.is_open())
        {
            file << left << setw(15) << products[i]
                 << setw(10) << price[i]
                 << setw(10) << quantity[i]
                 << product_total << endl;
        }
    }

    cout << "\nTotal Bill : " << total_bill << endl;
    cout << "Discount   : " << discount << endl;
    cout << "Tax        : " << tax << endl;
    cout << "Sub Total  : " << sub_total << endl;

    if (file.is_open())
    {
        file << "\nTotal Bill : " << total_bill << endl;
        file << "Discount   : " << discount << endl;
        file << "Tax        : " << tax << endl;
        file << "Sub Total  : " << sub_total << endl;
        file << "\n======= END OF BILL =======\n\n--------------------------------------\n\n";
        file.close();
        cout << "\nBill saved to 'bill_summary.txt'\n";
    }
    else
    {
        cout << RED << "\nError: Could not open 'bill_summary.txt' to save bill.\n" << RESET;
    }
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    do
    {
        if (!login())
        {
            return 0;
        }

        cout << GREEN << "=======================================" << RESET << endl;
        cout << BLUE << "=============BILLING MODE==============" << RESET << endl;
        cout << YELLOW << "=======================================" << RESET << endl << endl;

        string customer_name;
        cout << CYAN << "Enter Customer Name : " << RESET;
        getline(cin >> ws, customer_name);
        cout << endl;

        int total_number_of_products;
        cout << CYAN << "Enter total number of products : " << RESET;

        while (true)
        {
            if (!read_int(total_number_of_products))
            {
                cout << RED << "Invalid input! please again enter total number of products : " << RESET;
                continue;
            }
            if (total_number_of_products < 0)
            {
                cout << RED << "Invalid input! please again enter total number of products : " << RESET;
                continue;
            }
            break;
        }
        cout << endl;

        string *products = (total_number_of_products > 0) ? new string[total_number_of_products] : nullptr;
        double *price     = (total_number_of_products > 0) ? new double[total_number_of_products] : nullptr;
        int *quantity     = (total_number_of_products > 0) ? new int[total_number_of_products] : nullptr;

        for (int i = 0; i < total_number_of_products; i++)
        {
            cout << MAGENTA << "Enter name of product " << i + 1 << " : " << RESET;
            // FIX: safe getline for product name
            getline(cin >> ws, products[i]);

            cout << YELLOW << "Enter price of product " << i + 1 << " : " << RESET;
            while (true)
            {
                if (!read_double(price[i]))
                {
                    cout << RED << "Invalid input! please again enter price of product : " << RESET;
                    continue;
                }
                if (price[i] < 0)
                {
                    cout << RED << "Invalid input! please again enter price of product : " << RESET;
                    continue;
                }
                break;
            }

            cout << YELLOW << "Enter quantity of product " << i + 1 << " : " << RESET;
            while (true)
            {
                if (!read_int(quantity[i]))
                {
                    cout << RED << "Invalid input! please again enter quantity of product :  " << RESET;
                    continue;
                }
                if (quantity[i] < 0)
                {
                    cout << RED << "Invalid input! please again enter quantity of product :  " << RESET;
                    continue;
                }
                break;
            }

            cout << endl;
        }

        int bill_number = rand() % 10000;

        time_t now = time(0);
        const char *dt = ctime(&now);

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

        for (int i = 0; i < total_number_of_products; i++)
        {
            cout << left
                 << WHITE << setw(16) << products[i]
                 << setw(12) << price[i]
                 << setw(10) << quantity[i]
                 << GREEN << price[i] * quantity[i] << " Rs." << RESET << endl;

            cout << BLUE << "--------------------------------------------------" << RESET << endl;
        }

        double total_bill = calculate_total(price, quantity, total_number_of_products);
        cout << CYAN << "\n              Total Bill : " << GREEN << total_bill << " Rs." << RESET << endl;

        double discount = 0;
        if (total_bill > 1000)
        {
            discount = 0.10 * total_bill;
            cout << CYAN << "                Discount : " << GREEN << discount << " Rs." << RESET << endl;
        }

        double tax = (0.05 * total_bill);
        cout << CYAN << "                     Tax : " << GREEN << tax << " Rs." << RESET << endl << endl;

        cout << BLUE << "--------------------------------------------------" << RESET << endl << endl;

        double sub_total = ((total_bill - discount) + tax); // FIX: keep precision (was float)
        cout << CYAN << "               Sub Total : " << GREEN << sub_total << " Rs." << RESET << endl << endl;

        cout << BLUE << "--------------------------------------------------" << RESET << endl << endl;

        int pay_choice;
        double recieved_cash, remaining_amount;

        cout << MAGENTA << "Payment Methods : " << RESET << endl << endl;
        cout << "     " << CYAN << "1-Jazzcash" << RESET << endl;
        cout << "     " << CYAN << "2-Bank Credit Card" << RESET << endl;
        cout << "     " << CYAN << "3-Easypaisa" << RESET << endl;
        cout << "     " << CYAN << "4-Cash" << RESET << endl << endl;

        cout << YELLOW << "Select Payment Method : " << RESET;

        do
        {
            if (!read_int(pay_choice))
            {
                cout << RED << "Invalid Choice! Please select a valid option (1 to 4): " << RESET;
                continue;
            }

            switch (pay_choice)
            {
            case 1:
                cout << GREEN << "Selected Method : JazzCash. Processing payment..." << endl;
                cout << "Payment Successful" << RESET << endl;
                break;

            case 2:
                cout << GREEN << "Selected Method : Credit Card. Redirecting..." << endl;
                cout << "Payment Successful" << RESET << endl;
                break;

            case 3:
                cout << GREEN << "Selected Method : EasyPaisa. Processing..." << endl;
                cout << "Payment Successful" << RESET << endl;
                break;

            case 4:
                cout << YELLOW << "Selected Method : Cash. Please pay at counter.\n" << RESET << endl;
                cout << CYAN << "Total Cash To Pay : " << GREEN << sub_total << " Rs." << RESET << endl;

                remaining_amount = sub_total;

                while (remaining_amount > 0)
                {
                    cout << CYAN << "Enter Cash Received : " << RESET;

                    if (!read_double(recieved_cash))
                    {
                        cout << RED << "Invalid amount! Enter again." << RESET << endl;
                        continue;
                    }

                    if (recieved_cash <= 0)
                    {
                        cout << RED << "Invalid amount! Enter again." << RESET << endl;
                        continue;
                    }

                    remaining_amount -= recieved_cash;

                    if (remaining_amount > 0)
                    {
                        cout << YELLOW << "You still need to pay: " << remaining_amount << " Rs.\n" << RESET;
                    }
                }

                if (remaining_amount < 0)
                {
                    cout << GREEN << "Change : " << -remaining_amount << " Rs." << RESET << endl;
                }

                cout << GREEN << "Payment Successful!" << RESET << endl;
                break;

            default:
                cout << RED << "Invalid Choice! Please select a valid option (1 to 4): " << RESET;
            }
        } while (pay_choice > 4 || pay_choice < 1);

        save_and_print_summary(customer_name, bill_number, dt,
                               products, price, quantity,
                               total_number_of_products, total_bill, discount, tax, sub_total);

        cout << GREEN << "\n\nThank you for shopping " << customer_name << " !" << RESET << endl;

        delete[] products;
        delete[] price;
        delete[] quantity;

    } while (choice != 3); 
    return 0;
}
