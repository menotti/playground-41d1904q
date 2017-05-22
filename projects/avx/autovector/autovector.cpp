#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zero-upper") //Enable AVX
#pragma GCC target("avx")  //Enable AVX
#include <x86intrin.h> //SSE Extensions
#include <bits/stdc++.h> //All main STD libraries

using namespace std;
using namespace std::chrono;

int main()
{
	const int N = 200000; //Array Size
	float a[N],b[N],c[N],result[N];
    auto now = high_resolution_clock::now();
    for (int i = 0; i < N; ++i)  //Data initialization	
	{ 
      a[i] =       ((float)i)+ 0.1335f; 
	  b[i] = 1.50f*((float)i)+ 0.9383f; 
	  c[i] = 0.33f*((float)i)+ 0.1172f; 
    }    
   for (int i = 0; i < 8000; ++i) //8000 tests of the array size
	 for (int j = 0; j < N; ++j)
	 {
	  result[j] = a[j]+b[j]-c[j]+3*(float)i;
	 }
	auto end_time = duration_cast<duration<double>>(high_resolution_clock::now() - now).count();
    cerr << "Time used: "<< end_time << endl;
    return 0;
}
