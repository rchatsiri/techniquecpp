#ifndef RUN_STR_H
#define RUN_STR_H

struct data_a{
	int * input_a_a;
  int * input_a_b;
};

struct data_b{

	struct data_a * str_a;
	int  * input_b_a;
	char * input_b_c;

};

struct data_c{
	int * input_c_a;
};

struct data_d{
	int data_d_a;
};

struct data_e{
	int * data_e_a;
};



int refer_strdata(struct data_b * st_data_b);

int refer_strd(struct data_d * str_data_d);

int refer_stre(struct data_e * str_data_e);


#endif /* RUN_STR_H */
