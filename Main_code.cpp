#include <iostream>
#include <random>
#include <time.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Stadium
{
private:
    vector<queue<int>> gate;         
    vector<queue<int>> VIP_gate; 
    vector<float> waiting_time;  
    int N;                        // Number of gates in the stadium
    int M;                        // Total capacity of the stadium
    float P;                      // Time taken (in min) for a single attendee to enter any gate
    int sum;                      // Total attendee at gate
    int NUM_GATE_VIP;             
    int NUM_VIP;                  
    float TIME_VIP;               // Entry time for VIP attendees
    int j;                        

public:
    // Constructor to initialize the stadium
    Stadium(int numGates, int capacity, float entryTime, int GATE_VIP, int TOTAL_VIP_PEOPLE, float time) : N(numGates), M(capacity), P(entryTime), NUM_GATE_VIP(GATE_VIP), NUM_VIP(TOTAL_VIP_PEOPLE), TIME_VIP(time)
    {
        gate.resize(N);         
        waiting_time.resize(N); 
        
        if (NUM_GATE_VIP > 0 && NUM_GATE_VIP <= N)
        {
            VIP_gate.resize(NUM_GATE_VIP);
        }
    }
     // Function to assign gate for VIPs
    void Random_Assignment_For_VIP()
    {
        cout << "Assigning  VIP Attendees..." << endl;
        srand(time(NULL)); 
        int j = NUM_VIP;
        int randgate;
        int newpeople;
        while (j != 0)
        {
            if (NUM_GATE_VIP == 1)
                randgate = 0;
            else
                randgate = rand() % NUM_GATE_VIP;

            newpeople = rand() % 20 + 1; 
            if (j < newpeople)
                newpeople = j;

            for (int i = 0; i < newpeople; i++)
            {
                VIP_gate[randgate].push(i); 
            }
            j -= newpeople;
        }

        
        for (int i = 0; i < NUM_GATE_VIP; i++)
        {
            cout << "Number of people at VIP gate " << i + 1 << " is " << VIP_gate[i].size() << endl;
        }

        cout << "Waiting time for vip at each gate:"<<endl;
        // Printing waiting time for VIPs
        for(int i=0;i<NUM_GATE_VIP;i++)
        {
            cout <<"Waiting time at gate " << i+1 << " is "<<(VIP_gate[i].size())*TIME_VIP<<endl;
        }
    }

    //Function to claculate waiting time for general gates 
     void Calculate_waiting_time() 
    {
        for (int i = 0; i < N; ++i) {
            waiting_time[i] = gate[i].size() * P;
            cout << "Waiting time for new attendee at gate " << i + 1 << ": " << waiting_time[i] << " minutes" << endl;
        }
        cout << endl;
 }

    void Waiting_time() 
    {
        for (int i = 0; i < N; ++i) {
            waiting_time[i] = gate[i].size() * P;
        }
    }

    void Random_Assignment(){
            srand(time(NULL));
        for (int i = 0; i < M / 2; i++) {
            int a = rand() % N;
            gate[a].push(i);
        }
        for (int i = 0; i < N; i++) {
            cout << "Number of attendee in " << i + 1 << " gate " << gate[i].size() << endl;
        }
        cout << endl;
    }

    int suggest_queue() {
        int min = waiting_time[0];
        cout << "Suggested gates are: ";
        for (int i = 0; i < N; ++i) {
            if (min >= waiting_time[i]) {
                min = waiting_time[i];
            }
        }
        int j;
        for (int i = 0; i < N; ++i) {
            if (waiting_time[i] == min) {
                cout << i + 1 << " ";
                j = i;
            }
        }
        cout << "and for this gate waiting time is " << min << " minutes" << endl;
        return j;
    }

    // Function to arrange gates according to waiting time 
    void sort()
    {
        int i = 0;
        while (i <= N - 1)
        {
            int j = i + 1;
            while (j <= N - 1)
            {
                if (gate[i].size() < gate[j].size())
                {
                    swap(gate[i], gate[j]);
                }
                j++;
            }
            i++;
        }
    }

    // Function to arrage people (to minimize waiting time)
    
    void Internal_Arrangement(int k)
    {
        cout << "After arranging people for minimum time :" << endl;
        for (int i = 0; i < N - 1; i++)
        {
            while (gate[i].size() != k / (N))
            {
                gate[i + 1].push(gate[i].front());
                gate[i].pop();
            }
        }

        for (int j = 0; j < N - 2; j++)
        {
            int a = gate[N - 1].size(), b = gate[j].size();
            if (a - b > 1)
            {
                gate[j].push(gate[N - 1].front());
                gate[N - 1].pop();
            }
        }
    }
    // Total no of people in Queue
    int sum_of_the_number_of_people_in_gates()
    {
        sum = 0;
        for (int i = 0; i < N; i++)
        {
            sum += gate[i].size();
        }
        return sum;
    }
    // Assigning  half of people 
    void addition_of_people_in_the_queue()
    {
        cout << "Now adding a random number of people to random gates:" << endl;
        int a, k;
        if (M % 2 == 0)
            a = M / 2;
        else
            a = (M / 2) + 1;
        int z;
        
        if (M / 2 < 200)
            z = 10;
        else if (M / 2 > 200 && M / 2 < 1000)
            z = 75;
        else if (M / 2 > 1000 && M / 2 < 3000)
            z = 250;
        else if (M / 2 > 3000 && M / 2 < 15000)
            z = 750;
        else if (M / 2 > 15000 && M / 2 < 50000)
            z = 2000;
        else
            z = 6000;

        srand(time(nullptr));
        while (a != 0 && a > 0)
        {
            int randomgate = rand() % N;      
            int newpeople = (rand() % z) + 1; 
            if (a < newpeople)
                newpeople = a;
            for (int i = 0; i < newpeople; i++)
            {
                gate[randomgate].push(i); 
            }
            cout << newpeople << " people added at gate no " << randomgate + 1 << endl;
            k = sum_of_the_number_of_people_in_gates();
            Calculate_waiting_time();
            sort();
            Internal_Arrangement(k);
            Calculate_waiting_time();
            a -= newpeople;
        }
    }


    
};



int main() 
{
    int N, M, P;
    cout << "Enter gate number: ";
    cin >> N;

    cout << "Enter capacity: ";
    cin >> M;
    if(M>150000)
    cout<<"Overflow"<<endl;

    cout << "Enter time (in minutes) for a single attendee to enter any gate: ";
    cin >> P;

    Stadium stadium(N, M, P);
    stadium.Random_Assignment();
    stadium.Calculate_waiting_time();
    stadium.add_in_suggested_queue();

 return 0;
}