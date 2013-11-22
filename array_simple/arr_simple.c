#include <stdio.h>
int main()
{

		int * a;
		a = (int*)malloc(sizeof(int) * 5);

		int count_arr;
		for(count_arr= 0; count_arr < 5; count_arr++)
		{
				a[count_arr] = 1 + count_arr;
		}

		for(count_arr= 0; count_arr < 5; count_arr++)
		{
				printf("Arr value : %d \n", a[count_arr]);
		}



}
