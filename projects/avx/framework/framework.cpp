#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable AVX
#pragma GCC target("avx") //Enable AVX
#include <x86intrin.h>    //SSE Extensions
#include <bits/stdc++.h>  //All main STD libraries
#include "v8i.h"          //AVX 8x float vectors
#include "v8f.h"          //SSE 8x short vectors
#include "vconvert.h"     //Vector short <-> float conversions
#include "vrandom.h"      //Pseudo-random numbers
using namespace std;
 
int main()
{
    v8i a(250);
    v8i b(1,-3,-4,6,20,250,-4003,4);
    cout << "Wrapper Tests: Integer Vectors" <<endl;
    cout << "a   :"<<a<<endl;
    cout << "b   :"<<b<<endl;
    cout << "a+b :"<<a+b<<endl;
    cout << "a-b :"<<a-b<<endl;
    cout << "a*b :"<<a*b<<endl; //Overflow!!!!! Remember that v8i is only 16-bit signed
    cout << "a/b :"<<a/b<<endl;
    cout << "a>b :"<<(a>b)<<endl; //true is -1, because it's a mask with all 16 bits set to 1.
    cout << "a==b:"<<(a==b)<<endl;
    cout << "Irandom(1,1348):"<<(Irandom<1,1348>())<<endl;    
    cout <<endl;

    v8f c(15.1f);
    v8f d(1.4f,3.3f,-12.5f,-33.4f,7.9f,-70.2f,15.1f,22.6f);    
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
    
	cout << "CG> message -channel \"exercise results\" ALL TEST COMPLETED" << endl;
    return 0;
}
