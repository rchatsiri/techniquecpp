#include <stdio.h>
void getfile(int **fileState,int **startState, int *stateSize, int array_size)
{
    printf("in Getfile... \n");
    int countState = 0;
    int countArray;
    int startPos = 0;

    for(countArray = 0; countArray <= array_size ; countArray++) {

        printf("-- Start state : %d,[ countArray : %d ==  array_size : %d ], fileState : %d  \n", startState[countState], countArray, array_size, fileState[countState]);

        if(countArray == fileState[countState]) {

            if(startPos == 0) {
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

void  insert_array(int **endStatePerFile, int *stateSize, int array_size)
{

    int partition = array_size/4;
    int countFilePerPar = 0;
    int mod_file  = array_size%4;

    printf("Data parttition : %d , mod_file : %d, array_size : %d \n", partition, mod_file, array_size);


    int countPos = 0;
    int countEndState = 0;
    int endState = 0;

    *stateSize = 0;

    int countIncSize = 1;

    for(countPos = partition; countPos <= array_size; countPos+= partition, countEndState++, 	(*stateSize)++) {
        if(countPos == partition) {
            endStatePerFile[countEndState] = countPos;
            printf("Start with endStatePerfile : %d \n", endStatePerFile[countEndState]);
        } else {
            if((countPos + countIncSize) >= array_size) {
                endStatePerFile[countEndState] = array_size;
                printf("-- End state with break: %d \n",  countEndState);
                (*stateSize)++;
                break;
            }

            endStatePerFile[countEndState] = countPos + countIncSize;
            countIncSize++;
            printf("-- End with : %d, CountEndState : %d  \n", endStatePerFile[countEndState], countEndState);
        }

    }
		printf("--- Add : endStatePerfile : %d , Array size : %d \n", endStatePerFile[countEndState], array_size);
    if(endStatePerFile[countEndState] != array_size) {
        endStatePerFile[countEndState] = array_size;
				(*stateSize)++;
        printf("Not equal array size, endStatePerFile[%d] \n", endStatePerFile[countEndState -1 ]);
    }
}


int main()
{

    //int size_array = 17;
    //int array_file[17] = {0,1,2,3,5,23,53,33,46,23,77,23,75,23,64,22,63};
    // int size_array  = 15;
    //int array_file[15] = {23,53,234,23,121,2,13,63,98,234, 6, 2,11,2,63};

   // int size_array = 5;
   // int array_file[5] = {0,1,2,3,5};

    int size_array = 32;
    int array_file[32];//
    // = {0,1,2,3,5,2};
    //
    int i;
    for(i = 0; i < size_array; i++)
		{
					array_file[i] = i * (rand()%100);
		}

   	//int size_array = 4;
    // int array_file[4] = {0,1,2,6};



    int c_array = 0;
    printf("---------------------------------------------------------\n");

    for(c_array = 0; c_array < size_array; c_array++)
        printf("%d, ", array_file[c_array]);

    printf("\n---------------------End count Array -------------------\n");

    int *endState[size_array];
    int *startState[size_array];

    int *stateSize = (int *)malloc(sizeof(int *));

    insert_array(endState, stateSize, size_array);

    int countFile;
    printf("State size : %d \n", *stateSize);

    for(countFile =  0; countFile < *stateSize; countFile++) {
        printf("-- Print all index ( not size ) = [ %d ] : %d \n",countFile,  endState[countFile]);
    }

    getfile(endState, startState, stateSize, size_array);


    countFile = 0;
    int countPerFile;

    for(; countFile  < *stateSize; countFile++) {
        printf("--- Start state : %d - %d \n", startState[countFile], endState[countFile]);
        int end = endState[countFile];
        int start = startState[countFile];
				
				if((end - start) == 0)
				{	
						break;
				}

        for(countPerFile = start; countPerFile <= end; ++countPerFile) {
            printf("--- Count Per file : %d , array_file : [ %d ] \n", countPerFile, array_file[countPerFile]);
        }

        countPerFile = 0;
    }

}
