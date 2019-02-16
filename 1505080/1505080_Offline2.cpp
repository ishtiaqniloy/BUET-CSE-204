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
        //cout << "Copy Constructor" << endl;

        capacity = l.capacity;
        listSize = l.listSize;

        arr = new int[capacity];

        for(int i=0; i<listSize ; i++){
            arr[i]=l.arr[i];
        }

    }

    int getSize(){
        return listSize;
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
            //cout << "List Full" << endl;
            int newCapacity= capacity*2;
            int *tempArr = new int [newCapacity];

            for(int i = 0; i<capacity; i++){
                tempArr[i]=arr[i];
            }

            delete []arr;
            arr = tempArr;
            capacity = newCapacity;
            //cout << "Doubled the capacity" << endl;
        }

        arr[listSize]=a;
        listSize++;

        //showList();

    }

    int deleteItem(){
        if(listSize==0)
            return -1;

        int temp = arr[listSize-1];

        listSize--;

        return temp;

    }


    void clearList(){
        listSize = 0;
        cout << "Clear Completed" << endl;

    }

};

int main(){

    List paren;
    char str[21];

    gets(str);

    int len = strlen(str);

    for(int i=0; i<len; i++) {
        if(str[i]=='(' || str[i]=='{' || str[i]=='[' ){
            paren.insertItem( str[i] );

        }

        else if(str[i]==')' || str[i]=='}' || str[i]==']' ){
            int c = paren.deleteItem();

            if(str[i]==')' && c!='(' || str[i]=='}' && c!='{' || str[i]==']' && c!='['){
                cout<< "Not Balanced" << endl;
                paren.clearList();
                return 0;

            }

        }

    }

    if(paren.getSize()!=0){
        cout<< "Not Balanced" << endl;
        paren.clearList();
        return 0;

    }

    cout << "Balanced" << endl;
    paren.clearList();
    return 0;

}












