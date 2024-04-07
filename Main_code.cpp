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
    // Function to arrange people in gates for minimum waiting time
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