#include<stdio.h>
#include<string.h>
typedef struct Q
{
	char data[5];
	int bt;
	int at;
}Q;
typedef struct PQ
{
	char data[5];
	int ct;
}PQ;
void sort (Q p[],int plen)
{
	//Burst Time Sort
		int x,y;
		Q temp;
			for(x=0;x<plen;x++)
				{
				for(y=0;y<plen-1;y++)
					{
					if(p[y].bt > p[y+1].bt)
						{
								temp=p[y];
								p[y]=p[y+1];
								p[y+1]=temp;
						}
					}
				}
}
int main()
{
	int n,i,j,sum=0,v1,v2,plen=0,rem=0,k=0,ex=0,x=0;
	int flag=0,old=0,ch,r=0;
	int ta[40],wt[40];
	float avg=0;
	
	PQ print[40];
	Q q[40], p[40],temp;

	printf("\nEnter number of Processes: ");
	scanf("%d",&n);

	for(i=0;i<n;i++)
	{
		printf("\nEnter tuple(Process Name,Arrival Time,Burst Time): ");
		scanf("%s%d%d",q[i].data,&q[i].at,&q[i].bt);
	}

	//Arrival Time Sorting.

		for(i=0;i<n;i++)
				{
					for(j=0;j<n-1;j++)
					{
						if(q[j].at > q[j+1].at)
						{
								temp=q[j];
								q[j]=q[j+1];
								q[j+1]=temp;
						}
					}
				}
//Null the end of Array.

q[n].bt=0;
q[n].at=0;
strcpy(q[n].data,'\0');

//Partial RR time quantum logic.
j=0;
	for(i=0;i<n-1;i++)
	{
		flag=0;
		v1=q[i].at;
		v2=q[i+1].at;
		rem=v2-v1;
		ch=sum+rem;

		if(q[i].bt > rem)
		{
			p[j].bt=q[i].bt;
			strcpy(p[j].data,q[i].data);
			p[j].at=0;
			j++;
			plen=j;
//---Sort & select smallest process.

	start:	flag=0;
			sort(p,plen);
			x=0;
		while (flag!=1 && x<plen)
		{
			if (p[x].bt > 0)
			{
				if(p[x].bt<rem)
			       {
					printf("\t|%s ",p[x].data);

					sum=sum+p[x].bt;

					strcpy(print[k].data,p[x].data);
					print[k].ct=sum;
					k++;
					rem=ch-sum;
					p[x].bt=0;
					goto start;

			       }
			       else
			       {
					old=p[x].bt-rem;
					ex=p[x].bt-old;
					p[x].bt=old;

					printf("\t|%s ",p[x].data);
					sum=sum+ex;

					strcpy(print[k].data,p[x].data);
					print[k].ct=sum;
					k++;
						flag=1;
					}
			}
			else
			{
				x++;
				flag=0;
			}

			}
		}
		else
		{
			p[j]=q[i];
			p[j].at=0;
			j++;
			plen=j;
			goto start;
		}
			if(sum < ch)
			{
				rem=ch-sum;
				goto start;
			}
	}

	//copy last process
	p[j].bt=q[i].bt;
	strcpy(p[j].data,q[i].data);
	p[j].at=0;
	j++;

	plen=j;
	sort(p,plen);
	{
			for(i=0;i<plen ;i++)
			{
				if(p[i].bt>0)
				{
				printf("\t|%s ",p[i].data);
				sum=sum+p[i].bt;

				strcpy(print[k].data,p[i].data);
				print[k].ct=sum;
				k++;
				}
			}
	}

	printf("\t|");
	printf("\n\t0");
	for(i=0;i<k;i++)
	{
		printf("\t%d ",print[i].ct);

	}
	
	r=k;
	k=0;
	printf("\n\tProcess Name \t | Waiting Time \t | Turnaround Time \t | Arrival Time \t | Burst Time \t | ");
	for(i=0;i<n;i++)
	{
		sum=0;
		for(j=0;j<r;j++)
		{
			if(strcmp(q[i].data,print[j].data)==0)
			{
				if (print[j].ct > sum)
				{
					sum=print[j].ct;
				}
				
			}
		}

		ta[k]=sum-q[i].at;
		wt[k]=ta[k]-q[i].bt;
		printf("\n\t%s \t\t | %d \t\t\t | %d \t\t\t | %d \t\t\t | %d \t\t | ",q[i].data,wt[k],ta[k],q[i].at,q[i].bt);
		k++;

		
	}
	
	for(i=0;i<k;i++)
		avg=avg+wt[i];
	
	printf("\nAverage Waiting Time: %4.2f",avg/n);
	printf("\n");
	return 0;
}
