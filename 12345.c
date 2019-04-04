#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

struct person
{
    char fname[35];
    char lname[50];
    long int mble_no;
    char sex[8];
    };

void addrecord();
void listrecord();
void modifyrecord();
void deleterecord();
void searchrecord();

void main()
{
    printf("\t|******************************************************************************|\n");
    printf("\t|                            WELCOME TO PHONEBOOK                              |\n");
    printf("\t|______________________________________________________________________________|\n");
    printf("\n\t\t\t\t\t1.Add New Contact  \n\t\t\t\t\t2.View All Contact  \n\t\t\t\t\t3.Modify Contact \n\t\t\t\t\t4.Search Contact \n\t\t\t\t\t5.Delete Contact\n\t\t\t\t\t6.Exit\n");

switch(getch())
{
    case '1':addrecord();
    break;
   case '2': listrecord();
    break;
    case '3': modifyrecord();
    break;
    case '4': searchrecord();
    break;
    case '5': deleterecord();
    break;
    case '6': exit(0);
    break;
    default :printf("Invalid record press any key to continue");
    getch();
    system("cls");
    main();
}
}
void addrecord()
{
        FILE *f;
        struct person p;
        f=(fopen("contact.txt","a"));

        printf("\nEnter First name : ");
        scanf("%s",&p.fname);
        printf("\nEnter Last name: ");
        scanf("%s",&p.lname);
        printf("\nEnter phone no.:");
        scanf("%ld",&p.mble_no);
        printf("\nEnter sex (M/F):");
        scanf("%s",&p.sex);
        fwrite(&p,sizeof(p),1,f);

        fflush(stdin);
        printf("\nCONTACT SAVED ");

fclose(f);
getch();
system("cls");
main();
}
void listrecord()
{
    struct person p;
    FILE *f;
    f=fopen("contact.txt","rb");
    rewind(f);
    if(f==NULL)
    {
    printf("\nfile opening error in listing :");
    }
while(fread(&p,sizeof(p),1,f)==1)
{
     printf("\n\n\n YOUR RECORD IS\n\n ");
        printf("\nFirst Name=%s\nLast Name=%s\nMobile no=%ld\nSex(M/F)=%s\n",p.fname,p.lname,p.mble_no,p.sex);

}
getch();
system("cls");
main();
}
void searchrecord()
{
    struct person p;
    FILE *f;
    char name[100];

    f=fopen("contact.txt","rb");
    rewind(f);
    if(f==NULL)
    {
    printf("\n error in opening\a\a\a\a");
    exit(1);

    }
    printf("\nEnter name of person to search\n");
    scanf("%s",&name);
    while(fread(&p,sizeof(p),1,f)==1)
{
    if(strcmp(p.fname,name)==0)
    {
        printf("\n\tDetail Information About %s",name);
        printf("\nFirst Name:%s\nLast Name:%s\nMobile no:%ld\nsex(M/F):%s\n",p.fname,p.lname,p.mble_no,p.sex);
    }


}
 fclose(f);
getch();
system("cls");
main();
}
void deleterecord()
{

    struct person p;
    FILE *f,*ft;
	char name[100];
	int flag;
	f=fopen("contact.txt","rb+");
    rewind(f);
	if(f==NULL)
		{
			printf("CONTACT'S DATA NOT ADDED YET.");
		}
	else
	{
		ft=fopen("temp.dat","wb+");
		if(ft==NULL)

            printf("file opening error");
		else

        {
		printf("Enter CONTACT'S NAME:");
		scanf("%s",&name);



		while(fread(&p,sizeof(p),1,f)==1)
		{
			if(strcmp(p.fname,name)!=0)
				fwrite(&p,sizeof(p),1,ft);
			if(strcmp(p.fname,name)==0)
                flag=1;
		}
	fclose(f);
	fclose(ft);
	if(flag!=1)
	{
		printf("NO CONACT'S RECORD TO DELETE.");
		remove("temp.dat");
	}
		else
		{
			remove("contact.txt");
			rename("temp.dat","contact.txt");
			printf("RECORD DELETED SUCCESSFULLY.");

		}
	}
}

getch();
system("cls");
main();
}

void modifyrecord()
{
    int c;
    FILE *f;
    int flag=0;
    struct person p;
	char  name[50];
	f=fopen("contact.txt","rb+");
	if(f==NULL)
		{
			printf("CONTACT'S DATA NOT ADDED YET.");
		}
	else
	{
		printf("\nEnter CONTACT'S NAME TO MODIFY:\n");
            scanf("%s",&name);
            while(fread(&p,sizeof(p),1,f)==1)
            {
                if(strcmp(name,p.fname)==0)
                {



                    printf("\n Enter First name:");
                    scanf("%s",&p.fname);
                    printf("\nEnter the Last Name:");
                    scanf("%s",&p.lname);
                    printf("\nEnter phone no:");
                    scanf("%ld",&p.mble_no);
                    printf("\nEnter sex(M/F):");
                    scanf("%s",&p.sex);
                    fseek(f,-sizeof(p),SEEK_CUR);
                    fwrite(&p,sizeof(p),1,f);
                    flag=1;
                    break;



                }
                fflush(stdin);


            }
            if(flag==1)
            {
                printf("\n your data id modified");

            }
            else
            {
                    printf(" \n data is not found");

            }
            fclose(f);
	}
getch();
system("cls");
main();
}
