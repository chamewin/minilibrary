#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// Prototypes
int adminMain();
int userMain();
int aMain();
int uMain();
void addBook();
void deleteBook();
int checkOut();
int returnBook();
void searchAuthor();
void searchBook();
int checkedOut();
int login();
int pass();
void quit();
int lineCount();
int countLines();
void printText();


// Global variables
char choice;
int bookId = 1;
char currentUser[100];


int main() {
  login();
  return 0;
}

int adminMain() {

  scanf("%c",&choice);
  switch(choice) {
    case 'a':
      addBook();
    case 'd':
      deleteBook();
    case 'o':
      checkOut();
    case 'r':
      returnBook();
    case 'x':
      quit();
    default:
      printf("Welcome to the ADMIN MENU.\n");
      aMain();
      printf("What would you like to do? ");
      adminMain();
  }
  return 0;
}

int userMain() {
  scanf("%c",&choice);
  switch(choice) {
    case 'q':
      searchAuthor();
    case 's':
      searchBook();
    case 'u':
      checkedOut();
    case 'x':
      quit();
    default:
      printf("Welcome to the USER MENU.\n");
      uMain();
      printf("What would you like to do? ");
      userMain();
  }
  return 0;
}

int aMain() {
  printf("Enter \"a\" to add a book to the library.\n");
	printf("Enter \"d\" to delete a book from the library.\n");
	printf("Enter \"o\" to check out a book.\n");
	printf("Enter \"r\" to return a book.\n");
	printf("Enter \"x\" Sign Out.\n");
  return 0;
}

int uMain() {
  printf("Enter \"q\" for book querry by author sorted by book title.\n");
  printf("Enter \"s\" for the status of a specific book.\n");
  printf("Enter \"u\" to list the books you have checked out.\n");
  printf("Enter \"x\" to Sign Out.\n");
  return 0;
}

// Admin Main Options
void addBook() {
  char title[100];
	char author[150];
	int feel = 1;
	char try[2];
	FILE *fp;

	fp = fopen("Mylibrary.txt","a");

	printf("Enter Book Title: ");
	scanf(" %[^'\n]s", title);
	printf("Enter Author's Name: ");
	scanf(" %[^'\n]s",author);

	bookId=countLines();

	fprintf(fp,"%d,%s,%s,library,null,null\n",bookId,title,author);
	fclose(fp);
	printf("Book %s was added succesfully!\n",title);
	while(feel != 0)
	{
		printf("Press t to try again or b to go back to the main menu\n");
		scanf(" %c",try);
		if(strcasecmp(try,"t")== 0)
		{
			addBook();
		}
		else if(strcasecmp(try,"b") == 0)
		{
			adminMain();
		}
		else
		{
			printf("Command not found/n");
		}
	}

}

void deleteBook() {
  	int rando=0;
	int num,feel=1;
	FILE *fp,*fp2;
	char yr;
	char try[2];
	char file[200],check[200]="copy.txt";
	char name[50],title[50];
	printText();
	fp = fopen("Mylibrary.txt","r");
	printf("Give the ID of the book you wish to delete\n");
	scanf(" %d",&num);
	fp2 = fopen("copy.txt","w");
	while(!feof(fp))
	{

		strcpy(file, "\0");
		fgets(file, 50, fp);
		sscanf(file,"%d,%[^,],[^,],",&rando,title,name);
		if(rando != num)
		{
			fprintf(fp2," %s",file);
		}
	}

	fclose(fp);
	fclose(fp2);
	remove("Mylibrary.txt");
	rename("copy.txt","Mylibrary.txt");
	while(feel != 0)
	{
		printf("Press t to try again or Press b to got back to main menu\n");
		scanf(" %c",try);
		if(strcasecmp(try,"t") == 0)
		{
			deleteBook();
		}
		else if(strcasecmp(try,"b") == 0)
		{
			adminMain();
		}
		else
		{
			printf("Command does not exist");
		}
	}
}

int checkOut() {

  return 0;
}

int returnBook() {
  return 0;
}

// User Main Options
void searchAuthor() {
  char try[2];
	char name[50],search[50],title[50],line[50];
	char c;
	int count=0;
	int id;
	int feel = 1;
	FILE *fp,*fp2;
	printf("What author are you looking for?: ");
	scanf("%[^'\n]s",search);
	fp = fopen("Mylibrary.txt","r");
	fp2 = fopen("sort.txt","w");
	while(!feof(fp))
	{
		fgets(line,100,fp);
		sscanf(line,"%d,%[^,],%[^,],",&id,title,name);
		if(strcasecmp(search,name)==0)
		{
			count++;
			fprintf(fp2,"%s\n",line);

		}
	}
	fclose(fp2);
	fp2 = fopen("sort.txt","r");
	c = fgetc(fp2);
	while(c != EOF)
	{
		printf("%c",c);
		c = fgetc(fp2);
	}
	fclose(fp);
	fclose(fp2);
	if(count==0)
	{
		printf("No Books By This Author!\n");
	}
	while(feel != 0)
	{
		printf("Press t to try again or Press b to go back to the main menu");
		scanf(" %c",try);
		if(strcasecmp(try,"t")== 0)
		{
			searchAuthor();
		}
		else if(strcasecmp(try,"b") == 0)
		{
			userMain();
		}
		else
		{
			printf("Command does not exist\n");
		}
	}


}

void searchBook() {
  char name[50],search[50],title[50],line[50],status[50],date[50];
	char c;
	char try[2];
	int count=0,feel=1;
	int id;
	FILE *fp,*fp2;
	printf("The name of the book you are looking for is?: ");
	scanf("%s[^'\n]",search);
	fp = fopen("Mylibrary.txt","r");
	fp2 = fopen("book.txt","w");
	while(!feof(fp))
	{
		fgets(line,100,fp);
		sscanf(line,"%d,%[^,],%[^,],%[^,],[^,]",&id,title,name,status,date);
		if(strcasecmp(search,title)==0)
		{
				count++;
				if(strcasecmp(status,"library")==0)
				{
					fprintf(fp2,"%s in library\n",title);
				}
				else
				{
					fprintf(fp2,"%s Available after %s\n",title,date);
				}
		}
	}
	fclose(fp2);
	fp2 = fopen("book.txt","r");
	c = fgetc(fp2);
	while(c != EOF)
	{
		printf("%c",c);
		c = fgetc(fp2);
	}
	fclose(fp);
	fclose(fp2);
	if(count==0)
	{
		printf("No Book By This Name\n");
	}
	while(feel != 0)
	{
		printf("Press t to try again or b to go back to the main menu");
		scanf(" %c",try);
		if(strcasecmp(try,"t")== 0)
		{
			searchBook();
		}
		else if(strcasecmp(try,"b") == 0)
		{
			userMain();
		}
	}


}

int checkedOut() {
  // User Info
  int id;
  char title[100], author[100], acc[100], co[100], due[100];

  time_t rawtime;
  struct tm *tm;
  char buffer[100];

  time(&rawtime);
  tm = localtime(&rawtime);

  strftime(buffer,100,"%F",tm);
  puts(buffer);

  printf("====CHECKED OUT=====");

  FILE *fp;
  fp = fopen("Mylibrary.txt","r");

  while(fscanf(fp,"%d,%100[^,],%100[^,],%100[^,],%100[^,],%100[^,]",&id,title,author,acc,co,due)==6) {
    if(strcasecmp(currentUser,acc)==0) {
      printf("%d,%100[^,],%100[^,],%100[^,],%100[^,],%100[^,]",&id,title,author,acc,co,due);

      char buf[100];
      char *arr[3];
      int numArr[3];
      int i = 0;
      int j = 0;

      strcpy(buf,due);
      char *p = strtok(buf,"-");

      while(p != NULL) {
        arr[i++] = p;
        p = strtok(NULL,"-");
      }

      while (j < 3) {
        int temp = atoi(arr[j]);
        numArr[j] = temp;
      }

      printf("%d",numArr[0]);
    }
  }

  fclose(fp);
  return 0;
}

void quit() {
  exit(0);
}

// Prompt for username
int login() {
  int id;
  char first[100], last[100], acc[100], p[100];
  char cat;

  // User Input
  char user[100];
  char welcome[100];

  printf("USERNAME: ");
  scanf("%s",user);

  FILE *fp;
  fp = fopen("UserInfo.txt","r");

  int success = 1;
  while(fscanf(fp,"%d,%10[^,],%10[^,],%10[^,],%10[^,],%c",&id,first,last,acc,p,&cat)==6) {
    if (strcasecmp(user,acc)==0) {
      success = 0;
    }
  }

  // If success = 0, then user match was successful and will now prompt for password.
  if (success == 0) {
    pass();
  }

  // If user did not match, success will remain false and prompt user to re-enter info.
  if (success == 1) {
    printf("User does not exist.\n");
    login();
  }

  fclose(fp);

  return 0;
}

// Prompt for user's password
int pass() {
  int id;
  char first[100], last[100], acc[100], p[100];
  char cat;

  char pw[100];
  printf("PASSWORD: ");
  scanf("%s",pw);

  FILE *fp;
  fp = fopen("UserInfo.txt","r");

  int success = 1;
  while(fscanf(fp,"%d,%10[^,],%10[^,],%10[^,],%10[^,],%c",&id,first,last,acc,p,&cat)==6) {
    if (strcmp(pw,p)==0) {
      printf("Welcome %s.\n",acc);
      strcpy(currentUser,acc);
      if (cat == 'B') {
        userMain();
      } else {
        adminMain();
      }
      success = 0;
    }
  }

  // If password did not match, success remains 1 and will prompt user to re-enter info
  if (success == 1) {
    printf("Password is incorrect.\n");
    login();
  }

  fclose(fp);
  return 0;
}

int lineCount() {
  FILE *fp;
  int count = 0;
  char filename[1000];
  char c;

  fp = fopen("UserInfo.txt", "r");

  if (fp == NULL) {
    printf("Could not open file.");
    return 0;
  }

  for (c = getc(fp); c != EOF; c = getc(fp)) {
      if (c == '\n') {
        count = count + 1;
      }
  }
  fclose(fp);
  return count;
}

int countLines() {
  FILE *fp2;
  int line = 0;
  char c;
  fp2 = fopen("Mylibrary.txt","r");
  for (c = getc(fp2); c != EOF; c = getc(fp2)) {
    if (c == '\n') {
      line = line + 1;
    }
  }
  return line;
  fclose(fp2);
}

void printText() {
  FILE *fp;
  char c;
  fp = fopen("Mylibrary.txt","r");
  c = fgetc(fp);
  while (c != EOF) {
    printf("%c",c);
    c = fgetc(fp);
  }
  fclose(fp);
}
