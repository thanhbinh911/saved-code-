#include<time.h>
#include<stdio.h>
#include<unistd.h>
#define MAX 100

int main()
{
	
	clock_t start,end;
	start=clock();
	int a[10];
	time_t now;
	time(&now);
	printf("%d\n", now);
//	for(int i=0; i<10; i++) 
//	scanf("%d", &a[i]);
//	sleep(2);
//	time_t pass=time(NULL);
//	printf("%ld\n", pass);
//		double diff=difftime(pass, now);
// 			printf("%f", diff);
//	time_t binhgiang;printf("%d", binhgiang);
	char*string_now=ctime(&now);
	printf("%s", string_now);
//	struct tm*gm_time=gmtime(&now);
//	printf("tm_sec : %d\n",gm_time->tm_sec);
//	printf("tm_min : %d\n",gm_time->tm_min);
//	printf("tm_hour : %d\n",gm_time->tm_hour);
//	printf("tm_mday : %d\n",gm_time->tm_mday); // day of the month
//	printf("tm_mon : %d\n",gm_time->tm_mon);//months since january(0-11)
//	printf("tm_year : %d\n",gm_time->tm_year);//years since 1900
//	printf("tm_wday : %d\n",gm_time->tm_wday); //days since Sunday(0-6)
//	printf("tm_yday : %d\n",gm_time->tm_yday); //days since january 1
//	printf("tm_isdst : %d\n",gm_time->tm_isdst); 
//	printf("\n");
	
	struct tm*local_time=localtime(&now);
	
	printf("tm_sec : %d\n",local_time->tm_sec);
	printf("tm_min : %d\n",local_time->tm_min);
	printf("tm_hour : %d\n",local_time->tm_hour);
	printf("tm_mday : %d\n",local_time->tm_mday); // day of the month
	printf("tm_mon : %d\n",local_time->tm_mon);//months since january(0-11)
	printf("tm_year : %d\n",local_time->tm_year);//years since 1900
	printf("tm_wday : %d\n",local_time->tm_wday); //days since Sunday(0-6)
	printf("tm_yday : %d\n",local_time->tm_yday); //days since january 1
	printf("tm_isdst : %d\n",local_time->tm_isdst); 
	printf("\n");
//	char*otherstring=asctime(local_time);
//	printf("%s",otherstring );
//	local_time->tm_min=local_time->tm_min+1;
//	time_t newtime=mktime(local_time);
//	printf("%d\n", now);
//	printf("%d\n", newtime);
	char s[MAX];
	int strlen=strftime(s,sizeof(s),"%x",local_time);
	printf("%s\n", s);
	printf("%d", strlen);
	end=clock();
	double total=(double)(end-start)/CLOCKS_PER_SEC;
	printf("%fs\n", total);
	printf("%d",CLOCKS_PER_SEC);
}
