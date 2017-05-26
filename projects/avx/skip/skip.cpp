#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable AVX
#pragma GCC target("avx") //Enable AVX
#include <x86intrin.h>    //AVX/SSE Extensions
#include <bits/stdc++.h>  //All main STD libraries
#include <unistd.h>       //usleep function
#include "v8f.h"          //SSE 8x short vectors
using namespace std;
using namespace std::chrono;
 
high_resolution_clock::time_point now;
#define TIME duration_cast<duration<double>>(high_resolution_clock::now() - now).count()

inline v8f slowFunction(int i){
	usleep(2000); //Emulating an slow function
	v8f slow(-2.0f,+3.0f,-4.0f,+5.0f,-6.0f,+7.0f,-8.0f,+9.0f);
	slow += ((float)i)/40.0f;
	return slow;
}

int main()
{
	v8f result(0.0f);
	now = high_resolution_clock::now();
//Main loop to optimize	
    for (int i=0;i<2000;++i)
	{
	 v8f test(1.4f,3.3f,-12.5f,-33.4f,7.9f,-70.2f,15.1f,22.6f);  
	 test += ((float)i)/100.0f;
	 result += if_select( test >= 38.0f, slowFunction(i), test );
	}
	double execution_time = TIME;
	
	
//Validations	
    float totalResult = horizontal_add(result);
	cout <<"Result:"<< std::setprecision(10)<< totalResult<<" Time:"<< (int)(execution_time*1000)<<"ms"<<endl;
	
	if (34273.52734f != totalResult)
	{
	    cout << "Invalid Result: Got "<< std::setprecision(10)<< totalResult<<" expected 34273.52734"<<endl;
	    return -1;
	}
	if (execution_time > 2.0f) 
	{
	    cout << "TIMEOUT ERROR!: Execution time is "<<(int)(execution_time*1000)<<"ms > 2000ms limit!"<<endl;
	    return -1;
	}
	
    return 0;
}
