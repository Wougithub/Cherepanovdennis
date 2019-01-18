#include <iostream>
#include <fstream>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;


const int maxsize =10000000;
int timesize = 1000;

void combine(int* array, int start, int middle, int end)
{

   int leftside = middle - start + 1; //our left combination
   int rightside =  end - middle; // our right combination

   int* left = new int [leftside]; //allocated memory for the right array
   int* right = new int[rightside]; //allocate memory for the right array

   for( int i = 0; i < leftside; i++){ //put everything from the array into the new one
       left[i] = array[start + i];}
   for( int j =0; j < rightside; j++){
       right[j] = array[middle + 1 + j];}

    int i = 0, j = 0, k = start; //setting values

   while(i < leftside && j < rightside){

       if(left[i] <= right[j]){ //sort the array
           array[k] = left[i];
           i++;}
       else{
           array[k] = right[j]; //sort the array
           j++;}

       k++;} //increment

   while (i < leftside){
   array[k] = left[i];
   i++;
   k++;}

   while (j < rightside){
       array[k] = right[j];
       j++;
       k++;}
   delete [] left; // clean up memory leaks
   delete [] right; //clean up memory leaks.

   }

void auxMergeSort(int* array, int start, int size){

   if (start < size){
       int middle = start + (size-start)/2; //get our middle
       auxMergeSort(array, start, middle); // call merge on the left
       auxMergeSort(array,middle+1, size); //call merge on the right
       combine(array, start, middle, size); //combine our sorted array
   }


}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int* Array, int low, int high)
{
    int pivot = Array[high];    // pivot
    int i = (low-1);  // Index of smaller element

    for (int j = low; j <= high-1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (Array[j] <= pivot)
        {
            i++;
            swap(Array[i], Array[j]);
        }
    }
    swap(Array[i+1], Array[high]);
    return (i + 1);
}

void auxQuickSort( int * array, int start, int size){

    if(start < size){
      int part = partition(array,start,size); //gets our partition
      auxQuickSort(array, start, part-1); //sorts everythign before our parition
      auxQuickSort(array, part+1, size); //sorts everything after partition

    }
}

bool helper (int *array, int size){
    if (size == 1 || size == 0){ //if the size or 1 or 0 we checked the entire array
        return true;}
    if(array[size-1] < array[size-2]){ //if something is bigger than the thing in front of it return false
        return false;
    }
    helper(array, size-1); //keep going

}

bool flgIsSorted(int *array){
    if(timesize < maxsize){
        return helper(array, timesize);} //less than 10 million so use timesize

    else{return helper(array, maxsize);} // we are at 10 million

}

int main()
{
 //Section 1
int* array = new int[maxsize];
ifstream readFile;
readFile.open("lab1_data.txt");

int counter = 0;
int value = 0;

if(readFile.is_open()){ // check to see if file is open don't continue if it isn't
   while(!readFile.eof()){ // while the file is not at the end keep going
       readFile >> value; // put value from text into value
       array[counter] = value; // place value into array
       counter++;}} // increment array

readFile.close(); // close file since we are done.

long long int sum = 0; // our sum
for(int i = 0; i < maxsize; i++){ // add everything into the array
   sum = sum + array[i];}

cout << sum << endl;

auxQuickSort(array, 0, maxsize-1);
bool trueorfalse = flgIsSorted(array);
cout << trueorfalse << endl;

int newvalue = 0;
for(int i = timesize; i <= maxsize; i *= 10){
    int* timearray = new int[timesize];
    ifstream readnew;
    readnew.open("lab1_data.txt");

    if(readnew.is_open()){ // check to see if file is open don't continue if it isn't
       for(int j = 0; j <= timesize; j++){ // while the file is not at the end keep going
           readnew >> newvalue; // put value from text into value
           timearray[j] = newvalue; // place value into array
       }} // increment array

    readnew.close();

    clock_t start, end;
    start = clock();
    auxMergeSort(timearray,0,timesize-1);
    cout << flgIsSorted(timearray) << endl;
    end = clock();
    double duration = double(end-start)/CLOCKS_PER_SEC;
    duration = 1000 * duration;
    cout << "Size of " << i << " Took " << setprecision(30) << fixed << duration  << " Seconds" << endl;

    delete [] timearray;}




int newvalue1 = 0;
timesize = 1000;
for(int i = timesize; i <= maxsize; i *= 10){
    int* timearray = new int[timesize];
    ifstream readnew;
    readnew.open("lab1_data.txt");

    if(readnew.is_open()){ // check to see if file is open don't continue if it isn't
       for(int j = 0; j <= timesize; j++){ // while the file is not at the end keep going
           readnew >> newvalue1; // put value from text into value
           timearray[j] = newvalue1; // place value into array
       }} // increment array

    readnew.close();

    clock_t start, end;
    start = clock();
    auxQuickSort(timearray,0,timesize-1);
    cout << flgIsSorted(timearray) << endl;
    end = clock();
    double duration = double(end-start)/CLOCKS_PER_SEC;
    duration = 1000 * duration;
    cout << "Size of " << i << " Took " << setprecision(30) << fixed << duration  << " Seconds" << endl;
    delete [] timearray;}



delete [] array; // delete array since we are done.
return 0;


}

