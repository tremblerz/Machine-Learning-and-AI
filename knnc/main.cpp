#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<bits/stdc++.h>
#include<sys/resource.h>


#define TRAININGFILENAME "pp_tra.dat"
#define TESTINGFILENAME "pp_tes.dat"
#define FOLDS 3
#define TRAIN_DATA 6670
#define M 20
#define FEATURES 192
#define TEST_DATA 3333

using namespace std;

int input[TRAIN_DATA][FEATURES+1];
int condensed[TRAIN_DATA][FEATURES+1];

struct Dist{
  float distance;
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

void readData( char *filename , int input[][FEATURES+1] ){
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
      if ( c == 13 ){
        row++;
        col=0;
      }
      else{
        col++;
      }
    }
    else{
      break;
    }
  }
  fclose(fp);
}


void randomizeData( int input[][FEATURES+1] , int limit ){
  srand(time(NULL));
  int i,k;
  for( i=limit-1; i>=0; i-- ){
    int j = rand() % (i+1);
    for( k=0; k<=FEATURES; k++ ){
      swap( input[i][k] , input[j][k] );
    }
  }
}

void copy( int *ar1 , int *ar2 ){
  for( int i=0; i<=FEATURES; i++ )
    ar1[i] = ar2[i];
}

int calcDistance( int point1 , int point2 ){
  return ( point1 - point2 ) * ( point1 - point2 );
}

long int findDistance( int *ar1 , int *ar2 ){
  long int dist=0;
  for( int i=0; i<=FEATURES-1; i++ )
    dist += calcDistance( ar1[i] , ar2[i] );
  return dist;
}

void reset( int freq[] , int &m , Dist distance[] ){
  for( int i=0; i<10; i++)
    freq[i]=0;
  m=0;
  for( int i=0; i<TRAIN_DATA; i++ )
    distance[i].index = distance[i].distance = 0;
}

void reset( float freq1[] , int &m , Dist distance[] ){
  for( int i=0; i<10; i++)
    freq1[i]=0;
  m=0;
  for( int i=0; i<TRAIN_DATA; i++ )
    distance[i].index = distance[i].distance = 0;
}

int train( int partition_size , Dist distance[] , int input[][FEATURES+1] , int freq[] , int error[][M+1] , float finalError[][M+1] , int size){
  int m=0,x=0;

  for( int i=0; i<FOLDS; i++ ){
    for( int j=i*partition_size; j<(1+i)*partition_size; j++ ){
      for( int l=0; l<size; l++ ){
        if( !( l>=i*partition_size && l<(1+i)*partition_size) ){
          distance[m].index=l;
          distance[m++].distance=findDistance(input[l],input[j]);
        }
      }
      sort(distance , distance+m , compare);
      for( int k=1; k<=M; k++ ){
        freq[input[distance[k].index][FEATURES]]++;
        int result_class = std::distance( freq , max_element( freq , freq + 10 ) );
        int original_class = input[j][FEATURES];
        if( result_class != original_class ){
          error[j][k] = 1;
        }
        else
          error[j][k] = 0;
      }
      reset(freq,m,distance);
    }
  }

  for( int i=0; i<FOLDS; i++ ){
    for( int k=1; k<=M; k++ ){
      int sum=0;
      for( int j=i*partition_size; j<(1+i)*partition_size; j++ ){
        sum+=error[j][k];
      }
      finalError[i][k]=(float)sum/(float)partition_size;
    }
  }

  int pos=-1;
  float min=1000.0;
  for( int k=1; k<=M; k++ ){
    float sum=0;
    for( int i=0; i<FOLDS; i++ ){
      sum += finalError[i][k];
    }
    finalError[0][k] = (float)sum/(float)FOLDS;
    if ( min > finalError[0][k] ){
      min = finalError[0][k];
      pos = k;
    }
  }
  return pos;
}

int test( int test_input[][FEATURES + 1] , Dist distance[] , int input[][FEATURES+1] , int freq[] , int test_data_size , int final_k , int size){
  int test_error = 0 , m = 0;
  for( int j=0; j<test_data_size; j++ ){
    for( int l=0; l<size; l++ ){
      distance[m].index=l;
      distance[m++].distance=findDistance(input[l],test_input[j]);
    }
    sort(distance , distance+m , compare);
    for( int k=0; k<final_k; k++ )
        freq[input[distance[k].index][FEATURES]]++;
    int result_class = std::distance( freq , max_element( freq , freq + 10 ) );
    int original_class = test_input[j][FEATURES];
    if( result_class != original_class ){
      test_error++ ;
    }
    reset(freq,m,distance);
  }
  return test_error;
}

bool insertionRequired( int condensed[][ FEATURES+1 ] , int example[] , Dist distance[] , int final_k , int freq[] ){
    int m=0; 
    for( int l=0; l<TRAIN_DATA; l++ ){
      distance[m].index=l;
      distance[m++].distance=findDistance( condensed[l] , example );
    }
    sort(distance , distance+m , compare);
    for( int k=0; k<final_k; k++ )
        freq[input[distance[k].index][FEATURES]]++;
    int result_class = std::distance( freq , max_element( freq , freq + 10 ) );
    int original_class = example[FEATURES];
    if( result_class != original_class ){
      return true;
    }
    return false;
}

int main(){


//---------------------------------------INCREASING STACK SIZE------------------------------------------------

/*
        const rlim_t kStackSize = 48 * 1024 * 1024;   // min stack size = 16 MB
        struct rlimit rl;
        int result;

        result = getrlimit(RLIMIT_STACK, &rl);
        if (result == 0)
        {
                if (rl.rlim_cur < kStackSize)
                {
                        rl.rlim_cur = kStackSize;
                        result = setrlimit(RLIMIT_STACK, &rl);
                        if (result != 0)
                        {
                                fprintf(stderr, "setrlimit returned result = %d\n", result);
                        }
                }
        }

*/

  int x;
  cout<<"Started program"<<endl<<"Finding Optimal K from the TRAINING dataset"<<endl;


  int test_input[TEST_DATA][FEATURES+1],a,error[TRAIN_DATA][M+1],min_index,result_class,original_class,partition_size = TRAIN_DATA/FOLDS,freq[10],m,pos=-1,final_k,test_error;
  float finalError[FOLDS][M+1],min=1000.0,freq1[10];

  Dist distance[TRAIN_DATA],weight[M+1];
  reset(freq,m,distance);

  readData( TRAININGFILENAME , input );
  randomizeData( input , TRAIN_DATA );


  final_k = train( partition_size , distance , input , freq , error , finalError , TRAIN_DATA );
  cout<<"Optimal k is "<<final_k<<endl<<"Running on TEST dataset"<<endl;

  readData( TESTINGFILENAME , test_input );
  test_error = test( test_input , distance , input , freq , TEST_DATA , final_k , TRAIN_DATA);

  cout<<"Error with simple KNNC is "<<((float)test_error/(float)TEST_DATA)*100.0<<"%"<<endl;


  cout<<"Running modified KNNC now"<<endl;
  test_error = 0;

  for( int i=0; i<10; i++ )
    freq1[i]=0;

  for( int j=0; j<TEST_DATA; j++){

    for( int i=0; i<TRAIN_DATA; i++ ){
      distance[i].index = i;
      distance[i].distance = findDistance( test_input[j] , input[i] );
    }
    sort( distance , distance + TRAIN_DATA , compare );

    for ( int i=0; i<final_k; i++ ){
      weight[i].index = distance[i].index;
      if( distance[final_k-1].distance != distance[0].distance )
        weight[i].distance = (float)( distance[final_k-1].distance - distance[i].distance ) / (float)( distance[final_k-1].distance - distance[0].distance );
      else
        weight[i].distance = 1;
//      cout<<"Test set's element is  "<<j<<" and weight is "<<weight[i].distance<<"and class is "<<input[weight[i].index][FEATURES]<<endl;
    }
/*
    for( int i=0; i<final_k; i++ ){
      distance[i].index = weight[i].index;
      distance[i].distance = weight[i].distance * distance[weight[i].index].distance;
    }
    sort( distance , distance + final_k , compare );
*/
    //for( int i=0; i<final_k; i++ ){
  //    freq[input[distance[i].index][FEATURES]] ++;
      for( int i=0; i<final_k; i++ ){
        freq1[input[weight[i].index][FEATURES]] += weight[i].distance;
        //cout<<"weight is "<<freq1[input[weight[i].index][FEATURES]]<<endl;
      }
    //}
    
      /*for( int i=0; i<10; i++ ){
        cout<<"votes for "<<i<<" is "<<freq1[i]<<endl;
      }*/
//    result_class = std::distance( freq1 , max_element( freq1 , freq1 + 10 ) );
    float max = 0.0;
    int pos=-1;
    for( int i=0; i<10; i++ ){
      if( freq1[i] > max ){
        max=freq1[i];
        pos=i;
      }
    }
    result_class = pos;
    original_class = test_input[j][FEATURES];
    if( result_class != original_class ){
      test_error++;
      //cout<<"result class is "<<result_class<<" and "<<original_class<<endl;
    }
    //cin>>x;    
    reset( freq1 , m , distance );
  }

  cout<<"Error with modified KNNC is "<<((float)test_error/TEST_DATA)*100.0<<"%"<<endl;




  
  int size = 1;
  copy(condensed[size-1] , input[1]);

  cout<<"Generating condensed set"<<endl;

  for( int i=0; i<TRAIN_DATA; i++ ){
    if( insertionRequired( condensed , input[i] , distance , 1 , freq ) == true ){
      size++;
      copy( condensed[size-1] , input[i] );
    }
  }

  cout<<"Condensed set genreated , reduction in the data set is "<<((float)(TRAIN_DATA - size)/(float)(TRAIN_DATA)) * 100<<"%"<<endl;

  partition_size = (size+1)/FOLDS;

  final_k = train( partition_size , distance , condensed , freq , error , finalError , size );
  cout<<"Optimal K for condensed training set is "<<final_k<<endl;
  //final_k = 1;

  test_error = test( test_input , distance , condensed , freq ,  TEST_DATA , final_k , size );
  cout<<"Error with condensed NNC is "<<((float)test_error/TEST_DATA)*100.0<<"%"<<endl;

  return 0;
}
