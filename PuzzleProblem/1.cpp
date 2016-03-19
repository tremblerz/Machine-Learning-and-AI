#include<bits/stdc++.h>
#include <sys/resource.h>

using namespace std;

int c=0;
map<long long int, int> table;

int goal1[3][3];/*={
	{1,2,3},
	{4,5,6},
	{7,8,0}
};
int goal1[][3]={
	{1,2,3},
	{8,0,4},
	{7,6,5}
};*/

bool hash(int ar[][3]){
	long long int x=0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			x += x*10 + ar[i][j];
		}
	}
	pair<map<long long int , int>::iterator,bool> ret;
	ret = table.insert(pair<long long int,int>(x,c++));
	if( ret.second == false){
		c--;
		return false;
	}
	else
		return true;
}

bool hash(int **ar){
	long long int x=0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			x += x*10 + ar[i][j];
		}
	}
	pair<map<long long int , int>::iterator,bool> ret;
	ret = table.insert(pair<long long int,int>(x,c++));
	if( ret.second == false){
		c--;
		return false;
	}
	else
		return true;
}

bool isequal(int a1[][3],int a2[][3]){
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(!(a1[i][j] == a2[i][j]))
				return false;
	return true;
}


bool dfs(int state[][3]){
	int i,j;
	for( i = 0; i < 3; i++){
		for( j = 0; j < 3; j++){
			if(state[i][j]==0){
				if(i-1 >= 0){
					swap(state[i][j],state[i-1][j]);
					if(hash(state)){
						if(isequal(state,goal1)){
							swap(state[i][j],state[i-1][j]);
							cout<<"\t\t^\n\t\t^\n----------------------------\n";
							for(int i=0;i<3;i++){
								for(int j=0;j<3;j++)
									cout<<state[i][j]<<" ";
								cout<<"\n";
							}
							cout<<"----------------------------\n";
							return true;
						}
						else if (dfs(state) == true){
							swap(state[i][j],state[i-1][j]);
							cout<<"\t\t^\n\t\t^\n----------------------------\n";
							for(int i=0;i<3;i++){
								for(int j=0;j<3;j++)
									cout<<state[i][j]<<" ";
								cout<<endl;
							}
							cout<<"----------------------------\n";
							return true;
						}
					}
					swap(state[i][j],state[i-1][j]);
				}
				if(i+1 <= 2){
					swap(state[i][j],state[i+1][j]);
					if(hash(state)){
						if(isequal(state,goal1)){
							swap(state[i][j],state[i+1][j]);
							cout<<"\t\t^\n\t\t^\n----------------------------\n";
							for(int i=0;i<3;i++){
								for(int j=0;j<3;j++)
									cout<<state[i][j]<<" ";
								cout<<"\n";
							}
							cout<<"----------------------------\n";
							return true;
						}
						else if (dfs(state) == true){
							swap(state[i][j],state[i+1][j]);
							cout<<"\t\t^\n\t\t^\n----------------------------\n";
							for(int i=0;i<3;i++){
								for(int j=0;j<3;j++)
									cout<<state[i][j]<<" ";
								cout<<endl;
							}
							cout<<"----------------------------\n";
							return true;
						}
					}
					swap(state[i][j],state[i+1][j]);
				}
				if(j-1 >= 0){
					swap(state[i][j],state[i][j-1]);
					if(hash(state)){
						if(isequal(state,goal1)){
							swap(state[i][j],state[i][j-1]);
							cout<<"\t\t^\n\t\t^\n----------------------------\n";
							for(int i=0;i<3;i++){
								for(int j=0;j<3;j++)
									cout<<state[i][j]<<" ";
								cout<<"\n";
							}
							cout<<"----------------------------\n";
							return true;
						}
						else if (dfs(state) == true){
							swap(state[i][j],state[i][j-1]);
							cout<<"\t\t^\n\t\t^\n----------------------------\n";
							for(int i=0;i<3;i++){
								for(int j=0;j<3;j++)
									cout<<state[i][j]<<" ";
								cout<<endl;
							}
							cout<<"----------------------------\n";
							return true;
						}
					}
					swap(state[i][j],state[i][j-1]);
				}
				if(j+1 <= 2){
					swap(state[i][j],state[i][j+1]);
					if(hash(state)){
						if(isequal(state,goal1)){
							swap(state[i][j],state[i][j+1]);
							cout<<"\t\t^\n\t\t^\n----------------------------\n";
							for(int i=0;i<3;i++){
								for(int j=0;j<3;j++)
									cout<<state[i][j]<<" ";
								cout<<"\n";
							}
							cout<<"----------------------------\n";
							return true;
						}
						else if (dfs(state) == true){
							swap(state[i][j],state[i][j+1]);
							cout<<"\t\t^\n\t\t^\n----------------------------\n";
							for(int i=0;i<3;i++){
								for(int j=0;j<3;j++)
									cout<<state[i][j]<<" ";
								cout<<"\n";
							}
							cout<<"----------------------------\n";
							return true;
						}
					}
					swap(state[i][j],state[i][j+1]);
				}
				return false;
			}
		}
	}
}

bool bfs(int orig[][3]){
	queue<int ** > l;
	hash(orig);
	int state[3][3],i,j;
	for( i = 0; i < 3; i++)
		for( j = 0; j < 3; j++)
			state[i][j] = orig[i][j];
	while(1){// (!isequal(state , goal1)) || (!isequal(state , goal1)) ){
		for( i = 0; i < 3; i++){
			for( j = 0; j < 3; j++){
				if( state[i][j] == 0 ){
/*
					for(int a=0;a<3;a++){
						for(int b=0;b<3;b++)
							cout<<state[a][b]<<" ";
						cout<<endl;
					}
					int kk;
					cin>>kk;
*/
					if( i - 1 >= 0 ){
						int** ary = new int*[3];
						for(int i1 = 0; i1 < 3; i1++)
   							ary[i1] = new int[3];
						for(int i1 = 0; i1 < 3; i1++)
							for(int j1 = 0; j1 < 3; j1++)
								ary[i1][j1] = state[i1][j1];
						swap(ary[i-1][j] , ary[i][j]);
	//					cout<<"cool\n";
						if(hash(ary))
							l.push(ary);
//						cout<<"cool\n";
					}
					if( i + 1 <= 2 ){
                                                int** ary = new int*[3];
                                                for(int i1 = 0; i1 < 3; i1++)
                                                        ary[i1] = new int[3];
                                                for(int i1 = 0; i1 < 3; i1++)
                                                        for(int j1 = 0; j1 < 3; j1++)
                                                                ary[i1][j1] = state[i1][j1];
						swap(ary[i+1][j] , ary[i][j]);
//						cout<<"cool\n";
						if(hash(ary))
	                                                l.push(ary);
                                        }
					if( j - 1 >= 0 ){
                                                int** ary = new int*[3];
                                                for(int i1 = 0; i1 < 3; i1++)
                                                        ary[i1] = new int[3];
                                                for(int i1 = 0; i1 < 3; i1++)
                                                        for(int j1 = 0; j1 < 3; j1++)
                                                                ary[i1][j1] = state[i1][j1];
						swap(ary[i][j-1] , ary[i][j]);
						if(hash(ary))
                                                	l.push(ary);
                                        }
					if( j + 1 <= 2 ){
                                                int** ary = new int*[3];
                                                for(int i1 = 0; i1 < 3; i1++)
                                                        ary[i1] = new int[3];
                                                for(int i1 = 0; i1 < 3; i1++)
                                                        for(int j1 = 0; j1 < 3; j1++)
                                                                ary[i1][j1] = state[i1][j1];
						swap(ary[i][j+1] , ary[i][j]);
						if(hash(ary))
                                                	l.push(ary);
                                        }
					break;
				}
			}
		}
//		cout<<"cool\n";
		if( l.empty() )
			return false;
		else{
			for(int i = 0; i < 3; i++)
				for( int j = 0; j < 3; j++)
					state[i][j] = l.front()[i][j];
			l.pop();
		}
		if(isequal(state,goal1))
			return true;
	}
	return true;
}
void printUsage(){
	cout<<"\tUsage--\nFor BFS -->\n./a.out bfs\nFor DFS -->\n./a.out dfs\n";
}
int main(int argc, char * argv[]){
	int orig[3][3];
	double execTime;
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

	if(argc>1){
		cout<<"Enter initial state\n";
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				cin>>orig[i][j];
		
		cout<<"Enter final state\n";
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				cin>>goal1[i][j];

		if ( strcmp( argv[1] , "dfs" ) == 0 ){
			clock_t tStart = clock();
			if(dfs(orig) == false)
				cout<<"Path not found\n";
			else
				cout<<"Path found\n";
			execTime = (double)(clock() - tStart)/CLOCKS_PER_SEC;
			cout<<"Time taken by DFS Algorithm = "<<execTime<<" seconds"<<endl;
			cout<<"Size of closed list = "<<table.size()<<endl;
		}
		else if ( strcmp( argv[1] , "bfs" ) == 0 ){
			clock_t tStart = clock();
			if(bfs(orig) == false)
				cout<<"Path not found\n";
			else
				cout<<"Path found\n";
			execTime = (double)(clock() - tStart)/CLOCKS_PER_SEC;
			cout<<"Time taken by BFS Algorithm = "<<execTime<<" seconds"<<endl;
			cout<<"Size of closed list = "<<table.size()<<endl;
		}
		else{
			printUsage();
			cout<<"Invalid parameters, please adhere to the usage\n";
		}
	}
	else{
		printUsage();
		cout<<"Invalid parameters, please adhere to the usage\n";
	}
	/*int x=1;
	while(x <= 10000){	
		clock_t tStart = clock();
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				cin>>orig[i][j];
		
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				cin>>goal1[i][j];
		dfs(orig);
		execTime = (double)(clock() - tStart)/CLOCKS_PER_SEC;
		cout<<execTime<<endl;
		x++;
	}*/
return 0;
}
