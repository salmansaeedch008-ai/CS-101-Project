#include<iostream>
using namespace std;

float calculate_total(float price[], int quantity[], int n) {
    float total = 0;
    for (int i = 0; i < n; i++) {
        total += price[i] * quantity[i];
    }
    return total;
}

int main(){



    return 0;
}