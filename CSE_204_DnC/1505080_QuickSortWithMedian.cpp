///1505080 Offline QuickSort using Median as Pivot

#include  <cstdio>
#include <cstdlib>
#include <ctime>

using  namespace  std;

void arraySwapItem(int *arr, int pos1, int pos2){
    if(pos1==pos2 || arr[pos1] == arr [pos2])   return;

    int temp = arr[pos1];
    arr[pos1] = arr [pos2];
    arr[pos2] = temp;

}

int getMedianPos(int *arr, int *s, int k, int n){
    int cl = 0, cv = 0, cr = 0;
    int *sl, *sv, *sr;

    sl = new int[n];
    sv = new int[n];
    sr = new int[n];

    int idx = rand() % n;
    int arrIdx =  s[idx];
    int v = arr [arrIdx];

    for(int i =0; i <n; i++){
        if(arr[s[i]] < v ){
            sl[cl] = s[i];
            cl++;
        }
        else if(arr[s[i]] == v ){
            sv[cv] = s[i];
            cv++;
        }
        else{
            sr[cr] = s[i];
            cr++;
        }
    }

    /*printf("Value = %d, k = %d, idx = %d, arrIdx = %d\n" , v,  k, idx, arrIdx);
    printf("\ns : ");
    for(int i= 0; i< n; i++){
        printf("%d ", s[i]);
    }
    printf("\nsl : ");
    for(int i= 0; i< cl; i++){
        printf("%d ", sl[i]);
    }
    printf("\nsv : ");
    for(int i= 0; i< cv; i++){
        printf("%d ", sv[i]);
    }
    printf("\nsr : ");
    for(int i= 0; i< cr; i++){
        printf("%d ", sr[i]);
    }
    printf("\n");*/


    if(k<= cl){
        delete []sv;
        delete []sr;
        return getMedianPos(arr, sl, k, cl);

    }
    else if (cl < k && k <= cl+cv){
        delete []sl;
        delete []sv;
        delete []sr;
        return arrIdx;
    }
    else{
        delete []sl;
        delete []sv;
        return  getMedianPos(arr, sr, k-cl-cv, cr);
    }

}

int partition(int *arr, int p, int r){
    int n = r-p+1, u, v;
    int *s;
    s = new int[n];
    for(u = 0, v = p; v<=r; u++, v++){
        s[u] = v;
    }

    int med = getMedianPos(arr, s, (n+1)/2, n);
    //printf("med = %d\n" , med);
    arraySwapItem(arr, r, med);

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

    srand (time(NULL));

    quickSort(arr, 0, n-1);

    /*int *s;
    s = new int[n];
    for(int i = 2; i<n; i++){
        s[i-2] = i;
    }
    int m = getMedianPos(arr, s, (n+1-2)/2,  n-2);
    printf("Median= %d, Position = %d\n", arr[m], m);
*/

    printf("Median = %d\n", arr[ (n)/2 ]);
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }

    printf("\nMedian = %d\n", arr[ (n)/2 ]);


    printf("\n\n\n");

    return 0;
}


