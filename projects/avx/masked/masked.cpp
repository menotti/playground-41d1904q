#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable AVX
#pragma GCC target("avx") //Enable AVX
#include <x86intrin.h>    //AVX/SSE Extensions
#include <bits/stdc++.h>  //All main STD libraries
#include "v8f.h"          //SSE 8x short vectors
using namespace std;


int main()
{
    v8f test(1.4f,3.3f,-12.5f,-33.4f,7.9f,-70.2f,15.1f,22.6f);    
    cout << "Wrapper Tests: Float Vectors" <<endl;    
    cout << "c   :"<<c<<endl;
    cout << "d   :"<<d<<endl;
    cout << "c+d :"<<c+d<<endl;
    cout << "c-d :"<<c-d<<endl;
    cout << "c*d :"<<c*d<<endl; 
    cout << "c/d :"<<c/d<<endl;
    cout << "c>d :"<<(c>d)<<endl; //true is -nan, because it's a mask with all 32 bits set to 1.
    cout << "c==d:"<<(c==d)<<endl;
    cout << "Frandom(1,1348):"<<(Frandom<1,1348>())<<endl;    
    return 0;
}
