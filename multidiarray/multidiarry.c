#include <stdio.h>
void getfile(int **fileState,int **startState, int *stateSize, int array_size)
{
    printf("in Getfile... \n");
    int countState = 0;
    int countArray;
    int startPos = 1;

    for(countArray = 0; countArray <= array_size ; countArray++) {

        printf("-- Start state : %d,[ countArray : %d ==  array_size : %d ], fileState : %d  \n", startState[countState], countArray, array_size, fileState[countState]);
	
        if(countArray == fileState[countState]) {
            if(startPos == 1) {
                startState[countState] = startPos;
                printf("--- Start Position %d \n", startState[countState]);
                int data = fileState[countState];
                startPos = data + 1;
                countState++;

            } else {
                startState[countState] = startPos;
                printf("--- Start Position: %d , startState[%d] \n", startPos, startState[countState]);
                int data = fileState[countState];
                startPos = data + 1;
                countState++;

            }
        }
    }

    int count_start;

    for(count_start = 0; count_start < *stateSize; count_start++)
        printf("-- Position start with : %d \n", startState[count_start]);
}

void insert_array(int **fileState, int *stateSize, int size_array, int *array)
{

    int partition = size_array/4;
    int countFilePerPar = 0;
    int mod_file   = size_array%4;

    printf("Data parttition : %d , mod_file : %d \n", partition, mod_file);


    int countPos = 0;
    int countEndState = 0;
		int endState = 0;
    
    *stateSize = 0;

    for(countPos = 0; countPos <= size_array; countPos++) {
        if(countFilePerPar == partition) {
            fileState[countEndState] = endState;
						printf("End state with : fileState [ %d ], countPos: %d \n", fileState[countEndState], countPos);
            (*stateSize)++;
            countEndState++;
            countFilePerPar = 0;
        }

        countFilePerPar++;
        endState++;
    }
    printf("-- End --\n");
}


int main()
{



    //int size_array = 17;
    //int a[17] = {0,1,2,3,5,23,53,33,46,23,77,23,75,23,64,22,63};
		int size_array  = 9;
		int array_file[9] = {23,53,234,23,11,12,36,23,1};

    int *fileState[size_array];
    int *startState[size_array];

    int *stateSize = (int *)malloc(sizeof(int *));

    insert_array(fileState, stateSize, size_array, array_file);

    int countFile;
    printf("State size : %d \n", *stateSize);

    for(countFile =  0; countFile < *stateSize; countFile++) {
        printf("-- Print all state[ %d ] : %d \n",countFile,  fileState[countFile]);
    }
		
    getfile(fileState, startState, stateSize, size_array);
		

		countFile = 0;
		int countPerFile;
		for(; countFile  < *stateSize; countFile++)
		{
			printf("--- Start state : %d - %d \n", startState[countFile], fileState[countFile]);
			for(countPerFile = startState[countFile]; countPerFile < fileState[countFile]; countPerFile++)
			{
						printf("--- Count Per file : %d , array_file : [ %d ] \n", countPerFile, array_file[countPerFile]);
			}
			countPerFile = 0; 
		}

}
