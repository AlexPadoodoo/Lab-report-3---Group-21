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
    scanf("%d", &howMany);
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


// Save the songs into a file

void saveToFile(void)
{
    FILE *file;
    int i;

    file = fopen("songs.txt", "w");   // writing into the file

    if (file ==NULL) {
        printf("Could not open the file! \n");
        return;
    }

    for (i = 0; i < count; i++) {
        fprintf(file, "%s\n", songs[i].band);
        fprintf(file, "%s\n", songs[i].title);
        fprintf(file, "%f %d\n", songs[i].price, songs[i].year);
    }

    fclose(file);
    printf("Saved %d songs! \n", count);
}



// Read the songs back from the file

void readFromFile(void)
{
    FILE *file;

    file = fopen("songs.txt", "r");

    if (file == NULL) {
        printf("Could not open the file! (Make sure you save first) \n");
        return;
    }

    count = 0;

    while (count < MAX_SONGS && fgets(songs[count].band, 100, file) != NULL) {
        removeNewline(songs[count].band);

        fgets(songs[count].title, 100, file);
        removeNewline(songs[count].title);

        fscanf(file, "%f %d", &songs[count].price, &songs[count].year);
        fgetc(file);

        count = count + 1;
    }

    fclose(file);
    printf("Loaded %d songs! \n", count);
}

// Put the songs in order of newest to oldest
void sortSongs(void)
{
    int i, j;
    struct Song temp;

    for (i = 0; i < count - 1; i++) {
        if (songs[j].year < songs[j +1].year) {
            temp = songs[j];
            songs[j] = songs[j + 1];
            songs[j + 1] = temp;
        }
    }
}