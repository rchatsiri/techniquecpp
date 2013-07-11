#include "stdio.h"
#include "stdlib.h"

struct data
{
	struct controller * data;
};

struct controller
{
	char * seta_char;
	int    setb_int;

};

void check_struct(struct data * dt)
{
		struct controller * ct = dt->data;
		printf("Check struct in controller->data : %s \n", ct->seta_char);
}

int main()
{
		struct data * d_one;
		d_one = (struct data*)malloc(sizeof(d_one));

		struct controller * ct;
		ct    = d_one->data;
		ct    = (struct controller*)malloc(sizeof(ct));
		char * strd = "data";
		ct->seta_char = strd;
		printf("Data : %s \n", ct->seta_char);
	
		d_one->data = ct;

		int countchar = 0;
		printf(" Data : ");
		while(ct->seta_char[countchar] != 	'\0')
		{
				printf("%c ", ct->seta_char[countchar]);
				countchar++;
				//ct->seta_char++;
		} 		

		printf("\n");
		check_struct(d_one);
}
