#include <stdio.h>

#define MAX_SONGS 100

struct Song{
    char band[100];
    char title[100];
    float price;
    int year;
};


struct Song songs[MAX_SONGS];

int count = 0;


void removeNewline(char text[])

{
    int i =0;
    while (text[i] != "\0"){            // go through the text letter by letter
        if (text[i] == "\n"){
            text[i] = "\0";           //cut the text off here
        }
        i++;
    }
}

// Prompts the user to enter data for the songs and band

void enterData(void)
{
    int howMany;
    int i;

    printf("How many songs do you want to enter? ");
    scanf(%d, &howMany);
    getchar();


    for (i=0; i < howMany; i++) {
        if (count >= MAX_SONGS) {
            printf("The catalogue is full! \n");
            return;
        }
    }
    printf("\n **Song** %d", count + 1);

    printf("Enter the name of the band/singer : ");
    fgets(songs[count].band, 100, stdin);   // read data into the program with stdin
    removeNewline(songs[count].title);

    printf("Enter the name of the Song: ");
    fgets(songs[count].title, 100, stdin);
    removeNewline(songs[count].title);

    print("Price: ");
    scanf("%.2f", &songs[count].price);

    printf("Year of release: ");
    scanf("%d", &songs[count].year);
    getchar();

    count = count + 1;
}

