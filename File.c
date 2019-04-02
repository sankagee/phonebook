#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100
#define BUFFER_SIZE 1000

void replaceAll(char *str, const char *oldWord, const char *newWord);
void removeAll(char * str, const char * toRemove);

void strtolower(char *str)
{
    int len = strlen(str);
    int i;
    for(i=0; i<len; i++) {
        str[i] = tolower(str[i]);
    }
}

typedef struct {
    char firstName[40];
    char lastName[40];
    char mobileNumber[20];
} Contact;

typedef enum { FIRST_NAME, LAST_NAME, MOBILE_NUMBER } search_t;


int main()
{
    char selection[41];
    int choice;
    while(1){
        puts("PhoneBook application main menu.");
        puts("    1. Add New Contact");
        puts("    2. Display All contact");
        puts("    3. Search by First Name");
        puts("    4. Search by Last Name");
        puts("    5. Search by Mobile Number");
        puts("    6. Delete a contact ");
        puts("    7. Modify Contact");

        printf("Enter your choice: ");
        gets(selection);
        choice = atoi(selection);

        switch(choice)
        {
        case 1:
            addEntry();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            printf("Enter first name to search: ");
            gets(selection);
            search(selection, FIRST_NAME);
            break;
        case 4:
            printf("Enter last name to search: ");
            gets(selection);
            search(selection, LAST_NAME);
            break;
        case 5:
            printf("Enter mobile number to search: ");
            gets(selection);
            search(selection, MOBILE_NUMBER);
            break;
        case 6:
            deletecontact();
            void removeAll(char * str, const char * toRemove);
            break;
        case 7:
            modifycon();
            void replaceAll(char *str, const char *oldWord, const char *newWord);
            break;
        default:
            break;
        }
    }
    return 0;
}

Contact phonebook[MAX_SIZE];
int currentSize = 0;

void addEntry()
{
    char fname[50];
    char lname[50];
    int num;

    FILE *fptr;
    fptr = (fopen("student.txt", "a"));
    printf("Enter first name: ");
    scanf("%s",&fname);
    printf("Enter last name: ");
    scanf("%s",&lname);
    printf("Enter Telephone Number: ");
    scanf("%d", &num);
    fprintf(fptr,"\nfirstName: %s \nlastName: %s \nNumber=%d \n", fname, lname, num );
    fclose(fptr);
    printf("Add Contact Is Successful");

}

void display(int index)
{
    if(index < 0 || index >= currentSize) {
        puts("Error: invalid index!");
        return;
    }

    Contact c = phonebook[index];
    printf("First Name: %s\n", c.firstName);
    printf("Last Name : %s\n", c.lastName);
    printf("Mobile No : %s\n", c.mobileNumber);


}

void displayAll()
{
    FILE* fileread;
    fileread=fopen("student.txt","r");
    char name[999];
    while(!feof(fileread))
    {
        fgets(name,999,fileread);
        puts(name);
    }
    fclose(fileread);
return 0;

}

void search(char *key, search_t type)
{
    int found = 0;
    int i;

    strtolower(key);
    char content[41];

    if(type == FIRST_NAME) {
        for(i=0; i<currentSize; i++) {

            strcpy(content, phonebook[i].firstName);
            strtolower(content);

            if(strcmp(content, key) == 0) {
                display(i);
                found = 1;
            }
        }
    }
    else if(type == LAST_NAME) {
        for(i=0; i<currentSize; i++) {
            strcpy(content, phonebook[i].lastName);
            strtolower(content);

            if(strcmp(content, key) == 0) {
                display(i);
                found = 1;
            }
        }
    }
    else if(type  == MOBILE_NUMBER) { // search by mobile number
        for(i=0; i<currentSize; i++) {
            strcpy(content, phonebook[i].mobileNumber);
            strtolower(content);

            if(strcmp(content, key) == 0) {
                display(i);
                found = 1;
            }
        }
    }

    else {
        puts("Error: invalid search type!");
        return;
    }

    if(!found) {
        puts("Not found in the phone book");
    }

}

int deletecontact()
{
    FILE * fPtr;
    FILE * fTemp;
    char path[100];
    char toRemove[100];
    char buffer[1000];
    printf("Enter word to remove: ");
    scanf("%s", toRemove);
    fPtr  = fopen("student.txt", "r");
    fTemp = fopen("delete.tmp", "w");

    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        removeAll(buffer, toRemove);
        fputs(buffer, fTemp);
    }
    fclose(fPtr);
    fclose(fTemp);
    remove("student.txt");
    rename("delete.tmp", "student.txt");
    printf("\nAll occurrence of '%s' removed successfully.", toRemove);

    return 0;
}
void removeAll(char * str, const char * toRemove)
{
    int i, j, stringLen, toRemoveLen;
    int found;
    stringLen   = strlen(str);
    toRemoveLen = strlen(toRemove);
    for(i=0; i <= stringLen - toRemoveLen; i++)
    {
        found = 1;
        for(j=0; j < toRemoveLen; j++)
        {
            if(str[i + j] != toRemove[j])
            {
                found = 0;
                break;
            }
        }
        if(str[i + j] != ' ' && str[i + j] != '\t' && str[i + j] != '\n' && str[i + j] != '\0')
        {
            found = 0;
        }
        if(found == 1)
        {
            for(j=i; j <= stringLen - toRemoveLen; j++)
            {
                str[j] = str[j + toRemoveLen];
            }
            stringLen = stringLen - toRemoveLen;
            i--;
        }
    }
}

int modifycon()
{
    FILE * fPtr;
    FILE * fTemp;
    char path[100];

    char buffer[BUFFER_SIZE];
    char oldWord[100], newWord[100];

    printf("Enter word to replace: ");
    scanf("%s", oldWord);

    printf("Replace '%s' with: ");
    scanf("%s", newWord);

    fPtr  = fopen("student.txt", "r");
    fTemp = fopen("replace.tmp", "w");
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        replaceAll(buffer, oldWord, newWord);
        fputs(buffer, fTemp);
    }

    fclose(fPtr);
    fclose(fTemp);

    remove("student.txt");
    rename("replace.tmp", "student.txt");
    printf("\nSuccessfully replaced of '%s' with '%s'.", oldWord, newWord);
    return 0;
}
void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newWord);
        strcat(str, temp + index + owlen);
    }
}
