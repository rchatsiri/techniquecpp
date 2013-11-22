#include <stdio.h>
#include <stdint.h>

#define MAX_ARRAY_SIZE_1  10
#define MAX_ARRAY_SIZE_2  2

int assign_arr(uint16_t ** array_di)
{
		array_di = (uint16_t**)malloc( MAX_ARRAY_SIZE_1 * sizeof(uint16_t*));
		int count_a_id;
		for(count_a_id = 0; count_a_id < MAX_ARRAY_SIZE_1; count_a_id++)
		{
				array_di[count_a_id] = (uint16_t*)malloc(MAX_ARRAY_SIZE_2 * sizeof(uint16_t));

		}

		//assign value
		int count_a_id2;
		for(count_a_id = 0; count_a_id < MAX_ARRAY_SIZE_1; count_a_id++)
		{
				for(count_a_id2 = 0; count_a_id2 < MAX_ARRAY_SIZE_2; count_a_id2++)
				{
						if(count_a_id == 3){
							array_di[count_a_id][count_a_id2] = 7;
					  }
						else{
							array_di[count_a_id][count_a_id2] = 2 + count_a_id2;
						}
				}
		}

		//print value
		for(count_a_id = 0; count_a_id < MAX_ARRAY_SIZE_1; count_a_id++)
		{
				for(count_a_id2 = 0; count_a_id2 < MAX_ARRAY_SIZE_2; count_a_id2++)
				{
						//array_di[count_a_id] = 2 + count_a_id2;
						printf("Array Dimession : %d \n", array_di[count_a_id][count_a_id2]);
				}
				printf("---\n");
		}

}


int main()
{
		uint16_t ** ch_mindist;
		assign_arr(ch_mindist);

}; 
