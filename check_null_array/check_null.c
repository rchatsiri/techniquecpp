#include <stdio.h>
#include <stdint.h>


struct data_control
{
		int sig[10][10][0];
};

int main()
{

		struct data_control * dc;
		dc  = (struct data_control*)malloc(sizeof(struct data_control) * 10);
	  struct data_control * dc_tmp;
		uint16_t count_str, count_str_j;

		for(count_str = 0; count_str < 10; count_str++)
		{
				for(count_str_j = 0; count_str_j < 10; count_str_j++)
				{
					
					 dc->sig[count_str][count_str_j][0] = 1 + count_str_j;
					 dc_tmp->sig[count_str][count_str_j][0] = dc->sig[count_str][count_str_j][0];
				}
		}


}
