#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable AVX
#pragma GCC target("avx") //Enable AVX
#include <x86intrin.h>    //AVX/SSE Extensions
#include <bits/stdc++.h>  //All main STD libraries
#include "v8f.h"          //SSE 8x short vectors
using namespace std;

int validateResult(const int& turn,const float& bestScore)
{
 cout << "Turn:"<<turn<<"  bestScore:"<< std::setprecision(10)<<bestScore<<endl;
 if (turn != 133)
 {
     cout << "ERROR, Expected turn exit at 133 != "<<turn<<endl;
     return -1;
 }
 if (bestScore != 1707.318481f)
 {
     cout << "ERROR, Expected a bestScore of 1707.318481f != "<< std::setprecision(10)<<bestScore<<endl;
     return -1;
 }
 return 0;
}

int main()
{
    int turn = 0;
    v8f Scores(1.0f,3.0f,7.0f,13.4f,22.7f,0.01f,4.556f,9.7f); //Initial load
    for (turn =0; turn < 200; ++turn)
    {
        Scores += ((float)(turn)/15.0f);
        if ( turn == 40)  { Scores *= Scores/15.0f+2.0f;}
        if ( turn == 70)  { Scores += if_select(Scores < 430.0f, 850.0f, 120.0f );  }
        //EXERCISE: BREAK THE LOOP ONCE YOU REACH MORE THAN 1700 POINTS
    }
    cout << "Scores: "<<Scores<<endl;    
    float bestScore = 0.0f;
    //TODO:LOAD THE bestScore
	
    return validateResult(turn,bestScore);
}
