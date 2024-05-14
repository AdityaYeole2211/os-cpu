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
};
bool compareArrival(const Process& a, const Process& b){
    return a.at < b.at;
}
int calcRoundRobin(vector<Process>& p, int quantum){
    int completed = 0;
    int cTime = 0;
    int wtSum = 0;
    vector<int> remainingTime(p.size());
    for(int i = 0 ; i < p.size(); i++){
        remainingTime[i] = p[i].bt;
    }
    int index = 0;
    while(completed < p.size()){
        if(remainingTime[index] > 0){
            if(remainingTime[index] > quantum){
                cTime += quantum;
                remainingTime[index] = remainingTime[index] - quantum;
            }
            else{
                //prcoess can be completed
                cTime += remainingTime[index];
                remainingTime[index] = 0;

                completed++;
                p[index].ct = cTime;
                p[index].tat = p[index].ct - p[index].at;
                p[index].wt  = p[index].tat - p[index].bt;
                wtSum += p[index].wt;

            }
        }
        index = (index + 1)% p.size();

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
    int quantum ;
    cout<<"Enter the time quantum"<<endl;
    cin>>quantum;
    cout<<endl;


    //sort processes acforing to at
    sort(Processes.begin(), Processes.end(), compareArrival);

    int totalWt = calcRoundRobin(Processes, quantum);

    //display results 
    cout<<"Process\tArrival\tBurst\tTAT\tWT"<<endl;
    for(int i = 0 ; i < Processes.size();i++){
        cout<<i+1<<"\t"<<Processes[i].at<<"\t"<<Processes[i].bt<<"\t"<<Processes[i].tat<<"\t"<<Processes[i].wt<<endl;

    }
    cout<<"Average waiting time = "<<(float)totalWt/numProcesses<<endl;

}