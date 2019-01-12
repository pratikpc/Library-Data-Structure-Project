#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
struct node
{
	char book_name[15];
	char author_name[15];
	char student_rollno[10];
	char book_no[5];
	struct node *next;
};
struct ll
{
	struct node *start;
};
struct node *insert(struct ll *l1)  // Function to create a linked list
{
	struct node *new_node;
	struct node *ptr;
	int num;
	char bname[15];
	char aname[15], srollno[10], bno[5];
	printf("Add the Books \n 1. Yes \n 2. No \n");
	scanf("%d", &num);
	while(num!=2)
	{
		new_node = (struct node*)malloc(sizeof(struct node)); // By Dynamic allocation
		printf("Enter the book name \n");
		scanf("%s",bname);
		printf("Enter Author name \n");
		scanf("%s",aname);
		printf("Enter student Roll Number \n");
		scanf("%s",srollno);
		printf("Enter Book no \n");
		scanf("%s", bno);
		strcpy(new_node->book_name,bname);
		strcpy(new_node->author_name,aname);
		strcpy(new_node->student_rollno,srollno);
		strcpy(new_node->book_no,bno);
		new_node->next = NULL;
		if(l1->start == NULL)
		{
			l1->start = new_node;
		}
		else
		{
			ptr = l1->start;
			while(ptr->next!=NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = new_node;
			
		}
		printf("Do you wanr to continue \n 1. Yes \t 2. No \n");
		scanf("%d", &num);
	}	
	return l1->start;	
}
struct node *delete_beg(struct ll *l1)
{
	struct node *ptr;
	ptr = l1->start;
	l1->start = l1->start->next;
	free(ptr);
	return l1->start;
}
struct node *delete(struct ll *l1)
{
	struct node *ptr, *preptr;
	char val[15];
	printf("Enter the book name to be deleted from the library\n");
	scanf("%s", &val);
	ptr = l1->start;
	if(strcmp(l1->start->book_name,val)==0)
	{
		l1->start = delete_beg(l1);
	}
	else
	{
		int temp = 0;
		preptr = ptr;
		while(ptr!= NULL)
		{
			preptr = ptr;
			ptr = ptr->next;
			if(strcmp(ptr->book_name,val) == 0)
			{
				temp = 1;
				break;
			}
		}
		if(temp == 1)
		{
			preptr->next = ptr->next;
		}
		else
		{
			printf("Book not Found \n");
		}
	}
	return l1->start;	
}
void display(struct ll *l1)
{
	struct node *ptr;
	ptr = l1->start;
	int i = 1;
	while(ptr!= NULL)
	{
		printf("%d\t", i);
		printf("%s\t", ptr->book_name);
		printf("%s\t", ptr->author_name);
		printf("%s\t", ptr->student_rollno);
		printf("%s\t", ptr->book_no);
		printf("\n");
		i++;
		ptr = ptr->next; 
	}
	
}
int main()
{
	struct ll l1;
	l1.start = NULL;
	int n;
	do
	{
	printf("ENTER YOUR CHOICE OF OPERATION \n 1. Add the books \n 2. Delete a book \n 3. Display books present \n 4. Exit \n");
	scanf("%d", &n);
	switch (n)
	{
		case 1 : printf("Enter the Book details to be added \n");
			 l1.start = insert(&l1);
			 break;
		case 2 : printf("Enter the Book details to be deleted \n");
				 l1.start = delete_beg(&l1);
			 break;
		case 3 : printf("Display the number of books \n");
			 display(&l1);
			 break;	
	}
	}while(n!=4);
	
}

