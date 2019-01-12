/*Login.h*/
#ifndef LOGIN_H
#define LOGIN_H

#include "Constants.h"
#include "FileIO.h"
#include "UserList.h"

struct UserList g_user_list;
FILE*           g_user_file;

char g_current_user[50];

void UserListWriteToFile(void)
{
   if (!FileOpenWrite(&g_user_file, USER_FILE_NAME))
      return;
   FileWriteUserList(&g_user_file, &g_user_list);
   FileClose(&g_user_file);
   UserListReset(&g_user_list);
}
void UserListReadFromFile(void)
{
   if (!FileOpenRead(&g_user_file, USER_FILE_NAME))
      return;
   UserListReset(&g_user_list);
   FileReadUserList(g_user_file, &g_user_list);
   FileClose(&g_user_file);
}

int Login(enum UserAuthority* p_authority)
{
   char username[50];
   char password[20];

   struct UserData user;

   system("cls");

   printf("\n\xDB\xDB\xDB\xDB\xB2 Please Enter Username\n");
   scanf(" %[^\n]s", username);
   printf("\n\xDB\xDB\xDB\xDB\xB2 Please Enter Password\n");
   scanf(" %[^\n]s", password);

   UserListReadFromFile();
   if (!UserListAuthenticateUser(&g_user_list, username, password, &user))
   {
      /*Unable to Login*/
      return 0;
   }
   /*Login Successful.*/
   strcpy(g_current_user, user.m_user_name);
   *p_authority = user.m_authority;
   return 1;
}

#endif
