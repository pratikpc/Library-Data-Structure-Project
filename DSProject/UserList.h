/*UserList.h*/
#ifndef USERLIST_H
#define USERLIST_H

#include <stdlib.h>
#include <string.h>

enum UserAuthority
{
   USER  = 0,
   ADMIN = 1
};
struct UserData
{
   char               m_user_name[50];
   char               m_passwd[20];
   enum UserAuthority m_authority;
};
struct UserNode
{
   struct UserData  data;
   struct UserNode* next;
};
struct UserList
{
   struct UserNode* m_head;
};
void UserNodeFree(struct UserNode* del)
{
   free(del);
}

int UserListEmpty(struct UserList* p_user_list)
{
   return p_user_list->m_head == NULL;
}

int UserListHasNoAdmin(struct UserList* p_user_list)
{
   struct UserNode* it;
   if (p_user_list == NULL)
      return 1;

   for (it = p_user_list->m_head; it != NULL; it = it->next)
   {
      if (it->data.m_authority == ADMIN)
         return 0;
   }
   return 1;
}

void UserListInitialise(struct UserList* p_user_list)
{
   p_user_list         = (struct UserList*)malloc(sizeof(struct UserList));
   p_user_list->m_head = NULL;
}
void UserListDestroy(struct UserList* p_list)
{
   struct UserNode* it;
   if (p_list == NULL)
      return;

   while (p_list->m_head != NULL)
   {
      it             = p_list->m_head;
      p_list->m_head = it->next;
      UserNodeFree(it);
   }
}
void UserListReset(struct UserList* p_list)
{
   UserListDestroy(p_list);
   UserListInitialise(p_list);
}
void UserListInsertToNode(struct UserList* p_user_list, struct UserNode* newnode)
{
   if (p_user_list == NULL)
      UserListInitialise(p_user_list);
   /* As we are Inserting at Front*/
   newnode->next       = p_user_list->m_head;
   p_user_list->m_head = newnode;
}
/*Use this to verify Existence of user*/
int UserListAuthenticateUser(struct UserList*  p_list,
                             const char* const p_user_name,
                             const char* const p_password,
                             struct UserData*  p_data)
{
   struct UserNode* it;
   /* Use this to iterate through the loop*/
   for (it = p_list->m_head; it != NULL; it = it->next)
   {
      /*User Found*/
      if (strcmp(it->data.m_user_name, p_user_name) == 0)
      {
         if (strcmp(it->data.m_passwd, p_password) == 0)
         {
            if (p_data != NULL)
               *p_data = it->data;
            return 1;
         }
         else
         {
            /*While User Name matches, password doesn't match*/
            /*User Not Authenticated*/
            return 0;
         }
      }
   }
   /*User Not Found*/
   return 0;
}
int UserListUserExists(struct UserList* p_list, const char* const p_user_name)
{
   struct UserNode* it;
   /* Use this to iterate through the loop*/
   for (it = p_list->m_head; it != NULL; it = it->next)
   {
      /*User Found*/
      if (strcmp(it->data.m_user_name, p_user_name) == 0)
         return 1;
   }
   /*User Not Found*/
   return 0;
}

int UserListAdd(struct UserList*         p_user_list,
                const char* const        p_user_name,
                const char* const        p_passwd,
                const enum UserAuthority p_authority)
{
   struct UserNode* user;

   if (UserListUserExists(p_user_list, p_user_name))
      return 0;

   user = (struct UserNode*)malloc(sizeof(struct UserNode));

   strcpy(user->data.m_user_name, p_user_name);
   strcpy(user->data.m_passwd, p_passwd);

   user->data.m_authority = p_authority;

   UserListInsertToNode(p_user_list, user);
   return 1;
}

int UserListDeleteUserByName(struct UserList* p_list, const char* p_user_name)
{
   struct UserNode* tmp;
   struct UserNode* it;

   /*Check Head First*/
   while (p_list->m_head != NULL &&
          strcmp(p_list->m_head->data.m_user_name, p_user_name) == 0)
   {
      tmp = p_list->m_head;
      if (tmp->data.m_authority == ADMIN)
         return 0;
      p_list->m_head = p_list->m_head->next;

      UserNodeFree(tmp);

      return 1;
   }

   it = p_list->m_head;
   /* Use this to iterate through the loop*/
   while (it != NULL && it->next != NULL)
   {
      /*Condition to Delete found*/
      if (strcmp(it->next->data.m_user_name, p_user_name) == 0)
      {
         tmp = it->next;
         if (tmp->data.m_authority == ADMIN)
            return 0;
         it->next = it->next->next;

         UserNodeFree(tmp);
         it = it->next;

         return 1;
      }
      else
      {
         it = it->next;
      }
   }
   return 0;
}

int UserListChangePassword(struct UserList*  p_list,
                           const char* const p_user_name,
                           const char* const p_old_password,
                           const char* const p_new_password)
{
   struct UserData    old_data;
   enum UserAuthority authority;

   /*Check if Old password gets authenticated*/
   if (!UserListAuthenticateUser(p_list, p_user_name, p_old_password, &old_data))
      return 0;
   /*Delete Old user*/
   UserListDeleteUserByName(p_list, p_user_name);
   /*Get User Authority*/
   authority = old_data.m_authority;
   /*Add New*/
   return UserListAdd(p_list, p_user_name, p_new_password, authority);
}

#endif
