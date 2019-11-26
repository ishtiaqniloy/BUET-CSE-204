#include <iostream>
#include <cstdio>

using namespace std;

class SortedList{
    int capacity;
    int listSize;
    int* arr;
public:

    SortedList(int c=5){
        capacity = c;
        listSize = 0;
        arr = new int[capacity];
    }

    ~SortedList(){
        delete[] arr;
    }

    SortedList(const SortedList &l){
        cout << "Copy Constructor" << endl;

        capacity = l.capacity;
        listSize = l.listSize;

        arr = new int[capacity];

        for(int i=0; i<listSize ; i++){
            arr[i]=l.arr[i];
        }

    }

    void showList(){
        for(int i = 0; i<listSize; i++){
            cout<<arr[i]<<' ';
        }
        if(listSize == 0){
            cout << "Empty List";
        }
        cout<<endl;
    }


    void insertItem(int a){
        if(listSize==capacity){
            cout << "List Full" << endl;
            int newCapacity= capacity*2;
            int *tempArr = new int [newCapacity];

            for(int i = 0; i<capacity; i++){
                tempArr[i]=arr[i];
            }

            delete []arr;
            arr = tempArr;
            capacity = newCapacity;
            cout << "Doubled the capacity" << endl;
        }
        int p;
        for(p = 0; p< listSize; p++){
            if(arr[p]>a)
                break;
        }

        listSize++;

        for(int j = listSize-1; j> p-1; j--){
            arr[j] = arr[j-1];

        }

        arr[p] = a;

        showList();
    }




    void deleteItem(int t){
        for(int i = 0; arr[i] <= t ; i++ ){
            if(arr[i] == t){
                for(int j=i; j < listSize-1; j++){
                    arr[j]=arr[j+1];
                }

                listSize--;
                showList();
                return;

            }

        }

        cout << "Element not found" << endl;

    }

    void clearList(){
        listSize = 0;
        cout << "Clear Completed" << endl;

    }

    int FindItem(int target){        ///binary search
        int last, first, mid;

        last=listSize-1;
        first=0;
        while(last>=first){
            mid=(last+first)/2;

            if(target==arr[mid]){
                cout << "Found at position " << mid << endl;
                return mid;
            }

            else if( target>arr[mid] ){
                first=mid+1;
            }

            else{
                last=mid-1;
            }

        }

        cout << "Not Found" << endl;
        return -1;

    }


};

int main(){

    char str[10];
    SortedList l;

    while(true){
        gets(str);

        if(str[0]=='T'){
            break;
        }

        else if(str[0]=='C'){
            l.clearList();
        }

        else if (str[0]== 'F'){
            int a;
            sscanf(str+2, "%d" , &a);
            //cout << a << endl;
            l.FindItem(a);
        }

        else if (str[0]=='I' ){
            int a;
            sscanf(str+2, "%d" , &a);
            //cout << a << endl;
            l.insertItem(a);

        }

        else if(str[0]=='D'){
            int a;
            sscanf(str+2, "%d" , &a);
            //cout << a << endl;
            l.deleteItem(a);
        }

        else{
            cout << "Invalid Input" << endl;

        }



    }






    return 0;
}

