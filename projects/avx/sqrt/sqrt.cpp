#pragma GCC optimize("Ofast","unroll-loops","omit-frame-pointer") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zero-upper") //Enable AVX
#pragma GCC target("avx")  //Enable AVX
#include <x86intrin.h> //SSE Extensions
#include <bits/stdc++.h> //All main STD libraries
using namespace std;
using namespace std::chrono;
 
high_resolution_clock::time_point now = high_resolution_clock::now();
#define TIME duration_cast<duration<double>>(high_resolution_clock::now() - now).count()

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

//Exercise 1: Create a vectorized version of "linear" function.
//Please note the following:
// "vectorized" array is size V=N/8, because each __m256 variable holds 8 floats.
// sqrtf(const float& f) vectorized function is: _mm256_sqrt_ps(const __m256& v)
__m256 __attribute__((aligned(32))) vectorized[V]; //Vectorized array
inline void avx_sqrt()
{
    for (int i = 0; i < V; ++i)
        vectorized[i] = _mm256_sqrt_ps(vectorized[i]);
}
 
int main()
{
//Data initialization	
    for (int i = 0; i < N; ++i) { lineal[i] = ((float)i)+ 0.1335f; }
    for (int i = 0; i < V; ++i) {
		for (int v=0;v<8;++v)
		 {  vectorized[i][v] = ((float)(i*8+v))+ 0.1335f; }
	}
 
 //Normal sqrt benchmarking. 10*64 Million Sqrts
    now = high_resolution_clock::now();
    for (int i = 0; i < 10; ++i)
    normal_sqrt();
    cerr << "Normal sqrtf: "<< TIME << endl;
 
 //AVX vectorized sqrt benchmarking. 10*8*8 Million Sqrts
    now = high_resolution_clock::now();
    for (int i = 0; i < 10; ++i)
    avx_sqrt();
    cerr << "AVX sqrtf : "<<TIME << endl;
 
    return 0;
}