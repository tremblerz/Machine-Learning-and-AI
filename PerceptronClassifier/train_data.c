#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<fcntl.h>

//#define NODES_HIDDEN 4
#define FILENAME "iris.data"

void readData(char *filename , float input[][5] , int output[][4] , int inp_limit ){
  FILE *fp = fopen( filename , "r" );
  int i = 0 , j , row=1;
  float data;
  char c  , str[20];
  if( fp == NULL ){
    printf("Can't open the file\n");
    return;
  }

  for ( ; i<5; i++ )
    input[0][i] = i + 1;
  
  for ( i=0; i<inp_limit; i++)
    output[0][i] = 0;

  while( (EOF != fscanf( fp , "%f,%f,%f,%f,%s\n" , &input[row][1] , &input[row][2] , &input[row][3] , &input[row][4] , str ) ) && row <= inp_limit ){
    input[row][0] = 1;
    if(strcmp(str , "Iris-versicolor") == 0)
      output[row][1] = 1;
    else if (strcmp(str , "Iris-virginica") == 0)
      output[row][2] = 1;
    else if (strcmp(str , "Iris-setosa") == 0)
      output[row][3] = 1;
    else{
      printf("Invalid data in file !\n");
      return;
    }
    row++;
  }
  for( i=1; i<row; i++ )
    output[i][0] = i;

/*  for(i=0;i<row;i++){
    for(j=0;j<4;j++)
      printf("%0.1f," , input[i][j]);
    printf("\n");
  }
  printf("number of rows = %d\n" , row);*/
}

float rando(){
	srand(time(NULL));
	return (1 + (0.5 * drand48()));
}
void swap (float *a, float *b){
    float temp = *a;
    *a = *b;
    *b = temp;
}

void randomizeData( float input[][5] , int output[][4] , int limit ){
  srand(time(NULL));
  int i,k;
  for( i=limit-1; i>=0; i-- ){
    int j = rand() % (i+1);
    for( k=0; k<5; k++ ){

      swap( &input[i][k] , &input[j][k] );
      if( k<4 )
        swap( &output[i][k] , &output[j][k] );
    }
  }
}


int main()
{
	int NODES_HIDDEN , i , j , k;
	printf("Enter No. of Hidden nodes:- ");
	scanf("%d",&NODES_HIDDEN);
	float MulIH[101][NODES_HIDDEN+1],WeightIH[5][NODES_HIDDEN+1],activate[101][NODES_HIDDEN+1],MulHO[101][4],WeightHO[NODES_HIDDEN][4],deltak[4],deltaj[5],sum[5],deltaIH[5][NODES_HIDDEN+1],deltaHO[NODES_HIDDEN+1][4];
	float eta=0.1,zeta=0.1,rand_weight=0.5;
	int trainInpLimit = 150 , targetInpLimit = 50;
	double Output[101][4];

	int patterns=100,input=4,hiddenNodes=NODES_HIDDEN,output=3;
	float inp_vector[151][5];
	int target[151][4];
	float inp_vector_test[51][5];
	int target_test[51][4];

	readData( FILENAME , inp_vector , target , trainInpLimit );
//	randomizeData( inp_vector , target , trainInpLimit);


	for( i=100;i<151;i++){
    	for( k=0; k<5; k++ ){	
      		inp_vector_test[i-100][k] = inp_vector[i][k]; 
      	//	printf("%0.2f,", inp_vector_test[i-100][k]);
    	}
    	for( k=0; k<4; k++ ){
    		target_test[i-100][k] = target[i][k];
    	//	printf("%d,", target_test[i-100][k]);
    	}
    	//printf("\n");
    }

/*
	for ( i=0; i<trainInpLimit; i++ ){
		for( j=0; j<5; j++)
			printf( "%0.2f," , inp_vector[i][j] );
		printf("\n");
	}
*/
	float wt=0.5;
//	int j=0,i=0;
	//printf("hidden nodes %d\n",hiddenNodes);
	for(i=1;i<=hiddenNodes;i++)
	{
		for(j=0;j<=input;j++)
		{
			deltaIH[j][i]=0.0;
			WeightIH[j][i]=rando();
	//		printf("i = %d - j = %d - weight = %f\n",i,j,WeightIH[j][i]);
		}
		//printf("\n");
	}
	/*for(i=1;i<=NODES_HIDDEN;i++)
	{
		for(j=0;j<=input;j++)
		{
			printf("Weight - %f\t",WeightIH[j][i]);
		}
		printf("\n");
	}*/
	
	for(k=1;k<=output;k++)
	{
		for(j=0;j<=hiddenNodes;j++)
		{
			deltaHO[j][k]=0.0;
			WeightHO[j][k]=rando();
		}
	}
	int epo=0;
	int po=0,temp=0;
	int var=10000;
	int hash_hidden[101];
	while(epo<var)
	{
			/*for(po=0;po<patterns;po++)
			{
				hash[po]=po;
			}
			for(po=0;po<patterns;po++)
			{
				po1=po+rando()*(patterns+1-po);
				temp=hash(po);
				hash[po]=hash[po1];
				hash[po1]=temp;
			}*/
		double error=0.0;
		for(po=1;po<=patterns;po++)
		{
			for(i=1;i<=hiddenNodes;i++)
			{	
				//printf("i is ->  %f\n",WeightIH[0][i]);
				MulIH[po][i]=WeightIH[0][i];
				for(j=1;j<=input;j++)
				{
					//printf("input is :- %f\n",WeightIH[j][i]);
					MulIH[po][i]+=inp_vector[po][j]*WeightIH[j][i];
				}
				//printf("Mul -> %f\n",exp(-MulIH[po][i]));
				activate[po][i]=(float)1.0/(float)(1.0 + exp(-MulIH[po][i]));
				//printf("activate is -> %lf\n",activate[po][i]);
			}
			for(k=1;k<=output;k++)
			{
				//printf("j is -> %f\n",WeightHO[0][k]);
				MulHO[po][k]=WeightHO[0][k];
				for(j=1;j<=hiddenNodes;j++)
				{
					MulHO[po][k]=activate[po][j]*WeightHO[j][k];
				}
				Output[po][k]=1.0/(1.0 + exp(-MulHO[po][k]));
				//printf("output is - %f\n ",Output[po][k]);
				error=0.5*((double)target[po][k]-(double)Output[po][k])*((double)target[po][k]-(double)Output[po][k]);
				deltak[k]=(target[po][k]-Output[po][k])*Output[po][k]*(1.0 - Output[po][k]);
			}
			for(i=1;i<=hiddenNodes;i++)
			{
				sum[i]=0.0;
				for(j=1;j<=output;j++)
				{
					sum[i]+=WeightHO[i][j]*deltak[j];
				}
				deltaj[i]=sum[i]*activate[po][i]*(1.0 - activate[po][i]);
				//printf("sum is - %f\n",sum[i]);
			}
			for(j=1;j<=hiddenNodes;j++)
			{

				deltaIH[0][j]=eta*deltaj[j]+zeta*deltaIH[0][j];

				WeightIH[0][j]+=deltaIH[0][j];
				for(k=1;k<=input;k++)
				{
					
					deltaIH[k][j]=eta*inp_vector[po][k]*deltaj[j]+zeta*deltaIH[k][j];
				//	printf("k is -> %f\n",deltaIH[k][j]);
					WeightIH[k][j]+=deltaIH[k][j];						
				}
			}
			for(i=1;i<=output;i++)
			{
				deltaHO[0][i]=eta*deltak[i]+zeta*deltaHO[0][i];

				for(j=1;j<=hiddenNodes;j++)
				{
					//printf("deltaHO is = %f\n", deltaHO[j][i] );
					deltaHO[j][i]=eta*activate[po][j]*deltak[i]+zeta*deltaHO[j][i];
					WeightHO[j][i]+=deltaHO[j][i];
				}
			}
		}
		if(epo%500==0)
		{
			printf("Epoch = %d  &  Error = %lf\n",epo,error);
		}	
		if(error<=0.004)
		{
			break;
		}
		epo++;
	}
	int o=0;
	int y=0;
	printf("Weight Between Input and Hidden Layer :- \n");
	for(o=1;o<=input;o++)
	{
		for(y=1;y<=NODES_HIDDEN;y++)
		{
			printf("%f\t",WeightIH[o][y]);
		}
		printf("\n");
	}
	printf("Weight Between hidden Layer and Output is :- \n");
	for(o=1;o<=NODES_HIDDEN;o++)
	{
		for(y=1;y<=output;y++)
		{
			printf("%f\t",WeightHO[o][y]);
		}
		printf("\n");
	}
	float MulIH_test[51][NODES_HIDDEN+1],activate_test[51][NODES_HIDDEN+1],MulHO_test[51][output],Output_test[51][output];
	
	i=1;
	float error_test=0.0;
	float sum1=0.0;
	while(i<51)
	{
		for(j=1;j<=NODES_HIDDEN;j++)
		{
			MulIH_test[i][j]=WeightIH[0][j-1];
			for(k=1;k<=input;k++)
			{
				MulIH_test[i][j]+=inp_vector_test[i][k]*WeightIH[k][j-1];
			}
			activate_test[i][j]=1.0/(1.0 + exp(-MulIH_test[i][j]));
		}
		for(j=1;j<=output;j++)
		{
			MulHO_test[i][j]=WeightHO[0][j-1];
			for(k=1;k<=NODES_HIDDEN;k++)
			{
				MulHO_test[i][j]+=activate_test[i][k]*WeightHO[k][j-1];
			}
			Output_test[i][j]=1.0/(1.0 + exp(-MulHO_test[i][j]));
			error_test+=0.5*(target_test[i][j]-Output_test[i][j])*(target_test[i][j]-Output_test[i][j]);
		}
		printf("Error rate is :- %f\n",error_test);
		sum1+=error_test;
		if(error_test<=0.00001)
		{
			break;
		}
		i++;
	}	
	
	float mean=0.0;
	mean=sum1/50;
	printf("\n\n\n\nMean Error is = %f\n",mean);
	return 0;
}