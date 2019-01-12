/*Main.c*/
#include "Menu.h"

void MainUIShow()
{
   enum UserAuthority authority;

   /*Setup The Books Menu*/
   MenuSetup();

   UserListReadFromFile();
   if (UserListHasNoAdmin(&g_user_list))
   {
      /*This Portion Exists for First Login*/
      /*In case of First Login, Set Default UserName and Password for Admin be*/
      /*admin admin*/
      UserListAdd(&g_user_list, "admin", "admin", ADMIN);
      SuccessMessageDisplay("Default UserName/Password is admin/admin");
      UserListWriteToFile();
      _getch();
      strcpy(g_current_user, "admin");
      /*First User Must be Admin*/
      authority = ADMIN;
   }
   else
   {
      while (!Login(&authority))
      {
         ErrorMessageDisplay("Unable to Login. Wrong UserName/Pasword");
      }
   }
   /*Show the Menu till Terminating Condition called*/
   if (authority == ADMIN)
   {
      while (adminmenu())
      {
      }
   }
   else
   {
      while (usermenu())
      {
      }
   }

   MenuDestroy();
}

int main()
{
   char ch;
   do
   {
      MainUIShow();
      system("cls");
      printf("Do you Wish to Login Again(Y\\N)?");
      scanf(" %c",&ch);
   } while (ch == 'y' || ch == 'Y');
   return 0;
}
