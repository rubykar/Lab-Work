#include<stdio.h>
#include<stdlib.h>

struct Process{
	int pid,at,bt,tat,wt,ct;
};


void sortProcess(struct Process process[],int n){
	for(int i = 0;i<n-1;i++){
		for(int j = 0; j< n-i-1;j++){
			if(process[j].bt > process[j+1].bt){
				struct Process temp = process[j];
				process[j] = process[j+1];
				process[j+1] = temp; 
			}
		}
	}
}





int main(){
	int n;
	float avg_wt = 0 , avg_tat = 0;
	
	printf("Enter the number of processes : ");
	scanf("%d",&n);
	
	struct Process process[n];
	
	for(int i = 0;i <n ;i++){
		printf("Enter arrival time and burst time of process %d :",i+1);
		scanf("%d %d",&process[i].at,&process[i].bt);
		process[i].pid = i + 1;
	}
	
	sortProcess(process,n);
	process[0].wt = 0 ;
	
	for(int i= 1 ;i< n ;i++){
		process[i].wt = process[i-1].wt + process[i-1].bt;
		avg_wt += process[i].wt;
	}
	
	for(int i= 0 ;i< n ;i++){
		process[i].tat = process[i].wt + process[i].bt;
		avg_tat += process[i].tat;
	}
	
	avg_wt /= n;
	avg_tat /= n;
	
	
	printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTrunAround\n");
	
	for(int i = 0;i < n;i++){
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",process[i].pid,process[i].at,process[i].bt,process[i].wt,process[i].tat);
		
	}
	
	
	    printf("\nAverage Waiting Time: %f\n", avg_wt);
    printf("Average Turnaround Time: %f\n", avg_tat);

    return 0;
	

}
