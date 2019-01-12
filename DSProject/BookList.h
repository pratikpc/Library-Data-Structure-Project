/*BookList.h*/
#ifndef BOOK_LIST_H
#define BOOK_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct BookData
{
   int  book_code;
   char book_name[50];
   char book_author[50];
   int  book_shelf_no;
   /*Set Value to 0 or 1 depending on if book is issued*/

   int    is_issued;
   char   issue_student_name[50];
   time_t issue_time;
};

struct BookNode
{
   struct BookNode* next;
   struct BookData  data;
};
struct BookList
{
   struct BookNode* m_head;
};

typedef void (*ShowBookData)(struct BookData);

void BookListFree(struct BookNode* del)
{
   free(del);
}

void BookListInitialise(struct BookList* p_book_list)
{
   p_book_list         = (struct BookList*)malloc(sizeof(struct BookList));
   p_book_list->m_head = NULL;
}
void BookListDestroy(struct BookList* p_list)
{
   struct BookNode* it;
   while (p_list != NULL && p_list->m_head != NULL)
   {
      it             = p_list->m_head;
      p_list->m_head = it->next;
      BookListFree(it);
   }
   p_list->m_head = NULL;
   p_list         = NULL;
}
void BookListReset(struct BookList* p_list)
{
   BookListDestroy(p_list);
   BookListInitialise(p_list);
}
int BookListEmpty(struct BookList* p_list)
{
   return p_list == NULL || p_list->m_head == NULL;
}
int BookListDeleteByCode(struct BookList* p_list, const int code)
{
   struct BookNode* tmp;
   struct BookNode* it;

   if (BookListEmpty(p_list))
      return 0;

   /*Check Head First*/
   if (p_list->m_head != NULL && (p_list->m_head->data.book_code == code))
   {
      tmp            = p_list->m_head;
      p_list->m_head = p_list->m_head->next;

      BookListFree(tmp);
      /*Node Deleted*/
      return 1;
   }

   it = p_list->m_head;
   /* Use this to iterate through the loop*/
   while (it != NULL && it->next != NULL)
   {
      /*Condition to Delete found*/
      if (it->next->data.book_code == code)
      {
         tmp      = it->next;
         it->next = it->next->next;
         BookListFree(tmp);
         /*Node Deleted*/
         return 1;
      }
      else
      {
         it = it->next;
      }
   }
   /*Unable to Delete Node*/
   return 0;
}
int BookListFindByCode(struct BookList* p_list, const int code, struct BookData* book)
{
   struct BookNode* it;
   /* Use this to iterate through the loop*/
   for (it = p_list->m_head; it != NULL; it = it->next)
   {
      if (it->data.book_code == code)
      {
         if (book != NULL)
            *book = it->data;
         /*Element Found Return True*/
         return 1;
      }
   }
   /*Element Not Found, Return False*/
   return 0;
}
int BookListFindByStudentName(struct BookList*  p_list,
                              const char* const student_name,
                              struct BookData*  book)
{
   struct BookNode* it;
   /* Use this to iterate through the loop*/
   for (it = p_list->m_head; it != NULL; it = it->next)
   {
      if (strcmp(it->data.issue_student_name, student_name) == 0)
      {
         /*We Shall Pass NULL Here when we do not need the Return Value*/
         if (book != NULL)
            *book = it->data;
         /*Element Found Return True*/
         return 1;
      }
   }
   /*Element Not Found, Return False*/
   return 0;
}
void SwapBookNode(struct BookNode* left, struct BookNode* right)
{
   struct BookData* tmp        = (struct BookData*)malloc(sizeof(struct BookData));
   struct BookData* left_data  = &left->data;
   struct BookData* right_data = &right->data;
   /*Assign left to tmp*/
   {
      strcpy(tmp->book_author, left_data->book_author);
      strcpy(tmp->book_name, left_data->book_name);
      strcpy(tmp->issue_student_name, left_data->issue_student_name);
      tmp->is_issued     = left_data->is_issued;
      tmp->issue_time    = left_data->issue_time;
      tmp->book_shelf_no = left_data->book_shelf_no;
      tmp->book_code     = left_data->book_code;
   }
   /*Assign right to left*/
   {
      strcpy(left_data->book_author, right_data->book_author);
      strcpy(left_data->book_name, right_data->book_name);
      strcpy(left_data->issue_student_name, right_data->issue_student_name);
      left_data->is_issued     = right_data->is_issued;
      left_data->issue_time    = right_data->issue_time;
      left_data->book_shelf_no = right_data->book_shelf_no;
      left_data->book_code     = right_data->book_code;
   }
   /*Assign Tmp to Right*/
   {
      strcpy(right_data->book_author, tmp->book_author);
      strcpy(right_data->book_name, tmp->book_name);
      strcpy(right_data->issue_student_name, tmp->issue_student_name);
      right_data->is_issued     = tmp->is_issued;
      right_data->issue_time    = tmp->issue_time;
      right_data->book_shelf_no = tmp->book_shelf_no;
      right_data->book_code     = tmp->book_code;
   }
}
void BookListShowByShelfNumber(struct BookList* p_list, ShowBookData p_show)
{
   struct BookNode* first_it;
   struct BookNode* end_it = NULL;

   int is_swapped;

   if (p_list == NULL || p_list->m_head == NULL)
      return;

   do
   {
      is_swapped = 0;

      for (first_it = p_list->m_head; first_it->next != end_it; first_it = first_it->next)
      {
         if (first_it->data.book_shelf_no > first_it->next->data.book_shelf_no)
         {
            SwapBookNode(first_it, first_it->next);
            is_swapped = 1;
         }
      }
      end_it = first_it;
   } while (is_swapped);

   /* Use this to iterate through the loop*/
   for (first_it = p_list->m_head; first_it != NULL; first_it = first_it->next)
   {
      const struct BookData book = first_it->data;
      if (!book.is_issued)
         p_show(book);
   }
}

void BookListDisplayDelayedList(struct BookList* p_list)
{
   struct BookNode* it;

   time_t    time_diff;
   struct tm spent_time;

   /* Use this to iterate through the loop*/
   for (it = p_list->m_head; it != NULL; it = it->next)
   {
      const struct BookData book = it->data;

      if (!book.is_issued)
         continue;

      time_diff  = time(NULL) - book.issue_time;
      spent_time = *localtime(&time_diff);

      /* Minimum Delay Period*/
      /* If less than that, student still has time to return*/
      if (spent_time.tm_yday <= 7)
         continue;

      printf("\n\xDB\xDB\xDB\xDB\xB2 Book Code\t:%d\n", book.book_code);
      printf("\n\xDB\xDB\xDB\xDB\xB2 Book Name\t:%s", book.book_name);
      printf("\n\xDB\xDB\xDB\xDB\xB2 Student Issuer Name\t:%s", book.issue_student_name);

      printf("\n\xDB\xDB\xDB\xDB\xB2 Delayed By\t: %d\n", spent_time.tm_yday - 7);
   }
}
void BookListDisplayByShelfNumber(struct BookList* p_list,
                                  const int        p_shelf_no,
                                  ShowBookData     p_show)
{
   struct BookNode* it;
   /* Use this to iterate through the loop*/
   for (it = p_list->m_head; it != NULL; it = it->next)
   {
      const struct BookData book = it->data;
      if (book.book_shelf_no == p_shelf_no)
         p_show(book);
   }
}
void BookListDisplayedAllList(struct BookList* p_list, ShowBookData show)
{
   struct BookNode* it;
   /* Use this to iterate through the loop*/
   for (it = p_list->m_head; it != NULL; it = it->next)
   {
      const struct BookData book = it->data;
      show(book);
   }
}
void BookListFindByString(struct BookList*  p_list,
                         const char* const find_str,
                         ShowBookData      show)
{
   struct BookNode* it;
   char*            search_str;
   struct BookData  book;

   /* Use this to iterate through the loop*/
   for (it = p_list->m_head; it != NULL; it = it->next)
   {
      book = it->data;

      search_str = (char*)malloc(sizeof(char) *
                                 (strlen(book.book_author) + strlen(book.book_name) + 2));
      strcpy(search_str, book.book_author);
      strcat(search_str, ":");
      strcat(search_str, book.book_name);

      if (strstr(search_str, find_str) != NULL)
      {
         show(book);
      }
      free(search_str);
   }
}
void BookListInsertInto(struct BookList* list, struct BookData data)
{
   struct BookNode* newnode = (struct BookNode*)(malloc(sizeof(struct BookNode)));

   newnode->data = data;
   newnode->next = NULL;

   /* As we are Inserting at Front*/
   newnode->next = list->m_head;
   list->m_head  = newnode;
}

int BookListBookDeIssue(struct BookList* p_list,
                        const int        book_code,
                        struct BookData* p_book)
{
   struct BookNode* it;
   struct BookData  tmp;

   /* Use this to iterate through the loop*/
   for (it = p_list->m_head; it != NULL; it = it->next)
   {
      if (it->data.book_code == book_code)
      {
         if (!it->data.is_issued)
            /*Cannot DeIssue Books which have not been issued*/
            return 0;
         strcpy(tmp.book_author, it->data.book_author);
         strcpy(tmp.book_name, it->data.book_name);
         strcpy(tmp.issue_student_name, "");
         tmp.is_issued     = 0;
         tmp.issue_time    = 0;
         tmp.book_shelf_no = it->data.book_shelf_no;
         tmp.book_code     = it->data.book_code;

         BookListDeleteByCode(p_list, book_code);
         BookListInsertInto(p_list, tmp);

         if (p_book != NULL)
            *p_book = tmp;

         return 1;
      }
   }
   return 0;
}
int BookListBookIssue(struct BookList*  p_list,
                      const char* const book_issuer_student,
                      const int         book_code)
{
   struct BookNode* it;
   struct BookData  tmp;

   /*Check if Student Has not issued another book*/
   if (BookListFindByStudentName(p_list, book_issuer_student, NULL))
      return 0;
   /* Use this to iterate through the loop*/
   for (it = p_list->m_head; it != NULL; it = it->next)
   {
      if (it->data.book_code == book_code)
      {
         if (it->data.is_issued)
            /*Cannot Issue Books Twice To Different People*/
            return 0;
         strcpy(tmp.book_author, it->data.book_author);
         strcpy(tmp.book_name, it->data.book_name);
         strcpy(tmp.issue_student_name, book_issuer_student);
         tmp.is_issued = 1;
         /*Get Current Time to set as time of issue*/
         tmp.issue_time    = time(NULL);
         tmp.book_shelf_no = it->data.book_shelf_no;
         tmp.book_code     = it->data.book_code;

         BookListDeleteByCode(p_list, book_code);
         BookListInsertInto(p_list, tmp);
         return 1;
      }
   }
   /*Unable to Insert Book*/
   return 0;
}

int BookListAdd(struct BookList*  list,
                const int         book_code,
                const char* const book_name,
                const char* const book_author,
                const int         book_shelf_no)
{
   struct BookData book;

   /* Books with the same code cannot be inserted*/
   if (BookListFindByCode(list, book_code, NULL))
      return 0;

   strcpy(book.issue_student_name, "");
   strcpy(book.book_author, book_author);
   strcpy(book.book_name, book_name);

   book.book_code     = book_code;
   book.book_shelf_no = book_shelf_no;
   book.issue_time    = 0;
   book.is_issued     = 0;

   BookListInsertInto(list, book);
   return 1;
}

#endif
