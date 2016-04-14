#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>


#define TRAININGFILENAME "pp_tes.dat"
#define TESTINGFILENAME "pp_tra.dat"
#define FOLDS 3
#define TOTAL_DATA 3333
#define M 20
#define FEATURES 192

using namespace std;

struct Dist{
  long int distance;
  int index;
};

void swap( int &a , int &b){
  int temp = a;
  a = b;
  b = temp;
}

bool compare( const Dist &lhs , const Dist &rhs ){
  return lhs.distance < rhs.distance;
}

void readData( char *filename , int input[][193] ){
  FILE *fp = fopen( filename , "r" );
  int i = 0 , j , row=0 , col=0;
  float data;
  char c  , str[20];
  if( fp == NULL ){
    printf("Can't open the file\n");
    return;
  }

  while( true ){
    if ( EOF != fscanf( fp, "%d%c", &input[row][col], &c) ){
      if ( c == '\n' ){
        row++;
        col=0;
      }
      else
        col++;
    }
    else
      break;
  }
}


void randomizeData( int input[][193] , int limit ){
  srand(time(NULL));
  int i,k;
  for( i=limit-1; i>=0; i-- ){
    int j = rand() % (i+1);
    for( k=0; k<193; k++ ){
      swap( input[i][k] , input[j][k] );
    }
  }
}

int calcDistance( int point1 , int point2 ){
  return ( point1 - point2 ) * ( point1 - point2 );
}

long int findDistance( int *ar1 , int *ar2 ){
  long int dist=0;
  for( int i=0; i<192; i++ )
    dist += calcDistance( ar1[i] , ar2[i] );
  return dist;
}

void reset( int freq[] , int &m , Dist distance[] ){
  for( int i=0; i<10; i++)
    freq[i]=0;
  m=0;
  for( int i=0; i<TOTAL_DATA; i++ )
    distance[i].index = distance[i].distance = 0;
}

int main(){
//  int a,error[TOTAL_DATA][M],
  int a,input[TOTAL_DATA][FEATURES + 1],min_index,result_class,original_class,partition_size = TOTAL_DATA/FOLDS,freq[10],m;
//  float finalError[FOLDS][FEATURES+1];
  Dist distance[TOTAL_DATA];
  reset(freq,m,distance);

  readData( TRAININGFILENAME , input );
  randomizeData( input , TOTAL_DATA+1 );
//  for( int i=0; i<3333; i++)
//    cout<<input[i][192]<<endl;
  for( int i=0; i<FOLDS; i++ ){
//    cout<<"Starting of cross validation is "<<i*partition_size<<" and ending of cross validation set is "<<(1+i)*partition_size<<endl;
    for( int j=i*partition_size; j<(1+i)*partition_size; j++ ){
      for( int l=0; l<TOTAL_DATA; l++ ){
        if( !( l>=i*partition_size && l<(1+i)*partition_size) ){
          distance[m].index=l;
          distance[m++].distance=findDistance(input[l],input[j]);
        }
      }
      sort(distance , distance+m , compare);
      for( int k=1; k<=M; k++ ){
        //cout<<"Expected class is "<<input[distance[k].index][FEATURES]<<endl;
        freq[input[distance[k].index][FEATURES]]++;
        result_class = std::distance( freq , max_element( freq , freq + 10 ) );
        original_class = input[j][FEATURES];
        if( result_class != original_class ){
  //        error[j][k] = 1;
//          cout<<"For k = "<<k<<" , Result class is "<< result_class <<" Original class is "<<original_class<<endl;
        }
       // else
        //  error[j][k] = 0;
        //cin>>a;
      }
      reset(freq,m,distance);
    }
  }
/*
  for( int i=0; i<FOLDS; i++ ){
    //int sum=0;
    for( int k=1; k<M; k++ ){
      int sum=0;
      for( int j=i*partition_size; j<(1+i)*partition_size; j++ )
        sum+=error[j][k];
//      cout<<sum<<endl;
      finalError[i][k]=(float)sum/(float)partition_size;
    }
  }
*/
  float min=100000.0;
  int pos=-1;
/*

  for( int k=1; k<M; k++ ){
    float sum=0;
    for( int i=0; i<FOLDS; i++ ){
//      cout<<finalError[i][k]<<endl;
      sum += finalError[i][k];
    }
//    cout<<sum<<endl;
    finalError[0][k] = (float)sum/(float)FOLDS;
//    cout<<finalError[0][k]<<endl;
    if ( min > finalError[0][k] ){
//      cout<<finalError[0][k]<<endl;
      min = finalError[0][k];
      pos = k;
    }
  }

 */ 
  cout<<"Optimal k is "<<pos<<endl;

  
//  for( int k=0; k<3333; k++ ){
//    distance[k] = findDistance( input[k] , input[3333] );
//  }

//  min_index = std::distance( distance , min_element( distance , distance + 3333 ) );
//  cout<<"Min-index is "<<min_index<<endl;
//  cout<<"Expected output is "<<input[min_index][192]<<" and original output is "<<input[3333][192]<<endl;
  return 0;
}
