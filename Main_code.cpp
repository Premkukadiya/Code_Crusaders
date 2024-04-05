#include <iostream>
#include <random>
#include <time.h>
#include <vector>
#include <queue>

using namespace std;

int main() 
{
    int N, M, P;
    cout << "Enter gate number: ";
    cin >> N;

    cout << "Enter capacity: ";
    cin >> M;

    cout << "Enter time (in minutes) for a single attendee to enter any gate: ";
    cin >> P;

    Stadium stadium(N, M, P);
    stadium.Random_Assignment();
    stadium.Calculate_waiting_time();
    stadium.add_in_suggested_queue();

    return 0;
}