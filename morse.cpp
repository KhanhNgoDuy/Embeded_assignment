#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fstream>

#include "error.cpp"

void text_morseFILE(const char* inp, const char* outp){
    fstream myFile;
    myFile.open(inp, ios::in);
    string line;
    string s = "";
    string s_res;
    if (myFile.is_open()) {
        while (getline(myFile , line)) {
            s += line + '\n';

        };
        s.resize(s.length() - 1);
        s_res = letter_to_morse(s);
        myFile.close();
    };

    myFile.open(outp, ios::out);
    if (myFile.is_open()) {
        myFile<< s_res;
        myFile.close();
    }
 }

void morse_textFILE(const char *inp, const char *outp){
    fstream myFile;
    myFile.open(inp, ios::in);
    string line;
    string s = "";
    string s_res;

    if (myFile.is_open()) {
        while (getline(myFile , line)) {
            s += line + '\n';
        };
        s.resize(s.length() - 1);
        s_res = morse_to_letter(s);
        myFile.close();
    };

    myFile.open(outp, ios::out);
    if (myFile.is_open()) {
        myFile<< s_res;
        myFile.close();
    }
 }


/* Local variables store date and time values 
as a number */
int year, month, day, 
hours, minutes, seconds;

/* A local variable detect error 
in the command line */ 
int error = 0, errText = 0;

/* Local variables store the name of 
input and output file without extension */
char new_inp[50], new_outp[50];

clock_t t;
double time_taken;
/* Perform -h command */
void h_command(){
    FILE *fptr;
    char c;

    /* Open readme file for reading */
    fptr = fopen("readme.txt", "r");
    c = fgetc(fptr);
    
    /* Print the content from readme.txt file */
    while (c != EOF)
        {
            printf ("%c", c); 
            c = fgetc(fptr);
        }
  
        fclose(fptr);   

}

/* Perform -t command */
void t_command(char **s){
    const char *inp, *outp;
    FILE *fp;
    char ans;
    int ansn = 1;
    fp = fopen(s[1], "r");
    t = clock();
 
    inp = s[1];
    outp = s[2];

    if (fopen(s[1],"r") == NULL) {
        printf("Error XX: %s could not be opened\n", s[1]);
        error = 1;
    }

    else {
        if (fopen(s[2], "r") != NULL){
            printf("Warning: %s already exists. Do you wish to overwrite (y, n)? ", s[2]);
            ans = getchar();
            ansn = 0;
            if (ans == 'y'){
                ansn = 1;
            }
            else{
                error = 1;
            }
        }
        if (ansn == 1) {
            text_morseFILE(inp, outp);
            err_textF(inp);
        }
    };

    fclose(fp);

    
    t = clock() - t;
    time_taken = ((double) t)/CLOCKS_PER_SEC;
}

void m_command(char **s){
    const char *inp, *outp;
    FILE *fp;
    char ans;
    int ansn = 1;
    fp = fopen(s[1], "r");
    t = clock();
 
    inp = s[1];
    outp = s[2];

    if (fopen(s[1],"r") == NULL) {
        printf("Error XX: %s could not be opened\n", s[1]);
        error = 1;
    }

    else {
        if (fopen(s[2], "r") != NULL){
            printf("Warning: %s already exists. Do you wish to overwrite (y, n)? ", s[2]);
            ans = getchar();
            ansn = 0;
            if (ans == 'y'){
                ansn = 1;
            }
            else{
                error = 1;
            }
        }
        if (ansn == 1) {
            morse_textFILE(inp, outp);
            err_morse(inp);
        }
    };

    fclose(fp);
    
    t = clock() - t;
    time_taken = ((double) t)/CLOCKS_PER_SEC;
}

// print out date and time
void current_time(FILE *fp){
    /* the variable store month 
    as a word */
    char cmonth[6];

    /* time_t is arithmetic time type */
    time_t now;

    /* time() returns the current time of
    the system as a time_t value */
    time(&now);

    /* Localtime converts a time_t value to calendar time */
    struct tm *local = localtime(&now);

    hours = local->tm_hour;             /* Get hours (0 - 23)   */
    minutes = local->tm_min;            /* Get minutes (0 - 59) */
    seconds = local->tm_sec;            /* Get seconds (0 - 59) */

    day = local->tm_mday;               /* Get day (1 to 31)    */
    month = local -> tm_mon + 1;        /* Get month (0 to 11)  */
    year = local -> tm_year + 1900;     /* Get year since 1900  */

    /* Convert month 
    from number to word */ 
    switch (month)
    {
    case 1:
        strcpy(cmonth,"Jan");
        break;
    case 2:
        strcpy(cmonth,"Feb");
        break;
    case 3:
        strcpy(cmonth,"Mar");
        break;
    case 4:
        strcpy(cmonth,"Apr");
        break;
    case 5:
        strcpy(cmonth,"May");
        break;
    case 6:
        strcpy(cmonth,"Jun");
        break;
    case 7:
        strcpy(cmonth,"Jul");
        break;
    case 8:
        strcpy(cmonth,"Aug");
        break;
    case 9:
        strcpy(cmonth,"Sep");
        break;
    case 10:
        strcpy(cmonth,"Oct");
        break;
    case 11:
        strcpy(cmonth,"Nov");
        break;
    case 12:
        strcpy(cmonth,"Dec");
        break;
    default:
        break;
    }

    /* Print out date and time */
    fprintf(fp ,"Time complete is: %d-%s-%02d  %02d:%02d:%02d \n",
    year, cmonth, day, hours, minutes, seconds);
}

/* Remove file extension of
input and output */
void rm_extension(char *s, char *s1){
    int i, j = 0;
    char duoi[2] = ".";
    int siz = strlen(s);
    int siz1 = strlen(s1);
    
    /* Return new_inp as the name of
    the input file without file extension */
    for (int i = 0; i < siz; i++){
        if(strstr(&s[i],duoi) == &s[i]){
            break;
        }
        else{
            new_inp[j++] = s[i];
        }
    }
    new_inp[j] = '\0';
    j = 0;
    
    /* Return new_outp as the name of
    the output file without file extension */
    for (int i = 0; i < siz1; i++){
        if(strstr(&s1[i],duoi) == &s1[i]){
            break;
        }
        else{
            new_outp[j++] = s1[i];
        }
    }
}

/* Rename log file of -c flag */
void rename_log(char **s) {
    
    char old_name[] = "data.log";
    
    /* Variables store values in the char type */
    char cyear[10], cmonth[10], cday[10], 
    chours[10], cminutes[10], cseconds[10];

    /* Convert int to char */
    itoa(year, cyear, 10);
    itoa(month, cmonth, 10);
    itoa(day, cday, 10);
    itoa(hours, chours, 10);
    itoa(minutes, cminutes, 10);
    itoa(seconds, cseconds, 10);

    rm_extension(s[1], s[2]);

    /* Combine components of 
    the name of log file */
    strcat(new_inp, "_");
    strcat(new_inp, new_outp);
    strcat(new_inp, "_");
    strcat(new_inp, cyear);
    strcat(new_inp, cmonth);
    strcat(new_inp, cday);
    strcat(new_inp, "_");
    strcat(new_inp, chours);
    strcat(new_inp, cminutes);
    strcat(new_inp, cseconds);
    strcat(new_inp, ".log");

    /* Change the name of log file */
    rename(old_name, new_inp);
}

/* Perform -c command */
void c_command(char **s) { 
    FILE *fp, *finp;
    int m_mis = 1, letter_count = 0, char_count = 0,
    pre_space = 0, first_time = 0, word_count = 0;
    char c;

    finp = fopen(s[1], "r");
    c = fgetc(finp);
    
    while (c != EOF) {
        if (c != ' ' && c != '\n') {
            char_count++;
        };
            
        if ((pre_space == 1 || first_time == 0) 
        && (('a'<=c && c <= 'z') || ('A' <= c && c <= 'Z'))){
            word_count++;
            first_time = 1;
            pre_space = 0;
        };
            
        if (c == ' ' || c == '\n') {
            pre_space = 1;
        };

        if (c != '.' && c != '/' && c != '-' && c != ' ' && c != '\n') {
            m_mis = 0;
            letter_count ++;
        };

        c = fgetc(finp);
    };

    if (m_mis == 1)
        m_command(s);
    
    else 
        t_command(s);
    
    if (error == 1) {
        return;
    }

    /* The initial log file of -c flag */
    fp = fopen ("data.log", "w");

    fprintf(fp, "Input file: %s\n", s[1]);  /* Get name of the input file */
    fprintf(fp, "Output file: %s\n", s[2]); /* Get name of the output file */
    
    /* Print date and time to data.log file */
    current_time(fp);  

    fprintf(fp, "Duration [seconds]: %f\n", time_taken);
    fprintf(fp, "Word count in input file: %d\n", word_count);
    fprintf(fp, "Word with error: %d\n", errchar);
    fprintf(fp, "Total number of characters: %d\n", char_count);

    fclose(fp);
    fclose(finp);
    /* Rename data.log file */
    rename_log(s);
}

/* Perform the command line
or detect errors in the command line */

void option_error(int n, char **s){
    int m_mis = 0;
    
    /* Error: Unrecognized command. */
    if (n == 1){
        printf("Error XX: Unrecognized command. Type “morse –h” for help \n");
        error = 1;
        return;
    }

    /* perform -h flag */
    else if (n == 2 && !(strcmp(s[n - 1],"-h"))){
        h_command();
    }
    else if(n > 2 && !(strcmp(s[n - 1], "-h"))){
        printf("Type “morse –h” for help");
    }

    else if (n == 3 && (strcmp(s[n - 1], "-c")
    && strcmp(s[n - 1], "-m")
    && strcmp(s[n - 1], "-t"))){
        c_command(s);
    }

    /* error: missing arguments */
    else if(n < 4 && (!strcmp(s[n - 1], "-t")
    || !strcmp(s[n - 1], "-m")
    || !strcmp(s[n - 1], "-c"))){
        printf("Error XX: Missing arguments. Type “morse –h” for help"); 
        error = 1;
    }

    /* error: more than 4 arguments */
    else if(n > 4){
        printf("Error XX: Too many arguments. Type “morse –h” for help"); 
        error = 1;
    }

    /* perform -t flag */
    else if(!(strcmp(s[3],"-t"))){
        t_command(s);
    }

    /* perform -m flag */
    else if(!(strcmp(s[3],"-m"))){
        m_command(s);
    }

    /* perform -c flag */
    else if(!(strcmp(s[3],"-c"))){
        c_command(s);
    }
    
    /* Error: Unknown command */ 
    else if(n == 4 
    && ((strcmp(s[3],"-t"))
    ||(strcmp(s[3],"-m"))
    ||(strcmp(s[3],"-c")))){
        printf("Error XX: Unknown command. Type “morse –h” for help");
        error = 1;
    }

    else{
        printf("Type “morse –h” for help\n");
        error = 1;
    }
}

int main(int argc, char *argv[]){
    // int i, t_mis = 0, m_mis = 0, c_mis = 0;
    

    /* Peform the command line or
    detect errors in the command line */
    option_error(argc, argv);
    
    /* If error, the program exits */
    if(error == 1){
        return 1;
    }

    return 0;

}