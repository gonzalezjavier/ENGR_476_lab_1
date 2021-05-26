//
//  Lab_1.c
//  476_Lab_1
//  ENGR 476-01
//  Created by Javier Gonzalez on 9/9/20.
//  Submission date: 9/14/20 
//  Copyright © 2020 Javier Gonzalez. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXLINESIZE 100
#define NUMOFSTUDENTS 7
#define DELIMS "\t \n"
#define HELP "a/1 to obtain all the students that got diploma\nb/2 to arrange subject A in ascending order\nc/3 to calculate the average and standard deviation\nd/4 to save all the above results in an output file\ne to exit\n"

char file_header[MAXLINESIZE];
char program_output[MAXLINESIZE*MAXLINESIZE];
int counter = 0;

struct student_info{
    char name[MAXLINESIZE/2];
    int student_number;
    float score_a;
    float score_b;
};

struct student_info students[NUMOFSTUDENTS];

//choice 1/a to determine which students obtained their dimploma
void diploma_obtained() {
    printf("All of the students that obtained a diploma:\n%s", file_header);
    counter+=sprintf(program_output+counter, "All of the students that obtained a diploma:\n%s", file_header);
    for (int i=0; i < NUMOFSTUDENTS; i++) {
        if (students[i].score_a >=50 && students[i].score_b >= 50) {
            printf("%-12s\t\t%-16d%-13.1f\t%-9.1f  \n", students[i].name, students[i].student_number, students[i].score_a, students[i].score_b);
            counter+=sprintf(program_output+counter, "%-12s\t\t%-16d%-13.1f\t%-9.1f  \n", students[i].name, students[i].student_number, students[i].score_a, students[i].score_b);
        }
    }
}
//choice 2/b to arrange subject A in ascending order and display student info
void subject_A_acending() {
    //sorts the students array
    for (int i=0; i < NUMOFSTUDENTS; i++) {
        for (int j =0; j < NUMOFSTUDENTS; j++) {
            if (students[i].score_a < students[j].score_a) {
                struct student_info temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("%s",file_header);
    counter+=sprintf(program_output+counter, "%s", file_header);
    for (int i=0; i < NUMOFSTUDENTS; i++) {
        printf("%-12s\t\t%-16d%-13.1f\t%-9.1f  \n",students[i].name, students[i].student_number, students[i].score_a, students[i].score_b);
        counter+=sprintf(program_output+counter, "%-12s\t\t%-16d%-13.1f\t%-9.1f  \n",students[i].name, students[i].student_number, students[i].score_a, students[i].score_b);
    }
}
//choice 3/c to calculate the average and std dev of each subject
void average_and_std_dev() {
    float average_A=0;
    float average_B=0;
    float std_dev_A=0;
    float std_dev_B=0;
    //calculates the mean/avg
    for (int i=0; i < NUMOFSTUDENTS; i++) {
        average_A+=students[i].score_a;
        average_B+=students[i].score_b;
    }
    average_A/=NUMOFSTUDENTS;
    average_B/=NUMOFSTUDENTS;
    //calculates the stdev
    for(int i=0; i <NUMOFSTUDENTS; i++) {
        std_dev_A+=pow(students[i].score_a - average_A, 2);
        std_dev_B+=pow(students[i].score_b - average_B, 2);
    }
    std_dev_A = sqrtf(std_dev_A/NUMOFSTUDENTS);
    std_dev_B = sqrtf(std_dev_B/NUMOFSTUDENTS);
    
    printf("Average of Subject A: %.2f\nAverage of Subject B: %.2f\nStd. Dev. of Subject A: %.2f\nStd. Dev. of Subject B: %.2f\n", average_A, average_B, std_dev_A, std_dev_B);
    counter+=sprintf(program_output+counter, "Average of Subject A: %.2f\nStd. Dev. of Subject A: %.2f\nAverage of Subject B: %.2f\nStd. Dev. of Subject B: %.2f\n", average_A,std_dev_A, average_B, std_dev_B);
}
//choice 4/d to save all output to output file
void save_output() {
    FILE *file_ptr;

    file_ptr = fopen("out.txt", "w");
    if (file_ptr==NULL) {
        perror("Could not write the file.\n");
        exit(1);
    }
    fprintf(file_ptr, "%sFILE SAVED.\n", program_output);
    printf("FILE SAVED.\n");
    fclose(file_ptr);
}

int main(int argc, const char * argv[]) {
    char fileName[16];
    char singleLine[MAXLINESIZE];
    FILE *filePtr;
    
    //ask user for a txt file
    printf("Please enter input file name: ");
    scanf("%s", fileName);
    printf("Given file name: %s\n", fileName);
    counter=sprintf(program_output, "Please enter input file name: %s\n",fileName);
    counter+=sprintf(program_output+counter, "Given file name: %s\n", fileName);
    
    //open the file the user specifies
    filePtr = fopen(fileName, "r");
    if(filePtr == NULL) {
        perror("Invalid file entry!");
        exit(1);
    }
    
    
    //reads the file line by line to get the values of data to be stored
    int line = 0;
    fgets(file_header, MAXLINESIZE, filePtr);
    printf("%s", file_header);
    counter+=sprintf(program_output+counter, "%s", file_header);
    while(!feof(filePtr)) {
        fgets(singleLine, MAXLINESIZE, filePtr);
        printf("%s", singleLine);
        counter+=sprintf(program_output+counter, "%s", singleLine);
        strcpy(students[line].name, strtok(singleLine, DELIMS));
        students[line].student_number = atoi(strtok(NULL, DELIMS));
        students[line].score_a = atof(strtok(NULL, DELIMS));
        students[line].score_b = atof(strtok(NULL, DELIMS));
        line++;
    }
    puts("\n"); //for formatting
    counter+=sprintf(program_output+counter, "\n");
    fclose(filePtr);
    
    //loop to ask user for further input
    char userCommand;
    while(1)    {
        printf("Please enter a command (enter h for help): ");
        scanf(" %c", &userCommand);
        counter+=sprintf(program_output+counter, "Please enter a command (enter h for help): %c\n", userCommand);
        switch (userCommand) {
            //obtain students that got a diploma
            case 'a':
            case '1':
                //call function
                diploma_obtained();
                break;
                
            //arrange Subject A in ascending order
            case 'b':
            case  '2':
                //call function
                subject_A_acending();
                break;
                
            //calculate average and std dev
            case 'c':
            case '3':
                //call function
                average_and_std_dev();
                break;
                
            //save output into an output file
            case 'd':
            case '4':
                //call function
                save_output();
                break;
            case 'e':
                //exit
                return 0;
            case 'h':
                //print out help sheet
                printf("%s", HELP);
                counter+=sprintf(program_output+counter, "%s", HELP);
                break;
            default:
                //invalid entry
                printf("Invalid entry, try again.\n");
                counter+=sprintf(program_output+counter, "Invalid entry, try again.\n");
                break;
        }
    }
}
