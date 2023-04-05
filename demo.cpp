#include <stdio.h>   // scanf
#include <iostream>  // cout , endl
#include <fstream>   // open, is_open, close, write, ignore
#include <string>    // string, find_last_of, substr, clear
#include <vector>    // vector, push_back
#include <cstdlib>   // atoi, system
#include <memory.h>
#include <algorithm>

using namespace std;

struct ItemType{
	int weight = 0 ;
    int value = 0 ;
};

vector<int> cost, Pweight;      
const int N = 100, W = 100000;
int c[N + 1][W + 1];
int mark[N+1][W+1] ;
vector<int> order ;
template <class KeyType>
KeyType **Matrix( int nr, int nc )
{
	KeyType **f;
	int i;

	f = (KeyType **) malloc( nr * sizeof( KeyType * ) );
	if ( !f ) return NULL;
	for ( i = 0 ; i < nr ; i++ )
	{
		f[i] = (KeyType *) malloc( nc * sizeof( KeyType ) );
		if ( !f[i] ) return NULL;
	}
	return f;
}

template <class KeyType>
void FreeMatrix( KeyType **f, int nr, int nc )
{
	int i;
	for ( i = 0 ; i < nr ; i++ )
		free( (KeyType *) f[i] );
	free( (KeyType *) f );
}



void knapsack(int count, int weight, vector<ItemType> list)
{
	
    //int c[N + 1][W + 1];
	//c = Matrix<int> (N + 1, W + 1);
	//mark = Matrix<int> (N+1, W + 1);
	memset(c, 0, sizeof(c));
    memset(mark, 0, sizeof(mark));

    for (int i = 0 ; i < count ; i++){      // 窮舉每種物品
//        int Pweight = list[i].weight;
//        int cost = list[i].value;
        for (int j = 0 ; j <= weight ; j++){  // 窮舉每種重量
            if (j - Pweight[i] < 0)
                // can't put in then not to put
                c[i+1][j] = c[i][j];
            else
                // can put in then put it to full
                c[i+1][j] = max( c[i][j], c[i][j-Pweight[i]] + cost[i] );
        } 
    } 

    cout << "Total Value : " << c[count][weight] << endl;
    cout << "Items" << endl ;

    for (int i = count-1, j = weight ; i >= 0; --i) {
//        int Pweight = list[i].weight;
//        int cost = list[i].value;
        if (j - Pweight[i] >= 0 && c[i+1][j] == c[i][j - Pweight[i]] + cost[i]) {
            order.push_back(i+1);
            j = j - Pweight[i];
        } // if
    } //for

}

int main(){
	int weight = 0 ;
    int count = 0 ; // how many of product 
    int index = 0 ;
    int oldweight = 0 ;
    vector<ItemType> list ;
    cin >> weight ;
    while(weight != -1 ){
	  ItemType Temp ;
	  index++;
    while(weight!=0){
      oldweight = weight ;
      cin >> count ;
      for(int i = 0; i < count ; i++){
	    cin >> Temp.weight;
        Pweight.push_back(Temp.weight);
        cin >> Temp.value ;
        cost.push_back(Temp.value);
      }  // for

      cin  >> weight ;
      cout << "Case#" << index << endl ;
	  knapsack(count,oldweight, list);
      sort(order.begin(),order.end());
      for(int i = 0 ; i < order.size() ; i++ )
	    cout << order[i] << endl ;
    } // while
    cout << endl ;
    cin >> weight ;
    order.clear();
} // while
    
}
