#include <iostream>
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

using namespace tbb;

struct Average{
	float * input;
	float * output;
	void operator()(const blocked_range<int> & range) const
	{
		for(int i = 0; i < range.begin(); ++i)
		{
			output[i] = (input[i-1]+input[1]+input[i+1])*(1/3.0f);
		}
	}
};

void ParallelAverage(float * output, float * input, size_t n)
{
		Average avg;
		avg.input = input;
		avg.output = output;
		parallel_for( blocked_range<int>(0, n, 1000), avg);
}

int main()
{
		float * output;
		float input  = 5.0f;
		size_t size   = 6;
		ParallelAverage(output, &input, size);
		std::cout<<" Input : " << input <<", Output : " << *output <<std::endl;
}
