#include  <cstdio>

#define MAX_HEAP_SIZE 10000

#define MAXREAL 999999.0

using  namespace  std;


class HeapItem{
public:
	int data; //actual data that is stored
	float key; //key value of the data, heap is constructed based on key
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
    void insertItem(int data, float key){     ///opt 1
        if(data<0 || data>MAXREAL){
            printf("Invalid input data\n");
            return;
        }
        else if (map[data]!=0){
            printf("Item already at index %d. Recurrence of Data not Supported...\n" , map[data]);
            return;
        }

        heapLength++;
        A[heapLength].data = data;
        A[heapLength].key = key;

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
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

	bool Empty(){
		if(heapLength==0)return true;
		else return false;
	}
};


int main(){
    MinHeap heap;

    int n;
    scanf("%d", &n);

    int coins[n], num[n], c;
    for(int i=0; i<n; i++){
        scanf("%d", &c);
        heap.insertItem(c,c);
    }

    for(int i=0; i<n; i++){
        coins[i] = heap.removeMin().data;
        num[i] = 0;
        //printf("%d ", coins[i]);
    }

    int val, i=n-1, temp, counter = 0;
    scanf("%d", &val);

    while(val!=0 && i>=0){
        if(val<coins[i]){
            i--;
            continue;
        }

        temp = val/coins[i];
        val%=coins[i];
        num[i] = temp;
        counter+=temp;
        i--;
    }

    printf("%d\n", counter);

    for(i=n-1; i>=0; i--){
        if(num[i]==0)   continue;
        printf("%d %d\n", coins[i], num[i]);
    }



    return 0;
}

