#include <stdio.h>

#define MAX_SONGS 100

struct Song{
    char band[100];
    char title[100];
    float price;
    int year;
};


struct Song songs[MAX_SONGS];

int count =0;