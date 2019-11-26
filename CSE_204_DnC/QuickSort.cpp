///1505080 QuickSort using Last Item as Pivot

#include  <cstdio>

using  namespace  std;

void arraySwapItem(int *arr, int pos1, int pos2){
    if(pos1==pos2 || arr[pos1] == arr [pos2])   return;

    int temp = arr[pos1];
    arr[pos1] = arr [pos2];
    arr[pos2] = temp;

}

int partition(int *arr, int p, int r){
    int x = arr[r];

    int i = p-1;
    for(int j = p; j < r; j++){
        if(arr[j]<=x){
            i++;
            arraySwapItem(arr, i, j);
        }
    }
    arraySwapItem(arr, i+1, r);

    return i+1;

}

void quickSort(int *arr, int p, int r){
    if(p<r){
        int q = partition(arr, p, r);
        quickSort(arr, p, q-1);
        quickSort(arr, q+1, r);

    }
}

int main(){
    int n;
    int *arr;
    printf("Enter number of items : ");
    scanf("%d", &n);
    arr = new int[n];

    printf("Enter the items :\n");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    quickSort(arr, 0, n-1);

    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
