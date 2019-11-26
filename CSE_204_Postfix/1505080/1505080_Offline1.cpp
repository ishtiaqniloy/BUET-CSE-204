#include <iostream>
#include <cstdio>

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

/*    List l(2);

    l.insertItem(1);
    l.insertItemAtPos(2,0);
    l.insertItem(4);
    l.insertItemAtPos(5,1);
    l.insertItemAtPos(6,1);
    l.insertItemAtPos(5, 1);

    cout<< l.deleteItem() << endl;

    //cout<< l.deleteItem() << endl;
    //cout<< l.deleteItem() << endl;
    //cout<< l.deleteItem() << endl;
    //cout<< l.deleteItem() << endl;
    //cout<< l.deleteItem() << endl;
    //cout<< l.deleteItem() << endl;

/*    cout << l.deleteFirstItem(5)<<endl;
    cout << l.deleteFirstItem(9
                              )<<endl;

    l.insertItem(5);
    l.insertItem(6);
    l.insertItem(5);

    cout << l.deleteLastItem(5)<<endl;
    cout << l.deleteLastItem(5)<<endl;
    cout << l.deleteLastItem(7)<<endl;

    //l.clearList();
    //l.showList();

    cout << l.searchItem(5) << endl;
    cout << l.searchItem(9) << endl;*/

    char str[10];
    List l;

    while(true){
        gets(str);

        if(str[0]=='T'){
            break;
        }

        else if(str[0]=='C'){
            l.clearList();
        }

        else if (str[0]== 'S'){
            int a;
            sscanf(str+2, "%d" , &a);
            //cout << a << endl;
            l.searchItem(a);
        }

        else if (str[0]=='I'){
            int a,p, counter=0;

            for(int i=0; str[i]!=0;i++){
                if(str[i]==' '){
                    counter++;
                }


            }

            if(counter == 1){
                int a;
                sscanf(str+2, "%d" , &a);
                //cout << a << endl;
                l.insertItem(a);
            }

            else{
                sscanf(str+2, "%d %d" , &a, &p);
                //cout << a << endl;
                l.insertItemAtPos(a, p);
            }

        }

        else if(str[0] == 'D' && str[2]=='F'){
            int a;
            sscanf(str+4, "%d" , &a);
            //cout << a << endl;
            l.deleteFirstItem(a);

        }


        else if(str[0] == 'D' && str[2]=='L'){
            int a;
            sscanf(str+4, "%d" , &a);
            //cout << a << endl;
            l.deleteLastItem(a);

        }

        else if(str[0]=='D' && str[1]==0){
            l.deleteItem();
        }

        else{
            cout << "Invalid Input" << endl;

        }



    }






    return 0;
}

