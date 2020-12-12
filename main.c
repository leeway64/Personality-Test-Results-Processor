// Lee-Way Wang
// 11/19/2020
// Personality Test
// This program finds the personality type of a person, based on their responses
// to the Keirsey Temperament Sorter, a personality test.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DIMENSIONS 4


void printIntroduction(){
    printf("This program processes a file of answers to the\n");
    printf("Keirsey Temperament Sorter. It converts the\n");
    printf("various A and B answers for each person into\n");
    printf("a sequence of B-percentages and then into a\n");
    printf("four-letter personality type.\n\n");
}


// Counts the number of A and B counts for the Keirsey personality test results.
// A counts represent answers corresponding to extrovert, sensation, thinking
// and judging. B counts represent answers corresponding to introvert, iNtuition,
// feeling, and perceiving.
// Inputs-
// responses[]: string of A/B responses from the personality test
// responseCounts[]: the number of A or B responses corresponding to each
// of the 4 dimensions. The function modifies responseCounts.
void countResponses(char responses[], int responseCounts[]){
    int location;

    for(int i = 0; i < strlen(responses); i++){
        if (i % 7 == 0){
            location = 0;
        } else if ((i - 1) % 7 == 0 || (i - 2) % 7 == 0){
            location = 1;
        } else if ((i - 3) % 7 == 0 || (i - 4) % 7 == 0){
            location = 2;
        } else {
            location = 3;
        }

        if (responses[i] == 'A' || responses[i] == 'a'){
            responseCounts[location]++;
        } else if (responses[i] == 'B' || responses[i] == 'b'){
            responseCounts[location + DIMENSIONS]++;
        }else{
        }
    }
}


// Calculates what percentage of responses within a given personality dimension
// is a "B" response. Modifies the array BPercentages.
void calculateBPercentages(int responseCounts[], int BPercentages[]){
    for (int i = 0; i < DIMENSIONS; i++){
        int BCount = responseCounts[i + DIMENSIONS];
        int totalCounts = responseCounts[i] + responseCounts[i + DIMENSIONS];

        double BPercent = 100.0 * BCount / totalCounts;
        int roundedBPercent = (int) round(BPercent);

        BPercentages[i] = roundedBPercent;
    }
}


// Finds the personality type of the person, based on the percentage of B
// responses. Personality type is represented as a 4 character string in
// personalityType[]; the array is modified within the function.
void getPersonalityType(int Bpercentages[], char personalityType[]){
    for (int i = 0; i < DIMENSIONS; i++){
        char type[2];
        switch(i){
            case 0:
                type[0] = 'E';
                type[1] = 'I';
                break;
            case 1:
                type[0] = 'S';
                type[1] = 'N';
                break;
            case 2:
                type[0] = 'T';
                type[1] = 'F';
                break;
            case 3:
                type[0] = 'J';
                type[1] = 'P';
                break;
            default:
                break;
        }

        if (Bpercentages[i] > 50){
            personalityType[i] = type[1];
        } else if (Bpercentages[i] < 50){
            personalityType[i] = type[0];
        } else {
            personalityType[i] = 'X';
        }
    }
}


// Prints an array of ints to an output file.
void printIntVector(int vector[], int length, FILE * writeFile){
    fprintf(writeFile, "[");
    for (int i = 0; i < length - 1; i++){
        fprintf(writeFile, "%d, ", vector[i]);
    }
    fprintf(writeFile, "%d] = ", vector[length - 1]);
}


int main(){
    printIntroduction();

    char inputFileName[100];
    char outputFileName[100];

    printf("input file name? ");
    scanf("%s", &inputFileName);

    printf("output file name? ");
    scanf("%s", &outputFileName);

    FILE * readFile = fopen(inputFileName, "r");
    FILE * writeFile = fopen(outputFileName, "w");

    char line[255];
    while (fgets(line, 255, readFile)){
        int responseCounts[] = {0, 0, 0, 0, 0, 0, 0, 0};
        int BPercentages[] = {0, 0, 0, 0};
        char personalityType[DIMENSIONS+1];

        // Considers 1 line at a time, stopping at the new line character
        strtok(line, "\n");

        fprintf(writeFile, "%s: ", line);

        fgets(line, 255, readFile);
        countResponses(line, responseCounts);

        calculateBPercentages(responseCounts, BPercentages);
        printIntVector(BPercentages, DIMENSIONS, writeFile);
        getPersonalityType(BPercentages, personalityType);

        fprintf(writeFile, "%s\n", personalityType);
    }

    fclose(readFile);
    fclose(writeFile);
    return 0;
}
