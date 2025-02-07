#include<stdio.h>
#include<pthread.h>
#define m 5
#define n 7
#define k 3

int A[5][3]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int B[3][7]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
int C[5][7];

struct send
{
	int row;
	int column;
	int *a;
	int *b;
};

//typdef struct send sender;
void *calc (struct send* input);

int main ( int argc, char *argv[ ] ) 
{ 
	int i,j;
	pthread_t tid[35];
	pthread_attr_t attr;
	pthread_attr_init ( &attr);

	struct send s[35];

	int inti=0;

	for(i=0;i<5;i++)
		for(j=0;j<7;j++)
		{
			s[inti].row=i;
			s[inti].column=j;
			s[inti].a=A[i];
			s[inti].b=&B[0][j];
			pthread_create ( &tid[inti],&attr,calc,&s[inti]);
			inti++;
		}

	for(i=0;i<35;i++)
		pthread_join ( tid[i], NULL );

	for(i=0;i<5;i++)
	{
		printf("\n");
		for(j=0;j<7;j++)
		{
			printf("%d\t",C[i][j]);
		}
	}

	return 0;
}

void *calc (struct send* input)
{
	int i=0,j=0;
	int sum=0;
	int rowval,colval;
	int *row=input->a;
	int *column=input->b;

	for ( i=0; i <5; i++ )
	{
		rowval=*(row+i);
		colval=*(column+(7*i));
		sum=sum+(rowval*colval);
	}

	C[input->row][input->column]=sum;
	pthread_exit(0);
}
