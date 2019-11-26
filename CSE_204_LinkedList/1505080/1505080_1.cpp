///1505080 Linked List
#include<stdio.h>
#include<stdlib.h>

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode{

    int item;
    struct listNode * next;
};

struct listNode * list;

struct listNode * searchItem(int item);

void initializeList(){

    list = 0;  //initially set to NULL
}

int insertItem(int item){    ///opt 1
                            //insert at the beginning of the linked list
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
	newNode->next = list ; //point to previous first node
	list = newNode ; //set list to point to newNode as this is now the first node
	return SUCCESS_VALUE ;
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

int insertBefore(int oldItem, int newItem){  ///opt 3
    struct listNode *temp, *prev, *newNode ;

    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = newItem;

	temp = list ;
	if(list==0 || list->item == oldItem){ // for an empty list or adding before first item
        newNode->next = list;
        list = newNode;
        return SUCCESS_VALUE;
	}

	while (temp->next!= 0){
        if(temp->next->item == oldItem){
            newNode->next = temp->next;
            temp->next = newNode;
            return SUCCESS_VALUE;
        }

        temp = temp->next;

	}

	newNode->next = list;
	list = newNode;

	return SUCCESS_VALUE;

}

int deleteItem(int item){        ///opt 4

	struct listNode *temp, *prev ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) break ;
		prev = temp;
		temp = temp->next ; //move to next node
	}
	if (temp == 0) return NULL_VALUE ; //item not found to delete
	if (temp == list) //delete the first node
	{
		list = list->next ;
		free(temp) ;
	}
	else
	{
		prev->next = temp->next ;
		free(temp);
	}
	return SUCCESS_VALUE ;

}

int deleteAfter(int oldItem){       ///opt 5
    struct listNode *oldItemPtr, *nextPtr, *temp;

	oldItemPtr = searchItem(oldItem);
    if(list==0 || oldItemPtr ==0 || oldItemPtr->next ==0 ){ //list is empty or item not found or there is no item after the oldItem
        return NULL_VALUE;
    }

	temp = oldItemPtr->next;
	nextPtr = temp->next;
	oldItemPtr->next = nextPtr;

	free(temp);
	return SUCCESS_VALUE;

}

int deleteLast(){            ///opt 6
    if(list==0){    //if the list is empty
        return NULL_VALUE;
    }

    struct listNode *temp, *prev ;
	temp = list;

	if(temp->next==0){  //if the list contains only one item
        list = 0;
        free(temp);
        return SUCCESS_VALUE;
	}

	while(temp->next !=0 ){
        prev = temp;
        temp=temp->next;
	}

	prev->next = 0;
	free(temp);

	return SUCCESS_VALUE;

}

struct listNode * searchItem(int item)      ///opt 7
{
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList()        ///opt 8
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d", temp->item);
        temp = temp->next;
        if(temp!=0)
            printf("->");
    }
    printf("\n");
}


int main(void)
{
    initializeList();
    while(1){

        printf("1. Insert new item.  2. Insert Last.   3. Insert Before.\n");
        printf("4. Delete Item.      5. Delete After.  6. Delete Last.\n");
        printf("7. Search Item.      8. Print.         9. exit.\n");

        //printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        //printf("4. Insert Last. 5. Print. 6. exit.\n");

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


        printf("List : ");  printList(); printf("\n");


    }

}
