#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

class List{
    int capacity;
    int listSize;
    int* arr;
public:

    List(int c=5){
        capacity = c;
        listSize = 0;
        arr = new int[capacity];
    }

    ~List(){
        delete[] arr;
    }

    List(const List &l){
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

        arr[listSize]=a;
        listSize++;

        showList();

    }

    void insertItemAtPos(int a, int p){
        if(listSize==capacity){
            //cout << "List Full" << endl;
            int newCapacity= capacity*2;
            int *tempArr = new int [newCapacity];

            for(int i = 0; i<capacity; i++){
                tempArr[i]=arr[i];
            }

            delete []arr;
            arr = tempArr;
            capacity = newCapacity;
            cout << "Doubled List Capacity" << endl;
        }
        listSize++;

        for(int i = listSize-1; i> p; i--){
            arr[i] = arr[i-1];

        }

        arr[p] = a;

        showList();

    }

    int deleteItem(){
        if(listSize==0)
            return NULL;

        int temp = arr[listSize-1];

        listSize--;

        if(listSize==0){
            cout << "Empty List" << endl;

        }
        else
            showList();

        return temp;

    }

    int deleteFirstItem(int a){
        for(int i = 0; i < listSize ; i++ ){
            if(arr[i] == a){
                int temp  = arr[i];
                for(int j=i; j < listSize-1; j++){
                    arr[j]=arr[j+1];
                }

                listSize--;
                showList();

                return temp;

            }

        }

        cout << "Element not found" << endl;

        return -1;

    }

    int deleteLastItem(int a){
        for(int i = listSize-1; i >=0 ; i-- ){
            if(arr[i] == a){
                int temp  = arr[i];
                for(int j=i; j < listSize-1; j++){
                    arr[j]=arr[j+1];
                }

                listSize--;
                showList();

                return temp;

            }

        }

        cout << "Element not found" << endl;

        return -1;

    }

    void clearList(){
        listSize = 0;
        cout << "Clear Completed" << endl;

    }

    int searchItem(int t){      ///linear search
        for(int i = 0; i < listSize ; i ++ ){
            if(arr[i]==t){
                cout << "Found at position " << i << endl;
                return i;
            }

        }

        cout << "Not Found" << endl;
        return -1;

    }







};

int main(){

    char str[80];
    List l;

    gets(str);
    int len = strlen(str);
    int op1=0, op2=0, r=0;

   // l.insertItem(str[0]-'0');
   // l.insertItem(str[1]-'0');

    for(int i = 0; i < len; i++){
        if(str[i]=='+' ){
            op2=l.deleteItem();
            op1=l.deleteItem();
            r=op1+op2;
            l.insertItem(r);
        }
        else if(str[i]=='-' ){
            op2=l.deleteItem();
            op1=l.deleteItem();
            r=op1-op2;
            l.insertItem(r);
        }
        else if(str[i]=='*' ){
            op2=l.deleteItem();
            op1=l.deleteItem();
            r=op1*op2;
            l.insertItem(r);
        }
        else if(str[i]=='/' ){
            op2=l.deleteItem();
            op1=l.deleteItem();
            r=op1/op2;
            l.insertItem(r);
        }

        else{
            l.insertItem(str[i] - '0');
        }

    }

    cout << "Result = " << l.deleteItem() << endl;




    return 0;
}


