#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process{
    int at;
    int bt; 
    int ct;
    int tat;
    int wt;
};
bool compareArrival(const Process&a,  const Process&b){
    return  a.at < b.at;
}

int calcSJF(vector<Process>& p){
    int cTime = 0; 
    int completed = 0;
    int wtSum = 0;
    vector<int> remTime(p.size());
    for(int i = 0; i < p.size();i++){
        remTime[i] = p[i].bt;
    }

    while(completed < p.size()){
        int shortestIndex = -1;
        int shortestTime = INT_FAST32_MAX;
        for(int i = 0; i < p.size(); i ++){
            if(p[i].at <= cTime && remTime[i] > 0){
                if(remTime[i] < shortestTime){
                    shortestIndex = i; 
                    shortestTime = remTime[i];
                }
            }
        }

        if(shortestIndex == -1){
            cTime++;
            continue;
        }

        remTime[shortestIndex] -- ;
        cTime++;

        if(remTime[shortestIndex] == 0){
            //process is completed 
            completed++;
            p[shortestIndex].ct = cTime;
            p[shortestIndex].tat = p[shortestIndex].ct - p[shortestIndex].at;
            p[shortestIndex].wt = p[shortestIndex].tat - p[shortestIndex].bt;
            wtSum += p[shortestIndex].wt;
        }
    }

    return wtSum;

}
int main(){
    //enter number of prcoess
    int numProcesses;
    cout<<"Enter number of processes"<<endl;
    cin>>numProcesses;

    //enter at & bt for each prcoess
    vector<Process> Processes(numProcesses);
    for(int i = 0; i < Processes.size(); i++){
        cout<<"enter the arrival  time for process "<< i+1<<endl;
        cin>>Processes[i].at;
        cout<<endl;

        cout<<"enter the burst time for prcoess "<<i+1<<endl;
        cin>>Processes[i].bt;
        cout<<endl;

    }

    //sort processes acforing to at
    sort(Processes.begin(), Processes.end(), compareArrival);

    int totalWt = calcSJF(Processes);

    //display results 
    cout<<"Process\tArrival\tBurst\tTAT\tWT"<<endl;
    for(int i = 0 ; i < Processes.size();i++){
        cout<<i+1<<"\t"<<Processes[i].at<<"\t"<<Processes[i].bt<<"\t"<<Processes[i].tat<<"\t"<<Processes[i].wt<<endl;

    }
    cout<<"Average waiting time = "<<(float)totalWt/numProcesses<<endl;

    
}