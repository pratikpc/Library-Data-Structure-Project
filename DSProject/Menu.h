/*Menu.h*/
#ifndef MENU_H
#define MENU_H

/*Define this to reduce error messages about unsafe functions like*/
/*scanf etc*/
#ifdef _MSC_VER
#   define _CRT_SECURE_NO_WARNINGS
#endif

#include <conio.h>
#include <stdio.h>

#include "BookList.h"
#include "Constants.h"
#include "FileIO.h"

#include "Login.h"

void addbook(void);
int  usermenu(void);
int  adminmenu(void);
void deletebook(void);
void searchbook(void);
void issuebookadmin(void);
void issuebookuser(void);
void returnbook(void);
void displaybook(void);
void adduser(void);
void deleteuser(void);
void changepassword(void);

struct BookList g_book_list;
FILE*           g_book_file;

void MenuSetup(void)
{
   /* Use current time as seed for random generator*/
   /* Required to Generate Random String*/
   /* Generates srand seed by current time*/
   srand(time(NULL));

   UserListInitialise(&g_user_list);
   BookListInitialise(&g_book_list);
}
void MenuDestroy(void)
{
   UserListDestroy(&g_user_list);
   BookListDestroy(&g_book_list);
}
void BookListWriteToFile(void)
{
   if (!FileOpenWrite(&g_book_file, BOOK_FILE_NAME))
      return;
   FileWriteBookList(&g_book_file, &g_book_list);
   FileClose(&g_book_file);
   BookListReset(&g_book_list);
}
void BookListReadFromFile(void)
{
   if (!FileOpenRead(&g_book_file, BOOK_FILE_NAME))
      return;
   BookListReset(&g_book_list);
   FileReadBookList(g_book_file, &g_book_list);
   FileClose(&g_book_file);
}

char* GenerateRandomString(const int p_length)
{

   static const char alpha_numeric_charset[] =
       "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

   char* random = NULL;
   int   key;
   int   i;

	/*If String Empty, Allocate Nothing*/
   if (p_length == 0)
   {
      return NULL;
   }
   /*Allocate String By Length*/
   random = malloc(sizeof(char) * (p_length + 1));
   for (i = 0; i < p_length; i++)
   {
      /*Get Key to use*/
      key       = rand() % (int)(sizeof(alpha_numeric_charset) - 1);
      random[i] = alpha_numeric_charset[key];
   }
   /*Set Last Elem as NULL*/
   random[p_length] = '\0';

   return random;
}

void BookDataDisplay(struct BookData book)
{
   printf("\n\xDB\xDB\xDB\xDB\xB2 Book Code\t:%d", book.book_code);
   printf("\n\xDB\xDB\xDB\xDB\xB2 Book Name\t:%s", book.book_name);
   printf("\n\xDB\xDB\xDB\xDB\xB2 Book Author\t:%s", book.book_author);
   printf("\n\xDB\xDB\xDB\xDB\xB2 Book Shelf\t:%d", book.book_shelf_no);
   printf("\n\xDB\xDB\xDB\xDB\xB2 Book Issued\t:%s\n", book.is_issued ? "Yes" : "No");
}

void ErrorMessageDisplay(const char* const p_error_message)
{
   printf("\n\xDB\xDB\xDB\xDB\xB2 Error:- ");
   printf("%s", p_error_message);
   _getch();
}
void SuccessMessageDisplay(const char* const p_error_message)
{
   printf("\n\xDB\xDB\xDB\xDB\xB2 Success:- ");
   printf("%s", p_error_message);
   _getch();
}

int adminmenu(void)
{
   char ch;

   system("cls");
   printf(
       "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU "
       "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
   printf("\n\xDB\xDB\xDB\xDB\xB2 1. Add Books   \n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 2. Delete books\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 3. Search Books\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 4. Issue Books\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 5, Return Book\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 6. Display Books\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 7. Add New User\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 8. Delete User\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 9. Change Password\n");
   scanf(" %c", &ch);

   system("cls");
   switch (ch)
   {
      case '1':
         addbook();
         break;
      case '2':
         deletebook();
         break;
      case '3':
         searchbook();
         break;
      case '4':
         issuebookadmin();
         break;
      case '5':
         returnbook();
         break;
      case '6':
         displaybook();
         break;
      case '7':
         adduser();
         break;
      case '8':
         deleteuser();
         break;
      case '9':
         changepassword();
         break;
      default:
         return 0;
   }
   /*Menu Worked Successfully*/
   return 1;
}
void deleteuser(void)
{
   char username[50];

   printf("\n\xDB\xDB\xDB\xDB\xB2 Please Enter Username to delete\n");
   scanf(" %[^\n]", username);

   if (strcmp(username, g_current_user) == 0)
   {
      ErrorMessageDisplay("\n\xDB\xDB\xDB\xDB\xB2 You Cannot Delete your own User Name");
      return;
   }

   UserListReadFromFile();
   if (!UserListDeleteUserByName(&g_user_list, username))
   {
      ErrorMessageDisplay("\n\xDB\xDB\xDB\xDB\xB2 Unable to Delete User");
      return;
   }
   UserListWriteToFile();
}
void changepassword(void)
{
   char old_pass[50];
   char new_pass[50];
   char confirm_new_pass[50];

   printf("\n\xDB\xDB\xDB\xDB\xB2 Enter old password\n");
   scanf(" %[^\n]", old_pass);
   printf("\n\xDB\xDB\xDB\xDB\xB2 Enter New Password\n");
   scanf(" %[^\n]", new_pass);
   printf("\n\xDB\xDB\xDB\xDB\xB2 Confirm Pass\n");
   scanf(" %[^\n]", confirm_new_pass);

   if (strcmp(new_pass, confirm_new_pass) != 0)
   {
      ErrorMessageDisplay("\n\xDB\xDB\xDB\xDB\xB2 Passwords do not match");
      return;
   }
   if (strcmp(old_pass, new_pass) == 0)
   {
      /*If Old and new password is same, do nothing*/
      return;
   }

   UserListReadFromFile();
   if (!UserListChangePassword(&g_user_list, g_current_user, old_pass, new_pass))
   {
      ErrorMessageDisplay("\n\xDB\xDB\xDB\xDB\xB2 Unable to Change Password");
      return;
   }
   UserListWriteToFile();
   SuccessMessageDisplay("Password Changed Successfully");
}
void addbook(void)
{
   char book_name[50], book_author[50];
   int  book_shelf_no, book_code;

   printf("\n\xDB\xDB\xDB\xDB\xB2 Enter Book Name\n");
   scanf(" %[^\n]", book_name);
   printf("\n\xDB\xDB\xDB\xDB\xB2 Enter Book Author\n");
   scanf(" %[^\n]", book_author);
   printf("\n\xDB\xDB\xDB\xDB\xB2 Enter Book Code\n");
   scanf("%d", &book_code);
   printf("\n\xDB\xDB\xDB\xDB\xB2 Enter Shelf No\n");
   scanf("%d", &book_shelf_no);

   BookListReadFromFile();
   if (!BookListAdd(&g_book_list, book_code, book_name, book_author, book_shelf_no))
   {
      ErrorMessageDisplay("Unable to Add Book");
      return;
   }
   BookListWriteToFile();

   SuccessMessageDisplay("Added To Book");
}
void adduser(void)
{
   char               username[50];
   char*              password;
   char               is_admin;
   enum UserAuthority authority;

   /*Get Random Password String*/
   password = GenerateRandomString(6);

   if (password == NULL)
   {
      ErrorMessageDisplay("Unable to create Randomised Password");
      return;
   }

   printf("\n\xDB\xDB\xDB\xDB\xB2 Please Enter Username to add\n");
   scanf(" %[^\n]s", username);

   printf("\n\xDB\xDB\xDB\xDB\xB2 Default Password is %s", password);
   printf("\n\xDB\xDB\xDB\xDB\xB2 Is New User Admin(Y\\N)?");
   scanf(" %c", &is_admin);

   authority = (is_admin == 'Y' || is_admin == 'y') ? ADMIN : USER;

   UserListReadFromFile();
   if (!UserListAdd(&g_user_list, username, password, authority))
   {
      ErrorMessageDisplay("\n\xDB\xDB\xDB\xDB\xB2 Unable to Add To List");
      return;
   }
   UserListWriteToFile();
   /*Note Password is allocated using malloc in function*/
   free(password);
   SuccessMessageDisplay("Added New User");
}
void issuebookadmin(void)
{
   int  code;
   char book_issuer[50];

   printf("\n\xDB\xDB\xDB\xDB\xB2 Enter Book Code\n");
   scanf("%d", &code);
   printf("\n\xDB\xDB\xDB\xDB\xB2 Enter Book Issuer\n");
   scanf(" %[^\n]", book_issuer);

   /*Check if Issuer is actually allowed to do so*/
   UserListReadFromFile();
   if (!UserListUserExists(&g_user_list, book_issuer))
   {
      ErrorMessageDisplay(
          "\n\xDB\xDB\xDB\xDB\xB2 Unable to Issue Book. User Does not Exist");
      return;
   }

   BookListReadFromFile();
   /* Check if Student has Already Issued Book or Not*/
   if (!BookListBookIssue(&g_book_list, book_issuer, code))
   {
      ErrorMessageDisplay("\n\xDB\xDB\xDB\xDB\xB2 Unable to Issue Book");
      return;
   }
   BookListWriteToFile();
   SuccessMessageDisplay("Issued Book");
}
void issuebookuser(void)
{
   int code;

   printf("\n\xDB\xDB\xDB\xDB\xB2 Enter Book Code\n");
   scanf("%d", &code);

   BookListReadFromFile();
   /* Check if Student has Already Issued Book or Not*/
   if (!BookListBookIssue(&g_book_list, g_current_user, code))
   {
      ErrorMessageDisplay("\n\xDB\xDB\xDB\xDB\xB2 Unable to Issue Book");
      return;
   }
   BookListWriteToFile();
   SuccessMessageDisplay("Found These Books");
}
void returnbook(void)
{
   int             code;
   struct BookData book;

   printf("\n\xDB\xDB\xDB\xDB\xB2 Enter code of Book which is returned\n");
   scanf("%d", &code);
   BookListReadFromFile();
   /* Check if Book can be Deissued*/
   if (!BookListBookDeIssue(&g_book_list, code, &book))
   {
      ErrorMessageDisplay("\n\xDB\xDB\xDB\xDB\xB2 Unable to Return Book");
      return;
   }
   BookListWriteToFile();
   printf("\n\xDB\xDB\xDB\xDB\xB2 Returned Book Place to %d Shelf", book.book_shelf_no);
   BookDataDisplay(book);
   _getch();
}
void deletebook(void)
{
   int code;
   printf("\n\xDB\xDB\xDB\xDB\xB2 Enter Book code\n");
   scanf("%d", &code);
   BookListReadFromFile();
   if (!BookListDeleteByCode(&g_book_list, code))
   {
      ErrorMessageDisplay("\n\xDB\xDB\xDB\xDB\xB2 Unable to Delete Book");
      return;
   }
   BookListWriteToFile();
   SuccessMessageDisplay("Deleted Book");
}

void searchbook(void)
{
   char ch;
   int  code;
   char text[50];

   struct BookData book;

   printf("\n\xDB\xDB\xDB\xDB\xB2 1. Search by Code\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 2. Search by Student Name\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 3. Search by Name/Author\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 4. Search by Shelf No\n");

   scanf(" %c", &ch);
   switch (ch)
   {
      case '1':
         printf("\n\xDB\xDB\xDB\xDB\xB2 Enter Book code\n");
         scanf("%d", &code);
         BookListReadFromFile();
         if (BookListFindByCode(&g_book_list, code, &book))
         {
            BookDataDisplay(book);
            SuccessMessageDisplay("Found These Books");
         }
         else
            ErrorMessageDisplay("\n\xDB\xDB\xDB\xDB\xB2 Unable to Find Book");
         break;

      case '2':
         printf("\n\xDB\xDB\xDB\xDB\xB2 Enter Student Name\n");
         scanf(" %[^\n]s", text);
         BookListReadFromFile();
         if (BookListFindByStudentName(&g_book_list, text, &book))
         {
            BookDataDisplay(book);
            SuccessMessageDisplay("Found These Books");
         }
         else
            ErrorMessageDisplay("\n\xDB\xDB\xDB\xDB\xB2 Unable to Find Book");
         break;
      case '3':
         printf("\n\xDB\xDB\xDB\xDB\xB2 Enter Name/Author\n");
         scanf(" %[^\n]s", text);
         BookListReadFromFile();
         BookListFindByString(&g_book_list, text, BookDataDisplay);
         SuccessMessageDisplay("Found These Books");
         break;
      case '4':
         printf("\n\xDB\xDB\xDB\xDB\xB2 Enter Shelf Number\n");
         scanf("%d", &code);
         BookListReadFromFile();
         BookListDisplayByShelfNumber(&g_book_list, code, BookDataDisplay);
         SuccessMessageDisplay("Found These Books");
         break;
   }
}
void displaybook(void)
{
   char ch;
   printf("\n\xDB\xDB\xDB\xDB\xB2 1. Display details of all books\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 2. Display details of Students not returned books\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 3. Display books by Shelf Number\n");
   scanf(" %c", &ch);

   BookListReadFromFile();
   switch (ch)
   {
      case '1':
         BookListDisplayedAllList(&g_book_list, BookDataDisplay);
         SuccessMessageDisplay("Found These Books");
         break;
      case '2':
         BookListDisplayDelayedList(&g_book_list);
         SuccessMessageDisplay("Found These Books");
         break;
      case '3':
         BookListShowByShelfNumber(&g_book_list, BookDataDisplay);
         SuccessMessageDisplay("Found These Books");
         break;
   }
}

int usermenu(void)
{
   char ch;
   char text[50];
   system("cls");
   printf("\n\xDB\xDB\xDB\xDB\xB2 1. Issue Books\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 2. Display Books by Shelf No\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 3. Search by Name/Author\n");
   printf("\n\xDB\xDB\xDB\xDB\xB2 4. Change Password\n");

   scanf(" %c", &ch);
   system("cls");
   switch (ch)
   {
      case '1':
         issuebookuser();
         break;
      case '2':
         BookListReadFromFile();
         BookListShowByShelfNumber(&g_book_list, BookDataDisplay);
         SuccessMessageDisplay("Found These Books");
         break;
      case '3':
         printf("\n\xDB\xDB\xDB\xDB\xB2 Enter Name/Author\n");
         scanf(" %[^\n]s", text);
         BookListReadFromFile();
         BookListFindByString(&g_book_list, text, BookDataDisplay);
         SuccessMessageDisplay("Found These Books");
         break;
      case '4':
         changepassword();
         break;
      default:
         return 0;
   }
   return 1;
}
#endif