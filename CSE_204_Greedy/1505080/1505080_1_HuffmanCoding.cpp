#include<cstdio>
#include <iostream>

using namespace std;

#define MAX_HEAP_SIZE 128
#define MAXREAL 999999.0

class charNode{
public:
    int data;
    charNode * leftChild;
    charNode * rightChild;
    char *str;


    charNode(int d=0, charNode * l=0, charNode * r=0 ){
        data = d;
        leftChild = l;
        rightChild = r;
        str = new char[10];
        str[0] = 0;
    }

};

class HeapItem{
public:
	int data; //actual data that is stored
	float key; //key value of the data, heap is constructed based on key
	charNode *node;

	HeapItem (){
        data = -1;
        key = -1;
        node = 0;
	}

	HeapItem(const HeapItem &h){
        this->data = h.data;
        this->key = h.key;
        this->node = new charNode(h.node->data, h.node->leftChild, h.node->rightChild);
	}

};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap{
public:
	HeapItem * A; //stores heap items, e.g., nodes
	int heapLength;
	int * map;

	MinHeap(){ //constructor
		A = new HeapItem[MAX_HEAP_SIZE];
		map = new int[MAX_HEAP_SIZE];
		for(int i=0; i<MAX_HEAP_SIZE; i++){
            map[i] = 0;     ///sometimes some values are not automatically set to 0, thus gives wrong output
		}
		heapLength=0;
	}

	~MinHeap(){ //destructor
		if(map) delete [] map;
		if(A) delete [] A;
		map = 0; //set to NULL after deletion
		A = 0; //set to NULL after deletion
	}

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
	void initialize(int v[], int n){
		heapLength = n;
		for(int i=0; i<n; i++){ //nodes are stored from index 1 instead of 0 in the heap
			A[i+1].data = v[i];
			A[i+1].key = MAXREAL;
			map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
		}
	}

	//this function inserts a new (data,key) pair in the heap
    //call to buHeapify is required
    void insertItem(int data, float key, charNode* c = 0){     ///opt 1

        if(data<0 || data>MAXREAL){
            printf("Invalid input data\n");
            return;
        }
        else if (data !=0 && map[data]!=0){
            printf("Item already at index %d. Recurrence of Data not Supported...\n" , map[data]);
            return;
        }

        heapLength++;
        A[heapLength].data = data;
        A[heapLength].key = key;
        if(c == 0){
            c = new charNode(data);
        }
        A[heapLength].node =  c;

        map[data] = heapLength;
        buHeapify(heapLength);

    }

    //this function removes (and returns) the node which contains the minimum key value
	HeapItem removeMin(){           ///opt 2
        HeapItem temp;
        if(heapLength==0){
            printf("Empty Heap\n");
            temp.data = -1;
            temp.key = MAXREAL+1;
            return temp;
        }

        temp = A[1];
        A[1] = A[heapLength];
        heapLength--;
        heapify(1);
        map[temp.data] = 0;
        return temp;
	}

    //The function updates the key value of an existing data stored in the heap
	//Note that updates can result in an increase or decrease of key value
	//Call to heapify or buheapify is required
	void updateKey(int data, float key){    ///opt 3
		//Write your codes here
		int index = map[data];
		if(index==0){
            printf("Item Not Found\n");
            return;
		}
		float oldKey = A[index].key;
		A[index].key = key;

		if(key >  oldKey){
            heapify(index);
		}
		else if(key < oldKey){
            buHeapify(index);
		}
	}

    //This function returns the key value of a data stored in heap
	float getKey(int data){
		int i = map[data];
		if( i == 0){
            printf("Invalid data\n");
            return MAXREAL+1;
		}
		return A[i].key;
	}

    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling this function will restore heap property
	void heapify(int i){
		int l,r,smallest;
		while(1)
		{
			l=2*i;      //left child index
			r=2*i+1;    //right child index
			smallest=i;
			if(l>heapLength && r>heapLength)
				break; //nothing to do, we are at bottom
			else if(r>heapLength)
				smallest = l;
			else if(l>heapLength)
				smallest = r;
			else if( A[l].key < A[r].key )
				smallest = l;
			else
				smallest = r;

			if(A[i].key <= A[smallest].key)
				break;	//we are done heapifying
            else{
                //swap nodes with smallest child, adjust map array accordingly
				HeapItem t;
				t=A[i];
				A[i]=A[smallest];
				map[A[i].data]=i;
				A[smallest]=t;
				map[A[smallest].data]=smallest;
				i=smallest;
			}
		}
	}

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then calling this function restores heap property
	void buHeapify(int i){
        int par;
        while(i!=1){
            par = i/2;
            if( A[par].key > A[i].key){
                HeapItem temp = A[par];
                A[par] = A [i];
                A[i] = temp;
                map[A[par].data] = par;
                map[A[i].data] = i;
                i = par;
            }
            else{
                break;
            }
        }
	}

    void printHeap(){
        printf("Heap length: %d\n", heapLength);
        for(int i=1;i<=heapLength;i++)
        {
            printf("(%d,%.0f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

	bool Empty(){
		if(heapLength==0)return true;
		else return false;
	}
};

void makeCode(charNode *node, char *codes[]){
    if(node->leftChild==0 && node ->rightChild==0){
        codes[node->data] = node->str;

        //printf("In recursion: %c %s\n", node->data, node->str);

        return;
    }

    if(node->leftChild!=0){
        char *temp = new char[11];
        sprintf(temp, "%s1", node->str);

        node->leftChild->str = temp;

        makeCode(node->leftChild, codes);

    }

    if(node->rightChild!=0){
        char *temp = new char[11];
        sprintf(temp, "%s0", node->str);

        node->rightChild->str = temp;

        makeCode(node->rightChild, codes);

    }

    return;

}

int main(){
    char d;
    int k;
    MinHeap heap;
    charNode *head = 0;
    charNode *c = 0;

    char *codes[128];
    for(int i=0; i<128; i++){
        codes[i] = 0;
    }

    int n;

    scanf("%d", &n);

    for(int i = 0; i< n; i++){
        cin >> d >> k;
        //charNode c(d);
        heap.insertItem( d, k);
    }


    HeapItem temp1, temp2;

    while(!heap.Empty()){

        //heap.printHeap();

        temp1 = heap.removeMin();
        float k1 = temp1.key;
        //printf("%d %.0f %d\n", temp1.data, k1, temp1.node->data);

        if(heap.Empty() ){
            head = temp1.node;
            break;
        }

        temp2 = heap.removeMin();
        float k2 = temp2.key;
        //printf("%d %.0f %d\n", temp2.data, k2, temp2.node->data);

        c  = new charNode(0, temp2.node, temp1.node);

        heap.insertItem(0, k1+k2, c);

    }

    //printf("\n\nhead data = %d\n", head->data);

    head->str[0] = 0;

    makeCode(head, codes);

    for(int i=0; i<128; i++){
        if(codes[i] == 0)    continue;

        else printf("%c %s\n", i, codes[i]);

    }

    return 0;

}


