#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>


#define TRAININGFILENAME "pp_tra.dat"
#define TESTINGFILENAME "pp_tes.dat"
#define FOLDS 3
#define TRAIN_DATA 6670
#define M 20
#define FEATURES 192
#define TEST_DATA 3333

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
//        cout<<"Row number = "<<row<<"and column is "<<col<<endl;
//        cout<<col<<endl;
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

int main(){
  int x;
  cout<<"Flag 1"<<endl;

//  int input[TRAIN_DATA][FEATURES+1];
//  readData( TRAININGFILENAME , input );
  int test_input[TEST_DATA][FEATURES+1],a,error[TRAIN_DATA][M+1],input[TRAIN_DATA][FEATURES+1],min_index,result_class,original_class,partition_size = TRAIN_DATA/FOLDS,freq[10],m,pos=-1,final_k;
  float finalError[FOLDS][M+1],min=1000.0;

  Dist distance[TRAIN_DATA];
  reset(freq,m,distance);

  readData( TRAININGFILENAME , input );
  randomizeData( input , TRAIN_DATA );
 // readData( TESTINGFILENAME , test_input );

/*
  for( int i=0; i<TEST_DATA; i++ ){
    for( int j=0; j<FEATURES; j++ ){
      cout<<test_input[i][j]<<" ";
    }
    cout<<test_input[i][FEATURES];
    cout<<endl;
  }
 // cin>>x;
*/
  for( int i=0; i<FOLDS; i++ ){
//    cout<<"Starting of cross validation is "<<i*partition_size<<" and ending of cross validation set is "<<(1+i)*partition_size<<endl;
    for( int j=i*partition_size; j<(1+i)*partition_size; j++ ){
      for( int l=0; l<TRAIN_DATA; l++ ){
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
          error[j][k] = 1;
//          cout<<"For k = "<<k<<" , Result class is "<< result_class <<" Original class is "<<original_class<<endl;
        }
        else
          error[j][k] = 0;
        //cin>>a;
      }
      reset(freq,m,distance);
    }
  }
//  cout<<"Flag1"<<endl;
/*  
    for( int i=0; i<FOLDS; i++ ){
    //int sum=0;
    for( int k=1; k<=M; k++ ){
      int sum=0;
      for( int j=i*partition_size; j<(1+i)*partition_size; j++ )
        sum+=error[j][k];
//      cout<<sum<<endl;
      finalError[i][k]=(float)sum/(float)partition_size;
    }
  }


  for( int k=1; k<=M; k++ ){
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
  final_k = pos;
  cout<<"Optimal k is "<<final_k<<endl;


  for( int j=0; j<TEST_DATA; j++ ){
    for( int l=0; l<TRAIN_DATA; l++ ){
      distance[m].index=l;
      distance[m++].distance=findDistance(input[l],test_input[j]);
    }
    sort(distance , distance+m , compare);
    for( int k=0; k<final_k; k++ )
        freq[input[distance[k].index][FEATURES]]++;
    result_class = std::distance( freq , max_element( freq , freq + 10 ) );
    original_class = test_input[j][FEATURES];
    if( result_class != original_class )
      cout<<"Result class is "<<result_class<<" and original class is "<<original_class<<endl;
    else
      cout<<"Pass"<<endl;
    reset(freq,m,distance);
  }
*/
  return 0;
}
