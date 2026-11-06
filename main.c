#include <stdio.h>

#define MAX_SONGS 100       //most songs the catalogue can hold

struct Song{
    char band[100];         // name of the band or singer
    char title[100];       // name of the song
    float price;               // price
    int year;           // year of release
};


struct Song songs[MAX_SONGS];

int count = 0;


void removeNewline(char text[])

{
    int i =0;
    while (text[i] != '\0'){            // go through the text letter by letter
        if (text[i] == '\n'){
            text[i] = '\0';           //cut the text off here
        }
        i++;
    }
}

// Prompts the user to enter data for the songs and band

void enterData(void)
{
    int howMany;
    int i;

    printf("\n How many songs do you want to enter? ");
    scanf("%d", &howMany);
    getchar();          // removes the enter left behind by scanf


    for (i=0; i < howMany; i++) {
        if (count >= MAX_SONGS) {
            printf("The catalogue is full! \n");
            return;
        }

        printf("\n ---- Song %d of %d ---- \n", i + 1, howMany);

        printf("Enter the name of the band/singer: ");
        fgets(songs[count].band, 100, stdin);    // 100 is the limit
        removeNewline(songs[count].band);

        printf("Enter the name of the song: ");
        fgets(songs[count].title, 100, stdin);
        removeNewline(songs[count].title);

        printf("Enter the price: ");
        scanf("%f", &songs[count].price);

        printf("Enter the year of release: ");
        scanf("%d", &songs[count].year);
        getchar();

        count = count + 1;
    }

}

// Save the songs into a file

void saveToFile(void)
{
    FILE *file;
    int i;

    file = fopen("songs.txt", "w");   // writing into the file

    if (file ==NULL) {
        printf("\nCould not open the file!\n");
        return;
    }

    for (i = 0; i < count; i++) {
        fprintf(file, "%s\n", songs[i].band);
        fprintf(file, "%s\n", songs[i].title);
        fprintf(file, "%f %d\n", songs[i].price, songs[i].year);
    }

    fclose(file);
    printf("\nSaved %d songs to songs.txt!\n", count);
}



// Read the songs back from the file

void readFromFile(void)
{
    FILE *file;

    file = fopen("songs.txt", "r");         //"r" = read

    if (file == NULL) {
        printf("\nCould not open the file! (Make sure you save first) \n");
        return;
    }

    count = 0;              // start again from an empty catalogue

    while (count < MAX_SONGS && fgets(songs[count].band, 100, file) != NULL) {
        removeNewline(songs[count].band);

        fgets(songs[count].title, 100, file);
        removeNewline(songs[count].title);

        fscanf(file, "%f %d", &songs[count].price, &songs[count].year);
        fgetc(file);

        count = count + 1;
    }

    fclose(file);
    printf("\nLoaded %d songs from songs.txt! \n", count);
}

// Put the songs in order of newest to oldest
void sortSongs(void)
{
    int i, j;
    struct Song temp;

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1; j++){
            if (songs[j].year < songs[j +1].year) {
                temp = songs[j];
                songs[j] = songs[j + 1];
                songs[j + 1] = temp;
            }
        }
    }
}

// display all songs on the screen

void printCatalogue(void)
{
    int i;

    if (count == 0) {
        printf("\nThere are no songs yet! \n");
        return;
    }

    sortSongs();

    printf("\n======= CATALOGUE (new to old) =======\n");

    for (i = 0; i < count; i++) {
        printf("Name of Band: %s\n", songs[i].band);
        printf("Name of Song: %s\n", songs[i].title);
        printf("Price: %.2f\n", songs[i].price);
        printf("Year of Release: %d\n", songs[i].year);
    }

    printf("\n=====================================\n");
}


int main(void)
{
    int choice = 0;

    while (choice != 5){
        printf("\n **** SONG CATALOGUE **** \n");
        printf("Enter data [1] \n");
        printf("Save data to file [2] \n");
        printf("Read data from file [3] \n");
        printf("Print out the catalogue [4] \n");
        printf("Exit the program [5] \n");
        printf("Enter your choice now: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1){
            enterData();
        }
        else if (choice == 2){
            saveToFile();
        }
        else if (choice == 3){
            readFromFile();
        }
        else if (choice == 4){
            printCatalogue();
        }
        else if (choice == 5){
            printf("\nGoodbye! \n");
        }
        else {
            printf("\nPlease choose a number from 1 to 5! \n");
        }
    }
    return 0;
}