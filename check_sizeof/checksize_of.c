#include <stdio.h> 
#include <stdint.h>
 
typedef struct ocl_ac_special {
int str[1024];
//struct ocl_ac_special * next[1024];
uint16_t len, num;
uint8_t type, negative;
}ocl_ac_special;
 
int main()
{
 
    struct ocl_ac_special *ocl_acp;
	struct ocl_ac_special * ocl_acs_temp; 
    ocl_acp = (struct ocl_ac_special *)malloc(sizeof(struct ocl_ac_special) * 150000);
 
    int count_str;
    for(count_str  = 0; count_str < 11; count_str++)
    {
            if(count_str < 1024){
								ocl_acs_temp = &ocl_acp[count_str];
                ocl_acs_temp->str[count_str] = 1+count_str;
            }
    }

		for(count_str = 0; count_str < 11; count_str++)
		{
				if(count_str < 10)
					printf("Data check sum reference : %d \n", ocl_acp[count_str].str[count_str]);

		}
		count_str = 0;
		for(count_str  = 11; count_str < 21; count_str++)
    {
            if(count_str < 1024){
								ocl_acs_temp = &ocl_acp[count_str];
                ocl_acs_temp->str[count_str] = 1+count_str;
            }
    }

 
		for(count_str = 11; count_str < 21; count_str++)
		{
				if(count_str < 21)
					printf("Data check sum reference 11-21: %d \n", ocl_acp[count_str].str[count_str]);

		}

    free(ocl_acp);
}
