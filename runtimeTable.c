#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const char DATA_FILE_NAME[] = "TestData.txt";

typedef struct functionRuntimes
{
    char *szName;            //name of the function being tested
    double **arrRuntimes;    //run times
    double *arrAvg;          //average runtime
    int iNumRepeats;         //number of times to repeat each test size
    int iNumTestCaseSizes;   //number of test case sizes
    int *arrTestSizes;       //array containing the test case sizes
} functionRuntimes;

//Functions used to test the runtimes 
functionRuntimes timeAlgorithm( char*, int, int, int[], void (*f)(FILE *) );
FILE *generateTestInput( int, int, int );
void computeAvg( functionRuntimes fRT );
void printRuntimeTable( functionRuntimes fRT );
void freeFunctionRuntimes( functionRuntimes fRT );

//Functions whose runtime will be tested (and helper functions)
void insertionSortInitial( FILE* input );
void insertionSort( int* points, int low, int high );
void quickSortOptInitial( FILE* input );
void quickSortOpt( int* points, int low, int high );
int partition( int* points, int low, int high );

void mysteryRuntime1( FILE* input );
void mysteryRuntime2( FILE* input );
void mysteryRuntime3( FILE* input );

/*
 * Provided code - DO NOT CHANGE THIS METHOD OTHER THAN TO ADD YOUR NAME AND YOUR PARTNER'S NAME
 * (if you make alterations for the sake of testing be sure to revert them before submission)
 */
int main( int argc, char *argv[] )
{
    functionRuntimes fRT;

    int sizes1[] = { 500, 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000};

    /* TODO : Fill in your name */
    printf("This solution was completed by:\n");
    printf("Qustandi Fashho\n");

    srand(time(0));

    fRT = timeAlgorithm("Insertion Sort", 6, 5, sizes1, insertionSortInitial );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    fRT = timeAlgorithm("quicksort (uses insertion sort when sorting <30 numbers)", 12, 8, sizes1, quickSortOptInitial );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    fRT = timeAlgorithm("Mystery 1", 3, 6, sizes1, mysteryRuntime1 );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    fRT = timeAlgorithm("Mystery 2", 3, 5, sizes1, mysteryRuntime2 );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    fRT = timeAlgorithm("Mystery 3", 3, 8, sizes1, mysteryRuntime3 );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    return 0;
}

/*************************************** Functions to have their runtimes tested *********************************************/

/* provided code - DO NOT CHANGE
 */
void mysteryRuntime1( FILE* input )
{
    int temp;
    int size;
    int n;
    int i=0;
    int *array;

    if( fscanf( input, "%d", &size ) != 1 )
    {
        exit(-1);
    }
    array = (int *) malloc( size*sizeof(int) );
    if( array == NULL )
    {
        exit(-1);
    }

    while( fscanf( input, "%d", &temp ) == 1 && i<size)
    {
        array[i] = temp;
        i++;
    }

    for( i=0; i<size; i++ )
    {
        for( n=size-1; n>1; n/=1.01 )
        {
            array[n-1] = array[n];
        }
    }

    free(array);
}

/* provided code - DO NOT CHANGE
 */
void mysteryRuntime2( FILE* input )
{
    int temp;
    int size;
    int i=0, j=0;
    int *array;

    if( fscanf( input, "%d", &size ) != 1 )
    {
        exit(-1);
    }
    array = (int *) malloc( size*sizeof(int) );
    if( array == NULL )
    {
        exit(-1);
    }

    while( fscanf( input, "%d", &temp ) == 1 && i<size)
    {
        array[i] = temp;
        i++;
    }

    i=0;
    while( j<size )
    {
        array[j] = array[i];

        i++;
        if( i>=size )
        {
            j++;
            i=0;
        }
    }

    free(array);
}

/* provided code - DO NOT CHANGE
 */
void mysteryRuntime3( FILE* input )
{
    int temp;
    int size;
    int i=0;
    int *array;

    if( fscanf( input, "%d", &size ) != 1 )
    {
        exit(-1);
    }
    array = (int *) malloc( size*sizeof(int) );
    if( array == NULL )
    {
        exit(-1);
    }

    while( fscanf( input, "%d", &temp ) == 1 && i<size)
    {
        array[i] = temp;
        i++;
    }

    while( size>1 )
    {
        size = size/2;
        array[size/2] = array[size];
    }

    free(array);
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void insertionSortInitial( FILE* input )
{
    int i;
    int size;
    int *array;

    fscanf( input, "%d", &size );
    array = (int *) malloc( size*sizeof(int) );

    for( i=0; i<size; i++)
    {
        fscanf( input, "%d", &array[i] );
    }

    insertionSort( array, 0, size-1 );

    //Error check to verify the array is sorted
    /*for( i=1; i<size; i++)
    {
        if(array[i-1]>array[i])
        {
            printf("Not sorted!");
            exit(-1);
        }
    }*/

    free(array);
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void insertionSort( int* points, int low, int high )
{
    int i, j;
    double temp;

    for( i = low+1; i <= high; i++)
    {
        for( j = i; j > low && points[j]<points[j-1]; j--)
        {
            temp = points[j];
            points[j] = points[j-1];
            points[j-1] = temp;
        }
    }
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void quickSortOptInitial( FILE* input )
{
    int i;
    int size;
    int *array;

    fscanf( input, "%d", &size );
    array = (int *) malloc( size*sizeof(int) );

    for( i=0; i<size; i++)
    {
        fscanf( input, "%d", &array[i] );
    }

    quickSortOpt( array, 0, size-1 );

    //Error check to verify the array is sorted
    /*for( i=1; i<size; i++)
    {
        if(array[i-1]>array[i]){
            printf("Not sorted!");
            exit(-1);
        }
    }*/

    free(array);
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void quickSortOpt( int* points, int low, int high )
{
    if( high < low+30 )
    {
        insertionSort( points, low, high );
    }
    else
    {
        int pivot = partition( points, low, high );

        quickSortOpt( points, low, pivot-1 );
        quickSortOpt( points, pivot+1, high );
    }
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
int partition( int* points, int low, int high )
{
    int pivot = rand() % (high - low + 1) + low;
    int pivotValue = points[pivot];
    int i = low+1;
    int j = high;
    int temp;

    points[pivot] = points[low];
    points[low] = pivotValue;

    while( i<j )
    {
        while( i<=high && points[i] <= pivotValue )
        {
            i++;
        }
        while( j>=low && points[j] > pivotValue )
        {
            j--;
        }
        if(i<j)  //swap out of order elements
        {
            temp = points[i];
            points[i] = points[j];
            points[j] = temp;
        }
    }
    if( i<=high && points[i] <= pivotValue )
    {
        i++;
    }

    points[low] = points[i-1];
    points[i-1] = pivotValue;

    return i-1;
}

/*************************************** Functions for finding and printing runtime *********************************************/

/*
TODO: Give your asymptotic estimates for the runtimes of the following 3 functions:

mysteryRuntime1:  O(   )
mysteryRuntime2:  O(   )
mysteryRuntime3:  O(   )
*/


/* TO BE COMPLETED BY YOU
 * Fill in the missing parts of the code (see TODOs below)
 */
functionRuntimes timeAlgorithm( char *szName, int iNumRepeats, int iNumTestCaseSizes, int arrTestSizes[], void (*f)(FILE *) )
{
    /* Call and calculate the runtime of the provided function f */
    clock_t start, end;
    int i, j;
    FILE *testData;

    //create functionRuntimes variable to return
    functionRuntimes fRT;

    //TODO: copy passed data into the fRT variable.  Specifically do the following:
    /* fill szName in fRT with the variable szName */
    fRT.szName = szName;
    /* fill iNumRepeats in fRT with the variable iNumRepeats */
    fRT.iNumRepeats = iNumRepeats;
    /* fill iNumTestCaseSizes in fRT with the variable iNumTestCaseSizes */
    fRT.iNumTestCaseSizes = iNumTestCaseSizes;
    /* malloc space for arrTestSizes in fRT to hold iNumTestCaseSizes number of ints */
    fRT.arrTestSizes = (int*)malloc(sizeof(int) * iNumTestCaseSizes);
    /* fill arrTestSizes in fRT with the variable arrTestSizes (hint: use a loop) */
    for(i = 0; i < iNumTestCaseSizes; i++){
        fRT.arrTestSizes[i] = arrTestSizes[i];
    }


    //TODO: malloc an array with iNumTestCaseSizes variables of type double* (on next line)
    fRT.arrRuntimes = (double**)malloc(sizeof(double* ) * iNumTestCaseSizes); /* replace NULL with your code */
    for( i=0; i<iNumTestCaseSizes; i++ )
    {
        //TODO: malloc an array with iNumRepeats variables of type double (on next line)
        // one step after previous malloc (like in example 00) but in an array. use "i" from for loop
        fRT.arrRuntimes[i] = (double*)malloc(sizeof(double)* iNumRepeats);

        for( j=0; j<iNumRepeats; j++ )
        {
            //Generate test data for the function f
            testData = generateTestInput( 0, arrTestSizes[i], arrTestSizes[i] );

            //Run f on the generated test data
            start = clock();
            f( testData );
            end = clock();
            fclose(testData);

            //Enter the elapsed number of seconds into the arrRuntimes array for fRT
            //TODO: uncomment the next line line after you've malloc-ed memory for fRT.arrRuntimes
            fRT.arrRuntimes[i][j] = (double)(end - start) / CLOCKS_PER_SEC; // 
        }
    }

    //TODO: on the next line, malloc space for fRT.arrAvg (you'll need to store iNumTestCaseSizes variables of type double)
    fRT.arrAvg = (double*)malloc(sizeof(double) * iNumTestCaseSizes); /* replace NULL with your code */
    //TODO: Calculate the average runtimes (i.e. call computeAvg here) !!!!IS THAT ALL I HAVE TO DO JUST CALL IT?? Yes
    computeAvg(fRT);

    return fRT;
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
FILE *generateTestInput( int min, int max, int size )
{
    int i;
    FILE *data = fopen( DATA_FILE_NAME, "w" );

    if( data==NULL )
    {
        printf("Failed to create file %s\n", DATA_FILE_NAME);
        exit(-1);
    }

    //add size to start of file
    fprintf( data, "%d ", size );
    //Fill the file with random data
    for( i=0; i<size; i++ )
    {
        fprintf( data, "%d ", rand()%(max-min+1)+min );
    }
    fclose(data);

    data = fopen( DATA_FILE_NAME, "r" );
    if( data==NULL )
    {
        printf("Failed to create file %s\n", DATA_FILE_NAME);
        exit(-1);
    }
    return data;
}


/* TODO: TO BE COMPLETED BY YOU
 * Calculate and insert the average runtime for each set of test data into fRT
 */
void computeAvg( functionRuntimes fRT ){
    int i = 0;
    int j = 0;
    for(i = 0; i < fRT.iNumTestCaseSizes; i++){ // check if iNumRepeats or  iNumTestCaseSizes
        double runTime = 0.0;
        for(j = 0; j < fRT.iNumRepeats; j++){
            runTime += fRT.arrRuntimes[i][j];
        }
        fRT.arrAvg[i] = (runTime / fRT.iNumRepeats);

    }

}












/* TODO: TO BE COMPLETED BY YOU
 * Print the information in fRT as a 2d table.  Display 3 digits after the decimal point.  You can assume all of the runtimes are <= 99.999 seconds.
 * The number of repeats will be <= 14.
 *
 * The columns should each line up.  Using printf to create minimum width sizes for your printed variables should make this easier.
 */
void printRuntimeTable( functionRuntimes fRT ){
        printf("\n%s\n", fRT.szName);

    // Print table header
    printf("%-1s", "Test Size   ");
    int i = 0;
    for (i = 0; i < fRT.iNumRepeats; i++) {
        if((i + 1) < 11){
            printf("   Test #%d", i + 1);
        }
        else{
            printf("  Test #%d", i + 1);

        }
        if (i < fRT.iNumRepeats - 1) {
            printf("%-2s", ""); // Add some spacing between the tests #s header
        }
    }
    if((i + 1) < 11){
        printf("%-15s%-15s\n", "     Average", "  Increase");
    }
    else{
        printf("%-15s%-15s\n", "    Average", " Increase");

    }

    // Compute averages
    computeAvg(fRT);

    // Print table rows

    int j = 0;
    for (i = 0; i < fRT.iNumTestCaseSizes; i++) {
        printf("%-10d", fRT.arrTestSizes[i]);
        for (j = 0; j < fRT.iNumRepeats; j++) {
            printf("%10.3lf", fRT.arrRuntimes[i][j]); ////////////////////////////
            if (j < fRT.iNumRepeats - 1) {
                printf("%2s", "  "); // Add some spacing between columns of test # (The acutal columns not the headers)
            }
        }
        printf("%12.3lf", fRT.arrAvg[i]);

        if (i > 0) {
            double increase = fRT.arrAvg[i] / fRT.arrAvg[i - 1];
            printf("%12.3lf", increase); // For increase colun spacing 
        } else {
            printf("%12s", "N/A"); // Display "N/A" for the first row
        }

        printf("\n");
    }
}




    



/* TODO: TO BE COMPLETED BY YOU
 * Free all of the dynamically allocated memory in fRT
 */
void freeFunctionRuntimes( functionRuntimes fRT ){
    free(fRT.arrTestSizes);
    free(fRT.arrAvg);
    // free 2D array
    int i = 0;
    for(i = 0; i < fRT.iNumTestCaseSizes; i++){
        free(fRT.arrRuntimes[i]);
    }
    free(fRT.arrRuntimes);


}

