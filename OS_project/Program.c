#include <stdio.h>

struct process
{
    int WT,AT,BT,TAT,PT;
};
struct process a[10];

//Function to swap two variables
void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
// For Non Preemptive
int Non_preemptive()
{
    int n;
    float total_wt=0,total_tat=0,avg_wt,avg_tat;
    printf("Enter Number of Processes: ");
    scanf("%d",&n);
    printf("\n\t!!!!Higher number -> Higher priority!!!!\n");
    // b is array for burst time, p for priority and index for process id
    int b[n],p[n],index[n];
    for(int i=0;i<n;i++)
    {
        printf("Enter Burst Time and Priority Value for Process %d: ",i+1);
        scanf("%d %d",&b[i],&p[i]);
        index[i]=i+1;
    }
    for(int i=0;i<n;i++)
    {
        int a=p[i],m=i;
 
        //Finding out highest priority element and placing it at its desired position
        for(int j=i;j<n;j++)
        {
            if(p[j] > a)
            {
                a=p[j];
                m=j;
            }
        }
 
        //Swapping processes
        swap(&p[i], &p[m]);
        swap(&b[i], &b[m]);
        swap(&index[i],&index[m]);
    }
 
    // T stores the starting time of process
    int t=0;
 
    //Printing scheduled process
    printf("Order of process Execution is\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d is executed from %d to %d\n",index[i],t,t+b[i]);
        t+=b[i];
    }
    printf("\n");
    printf("Process Id \tBurst Time\t Wait Time \tTurnAround Time\n");
    int wait_time=0;
    for(int i=0;i<n;i++)
    {
        printf("P%d\t\t %d\t\t %d\t\t %d\n",index[i],b[i],wait_time,wait_time + b[i]);
        total_wt = total_wt + wait_time;
        wait_time += b[i];
        total_tat = total_tat +wait_time;
    }
    avg_wt= total_wt/n;
    avg_tat = total_tat/n;
    printf("Average waiting time:%f\n",avg_wt);
    printf("Average TrunAround time:%f\n",avg_tat);

    return 0;
}

    // For Preemptive 
int preemptive()
{
    int n,temp[10],t,count=0,short_p;
    float total_WT=0,total_TAT=0,Avg_WT,Avg_TAT;
    printf("Enter the number of the process\n");
    scanf("%d",&n);
    printf("Enter the arrival time , burst time and priority of the process\n");
    printf("AT BT PT\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d%d%d",&a[i].AT,&a[i].BT,&a[i].PT);
        
        // copying the burst time in
        // a temp array fot futher use
        temp[i]=a[i].BT;
    }
    
    // we initialize the burst time
    // of a process with maximum 
    a[9].PT=10000;
    
    for(t=0;count!=n;t++)
    {
        short_p=9;
        for(int i=0;i<n;i++)
        {
            if(a[short_p].PT>a[i].PT && a[i].AT<=t && a[i].BT>0)
            {
                short_p=i;
            }
        }
        
        a[short_p].BT=a[short_p].BT-1;
        
        // if any process is completed
        if(a[short_p].BT==0)
        {
            // one process is completed
            // so count increases by 1
            count++;
            a[short_p].WT=t+1-a[short_p].AT-temp[short_p];
            a[short_p].TAT=t+1-a[short_p].AT;
            
            // total calculation
            total_WT=total_WT+a[short_p].WT;
            total_TAT=total_TAT+a[short_p].TAT;
            
        }
    }
    
    Avg_WT=total_WT/n;
    Avg_TAT=total_TAT/n;
    
    // printing of the answer
    printf("ID WT TAT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d %d\t%d\n",i+1,a[i].WT,a[i].TAT);
    }
    
    printf("Avg waiting time of the process  is %f\n",Avg_WT);
    printf("Avg turn around time of the process is %f\n",Avg_TAT);
    
    return 0;
}

int main(){

    int choice;
    printf("Enter the scheduling type:\n1. Preemptive\n2. Non Preemptive\t:");
    scanf("%d",&choice);

    if (choice==1)
    {  
        printf("\t******PREEMPTIVE PRIORITY SCHEDULING******\n");
        preemptive();
    }else if (choice==2)
    {
        printf("\t******NON-PREEMPTIVE PRIORITY SCHEDULING******\n");
        Non_preemptive();
    }else{
        printf("\t\tInvalid choice!\n\t\tExit Terminal\n");
    }

    return 0;
}