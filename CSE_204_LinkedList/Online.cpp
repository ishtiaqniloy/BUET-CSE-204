///1505080 Doubly Linked  List Online

#include<stdio.h>
#include<stdlib.h>

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
    struct listNode * prev;
};

struct listNode * list;
struct listNode * tail;

struct listNode * searchItem(int item);

void initializeList(){
    list = 0;  //initially set to NULL
    tail = 0;
}

int insertFirst(int item){      ///opt 1
                                //insert at the beginning
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;

	if(list==0) //inserting the first item
    {
        newNode->next = 0;
        newNode->prev = 0;
        list = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = list;
        list->prev = newNode;
        newNode->prev = 0;
        list = newNode;
    }
	return SUCCESS_VALUE ;
}

void insertAfter(int oldItem, int newItem){
    struct listNode * newNode, *oldNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item =  newItem ;

	if(list==0){            ///empty list
        list = newNode;
        newNode->next = 0;
        newNode->prev = 0;
        tail = newNode;
        return;
	}

	oldNode = searchItem(oldItem);

	if(oldNode == 0){       ///not found
        newNode->next = list;
        newNode->prev = 0;
        list = newNode;

	}

	else if(oldNode == tail){      ///at last
        oldNode->next = newNode;
        newNode->next = 0;
        newNode->prev = oldNode;

        tail = newNode;

	}

	else{       ///middle
        newNode->next = oldNode->next;
        newNode->next->prev = newNode;
        newNode->prev = oldNode;

        oldNode->next = newNode;

	}




}

struct listNode * searchItem(int item){     ///opt 2
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}


int deleteItem(int item){        ///opt 3
    struct listNode *tempNode, *prevNode ;

	tempNode = searchItem(item);

	if (tempNode == 0) return NULL_VALUE ; //item not found to delete

	else if (tempNode == list && tempNode == tail){  //only element
		list = 0;
		tail = 0;

		free(tempNode) ;
	}

	else if (tempNode == list){  //delete the first node
		list = list->next ;
		list->prev = 0;
		free(tempNode) ;
	}

	else if (tempNode == tail){  //delete the last node
        prevNode = tempNode->prev;
		prevNode->next = 0 ;
		tail = prevNode;
		free(tempNode);
	}

	else{
        prevNode = tempNode->prev;
		prevNode->next = tempNode->next ;
		tempNode->next->prev = prevNode;
		free(tempNode);
	}

	return SUCCESS_VALUE ;

}

int deleteAfter(int oldItem){  ///opt 4
    //write your codes here
    struct listNode *oldItemPtr, *nextPtr, *temp;

	oldItemPtr = searchItem(oldItem);
    if(list==0 || oldItemPtr ==0 || oldItemPtr->next ==0 ){ //list is empty or item not found or there is no item after the oldItem
        return NULL_VALUE;
    }

	temp = oldItemPtr->next;
	nextPtr = temp->next;
	oldItemPtr->next = nextPtr;

	if(nextPtr!=0){
        nextPtr->prev = oldItemPtr;
	}
	else{       //setting the tail correctly
        tail = oldItemPtr;
	}

	free(temp);
	return SUCCESS_VALUE;


}

int deleteLast(){           /// opt 5
    //write your codes here

    if(list==0){     //empty list
        return NULL_VALUE;
    }

    struct listNode *temp;
    temp = tail;

    if(list==tail){     //only 1 item
        list = 0;
        tail = 0;
    }
    else{
        tail = temp->prev;
        tail->next = 0;

    }

    free(temp);

    return SUCCESS_VALUE;
}



void printListForward(){        ///opt 6
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

void printListBackward(){       /// opt 7
	//will print the list backward starting from the tail position
    struct listNode * temp;
    temp = tail;
    while(temp!=0){
        printf("%d", temp->item);
        temp = temp->prev;

        if(temp!=0)
            printf("<-");
    }
    printf("\n");

}

int main(void)
{
    initializeList();
    while(1){
        printf("1. Insert First.  2. Insert After.   3. Search item.  \n");
        printf("4. Delete item.   5. Delete After.   6. Delete Last. \n");
        printf("7. Print forward. 8. Print backward. 9. exit.\n");

        int ch;
        scanf("%d",&ch);

        if(ch==1){
            int item;
            scanf("%d", &item);
            insertFirst(item);
        }

        else if(ch==2){
            int oldItem, newItem;
            scanf("%d %d", &oldItem, &newItem);
            insertAfter(oldItem, newItem);
        }

        else if(ch==3){
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
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

        else if(ch==6){
            int item = deleteLast();
            //if(item!=NULL_VALUE) printf("Deleted: %d\n", item);
        }

        else if(ch==7){
            printListForward();
        }

        else if(ch==8){
            printListBackward();
        }

        else if(ch==9){
            break;
        }

        else{
            printf("Invalid Selection\n");
        }

        printf("Forward  : ");  printListForward();
        printf("Backward : ");  printListBackward();
        printf("\n");

    }

}
