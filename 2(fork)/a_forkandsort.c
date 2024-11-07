/*
================================================================================================
 Name        	   : a_forkandsort.c
 Author      	   : Amar Chandole	
 Roll No.	 	   : 3807
 Problem Statement : Process control system calls: The demonstration of fork, execve and
			   		 wait system calls along with zombie and orphan states.
			   
					 a. Implement the C program in which main program accepts the integers to be
					    sorted. Main program uses the fork system call to create a new process 
						called a child process. Parent process sorts the integers using merge sort 
						and waits for child process using wait system call to sort the integers using 
						quick sort. Also demonstrate zombie and orphan state.						  	
================================================================================================
*/

#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h>    
#include <stdlib.h>    
#include <unistd.h>  

void quicksort(int [10],int,int);
void main()
{
	int pid, ppid, a[10], size, i;

	printf("\nPARENT: My process-id is %d.", getpid());
	
	printf("\n\nEnter the number of elements in the array: ");
	scanf("%d", &size);
	printf("Enter %d elements: ", size);
  	for(i=0;i<size;i++)
    	scanf("%d",&a[i]);
	
	printf("\nForking now!\n");

	pid = fork();			//Here, the child process is created and both child & parent run 
							//simultaneously. fork() returns 0 to child process and pid of 								//child to parent process. So, if int pid here is 0, it means we 								//are in child process and if any +ve no., then in parent process 								//where the +ve no. is the child's pid.
	if(pid==0)
	{
		printf("\nCHILD: My process-id is %d.", getpid());
		printf("\nCHILD: My parent's process-id is %d.", getppid());
		quicksort(a, 0, size-1);
		
		printf("\nSorted elements: ");
 		for(i=0;i<size;i++)
    		printf(" %d",a[i]);
		
		printf("\nCHILD: I am dying now");
		printf("\n-------------------------------------------------------");
		/*	ORPHAN
		printf("\nCHILD: I am sleeping now.");
		sleep(10);
		printf("\n-------------------------------------------------------\n\n");
		system("ps -elf | grep a.out");*/

		//  ZOMBIE
		printf("\nCHILD: I am dying now");
		printf("\n-------------------------------------------------------\n\n");
		system("ps -elf | grep a.out");
		exit(0);
	}
	else if (pid>0)
	{
		system("wait");
		printf("\nPARENT: I am back. ");
		printf("\nPARENT: My process-id is %d.", getpid());	
		printf("\nPARENT: My child's process-id is %d.", pid);
		quicksort(a, 0, size-1);
		
		printf("\nSorted elements: ");
 		for(i=0;i<size;i++)
    		printf(" %d",a[i]);
		
		printf("\nPARENT: I am dying now.");
		printf("\n-------------------------------------------------------");
		/*  ORPHAN
		system("ps -elf | grep a.out");
		exit(0);*/

		// ZOMBIE
		printf("\nPARENT: I am sleeping now.");
		sleep(10);
		printf("\n-------------------------------------------------------\n");
		system("ps -elf | grep a.out");
	}
}

void quicksort(int a[10],int first,int last)
{
    int pivot,j,temp,i;

    if(first<last)
	{
		pivot=first;
        i=first;
        j=last;

        while(i<j){
            while(a[i]<=a[pivot]&&i<last)
                i++;
            while(a[j]>a[pivot])
                j--;
            if(i<j){
				temp=a[i];
                a[i]=a[j];
                a[j]=temp;
             }
         }

         temp=a[pivot];
         a[pivot]=a[j];
         a[j]=temp;
         quicksort(a,first,j-1);
         quicksort(a,j+1,last);
    }
}


/*
====================================OUTPUT====================================
pict@ubuntu:~/3807/Final$ gcc a_forkandsort.c 
pict@ubuntu:~/3807/Final$ ./a.out 

PARENT: My process-id is 2932.

Enter the number of elements in the array: 4
Enter 4 elements: 
56
12
388
92

Forking now!

CHILD: My process-id is 2934.
CHILD: My parent's process-id is 2932.
Sorted elements:  12 56 92 388
CHILD: I am dying now
-------------------------------------------------------
PARENT: I am back. 
PARENT: My process-id is 2932.
PARENT: My child's process-id is 2934.
Sorted elements:  12 56 92 388
PARENT: I am dying now.
-------------------------------------------------------
pict@ubuntu:~/3807/Final$

ORPHAN:
====================================OUTPUT====================================
pict@ubuntu:~/3807/Final$ gcc a_orphan.c
pict@ubuntu:~/3807/Final$ ./a.out 

PARENT: My process-id is 2949.
Forking now!

PARENT: I am back. 
PARENT: My process-id is 2949.
PARENT: My child's process-id is 2950.
PARENT: I am dying now
-------------------------------------------------------

CHILD: My process-id is 2950.
CHILD: My parent's process-id is 2949.
0 S pict      2949  2693  0  80   0 -   507 wait   12:37 pts/11   00:00:00 ./a.out
1 S pict      2950  2949  0  80   0 -   507 hrtime 12:37 pts/11   00:00:00 ./a.out
0 S pict      2951  2949  0  80   0 -   567 wait   12:37 pts/11   00:00:00 sh -c ps -elf | grep a.out
0 S pict      2953  2951  0  80   0 -  1170 pipe_w 12:37 pts/11   00:00:00 grep a.out
pict@ubuntu:~/3807/Final$ CHILD: I am sleeping now.
-------------------------------------------------------

1 S pict      2950  1852  0  80   0 -   507 wait   12:37 pts/11   00:00:00 ./a.out
0 S pict      2955  2950  0  80   0 -   567 wait   12:37 pts/11   00:00:00 sh -c ps -elf | grep a.out
0 S pict      2957  2955  0  80   0 -  1170 pipe_w 12:37 pts/11   00:00:00 grep a.out

pict@ubuntu:~/3807/Final$


ZOMBIE:
gcc a_zombie.c
amar@Amar-Dell-System-Inspiron-5420:~/Final$ ./a.out 

PARENT: My process-id is 2480.
Forking now!

PARENT: I am back. 
PARENT: My process-id is 2480.
PARENT: My child's process-id is 2481.

CHILD: My process-id is 2481.
CHILD: My parent's process-id is 2480.
CHILD: I am dying now
-------------------------------------------------------

0 S amar      2480  2395  0  80   0 -  1049 hrtime 13:21 pts/0    00:00:00 ./a.out
1 S amar      2481  2480  0  80   0 -  1049 wait   13:21 pts/0    00:00:00 ./a.out
0 S amar      2482  2481  0  80   0 -  1111 wait   13:21 pts/0    00:00:00 sh -c ps -elf | grep a.out
0 S amar      2484  2482  0  80   0 -  3985 pipe_w 13:21 pts/0    00:00:00 grep a.out
PARENT: I am sleeping now.
-------------------------------------------------------
0 S amar      2480  2395  0  80   0 -  1049 wait   13:21 pts/0    00:00:00 ./a.out
1 Z amar      2481  2480  0  80   0 -     0 exit   13:21 pts/0    00:00:00 [a.out] <defunct>
0 S amar      2486  2480  0  80   0 -  1111 wait   13:21 pts/0    00:00:00 sh -c ps -elf | grep a.out
0 S amar      2488  2486  0  80   0 -  3985 pipe_w 13:21 pts/0    00:00:00 grep 
*/
