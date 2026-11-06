#include <stdio.h>

#define MAX_SONGS 100       //most songs the catalogue can hold

//structure to group all the details of one song into a single item

struct Song{
    char band[100];         // name of the band or singer (up to 99)
    char title[100];       // name of the song
    float price;            // price
    int year;               // year of release
};

// Array of structures to hold all the songs (up to the max amount of songs which is 100)
struct Song songs[MAX_SONGS];

int count = 0;          //keep track of how many songs are stored at the moment, starting with 0
                        //global so I can use for each function


// function to keep the text clean in the UI when printing or saving
void removeNewline(char text[])

{
    int i =0;
    while (text[i] != '\0'){            // go through the text letter by letter
        if (text[i] == '\n'){           // if this letter is the new line then
            text[i] = '\0';           //cut the text off here
        }
        i++;        // move ontp the next letter
    }
}

// Prompts the user to enter data for the songs and band

void enterData(void)
{
    int howMany;
    int i;          // loop counter

    printf("\n How many songs do you want to enter? ");
    scanf("%d", &howMany);          //read keyboard input
    getchar();          // removes the enter left behind by scanf otherwise the next fgets would read an empty line

// repeat once for each song the user wants to enter
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
    FILE *file;         //pointer used to refer to the file
    int i;          // loop counter

    file = fopen("songs.txt", "w");   // writing into the file but also wipes if it exists


//fopen will give NULL if the file cannot be opened    
    if (file ==NULL) {
        printf("\nCould not open the file!\n");
        return;
    }

    for (i = 0; i < count; i++) {           //writes every song into the file
        fprintf(file, "%s\n", songs[i].band);
        fprintf(file, "%s\n", songs[i].title);
        fprintf(file, "%.2f %d\n", songs[i].price, songs[i].year);
    }

    fclose(file);           //always close the file so everything is saved
    printf("\nSaved %d songs to songs.txt!\n", count);
}



// Read the songs back from the file

void readFromFile(void)
{
    FILE *file;

    file = fopen("songs.txt", "r");         //"r" = read

    // if file doesn't exist or nothing is saved yet, then fopen gives NULL
    if (file == NULL) {
        printf("\nCould not open the file! (Make sure you save first) \n");
        return;
    }

    count = 0;              // start again from an empty catalogue

    //keep going while the array isn't full and there is another line to read
    //fgets will give NULL once it reaches the end of the file, which will stop the loop
    
    while (count < MAX_SONGS && fgets(songs[count].band, 100, file) != NULL) {
        removeNewline(songs[count].band);

        fgets(songs[count].title, 100, file);
        removeNewline(songs[count].title);

        fscanf(file, "%f %d", &songs[count].price, &songs[count].year);
        fgetc(file);            // skip the '\n' left at the end of line 3

        count = count + 1;      //load one more song
    }

    fclose(file);           //close the file once we have finished using it
    printf("\nLoaded %d songs from songs.txt! \n", count);
}

// Put the songs in order of newest to oldest
// Bubble sort which will compare neighbouring songs and swap them
//if in the wrong order, it will repeat the loop until everything is in the correct order

void sortSongs(void)
{
    int i, j;
    struct Song temp;           //temporary song to help swap two songs

    for (i = 0; i < count - 1; i++) {       //repeat the pass several times
        for (j = 0; j < count - 1; j++){            //compare each song with the next one
            if (songs[j].year < songs[j +1].year) {     //if the song on the left is older than the one on the right
                // it will swap them so the newer song moves to the left
                temp = songs[j];            // swap the songs so that newer song moves to the left and save it                 
                songs[j] = songs[j + 1];        // copy right song into left place
                songs[j + 1] = temp;        //put the saved song into the right place
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

    sortSongs();        //puts the songs in order before printing

    printf("\n======= CATALOGUE (new to old) =======\n");

    for (i = 0; i < count; i++) {
        printf("\n");
        printf("Name of Band: %s\n", songs[i].band);
        printf("Name of Song: %s\n", songs[i].title);
        printf("Price: %.2f\n", songs[i].price);
        printf("Year of Release: %d\n", songs[i].year);
    }

    printf("\n=====================================\n");
}

// main program starts here
int main(void)
{
    int choice = 0;

    while (choice != 5){
        printf("\n **** SONG CATALOGUE **** \n");
        printf("Enter data [1] \n");
        printf("Save data to file [2] \n");
        printf("Read data from file [3] \n");
        printf("Print out the catalogue to screen [4] \n");
        printf("Exit program [5] \n");
        printf("Enter your choice now: ");
        scanf("%d", &choice);
        getchar();      //remove the enter left behind by scanf

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
    return 0;           // tells the computer the program has finished normally
}