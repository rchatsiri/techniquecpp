#include <stdio.h>
#include <stdlib.h>


#include "run_str.h"

int refer_strdata(struct data_b * str_data_b)
{
  printf("Value of str_a : %d \n", *(&str_data_b->str_a) );

 	str_data_b->str_a = (struct data_a*)malloc(sizeof(str_data_b->str_a));	
	if(*(&str_data_b->str_a) == NULL) return 0;

  printf("After assigned malloc address to str_a of *(&str_data_b->str_a) : %d \n", *(&str_data_b->str_a) );
  printf("After assigned malloc address to str_a of &str_data_b->str_a : %d \n", &str_data_b->str_a );

	str_data_b->str_a->input_a_a = (int*) malloc(sizeof(str_data_b->str_a->input_a_a));

 printf("Print value address of input_a_a, &str_data_b->str_a->input_a_a : %d \n", &str_data_b->str_a->input_a_a);
	
 printf("Print value address of input_a_a, *(&str_data_b->str_a->input_a_a) : %d \n", *(&str_data_b->str_a->input_a_a));

	
  *(*(&str_data_b->str_a->input_a_a)) = 10; 
	//str_data_b->str_a->input_a_a = 10; 
  //*(&str_data_b->str_a->input_a_a) = 10; 
     
  printf("Print value struct a pointer of input_a_a value : %d  *(*(&sb->sa->iaa)) \n",*(*(&str_data_b->str_a->input_a_a)));
  printf("Print value struct a pointer of input_a_a value : %d, *(sb->sa->iaa) \n", *(str_data_b->str_a->input_a_a) );


}

int refer_strd(struct data_d * str_data_d)
{
	str_data_d->data_d_a = 12;

  return 1;	
}

int refer_stre(struct data_e * str_data_e)
{
	str_data_e->data_e_a = (int *)malloc(sizeof(str_data_e->data_e_a));
  *(&str_data_e->data_e_a) = 12;
	return 1;
}
int main()
{
  struct  data_b * str_b;
	str_b= (struct data_b*)malloc(sizeof(str_b));
	int err = refer_strdata(str_b);

  if(!err) printf("Print not equal \n");

	printf("Print value of struct a in b by input_a_a(Pass by ref.) : %d \n",*(*(&str_b->str_a->input_a_a)));

  struct data_d datad;
	datad.data_d_a = 12;
	printf("Print value data_d->data_d_a : %d \n", datad.data_d_a);

	err = refer_strd(&datad);

  printf("Print value data_d->data_d_a in reference function refer_strd : %d \n",datad.data_d_a); 

	struct data_e datae;
	refer_stre(&datae);
	printf("Print value data_e->data_e_a in reference function refer_stre : %d \n", datae.data_e_a);

	return 0;


};
