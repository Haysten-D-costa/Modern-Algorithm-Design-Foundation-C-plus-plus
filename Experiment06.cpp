/* **********************************************************************************************************
Lab ID        : 6.0
Program Title : 0/1 Knapscak Problem Algorithm...
Author        : Haysten D'costa
Roll No.      : 21co56
Class         : Comp B[Batch P3]
Language      : C++
Due Date      :   -04-2023
-------------------------------------------------------------------------------------------------------------
Description   : Program to implement 0/1(binary), Knapsack Program algorithm...
Input         : --------------------------------------------------------------
    -> n = 4
    -> capacity = 5
    -> weights  = 0 2 1 3 2
    -> profits  = 0 12 10 20 15....
Output  : --------------------------------------------------------------------
            KnapSack (Profit)Table generated : 
            0       0       0       0       0       0
            0       0       12      12      12      12
            0       10      12      22      22      22
            0       10      12      22      30      32
            0       10      15      25      30      37

            -> Item '4' added to Knapsack...
            -> Item '2' added to Knapsack...
            -> Item '1' added to Knapsack...
 
            -> Maximim profit   : 37
            -> Optimal solution : (     1     1     0     1     ) <== soln Vctr
-------------------------------------------------------------------------------
Algorithm     : -
Prerequisites : Basics of C and C++
Known Bugs    : NONE
********************************************************************************************************** */
#include <iostream>
using namespace std;

int max(int item1, int item2); // Function to find max of two items...
int knapSackRecursive(int weight[], int profit[], int n, int Capacity); //todo Check this later...
void knapsackTable(int n, int capacity, int profit[], int weight[], int T[][10]); // Function to compute the knapsack table...
void selectItem(int no_items, int capacity, int profit[], int weight[],int T[][10]);

int main()
{
    int no_items = 4; // Total number of items...
    int capacity = 5; // Total capacity of the knapsack...
    int weight[10] = {0, 2, 1, 3, 2}; // Weights of all items...
    int profit[10] = {0, 12, 10, 20, 15}; // Profit over all items...
    int T[10][10]; // Knapsack table...

    knapsackTable(no_items, capacity, profit, weight, T);
    // cout << knapSackRecursive(weight, profit, no_items, capacity);

    selectItem(no_items, capacity, profit, weight, T);

    return(0);
}
int max(int item1, int item2) {
    return ((item1 > item2) ? item1 : item2);
}
void knapsackTable(int no_items, int capacity, int profit[], int weight[], int T[][10]) {

    cout << endl << "KnapSack (Profit)Table generated : " << endl;
    for(int i=0; i<=no_items; i++) {
        for(int j=0; j<=capacity; j++) {

            if((i == 0) || (j == 0)) { T[i][j] = 0; }
            else if(weight[i] > j) { T[i][j] = T[i-1][j]; }
            else if(j < weight[i]) { T[i][j] = T[i-1][j]; }
            else { T[i][j] = max(T[i-1][j], T[i-1][j-weight[i]] + profit[i]); } // if (weight[i] <= j)
        }
    }
    for(int i=0; i<=no_items; i++) { // To diaplay the table....
        for(int j=0; j<=capacity; j++) {
            cout << T[i][j] << "\t";  
        }
        cout << endl;
    }
}
void selectItem(int no_items, int capacity, int profit[], int weight[],int T[][10]) {

    int i = no_items;
    int j = capacity;
    bool optimal_solution[10];

    while((i > 0) && (j > 0)) {
        if(T[i][j] != T[i-1][j]) {

            optimal_solution[i] = true; // To simply display status of items(added or not)...
            cout << endl << "-> Item '" << i << "' added to Knapsack...";
            j = j - weight[i];
            i = i - 1;
        }
        else {
            optimal_solution[i] = false;
            i = i - 1;
        }
    }
    cout << endl << "\n-> Maximim profit   : " << T[no_items][capacity];  
    cout << endl << "-> Optimal solution : (     ";
    for(int i=1; i<=no_items; i++) {
        cout << optimal_solution[i] << "     ";
    }
    cout << ")" << endl;
}
int knapSackRecursive(int weight[], int profit[], int n, int Capacity) {

    if(n == 0 || Capacity == 0) {
        return(0);
    }
    if(weight[n-1] > Capacity) {
        return(weight, profit, n-1, Capacity);
    }
    return(
        max(
            knapSackRecursive(weight, profit, n-1, Capacity + weight[n-1])+(profit[n-1]),
            knapSackRecursive(weight, profit, n-1, Capacity)
        )
    );
}