#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zero-upper") //Enable AVX
#pragma GCC target("avx")  //Enable AVX
#include <x86intrin.h> //SSE Extensions
#include <bits/stdc++.h> //All main STD libraries

const int N = 64000000; //Number of tests
const int V = N/8;      //Vectorized size

//Lineal function, 
float lineal[N];
__attribute__((optimize("no-tree-vectorize"))) //Force disable auto-vectorization
inline void normal_sqrt()
{
    for (int i = 0; i < N; ++i)
        lineal[i] = sqrtf(lineal[i]);
}

//Exercise 1: Create a vectorized version of the "linear" function.
//Please note the following:
// "vectorized" array is size V=N/8, because each __m256 variable holds 8 floats.
// sqrtf(const float& f) vectorized function is: _mm256_sqrt_ps(const __m256& v)
__m256 __attribute__((aligned(32))) vectorized[V]; //Vectorized array
inline void avx_sqrt()
{
  //****** Add AVX code here*******
}
 
 
using namespace std;
using namespace std::chrono;
 
high_resolution_clock::time_point now = high_resolution_clock::now();
#define TIME duration_cast<duration<double>>(high_resolution_clock::now() - now).count()

int main()
{
//Data initialization	
    for (int i = 0; i < N; ++i) { lineal[i] = ((float)i)+ 0.1335f; }
    for (int i = 0; i < V; ++i) {
		for (int v=0;v<8;++v)
		 {  vectorized[i][v] = ((float)(i*8+v))+ 0.1335f; }
	}
 
 //Normal sqrt benchmarking. 20*64 Million Sqrts
    now = high_resolution_clock::now();
    for (int i = 0; i < 20; ++i)
    normal_sqrt();
    double linear_time = TIME;
    cerr << "Normal sqrtf: "<< linear_time << endl;
 
 //AVX vectorized sqrt benchmarking. 20*8*8 Million Sqrts
    now = high_resolution_clock::now();
    for (int i = 0; i < 20; ++i)
    avx_sqrt();
    double avx_time = TIME;
    cerr << "AVX sqrtf : "<<avx_time << endl;
	
	//Check values
	for (int i = 0; i < V; ++i) {
		for (int v=0;v<8;++v)
		 { 
  	       if (abs(lineal[i*8+v] - vectorized[i][v]) > 0.00001f)
		   {
	         cerr << "ERROR: AVX sqrt is not the same as linear!!!";
	         cerr << lineal[i*8+v]<<" <-> "<<vectorized[i][v]<<endl;
			 return -1;
		   }
		 }
	}
	cout << "CG> message -channel \"exercise results\" Linear to AVX improvement : "<< (linear_time/avx_time*100)<<"%" << endl;
 
    return 0;
}
