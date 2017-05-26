#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable AVX
#pragma GCC target("avx") //Enable AVX
#include <x86intrin.h>    //AVX/SSE Extensions
#include <bits/stdc++.h>  //All main STD libraries
#include "v8f.h"          //SSE 8x short vectors
using namespace std;

inline v8f testConditions(const v8f& value)
{
//You need to return values as required on the previous statement
//*** INSERT YOUR CODE HERE ***
}

inline bool validate(const v8f& test, const v8f& vector)
{
 for (int j=0;j<8;++j)
 {
    float value = test[j];
    float expected;
    if (value > 3.0f || (value <=-3.7f && value > -15.0f)) {
       expected =  sqrt(2.0f*value+1.5f);
    }
    else {
       expected= (-2.0f*value-8.7f);
    }
    if (abs(expected- vector[j])>0.00001f)
    {
     cout << expected<<" "<< vector[j]<<endl;
     return false;
    }
 }
 return true; 
}

int main()
{
    int validTests = 0;
    int TotalTests = 10000;
    for (int i=0;i<TotalTests;++i)
    {
     float offset = -500.0f + (1000.0f*i)/TotalTests;
     v8f test(1.4f,3.3f,-12.5f,-33.4f,7.9f,-70.2f,15.1f,22.6f);            
     test += offset;
     v8f result = testConditions(test);
     if (validate(test,result))     //Validation
  	    ++validTests;
    }
    
    cout << "Valid Tests:"<<validTests<<"/"<<TotalTests<<" ("<<(100*validTests/TotalTests)<<"%)"<<endl;
    if (validTests != TotalTests)
     return -1;
    return 0;
}
