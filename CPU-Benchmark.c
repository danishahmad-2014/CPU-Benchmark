/****************************************************************************************
			DANISH AHMAD
			
			Code Reuse			

			Component Based Learning FOR SOFTWARE ENGINEERING
			
			VIT University CHENNAI CAMPUS.

			CPU BENCHMARK				
/*****************************************************************************************/
#include<omp.h>
#include<stdio.h>
#include<time.h>
#include<sys/utsname.h>
#include <stdlib.h>
#include <string.h>


#define _GNU_SOURCE
#define FLOPS_ARRAY_SIZE (1024*1024)
#define MAXFLOPS_ITERS 100000000
#define LOOP_COUNT 128
#define FLOPSPERCALC 2
float fa[FLOPS_ARRAY_SIZE] ;
float fb[FLOPS_ARRAY_SIZE] ;
float fa1[FLOPS_ARRAY_SIZE];
float fb1[FLOPS_ARRAY_SIZE] ;
float fa2[FLOPS_ARRAY_SIZE] ;
float fb2[FLOPS_ARRAY_SIZE] ;
float fa3[FLOPS_ARRAY_SIZE] ;
float fb3[FLOPS_ARRAY_SIZE] ;
int main(int argc, char **argv)

{
//========================================================================================
//					VARIABLES						 
//========================================================================================
double istart,iend,itotal,istart2,iend2,itotal2,istart3,iend3,itotal3,istart4,iend4,itotal4;
double pstart,pend,ptotal,pstart2,pend2,ptotal2,pstart3,pend3,ptotal3,pstart4,pend4,ptotal4;
double gstart,gend,gtotal,gstart2,gend2,gtotal2,gstart3,gend3,gtotal3,gstart4,gend4,gtotal4;
int i,j,k, thread_id, nloops,sum;
int num=1,prime=0;
int limit=500000;
int numthreads;
double gflops = 0.0,gflops2 = 0.0,gflops3 = 0.0,gflops4 = 0.0;
float a=1.1;
/*****************************************************************************************
			FOR CPU INFORMATION				
******************************************************************************************/

FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");
   char *arg = 0;
   size_t size = 0;
   while(getdelim(&arg, &size, 0, cpuinfo) != -1)
   {
      puts(arg);
   }
   free(arg);
   fclose(cpuinfo);
/*****************************************************************************************
			FOR SYSTEM INFORMATION				
******************************************************************************************/
char hostname[1024];
struct utsname userinfo;
if(uname(&userinfo)>=0)
{
  printf("\n***** System Details ******\n");
  printf("System Name    : %s\n",userinfo.sysname);
  printf("System Node    : %s\n",userinfo.nodename);
  printf("System Release : %s\n",userinfo.release);
  printf("System Version : %s\n",userinfo.version);
  printf("System Machine : %s\n",userinfo.machine);
}
else
 printf("\nSystem details fetch failed..\n");



if(gethostname(&hostname,1024)==0)
{
  printf("Hostname       : %s\n",hostname);
}  
else
 printf("\nHostname details fetch failed..\n");

int id=omp_get_max_threads();
printf("No of Cores are %d\n",id);
printf("\n\n");
printf("============================================================================================================\n");
printf("\t\t\t\t\t\tCPU BENCHMARKING\n");
printf("============================================================================================================\n");
printf("\t\t\tCORE 1\t\t\tCORE 2\t\t\tCORE 4\t\t\tCORE 8  \n");






/****************************************************************************************
 ****************************************************************************************
			FOR SINGLE CORE (LIKE CELERON,PENTIUM III,AMD SEMPRON)	
*****************************************************************************************			
*****************************************************************************************/

if(id==1)
{

printf("\nITERATION\t\t");
//========================================================================================
//					ITRATION						 
//========================================================================================
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				SEQUENTIAL (1 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
istart=omp_get_wtime();
omp_set_num_threads(1);
#pragma omp parallel for schedule(dynamic)
  
  for (i=0; i<400000; ++i)
      {
	for(j=0;j<=10000;j++){
	sum=i+j;
       
	}
      }

    
iend=omp_get_wtime();

  
itotal=iend-istart;
printf("%f\t\t",itotal);


//========================================================================================
//					PRIME CALCULATION						 
//========================================================================================
printf("\nPRIME\t\t\t");
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				SEQUENTIAL (1 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
pstart=omp_get_wtime();
omp_set_num_threads(1);

#pragma omp parallel for schedule(dynamic) reduction(+:prime)
for(num=1;num<limit;num++)
{
int i=2;
while(i<=num)
{
if(num%i==0)
break;
i++;
if(i==num){
prime++;

}
}
}

pend=omp_get_wtime();
ptotal=pend-pstart;
printf("%f\t\t",ptotal);

//========================================================================================
//					GFLOPS						 
//========================================================================================*/
printf("\nGFLOPS\t\t");
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				SEQUENTIAL (1 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
omp_set_num_threads(1);
#pragma omp parallel for
  for(i=0; i<FLOPS_ARRAY_SIZE; i++)
  {
    if (i==0) numthreads = omp_get_num_threads();
    fa[i] = (float)i + 0.1;
    fb[i] = (float)i + 0.2;
  }
  
 
  gstart=omp_get_wtime();
  



#pragma omp parallel for private(j,k)
  for (i=0; i<numthreads; i++)
  {
    
    int offset = i*LOOP_COUNT;

    
    for(j=0; j<MAXFLOPS_ITERS; j++)
    {
    
      for(k=0; k<LOOP_COUNT; k++)
      {
        fa[k+offset] = a * fa[k+offset] + fb[k+offset];
      }
    }
  }
  
  gend=omp_get_wtime();
  
  gflops = (double)( 1.0e-9 * numthreads * LOOP_COUNT * MAXFLOPS_ITERS * FLOPSPERCALC );
  
  gtotal = gend - gstart;
printf("   %lf\t\t %lf\t\t %lf\t\t", gflops,gflops2,gflops3);
printf("\nTime\t\t   %lf\t\t %lf\t\t %lf\t\t", gtotal,gtotal2,gtotal3);
printf("\nGflops/sec    \t   %lf\t\t %lf\t\t %lf\t\t", gflops/gtotal,gflops2/gtotal2,gflops3/gtotal3);

}
/****************************************************************************************
 ****************************************************************************************
			FOR DUAL CORE 	(LIKE PENTIUM 4,INTEL DUAL CORE,AMD ATHLON )	
*****************************************************************************************			
*****************************************************************************************/
if(id==2)
{

printf("\nITERATION\t\t");
//========================================================================================
//					ITRATION						 
//========================================================================================

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				SEQUENTIAL (1 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
istart=omp_get_wtime();
omp_set_num_threads(1);
#pragma omp parallel for schedule(dynamic)
  
  for (i=0; i<400000; ++i)
      {
	for(j=0;j<=10000;j++){
	sum=i+j;
       
	}
      }

    
iend=omp_get_wtime();

  
itotal=iend-istart;
printf("%f\t\t",itotal);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (2 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
istart2=omp_get_wtime();
omp_set_num_threads(2);
#pragma omp parallel for schedule(dynamic)
  
  for (i=0; i<400000; ++i)
      {
	for(j=0;j<=10000;j++){
	sum=i+j;
       
	}
      }

    
iend2=omp_get_wtime();

  
itotal2=iend2-istart2;
printf("%f\t\t",itotal2);
//========================================================================================
//					PRIME CALCULATION						 
//========================================================================================
printf("\nPRIME\t\t\t");
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				SEQUENTIAL (1 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
pstart=omp_get_wtime();
omp_set_num_threads(1);

#pragma omp parallel for schedule(dynamic) reduction(+:prime)
for(num=1;num<limit;num++)
{
int i=2;
while(i<=num)
{
if(num%i==0)
break;
i++;
if(i==num){
prime++;

}
}
}

pend=omp_get_wtime();
ptotal=pend-pstart;
printf("%f\t\t",ptotal);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (2 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
pstart2=omp_get_wtime();
omp_set_num_threads(2);
#pragma omp parallel for schedule(dynamic) reduction(+:prime)
for(num=1;num<limit;num++)
{
int i=2;
while(i<=num)
{
if(num%i==0)
break;
i++;
if(i==num){
prime++;

}
}
}
pend2=omp_get_wtime();
ptotal2=pend2-pstart2;
printf("%f\t\t",ptotal2);

//========================================================================================
//					GFLOPS						 
//========================================================================================*/
printf("\nGFLOPS\t\t");
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				SEQUENTIAL (1 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
omp_set_num_threads(1);
#pragma omp parallel for
  for(i=0; i<FLOPS_ARRAY_SIZE; i++)
  {
    if (i==0) numthreads = omp_get_num_threads();
    fa[i] = (float)i + 0.1;
    fb[i] = (float)i + 0.2;
  }
  
 
  gstart=omp_get_wtime();
  



#pragma omp parallel for private(j,k)
  for (i=0; i<numthreads; i++)
  {
    
    int offset = i*LOOP_COUNT;

    
    for(j=0; j<MAXFLOPS_ITERS; j++)
    {
    
      for(k=0; k<LOOP_COUNT; k++)
      {
        fa[k+offset] = a * fa[k+offset] + fb[k+offset];
      }
    }
  }
  
  gend=omp_get_wtime();
  
  gflops = (double)( 1.0e-9 * numthreads * LOOP_COUNT * MAXFLOPS_ITERS * FLOPSPERCALC );
  
  gtotal = gend - gstart;
  
 
  
  
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (2 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
omp_set_num_threads(2);
#pragma omp parallel for
  for(i=0; i<FLOPS_ARRAY_SIZE; i++)
  {
    if (i==0) numthreads = omp_get_num_threads();
    fa1[i] = (float)i + 0.1;
    fb1[i] = (float)i + 0.2;
  }
  
 
  gstart2=omp_get_wtime();
  



#pragma omp parallel for private(j,k)
  for (i=0; i<numthreads; i++)
  {
    
    int offset = i*LOOP_COUNT;

    
    for(j=0; j<MAXFLOPS_ITERS; j++)
    {
    
      for(k=0; k<LOOP_COUNT; k++)
      {
        fa1[k+offset] = a * fa1[k+offset] + fb1[k+offset];
      }
    }
  }
  
  gend2=omp_get_wtime();
  
  gflops2 = (double)( 1.0e-9 * numthreads * LOOP_COUNT * MAXFLOPS_ITERS * FLOPSPERCALC );
  
  gtotal2 = gend2 - gstart2;
printf("   %lf\t\t %lf\t\t %lf\t\t", gflops,gflops2,gflops3);
printf("\nTime\t\t   %lf\t\t %lf\t\t %lf\t\t", gtotal,gtotal2,gtotal3);
printf("\nGflops/sec    \t   %lf\t\t %lf\t\t %lf\t\t", gflops/gtotal,gflops2/gtotal2,gflops3/gtotal3);

}
/****************************************************************************************
 ****************************************************************************************
			FOR QUAD CORE 	(LIKE i3)			
*****************************************************************************************			
*****************************************************************************************/
if(id==4)
{


printf("\nITERATION\t\t");
//========================================================================================
//					ITRATION						 
//========================================================================================

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				SEQUENTIAL (1 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
istart=omp_get_wtime();
omp_set_num_threads(1);
#pragma omp parallel for schedule(dynamic)
  
  for (i=0; i<400000; ++i)
      {
	for(j=0;j<=10000;j++){
	sum=i+j;
       
	}
      }

    
iend=omp_get_wtime();

  
itotal=iend-istart;
printf("%f\t\t",itotal);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (2 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
istart2=omp_get_wtime();
omp_set_num_threads(2);
#pragma omp parallel for schedule(dynamic)
  
  for (i=0; i<400000; ++i)
      {
	for(j=0;j<=10000;j++){
	sum=i+j;
       
	}
      }

    
iend2=omp_get_wtime();

  
itotal2=iend2-istart2;
printf("%f\t\t",itotal2);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (4 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
istart3=omp_get_wtime();
omp_set_num_threads(4);
#pragma omp parallel for schedule(dynamic)
  
  for (i=0; i<400000; ++i)
      {
	for(j=0;j<=10000;j++){
	sum=i+j;
       
	}
      }

    
iend3=omp_get_wtime();

  
itotal3=iend3-istart3;
printf("%f\t\t",itotal3);

//========================================================================================
//					PRIME CALCULATION						 
//========================================================================================
printf("\nPRIME\t\t\t");
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				SEQUENTIAL (1 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
pstart=omp_get_wtime();
omp_set_num_threads(1);

#pragma omp parallel for schedule(dynamic) reduction(+:prime)
for(num=1;num<limit;num++)
{
int i=2;
while(i<=num)
{
if(num%i==0)
break;
i++;
if(i==num){
prime++;

}
}
}

pend=omp_get_wtime();
ptotal=pend-pstart;
printf("%f\t\t",ptotal);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (2 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
pstart2=omp_get_wtime();
omp_set_num_threads(2);
#pragma omp parallel for schedule(dynamic) reduction(+:prime)
for(num=1;num<limit;num++)
{
int i=2;
while(i<=num)
{
if(num%i==0)
break;
i++;
if(i==num){
prime++;

}
}
}
pend2=omp_get_wtime();
ptotal2=pend2-pstart2;
printf("%f\t\t",ptotal2);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (4 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
pstart3=omp_get_wtime();
omp_set_num_threads(4);
  
#pragma omp parallel for schedule(dynamic) reduction(+:prime)
for(num=1;num<limit;num++)
{
int i=2;
while(i<=num)
{
if(num%i==0)
break;
i++;
if(i==num){
prime++;

}
}
}

pend3=omp_get_wtime();
ptotal3=pend3-pstart3;
printf("%f\n",ptotal3);




//========================================================================================
//					GFLOPS						 
//========================================================================================*/
printf("\nGFLOPS\t\t");
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				SEQUENTIAL (1 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
omp_set_num_threads(1);
#pragma omp parallel for
  for(i=0; i<FLOPS_ARRAY_SIZE; i++)
  {
    if (i==0) numthreads = omp_get_num_threads();
    fa[i] = (float)i + 0.1;
    fb[i] = (float)i + 0.2;
  }
  
 
  gstart=omp_get_wtime();
  



#pragma omp parallel for private(j,k)
  for (i=0; i<numthreads; i++)
  {
    
    int offset = i*LOOP_COUNT;

    
    for(j=0; j<MAXFLOPS_ITERS; j++)
    {
    
      for(k=0; k<LOOP_COUNT; k++)
      {
        fa[k+offset] = a * fa[k+offset] + fb[k+offset];
      }
    }
  }
  
  gend=omp_get_wtime();
  
  gflops = (double)( 1.0e-9 * numthreads * LOOP_COUNT * MAXFLOPS_ITERS * FLOPSPERCALC );
  
  gtotal = gend - gstart;
  
 
  
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (2 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
omp_set_num_threads(2);
#pragma omp parallel for
  for(i=0; i<FLOPS_ARRAY_SIZE; i++)
  {
    if (i==0) numthreads = omp_get_num_threads();
    fa1[i] = (float)i + 0.1;
    fb1[i] = (float)i + 0.2;
  }
  
 
  gstart2=omp_get_wtime();
  



#pragma omp parallel for private(j,k)
  for (i=0; i<numthreads; i++)
  {
    
    int offset = i*LOOP_COUNT;

    
    for(j=0; j<MAXFLOPS_ITERS; j++)
    {
    
      for(k=0; k<LOOP_COUNT; k++)
      {
        fa1[k+offset] = a * fa1[k+offset] + fb1[k+offset];
      }
    }
  }
  
  gend2=omp_get_wtime();
  
  gflops2 = (double)( 1.0e-9 * numthreads * LOOP_COUNT * MAXFLOPS_ITERS * FLOPSPERCALC );
  
  gtotal2 = gend2 - gstart2;
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (4 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
omp_set_num_threads(4);
#pragma omp parallel for
  for(i=0; i<FLOPS_ARRAY_SIZE; i++)
  {
    if (i==0) numthreads = omp_get_num_threads();
    fa2[i] = (float)i + 0.1;
    fb2[i] = (float)i + 0.2;
  }
  
 
  gstart3=omp_get_wtime();
  



#pragma omp parallel for private(j,k)
  for (i=0; i<numthreads; i++)
  {
    
    int offset = i*LOOP_COUNT;

    
    for(j=0; j<MAXFLOPS_ITERS; j++)
    {
    
      for(k=0; k<LOOP_COUNT; k++)
      {
        fa2[k+offset] = a * fa2[k+offset] + fb2[k+offset];
      }
    }
  }
  
  gend3=omp_get_wtime();
  
  gflops3 = (double)( 1.0e-9 * numthreads * LOOP_COUNT * MAXFLOPS_ITERS * FLOPSPERCALC );
  
  gtotal3 = gend3 - gstart3;
printf("   %lf\t\t %lf\t\t %lf\t\t", gflops,gflops2,gflops3);
printf("\nTime\t\t   %lf\t\t %lf\t\t %lf\t\t", gtotal,gtotal2,gtotal3);
printf("\nGflops/sec    \t   %lf\t\t %lf\t\t %lf\t\t", gflops/gtotal,gflops2/gtotal2,gflops3/gtotal3);

}
/****************************************************************************************
			FOR OCTA CORE 	(LIKE i7)			
/*****************************************************************************************/
if(id==8)
{

printf("\nITERATION\t\t");
//========================================================================================
//					ITRATION						 
//========================================================================================

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				SEQUENTIAL (1 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
istart=omp_get_wtime();
omp_set_num_threads(1);
#pragma omp parallel for schedule(dynamic)
  
  for (i=0; i<400000; ++i)
      {
	for(j=0;j<=10000;j++){
	sum=i+j;
       
	}
      }

    
iend=omp_get_wtime();

  
itotal=iend-istart;
printf("%f\t\t",itotal);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (2 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
istart2=omp_get_wtime();
omp_set_num_threads(2);
#pragma omp parallel for schedule(dynamic)
  
  for (i=0; i<400000; ++i)
      {
	for(j=0;j<=10000;j++){
	sum=i+j;
       
	}
      }

    
iend2=omp_get_wtime();

  
itotal2=iend2-istart2;
printf("%f\t\t",itotal2);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (4 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
istart3=omp_get_wtime();
omp_set_num_threads(4);
#pragma omp parallel for schedule(dynamic)
  
  for (i=0; i<400000; ++i)
      {
	for(j=0;j<=10000;j++){
	sum=i+j;
       
	}
      }

    
iend3=omp_get_wtime();

  
itotal3=iend3-istart3;
printf("%f\t\t",itotal3);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (8 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
istart4=omp_get_wtime();
omp_set_num_threads(8);
#pragma omp parallel for schedule(dynamic)
  
  for (i=0; i<400000; ++i)
      {
	for(j=0;j<=10000;j++){
	sum=i+j;
       
	}
      }

    
iend4=omp_get_wtime();

  
itotal4=iend4-istart4;
printf("%f\t\t",itotal4);

//========================================================================================
//					PRIME CALCULATION						 
//========================================================================================
printf("\nPRIME\t\t\t");
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				SEQUENTIAL (1 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
pstart=omp_get_wtime();
omp_set_num_threads(1);

#pragma omp parallel for schedule(dynamic) reduction(+:prime)
for(num=1;num<limit;num++)
{
int i=2;
while(i<=num)
{
if(num%i==0)
break;
i++;
if(i==num){
prime++;

}
}
}

pend=omp_get_wtime();
ptotal=pend-pstart;
printf("%f\t\t",ptotal);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (2 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
pstart2=omp_get_wtime();
omp_set_num_threads(2);
#pragma omp parallel for schedule(dynamic) reduction(+:prime)
for(num=1;num<limit;num++)
{
int i=2;
while(i<=num)
{
if(num%i==0)
break;
i++;
if(i==num){
prime++;

}
}
}
pend2=omp_get_wtime();
ptotal2=pend2-pstart2;
printf("%f\t\t",ptotal2);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (4 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
pstart3=omp_get_wtime();
omp_set_num_threads(4);
  
#pragma omp parallel for schedule(dynamic) reduction(+:prime)
for(num=1;num<limit;num++)
{
int i=2;
while(i<=num)
{
if(num%i==0)
break;
i++;
if(i==num){
prime++;

}
}
}

pend3=omp_get_wtime();
ptotal3=pend3-pstart3;
printf("%f\t\t",ptotal3);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (8 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
pstart4=omp_get_wtime();
omp_set_num_threads(8);
  
#pragma omp parallel for schedule(dynamic) reduction(+:prime)
for(num=1;num<limit;num++)
{
int i=2;
while(i<=num)
{
if(num%i==0)
break;
i++;
if(i==num){
prime++;

}
}
}

pend4=omp_get_wtime();
ptotal4=pend4-pstart4;
printf("%f\n",ptotal4);



//========================================================================================
//					GFLOPS						 
//========================================================================================*/
printf("GFLOPS\t\t\t");
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				SEQUENTIAL (1 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
omp_set_num_threads(1);
#pragma omp parallel for
  for(i=0; i<FLOPS_ARRAY_SIZE; i++)
  {
    if (i==0) numthreads = omp_get_num_threads();
    fa[i] = (float)i + 0.1;
    fb[i] = (float)i + 0.2;
  }
  
 
  gstart=omp_get_wtime();
  



#pragma omp parallel for private(j,k)
  for (i=0; i<numthreads; i++)
  {
    
    int offset = i*LOOP_COUNT;

    
    for(j=0; j<MAXFLOPS_ITERS; j++)
    {
    
      for(k=0; k<LOOP_COUNT; k++)
      {
        fa[k+offset] = a * fa[k+offset] + fb[k+offset];
      }
    }
  }
  
  gend=omp_get_wtime();
  
  gflops = (double)( 1.0e-9 * numthreads * LOOP_COUNT * MAXFLOPS_ITERS * FLOPSPERCALC );
  
  gtotal = gend - gstart;
  
 
  
  
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (2 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
omp_set_num_threads(2);
#pragma omp parallel for
  for(i=0; i<FLOPS_ARRAY_SIZE; i++)
  {
    if (i==0) numthreads = omp_get_num_threads();
    fa1[i] = (float)i + 0.1;
    fb1[i] = (float)i + 0.2;
  }
  
 
  gstart2=omp_get_wtime();
  



#pragma omp parallel for private(j,k)
  for (i=0; i<numthreads; i++)
  {
    
    int offset = i*LOOP_COUNT;

    
    for(j=0; j<MAXFLOPS_ITERS; j++)
    {
    
      for(k=0; k<LOOP_COUNT; k++)
      {
        fa1[k+offset] = a * fa1[k+offset] + fb1[k+offset];
      }
    }
  }
  
  gend2=omp_get_wtime();
  
  gflops2 = (double)( 1.0e-9 * numthreads * LOOP_COUNT * MAXFLOPS_ITERS * FLOPSPERCALC );
  
  gtotal2 = gend2 - gstart2;
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (4 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
omp_set_num_threads(4);
#pragma omp parallel for
  for(i=0; i<FLOPS_ARRAY_SIZE; i++)
  {
    if (i==0) numthreads = omp_get_num_threads();
    fa2[i] = (float)i + 0.1;
    fb2[i] = (float)i + 0.2;
  }
  
 
  gstart3=omp_get_wtime();
  



#pragma omp parallel for private(j,k)
  for (i=0; i<numthreads; i++)
  {
    
    int offset = i*LOOP_COUNT;

    
    for(j=0; j<MAXFLOPS_ITERS; j++)
    {
    
      for(k=0; k<LOOP_COUNT; k++)
      {
        fa2[k+offset] = a * fa2[k+offset] + fb2[k+offset];
      }
    }
  }
  
  gend3=omp_get_wtime();
  
  gflops3 = (double)( 1.0e-9 * numthreads * LOOP_COUNT * MAXFLOPS_ITERS * FLOPSPERCALC );
  
  gtotal3 = gend3 - gstart3;
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//				PARALLEL (8 CORES)
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
omp_set_num_threads(8);
#pragma omp parallel for
  for(i=0; i<FLOPS_ARRAY_SIZE; i++)
  {
    if (i==0) numthreads = omp_get_num_threads();
    fa3[i] = (float)i + 0.1;
    fb3[i] = (float)i + 0.2;
  }
  
 
  gstart4=omp_get_wtime();
  



#pragma omp parallel for private(j,k)
  for (i=0; i<numthreads; i++)
  {
    
    int offset = i*LOOP_COUNT;

    
    for(j=0; j<MAXFLOPS_ITERS; j++)
    {
    
      for(k=0; k<LOOP_COUNT; k++)
      {
        fa3[k+offset] = a * fa3[k+offset] + fb3[k+offset];
      }
    }
  }
  
  gend4=omp_get_wtime();
  
  gflops4 = (double)( 1.0e-9 * numthreads * LOOP_COUNT * MAXFLOPS_ITERS * FLOPSPERCALC );
  
  gtotal4 = gend4 - gstart4;
printf("   %lf\t\t %lf\t\t %lf\t\t%lf\t\t", gflops,gflops2,gflops3,gflops4);
printf("\nTime\t\t   %lf\t\t %lf\t\t %lf\t\t%lf\t\t", gtotal,gtotal2,gtotal3,gflops4);
printf("\nGflops/sec    \t   %lf\t\t %lf\t\t %lf\t\t%lf\t\t", gflops/gtotal,gflops2/gtotal2,gflops3/gtotal3,gflops4/gtotal4);
printf("\n");
}

return 0;
}
