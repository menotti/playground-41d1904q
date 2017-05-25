#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable AVX
#pragma GCC target("avx")  //Enable AVX
#include <x86intrin.h> //SSE Extensions
#include <bits/stdc++.h> //All main STD libraries
#include "v8i.h"
#include "v8f.h"
//#include "helpers.h"
using namespace std;
 
int main()
{
    v8i a(4);
    v8f b(15.1f);
    v8f c(1.4f,3.3f,-12.5f,-33.4f,7.9f,-70.2f,191.3f,22.6f);
	cout << "CG> message -channel \"exercise results\" WORK IN PROGRESS: "<< (a*a-2*a)<<" "<<(b/(2*b)-b)<<"\n "<<b+c << endl;
    return 0;
}
