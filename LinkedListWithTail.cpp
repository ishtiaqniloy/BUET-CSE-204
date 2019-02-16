#include<stdio.h>
#include<stdlib.h>

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;
struct listNode * tail;

void initializeList(){
    list = 0;  //initially set to NULL
	tail = 0;
}

struct listNode * searchItem(int item){
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList(){
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

//add required codes to insert item at the beginning, remember to properly set the tail pointer!

int insertItem(int item){    ///opt 1
                            //insert at the beginning of the linked list
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
	newNode->next = list ; //point to previous first node
	list = newNode ; //set list to point to newnode as this is now the first node
	return SUCCESS_VALUE ;
}


//add required codes to delete item, remember to properly set the tail pointer!

int deleteAfter(int oldItem){       ///opt 5


    struct listNode *oldItemPtr, *nextPtr, *temp;

	oldItemPtr = searchItem(oldItem);
    if(list==0 || oldItemPtr ==0){ //list is empty or item not found
        return NULL_VALUE;
    }

	temp = oldItemPtr->next;
    if(temp ==0){   //there is no item after the oldItem
        return NULL_VALUE;
    }
	nextPtr = temp->next;

	oldItemPtr->next = nextPtr;

	free(temp);

	return SUCCESS_VALUE;


}
int insertLast(int item){    ///opt 2

    struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
	newNode->next = 0;

	if(list==0){    //empty list
        list = newNode;
        return SUCCESS_VALUE;
	}

    struct listNode * temp=list;
    while(temp->next!=0){
        temp = temp->next;

    }
	temp->next = newNode;

	return SUCCESS_VALUE;



}



int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item.  2. Insert Last.   3. Insert Before.\n");
        printf("4. Delete Item.      5. Delete After.  6. Delete Last.\n");
        printf("7. Search Item.      8. Print.         9. exit.\n");

        //printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        //printf("4. (Add from homework). 5. Print. 6. exit.\n");

        int ch;
        scanf("%d",&ch);

        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }

        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            insertLast(item);
        }

        else if(ch==3)
        {
            int newItem, oldItem;
            scanf("%d %d", &oldItem, &newItem);
            insertBefore(oldItem, newItem);
        }

        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }

        else if(ch==5)
        {
            int oldItem;
            scanf("%d", &oldItem);
            deleteAfter(oldItem);


        }

        else if(ch==6)
        {
            deleteLast();


        }

        else if(ch==7)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }

        else if(ch==8)
        {
            printList();
        }

        else if(ch==9)
        {
            break;
        }

        else{
            printf("Invalid Selection\n");
        }


        printf("List : ");  printList();



    }

}
