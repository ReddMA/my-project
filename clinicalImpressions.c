/*
Description: Clinnical Impressions referred to as the initial opinion of a doctor 
after examining a patient.
    Programmed by: Rafael Antonio M. Austria S15B
                   Dlareinnej Jherby C. Jaime S15B
    Last modified: 6/16/2022
    Version: 7
    [Acknowledgements:Learning Structs- https://www.youtube.com/watch?
v=7zXqMD6Fj_E&list=LL&index=12
                                       - https://www.youtube.com/watch?v=-
Vy4qrl675E&t=76s
                        Learning functions like strtok, atoi, and fseek - 
https://www.tutorialspoint.com/cprogramming/index.htm 
    This is to certify that this project is my own work, based on my personal 
efforts in studying and
    applying the concepts learned. I have constructed the functions and their 
respective algorithms
    and corresponding code by myself. The program was run, tested, and debugged by 
my own efforts. I
    further certify that I have not copied in part or whole or otherwise 
plagiarized the work of other
    students and/or persons.
    Rafael Antonio M. Austria, 12194085
    Dlareinnej Jherby C. Jaime, 12175005
    
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXsymp 20
#define MAXimpr 20
typedef char string[50];
struct Symptom {
    string name;
    string question;
    int index;
    int numOfSymp;
};
struct Impression {
    string illnessName;
    int sympCount;
    struct Symptom symptoms[MAXsymp];
    int patientReportedSymptom;
    int numOfImp;
};
struct Patient {
    string name;
    int number;
    int age;
    char gender;
    int sympCount;
    int impCount;
    struct Impression impressions[MAXimpr];
    struct Symptom symptoms[MAXsymp];
};
void patientMenu();
int extractImpressionsTxt (struct Impression* impression, struct Symptom* 
symptoms);
int extractSymptomsTxt (struct Symptom* symptoms);
struct Patient checkPatient(struct Symptom *symptoms, struct Patient patient, int 
sympCount);
struct Patient reportImpression(struct Patient patient, struct Impression 
*impressions, int impCount);
void displayMenu1();
void docMenu(struct Symptom symptoms[], struct Impression impressions[], int 
*numSymps, int *numImpressions);
void print_impression(struct Impression impression);
void displayDocMenu();
char getInput();
int inputSymptoms(struct Symptom *symptoms);
int inputImpressions(struct Impression impressions[], struct Symptom symptoms[], 
int numSymps);
void getImpressionDetails(struct Impression impressions[], int impressionCount);
void modifyImpression(struct Impression impressions[], struct Symptom 
symptoms[],int impressionCount, int symptomsCount);
void patientDiagnosis(struct Patient symptom, struct Impression symotoms[]);
struct Patient enterPatientInformation();
int textFileChecker();
void printSymptomsToFile(struct Symptom symptoms[], int numSymps);
void printImpressionToFile(struct Impression impressions[], struct Symptom 
symptoms[], int numImpressions, int numberOfSymptoms);
void impressionInput(struct Impression impressions[], string 
inputtedImpressionName);
void printModifiedImpressions(struct Impression impressions, struct Symptom 
symptoms[]);
void printPatientInfoToFile (struct Patient patient);
void printHPI (struct Patient patient);
int main()
{
    struct Symptom symptoms[MAXsymp];
    struct Impression impressions[MAXimpr];
    int numSymps = 0;
    int numImpress = 0;
    char cMenuInput;
    do
    {
        displayMenu1();
        scanf(" %c", &cMenuInput);
        if(cMenuInput == 'D')
        {
            docMenu(symptoms, impressions, &numSymps, &numImpress);
        }
        if(cMenuInput == 'P')
        {
            patientMenu();
        }
        if(cMenuInput == 'E')
        {
            printf("\nThank you for your cooperation.");
        }
    } while(cMenuInput != 'E');
    return 0;
}
/*
    patientMenu calls out necessary functions to update data in the patient struct
*/
void
patientMenu()
{
    struct Symptom symptoms[MAXsymp];
    struct Impression impressions[MAXimpr];
    struct Patient patient;
    int sympCount = 0;
    int impCount = 0;
    sympCount = extractSymptomsTxt(symptoms);
    impCount = extractImpressionsTxt(impressions, symptoms);
    if(impressions->sympCount > 0)
    {
        patient = enterPatientInformation();
        patient = checkPatient(symptoms, patient, sympCount);
        patient = reportImpression(patient, impressions, impCount);
        printHPI (patient);
        printPatientInfoToFile(patient);
    }
    else
    {
        printf("Invalid! No symptoms or impressions detected.\n");
    }
}
/*
    displayMenu1 displays the menu#1 user type 
*/
void
displayMenu1()
{
    printf("\nMenu #1 User type\n");
    printf("D for Doctor\n");
    printf("P for Patient\n");
    printf("E for Exit\n");
    printf("Enter your choice: ");
}
/*
    print_impression prints out symptoms of an impression
    @param impressions - conatins the variable of illness name, symptom count, and 
symptom name array in struct Impression
*/
void
print_impression(struct Impression impressions)
{
    int i;
    printf("Illness: %s\n", impressions.illnessName);
    for(i = 0; i < impressions.sympCount; ++i)
    {
        printf("Symptom %d: %s\n", i+1, impressions.symptoms[i].name);
    }
}
/*
    displayDocMenu displays the menu#2 doctor menu
*/
void
displayDocMenu()
{
    printf("\nMenu #2 Doctor\n");
    printf("\nC to Create a new list of symptoms and impressions\n");
    printf("U to Use the existing list of symptoms and impressions\n");
    printf("D to display symptoms\n");
    printf("M to modify symptoms\n");
    printf("E to return to Main Menu\n");
}
/*
    docMenu contains the functions for doctor
    @param symptoms[] - contains the array element of inputted symptoms in struct 
Symptom
    @param impressions[] - contains the array element of inputted impressions in 
struct Impression
    @param numSymps - is the overall number of symptoms
    @param numImpressions - is the overall number of impressions
*/
void
docMenu(struct Symptom symptoms[], 
        struct Impression impressions[], 
        int *numSymps, 
        int *numImpressions)
{
    char input;
    do {
        displayDocMenu();
        input = getInput();
        getchar();
        switch (input) {
            case 'C': {
                getchar();
                *numSymps = inputSymptoms(symptoms);
                printSymptomsToFile(symptoms, *numSymps);
                *numImpressions = inputImpressions(impressions, symptoms, 
*numSymps);
                break;
            }
            case 'U': {
                if (textFileChecker() == 1)
                {
                    *numSymps = extractSymptomsTxt(symptoms);
                    *numImpressions = extractImpressionsTxt(impressions, symptoms);
                    printf("Files have been extracted.\n");
                }
                else
                    printf("Files does not exist or are incomplete\n");
                getchar();
                break;
            }
            case 'D': {
                getImpressionDetails(impressions, *numImpressions);
                break;
            }
            case 'M': {
                modifyImpression(impressions, symptoms, *numImpressions, 
*numSymps);
                getchar();
                break;
            }
            case 'E': {
                getchar();
                break;
            }
            default: {
                printf("Invalid input! Input a valid choice.\n");
                break;
            }
        }
    } while(input != 'E' && input != 'U');
}
/*
    getInput gets the input for the doctor menu
    return input if the input is valid
*/
char
getInput()
{
    char input;
    while(input != 'C' && input != 'U' && input != 'D' && input != 'M' && input != 
'E')
    {
        getchar();
        printf("Enter your choice: ");
        scanf("%c", &input);
    }
    return input;
}
/*
    inputSymptoms returns the inputted number of symptoms
    @param symptoms - contains the array for the symptoms
    return numSymps updates the general number of symptoms
*/
int
inputSymptoms(struct Symptom *symptoms)
{
    int numSymps = 0;
    int i;
    do {
        printf("How many symptoms do you want to consider? ");
        scanf("%d", &numSymps);
        if(numSymps > MAXsymp || numSymps <= 0)
        {
            printf("Invalid number of symptoms!\n");
        }
    } while (numSymps > MAXsymp || numSymps <= 0);
    for(i = 0; i < numSymps; ++i) {
        getchar();
        printf("What is your symptom? ");
        scanf("%[^\n]s", symptoms[i].name);
        getchar();
        printf("How do you want to ask the question?\n");
        scanf("%[^\n]s", symptoms[i].question);
        symptoms[i].index = i+1;
    }
    return numSymps;
}
/*
    printImpressionToFile prints the date of struct impression to impressions.txt
    @param symptoms[] - contains the symptom name of the symptoms array in struct 
Symptom
    @param numSymps - is the general number of symptoms
*/
void
printSymptomsToFile(struct Symptom symptoms[], 
                    int numSymps)
{
    FILE *file;
    int i;
    file = fopen("Symptoms.txt", "w");
    fprintf(file, "%d\n", numSymps);
    for(i = 0; i < numSymps; i++) {
        fprintf(file, "%d\n", i+1);
        fprintf(file, "%s\n", symptoms[i].name);
        fprintf(file, "%s\n", symptoms[i].question);
    }
    fclose(file);
}
/*
    impressionChecker returns the index of the impression array if it matches the 
impression element in the array
    @param impressions[] - contains the illness name of the impression from the 
impression array in struct Impression
    @param impressionInput - is the inputted impression name to be compared
    returns -1 if the index is not valid
*/
int
impressionChecker(struct Impression impressions[],
                  string impressionInput)
{
    int i;
    for(i = 0; i < MAXimpr; i++)
    {
        if(strcmp(impressionInput, impressions[i].illnessName) == 0)
        {
            return i;
        }
    }
    return -1;
}
/*
    inputImpressions returns the number of inputted impressions 
    @param impressions[] - contains the illness name, and symptom count of the 
impression array in struct Impression
    @param symptoms[] - contains the symptom name of the symptoms array in struct 
Symptom
    @param numSymps - is the general number of symptoms
    return numImpressions if number of impressions is valid
*/
int
inputImpressions(struct Impression impressions[],
                 struct Symptom symptoms[],
                 int numSymps)
{
    int numImpressions = 0;
    int numberOfSymptoms = 0;
    do {
        printf("How many impressions do you want to enter? ");
        scanf("%d", &numImpressions);
        if(numImpressions > MAXimpr ||numImpressions <= 0) {
            printf("Invalid number of impressions!\n");
        }
    } while (numImpressions > MAXimpr || numImpressions <= 0);
    impressions->numOfImp = numImpressions;
    for(int i = 0; i < numImpressions; ++i)
    {
        getchar();
        printf("What is the illness? ");
        scanf("%[^\n]s", impressions[i].illnessName);
        getchar();
        printf("Below is the list of symptoms.\n");
        printf("\n");
        int position = 1;
        for(int j = 0; j < numSymps; j++)
        {
            printf("%d. %s\n", position++, symptoms[j].name);
        }
        do {
            printf("How many symptoms do you want to enter? ");
            scanf("%d", &numberOfSymptoms);
            if(numberOfSymptoms > MAXsymp || numberOfSymptoms <= 0)
            {
                printf("Invalid number of symptoms!\n");
            }
        } while (numberOfSymptoms > MAXsymp || numberOfSymptoms <= 0);
        impressions[i].sympCount = numberOfSymptoms;
        for(int k = 0; k < numberOfSymptoms; ++k)
        {
            int symptomNum = 0;
            do {
                printf("Enter the number that correspond to the symptom: ");
                scanf("%d", &symptomNum);
                if(symptomNum > numSymps || symptomNum <= 0)
                {
                    printf("\nInvalid number of symptoms, Input a valid one.\n");
                }
                else
                {
                    impressions[i].symptoms[k] = symptoms[symptomNum - 1];
                }
            } while (symptomNum > numSymps || symptomNum <= 0);
        }
    }
    printImpressionToFile(impressions, symptoms, numImpressions, numberOfSymptoms);
    return numImpressions;
}
/*
    printImpressionToFile prints the date of struct impression to impressions.txt
    @param impressions[] - contains the illness name, and symptom count of the 
impression array in struct Impression
    @param symptoms[] - contains the symptom name of the symptoms array in struct 
Symptom
    @param numImpressions - is the general number of impressions
    @param numberOfSymptoms - is the general number of symptoms
*/
void
printImpressionToFile(struct Impression impressions[], 
                        struct Symptom symptoms[], 
                        int numImpressions, 
                        int numberOfSymptoms)
{
    FILE *file;
    int i;
    int j;
    file = fopen("Impressions.txt", "w");
    fprintf(file, "%d\n", numImpressions);
    for (i = 0; i < numImpressions; ++i){
        fprintf(file, "%d\n", i+1);
        fprintf(file, "%s\n", impressions[i].illnessName);
        for (j = 0; j < impressions[i].sympCount; ++j){
            fprintf(file, "%d ", impressions[i].symptoms[j].index);
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
}
/*
    getImpressionDetails displays the impression and its symptoms
    @param impressions[] - contains the impression array to access the impression 
element in struct Impression
    @param impressionCount - is the general number of impressions
*/
void
getImpressionDetails(struct Impression impressions[], 
                    int impressionCount)
{
    int index;
    getchar();
    string inputtedImpressionName;
    if(impressions->sympCount > 0)
    {
        printf("What is the impression? ");
        scanf("%[^\n]s", inputtedImpressionName);
        index = impressionChecker(impressions, inputtedImpressionName);
        if(index != -1)
        {
            print_impression(impressions[index]);
        }
        else
        {
            printf("Invalid Impression! Input a valid one!\n");
            getImpressionDetails(impressions, impressionCount);
        }
    }
    else
    {
        printf("Invalid! No symptoms or impressions detected.\n");
    }
}
/*
    impressionInput inputs an impression name and updates impression name if valid
    @param impressions[] - contains the impression array to access the impression 
element in struct Impression
    @param inputtedImpressionName - is the inputted impression name to be compared 
*/
void
impressionInput(struct Impression impressions[],
                string inputtedImpressionName)
{
    string input;
    printf("What is the Impression? ");
    scanf(" %[^\n]", input);
    if(impressionChecker(impressions, input) == -1){
        printf("Wrong input, try again.\n\n");
        impressionInput(impressions, inputtedImpressionName);
    }
    else{
        strcpy(inputtedImpressionName, input);
    }
}
/*
    modifyImpression modifies the current impression and its symptoms
    @param impressions[] - contains the illness name, and symptom count of the 
impression array in struct Impression
    @param symptoms[] - contains the symptom name, and symptom array in struct 
Symptom
    @param impressionCount - is the general number of impressions
    @param symptoms - is the general number of symptoms
*/
void 
modifyImpression(struct Impression impressions[], 
                struct Symptom symptoms[], 
                int impressionCount, 
                int symptomsCount)
{
    int i;
    getchar();
    string inputtedImpressionName;
    impressionInput(impressions, inputtedImpressionName);
    int index = impressionChecker(impressions, inputtedImpressionName);
    printf("Below is the list of symptoms.\n");
    for (i = 0; i < symptomsCount; ++i) {
        printf("%d. %s\n", i+1, symptoms[i].name);
    }
    int newNumSymps = 0;
    printf("How many of the symptoms above are present in a/an %s case? ", 
impressions[index].illnessName);
    scanf("%d", &newNumSymps);
    impressions[index].sympCount = newNumSymps;
    for (i = 0; i < newNumSymps; ++i) {
        int inputtedSymptomNum = 0;
        do {
            printf("Enter the corresponding number of each symptom: ");
            scanf("%d", &inputtedSymptomNum);
            if(inputtedSymptomNum > symptomsCount || inputtedSymptomNum <= 0)
            {
                printf("Enter a valid symptom number\n");
            }
        } while (inputtedSymptomNum > symptomsCount || inputtedSymptomNum <= 0);
        impressions[index].symptoms[i] = symptoms[inputtedSymptomNum - 1];
    }
    printModifiedImpressions(impressions[index], symptoms);
}
/*
    printModifiedImpressions updates the modified impression and its symptoms to 
impressions.txt
    @param impressions[] - contains the illness name, and symptom count of the 
impression array in struct Impression
    @param symptoms[] - contains the symptom name, and symptom array in struct 
Symptom
*/
void 
printModifiedImpressions(struct Impression impressions, 
                        struct Symptom symptoms[]) 
{
    FILE *file;
    FILE *file2;
    string token;
    string token2;
    int i;
    file = fopen("Impressions.txt", "r+");
    file2 = fopen("Temp.txt", "w");
    while((fscanf(file, " %[^\n]", token)) == 1){
        fprintf(file2, "%s\n", token);
        printf("%s %s\n", token, impressions.illnessName);
        if(strcmp(token, impressions.illnessName) == 0){
            printf("%d", impressions.sympCount);
            for (i = 0; i < impressions.sympCount; ++i){
                printf("%d", impressions.symptoms[i].index);
                fprintf(file2, "%d ", impressions.symptoms[i].index);
            }
            fprintf(file2, "\n");
            fscanf(file, " %[^\n]", token2);
        }
    }
    fclose(file);
    fclose(file2);
    remove("Impressions.txt");
    rename("Temp.txt", "Impressions.txt");
}
/*
    enterPatientInformation asks for basic patient information of user
    return patient updates the variable patient after the function
*/
struct 
Patient enterPatientInformation()
{
    struct Patient patient;
    printf("What is your name? ");
    scanf(" %[^\n]s", patient.name);
    getchar();
    printf("What is your patient number? ");
    scanf("%d", &patient.number);
    getchar();
    printf("Enter your age: ");
    scanf("%d", &patient.age);
    getchar();
    printf("Gender (M/F): ");
    scanf("%c", &patient.gender);
    getchar();
    return patient;
}
/*
    printPatientInfoToFile print the data of the struct Patient to a txt file
    @param patient - contains the variables of struct Patient to the variable 
patient
*/
void 
printPatientInfoToFile (struct Patient patient)
{
    FILE *file;
    string filename;
    int i;
    sprintf(filename, "%d.txt", patient.number);
    file = fopen(filename, "w");
    fprintf(file,"\n         HISTORY OF PRESENT ILLNESS\n");
    fprintf(file, "\n%s,", patient.name);
    fprintf(file, "patient # %d ", patient.number);
    fprintf(file, "is a %d-year old ", patient.age);
    if(patient.gender == 'M')
        fprintf(file, "male. He has");
    else
        fprintf(file, "female. She has");
    for (i=0; i<patient.sympCount; i++){
        fprintf(file, " %s", patient.symptoms[i].name);
        if(i<patient.sympCount-2)
            fprintf(file, ",");
        else if (i<patient.sympCount-1)
            fprintf(file, " and");
    }
    if (patient.sympCount <= 0)
        fprintf(file, " no symptoms");
    fprintf(file, ". Impressions are");
    for (i=0; i<patient.impCount; i++){
        fprintf(file, " %s", patient.impressions[i].illnessName);
        if(i<patient.impCount-2)
            fprintf(file, ",");
        else if (i<patient.impCount-1)
            fprintf(file, " and");
    }
    if (patient.impCount <= 0)
        fprintf(file, " not applicable");
    fprintf(file, ".");
    fclose(file);
}
/*
    printHPI prints History of Patient Illness
    @param patient - contains the variables of struct Patient to the variable 
patient
*/
void 
printHPI (struct Patient patient)
{
    int i;
    printf("\n         HISTORY OF PRESENT ILLNESS\n");
    printf("%s, patient # %d is a %d-year old ", patient.name, patient.number, 
patient.age);
    if (patient.gender == 'M')
        printf("male. He has");
    else
        printf("female. She has");
    for (i=0; i<patient.sympCount; i++){
        printf(" %s", patient.symptoms[i].name);
        if(i<patient.sympCount-2)
            printf(",");
        else if (i<patient.sympCount-1)
            printf(" and");
    }
    if (patient.sympCount <= 0)
        printf(" no symptoms");
    printf(". Impressions are");
    for (i=0; i<patient.impCount; i++){
        printf(" %s", patient.impressions[i].illnessName);
        if(i<patient.impCount-2)
            printf(",");
        else if (i<patient.impCount-1)
            printf(" and");
    }
    if (patient.impCount <= 0)
        printf(" not applicable");
    printf(".");
}
/*
    checkPatient asks the user the questions of the symptom to diagnose
    @param symptoms - contains the name, and question in struct Symptom
    @param patient - contains the struct Patient variable to be updated
    @param sympCount - is the general number of symptoms
    return patient updates the variable patient after the function
*/
struct 
Patient checkPatient(struct Symptom *symptoms, 
                    struct Patient patient, 
                    int sympCount)
{
    char answer;
    patient.sympCount = 0;
    int i;
    for(i = 0; i < sympCount; ++i)
    {
        printf("%s ", symptoms[i].question);
        scanf("%c", &answer);
        answer = toupper(answer);
        if(answer == 'Y') {
            patient.symptoms[patient.sympCount] = symptoms[i];
            patient.sympCount++;
        }
        getchar();
    }
    return patient;
}
/*
    reportImpression compares the symptoms of the patient to the impression to 
diagnose the user of the impression
    @param patient - contains the struct Patient variable to be updated
    @param impressions - contains the reported symptom that is equal to the patient
symptom
    @param impCount - is the general number of impressions
    return patient updates the variable patient after the function
*/
struct 
Patient reportImpression(struct Patient patient, 
                    struct Impression *impressions, 
                    int impCount)
{
    patient.impCount = 0;
    int i;
    int j;
    int k;
    for(i = 0; i < impCount; i++)
    {
        impressions[i].patientReportedSymptom = 0;
        for(j = 0; j < patient.sympCount; j++)
        {
            for(k = 0; k < impressions[i].sympCount; k++)
            {
                if(strcmp(patient.symptoms[j].name, 
impressions[i].symptoms[k].name) == 0)
                {
                    impressions[i].patientReportedSymptom++;
                }
            }
        }
        if(impressions[i].patientReportedSymptom == impressions[i].sympCount)
        {
            patient.impressions[patient.impCount] = impressions[i];
            patient.impCount++;
        }
    }
    return patient;
}
/*
    textFileChecker checks if symptoms.txt and impressions.txt exist or contains 
data
    return 0 if symptoms.txt and impressions.txt does not exist or does not 
contains data
    return 1 if symptoms.txt and impressions.txt exists and contains data
*/
int 
textFileChecker()
{
    FILE *symptoms;
    FILE *impressions;
    int sizeOfSymp;
    int sizeOfImp;
    symptoms = fopen("Symptoms.txt", "r");
    impressions = fopen("Impressions.txt", "r");
    if ((symptoms == NULL) || (impressions == NULL))
        return 0;
    else
    {
        fseek(symptoms, 0, SEEK_END);
        sizeOfSymp = ftell(symptoms);
        fseek(symptoms, 0, SEEK_SET);
        fseek(impressions, 0, SEEK_END);
        sizeOfImp = ftell(impressions);
        fseek(impressions, 0, SEEK_SET);
        if (sizeOfSymp == 0 || sizeOfImp == 0)
            return 0;
    }
    fclose(symptoms);
    fclose(impressions);
    return 1;
}
/*
    extractSymptomsTxt extracts the data of symptom.txt and puts the data in the 
struct symptom
    @param symptoms[] - contains the array element of inputted symptoms
    return sympCount if sympCount is valid
*/
int 
extractSymptomsTxt (struct Symptom* symptoms)
{
    FILE *file;
    int i;
    int sympCount;
    file = fopen("Symptoms.txt", "r");
    fscanf(file, "%d", &sympCount);
    for (i=0; i<sympCount; i++){
        fscanf(file, "%d", &symptoms[i].index);
        fscanf(file, " %[^\n]", symptoms[i].name);
        fscanf(file, " %[^\n]", symptoms[i].question);
    }
    fclose(file);
    return sympCount;
}
/*
    extractImpressionsTxt extracts the data of impressions.txt and puts the data in
the struct impression
    @param impressions[] - contains the array element of inputted impressions
    @param symptoms[] - contains the array element of inputted symptoms
    return impCount if impCount is valid
*/
int 
extractImpressionsTxt (struct Impression impression[], 
                    struct Symptom symptoms[])
{
    FILE *file;
    int i;
    int impIndex;
    string symptomsholder;
    char *token;
    int impCount;
    file = fopen("Impressions.txt", "r");
    fscanf(file, "%d", &impCount);
    for (i=0; i<impCount; i++){
        fscanf(file, "%d", &impIndex);
        fscanf(file, " %[^\n]", impression[i].illnessName);
        fscanf(file, " %[^\n]", symptomsholder);
        impression[i].sympCount = 0;
        token = strtok(symptomsholder, " ");
        while( token != NULL ) {
            impression[i].symptoms[impression[i].sympCount] =  symptoms[atoi(token)
- 1];
            impression[i].sympCount++;
            token = strtok(NULL, " ");
        }
    }
    fclose(file);
    return impCount;
}
/*  
    This is to certify that this project is my own work, based on my personal 
efforts in studying and
    applying the concepts learned. I have constructed the functions and their 
respective algorithms
    and corresponding code by myself. The program was run, tested, and debugged by 
my own efforts. I
    further certify that I have not copied in part or whole or otherwise 
plagiarized the work of other
    students and/or persons.
    Rafael Antonio M. Austria, 12194085
    Dlareinnej Jherby C. Jaime, 12175005
*/
