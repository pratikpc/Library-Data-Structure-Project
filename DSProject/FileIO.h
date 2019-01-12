/*FileIO.h*/
#ifndef FILEIO_H
#define FILEIO_H

/* Use this to Interact with the File*/
#include <stdio.h>

/* Returns true if file opened for writing*/
int FileOpenWrite(FILE** f, const char* p_file_name)
{
   *f = fopen(p_file_name, "wb");
   return (*f != NULL);
}
/* Returns true if file opened for append*/
int FileOpenAppend(FILE** f, const char* p_file_name)
{
   *f = fopen(p_file_name, "ab");
   return (*f != NULL);
} /* Returns true if file opened for reading*/
int FileOpenRead(FILE** f, const char* p_file_name)
{
   *f = fopen(p_file_name, "rb");
   return (*f != NULL);
}

void FileClose(FILE** f)
{
   fclose(*f);
}

#include "UserList.h"

int FileWriteUserList(FILE** f, struct UserList* p_list)
{
   struct UserNode* it;
   for (it = p_list->m_head; it != NULL; it = it->next)
   {
      const size_t ret = fwrite(&it->data, sizeof(struct UserData), 1, *f);
      if (ret != 1)
      {
         /*If Writing Failed*/
         return 0;
      }
   }
   /*All Elements were properly written*/
   return 1;
}

void FileReadUserList(FILE* f, struct UserList* p_list)
{
   void* buf = malloc(sizeof(struct UserData));
   while (fread(buf, sizeof(struct UserData), 1, f) > 0)
   {
      /*Write All Elements to Buffer*/
      struct UserData* data = (struct UserData*)buf;
      UserListAdd(p_list, data->m_user_name, data->m_passwd, data->m_authority);
   }
   free(buf);
   /*All Elements were properly read*/
}

#include "BookList.h"

int FileAppendBook(FILE** f, struct BookData* data)
{
   return fwrite(data, sizeof(struct BookData), 1, *f) == 1;
}
int FileWriteBookList(FILE** f, struct BookList* p_list)
{
   struct BookNode* it;

   size_t ret;
   for (it = p_list->m_head; it != NULL; it = it->next)
   {
      ret = fwrite(&it->data, sizeof(struct BookData), 1, *f);
      if (ret != 1)
      {
         /*If Writing Failed*/
         return 0;
      }
   }
   /*All Elements were properly written*/
   return 1;
}
void FileReadBookList(FILE* f, struct BookList* p_list)
{
   void* buf = malloc(sizeof(struct BookData));
   while (fread(buf, sizeof(struct BookData), 1, f) > 0)
   {
      /*Write All Elements to Buffer*/
      struct BookData* data = (struct BookData*)buf;
      BookListInsertInto(p_list, *data);
   }
   free(buf);
   /*All Elements were properly read*/
}

#endif
