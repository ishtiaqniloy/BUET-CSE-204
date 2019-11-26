#include<stdio.h>
#include<stdlib.h>

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode{
    int item;
    struct listNode * next;
};

struct listNode * searchItem(int item);

struct listNode * list;
struct listNode * tail;

void initializeList(){
    list = 0;  //initially set to NULL
	tail = 0;
}

//add required codes to insert item at the beginning, remember to properly set the tail pointer!
int insertItem(int newItem){        ///opt 1
    struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = newItem ;

	if(list==0){        //adding to empty list
        tail = newNode;
	}

	newNode->next = list ; //point to previous first node
	list = newNode ; //set list to point to newNode as this is now the first node
	return SUCCESS_VALUE ;


}

int insertLast(int item){        ///opt 2
    struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item;
	newNode->next=0;

	if(list==0){        //adding to an empty list
        list = newNode;
        tail = newNode;
        return SUCCESS_VALUE;
	}

	tail->next = newNode;
	tail = newNode;

    return SUCCESS_VALUE;


}

//add required codes to delete item, remember to properly set the tail pointer!

int deleteItem(int item){        ///opt 3
    struct listNode *temp, *prev ;
	temp = list ; //start at the beginning

	while (temp != 0){
		if (temp->item == item) break ;
		prev = temp;
		temp = temp->next ; //move to next node
	}

	if (temp == 0) return NULL_VALUE ; //item not found to delete

	if (temp == list && temp == tail){  //only element
		list = 0;
		tail = 0;

		free(temp) ;
	}

	else if (temp == list){  //delete the first node
		list = list->next ;
		free(temp) ;
	}

	else if (temp == tail){  //delete the last node
		prev->next = temp->next ;
		tail = prev;
		free(temp);
	}

	else{
		prev->next = temp->next ;
		free(temp);
	}
	return SUCCESS_VALUE ;

}

int deleteAfter(int oldItem){        ///opt 4
    struct listNode *oldItemPtr, *nextPtr, *temp;

	oldItemPtr = searchItem(oldItem);
    if(list==0 || oldItemPtr ==0 || oldItemPtr->next ==0 ){ //list is empty or item not found or there is no item after the oldItem
        return NULL_VALUE;
    }

	temp = oldItemPtr->next;
	nextPtr = temp->next;
	oldItemPtr->next = nextPtr;

	if(nextPtr == 0){       //setting the tail correctly
        tail = oldItemPtr;
	}

	free(temp);
	return SUCCESS_VALUE;
}

struct listNode * searchItem(int item){     ///opt 5
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList(){       ///opt 6
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

        printf("1. Insert new item.  2. Insert Last.\n");
        printf("3. Delete Item.      4. Delete After.\n");
        printf("5. Search Item.      6. Print.          7. exit.\n");

        int ch;
        scanf("%d",&ch);

        if(ch==1){
            int item;
            scanf("%d", &item);
            insertItem(item);
        }

        else if(ch==2){
            int item;
            scanf("%d", &item);
            insertLast(item);
        }

        else if(ch==3){
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }

        else if(ch==4){
            int item;
            scanf("%d", &item);
            deleteAfter(item);
        }

        else if(ch==5){
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }

        else if(ch==6){
            printList();
        }

        else if(ch==7){
            break;
        }

        printf("List : ");  printList(); printf("\n");


    }

}
