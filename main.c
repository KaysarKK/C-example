////////////////////
// Kaisar Kassenov//
// Bakyt Nazirov  //
// Assignment 4   //
////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// defining the variable of number of countries to make it easier to understand
#define SIZE 158

typedef struct {
    char* country;
    long females;
    long males;
} person_count;

//function for freeing the pointers
void freeAll(person_count *item[])
{
    int i;
    for(i = 0; i < 158; i++)
    {
        free(item[i]->country);
        free(item[i]);
    }
}

void insertionsort(person_count *x[]) {
    int i;
    for (i = 0; i < SIZE; i++) {
        person_count *toInsert = x[i];
        int j;
        for (j = i; j >= 0; j--) {
            if (j == 0 || x[j - 1]->males > toInsert->males) {
                
                x[j] = toInsert;
                break;
                
            } else {
                x[j] = x[j - 1];
            }
        }
    }
    
}

void selectionsort(person_count *x[]) {
    
    // Put your selection sort code here
    int i;
    for (i = 0; i < SIZE - 1; i++) {
        
        int j, mindex = i;
        for (j = i + 1; j < SIZE; j++) {
            if (x[j]->females < x[mindex]->females) {
                mindex = j;
            }
        }
        
        person_count *temp = x[i];
        x[i] = x[mindex];
        x[mindex] = temp;
    }
    
}

void bubblesort(person_count *x[]) {
    
    // Put your bubble sort code here
    int i, j;
    
    for (i = 0; i < SIZE - 1; i++) {
        
        for (j = 0; j < SIZE - 1 - i; j++) {
            
            if (strcmp(x[j]->country, x[j + 1]->country) > 0)
            {
                person_count *temp = x[j + 1];
                x[j + 1] = x[j];
                x[j] = temp;
            }
        }
        
    }
    
}


//quick sort
void sort(person_count *x[], int first, int last) {
    
    if (first < last) {
        int pivIndex = partition(x, first, last);
        sort(x, first, pivIndex - 1);
        sort(x, pivIndex + 1, last);
    }
}

int partition(person_count *x[], int first, int last)
{
    int pivot = first;
    int up = first, down = last;
    while (up < down)
    {
        
        while ((x[up]->females + x[up]->males) > (x[pivot]->females + x[pivot]->males) && up < last)
            up++;
        while ((x[down]->females + x[down]->males) < (x[pivot]->females + x[pivot]->males))
            down--;
        if (up < down)
        {
            person_count *temp = x[up];
            x[up] = x[down];
            x[down] = temp;
        }
    }
    person_count *temp2 = x[pivot];
    x[pivot] = x[down];
    x[down] = temp2;
    return down;
}

// quicksort with using person_count varialble
void quicksort(person_count *x[]) {
    sort(x, 0, SIZE - 1);
}




int main() {
    
    setvbuf(stdout, NULL, _IONBF, 0);
    //opening file
    FILE *infile;
    infile = fopen("SecondaryEd2005.txt", "r");
    
    if (infile == NULL) {
        printf("Problem opening files.");
        return 1;
    }
    
    printf("File opened successfully. \n");
    
    //creation of person_count array
    person_count *data[SIZE];
    int i = 0;
    //filling the array from file
    do {
        char c[32];
        long y, z;
        fscanf(infile, "%s %li %li", c, &y, &z);
        
        // memory allocation for person_count variable
        data[i] = (person_count*)malloc(sizeof(person_count));
        
        data[i]->country = (char*)malloc(strlen(c) + 1);
        
        strcpy(data[i]->country, c);
        data[i]->females = y;
        data[i]->males = z;
        i++;
    } while (!feof(infile));
    //closing file
    fclose(infile);
    
    //printing of array with selection sort
    printf("Selection sort \n");
    selectionsort(data);
    for (int i = 0; i < SIZE; i++) {
        printf("%30s %9li %9li \n", data[i]->country, data[i]->females, data[i]->males);
    }
        //printing of array with insertion sort
    insertionsort(data);
    printf("Insertion sort \n");
    for (int i = 0; i < SIZE; i++) {
        printf("%30s %9li %9li \n", data[i]->country, data[i]->females, data[i]->males);
    }
    //printing of array with quick sort
    quicksort(data);
    printf("Quick sort \n");
    for (int i = 0; i < SIZE; i++) {
        printf("%30s %9li %9li %10li \n", data[i]->country, data[i]->females, data[i]->males, data[i]->males + data[i]->females);
    }
    //printing of array with bubble sort
    bubblesort(data);
    printf("Bubble sort \n");
    for (int i = 0; i < SIZE; i++) {
        printf("%30s %9li %9li \n", data[i]->country, data[i]->females, data[i]->males);
    }
    //freeing the memory
    freeAll(data);
    return 0;
}
