#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Process{
    int at;
    int bt; 
    int ct;
    int tat;
    int wt;
    int priority;
};
bool compareArrival(const Process& a, const Process& b){
    return a.at < b.at;
}
int calcPriorityPremptive(vector<Process>& p){
    int completed = 0; 
    int cTime = 0; 
    int wtSum = 0;
    vector<int> remainingTime(p.size());
    for(int i = 0 ; i < p.size(); i++){
        remainingTime[i] = p[i].bt;
    }

    while(completed < p.size()){
        int index = -1;
        int highestPriority = INT_FAST16_MAX;

        //check for higher priorty process
        for(int i = 0; i < p.size() && p[i].at <= cTime ; i++){
            if(p[i].priority < highestPriority && remainingTime[i] > 0){
                index = i;
                highestPriority = p[i].priority;
            }
        }
        if(index != -1){
            remainingTime[index] -- ;
            cTime++;

            if(remainingTime[index] == 0){
                //prcess completed 
                completed++;
                p[index].ct = cTime;
                p[index].tat = p[index].ct - p[index].at;
                p[index].wt = p[index].tat - p[index].bt;
                wtSum += p[index].wt; 
            }
        }
        else{
            cTime++;
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

        cout<<"enter the priority for prcoess "<<i+1<<endl;
        cin>>Processes[i].priority;
        cout<<endl;

    }

    //sort processes acforing to at
    sort(Processes.begin(), Processes.end(), compareArrival);

    int totalWt = calcPriorityPremptive(Processes);

    //display results 
    cout<<"Process\tArrival\tBurst\tPriority\tTAT\tWT"<<endl;
    for(int i = 0 ; i < Processes.size();i++){
        cout<<i+1<<"\t"<<Processes[i].at<<"\t"<<Processes[i].bt<<"\t"<<Processes[i].priority<<"\t\t"<<Processes[i].tat<<"\t"<<Processes[i].wt<<endl;

    }
    cout<<"Average waiting time = "<<(float)totalWt/numProcesses<<endl;

    
}