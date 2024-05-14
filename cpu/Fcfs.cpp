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
bool compareArrival(const Process&a, const Process&b){
    return a.at < b.at;
}
int calcFCFS(vector<Process>& p){
    int cTime = 0;
    int wtSum = 0;

    for(int i = 0; i < p.size(); i++){
        cTime += p[i].bt;

        p[i].ct = cTime;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        if(i < p.size()-1 && cTime < p[i+1].at){
            cTime += p[i+1].at;
        }
        wtSum += p[i].wt;        
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

    int totalWt = calcFCFS(Processes);

    //display results 
    cout<<"Process\tArrival\tBurst\tTAT\tWT"<<endl;
    for(int i = 0 ; i < Processes.size();i++){
        cout<<i+1<<"\t"<<Processes[i].at<<"\t"<<Processes[i].bt<<"\t"<<Processes[i].tat<<"\t"<<Processes[i].wt<<endl;

    }
    cout<<"Average waiting time = "<<(float)totalWt/numProcesses<<endl;


    
}