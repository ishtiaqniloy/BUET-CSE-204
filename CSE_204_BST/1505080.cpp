///1505080 Offline Binary Search Tree

#include <stdio.h>
#include <stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode{

    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;

void initializeTree(){

    root = 0;
}

struct treeNode * makeTreeNode(int item){

    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item){     ///opt 1

    if(node==0) { //insert as the root as the tree is empty

        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0){ //insert as the left child

        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0){ //insert as the right child

        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}


 int deleteModule(struct treeNode * parent, struct treeNode *node){
    struct treeNode * temp = node;
    int minVal = -1;

    if(temp->left==0){
        minVal = temp->item;
        parent ->right = temp->right;
        free(temp);

        return minVal;
    }

    while(temp->left!=0){
        parent = temp;
        temp = temp->left;
        minVal= temp->item;

    }

    parent ->left = temp->right;
    free(temp);

    return minVal;


 }


int deleteItem(struct treeNode * node, int item){   ///opt 2
                                                    ///write your code here, return TRUE, FALSE

    if(root == 0){
        printf("Empty Tree\n");
        return FALSE_VALUE;
    }

    struct treeNode * target = node;
    struct treeNode * parent = 0;

    bool isLeftChild = false;
    while(true){        //searching for the item node and its parent
        if(target == 0){
            printf("Not Found");
            return FALSE_VALUE;
        }

        else if(item == target->item){
            printf("Found. Deleting...\n");
            break;
        }

        else if(item<target->item){
            parent = target;
            target = target->left;
            isLeftChild = true;
        }

        else if(item>target->item){
            parent = target;
            target = target->right;
            isLeftChild = false;
        }

    }

    if(target->left == 0 && target->right == 0){

        if(target == root){
            free(root);
            root = 0;
            return TRUE_VALUE;
        }

        if(isLeftChild){
            parent->left = 0;
            free(target);
        }

        else{
            parent->right = 0;
            free(target);
        }

    }

    else if(target->left == 0 && target->right != 0){
        struct treeNode * temp = target->right;

        target->item = temp->item;
        target->left = temp->left;
        target->right = temp->right;

        free(temp);

    }

    else if(target->left != 0 && target->right == 0){

        struct treeNode * temp = target->left;

        target->item = temp->item;
        target->left = temp->left;
        target->right = temp->right;

        free(temp);

    }

    else{
        int minVal = deleteModule(target, target->right);
        target->item = minVal;
    }

    return TRUE_VALUE;

}


struct treeNode * searchItem(struct treeNode * node, int item){     ///opt 3

    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


int calcNodeHeight(struct treeNode * node){      ///opt 4
                                                //return height of a node

    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item){       ///opt 5
                                //return height of an item in the tree
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);

}

void printInOrder(struct treeNode * node, int height){      ///opt 6

    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



int getSize(struct treeNode * node){        ///opt 7
    if (node == 0){
        return 0;
    }

    return getSize(node->left) + getSize(node->right) + 1;


}

int calcNodeDepth(struct treeNode * node){      ///opt 8
                                                //return depth of a node
    int c = 0, item;
    if(node == 0){
        return -1;
    }
    item = node->item;

    struct treeNode * temp;
    temp = root;

    while(true){

        if(temp == 0){
            return -1;
        }

        else if(item == temp->item){
            return c;
        }

        else if(item<temp->item){
            temp = temp->left;
        }

        else if(item>temp->item){
            temp = temp->right;
        }

        c++;

    }

 }


int calcDepth(int item){    ///opt 9
                            //return depth of an item in the tree
    int c = 0;

    struct treeNode * temp;
    temp = root;

    while(true){

        if(temp == 0){
            return -1;
        }

        else if(item == temp->item){
            return c;
        }

        else if(item<temp->item){
            temp = temp->left;
        }

        else if(item>temp->item){
            temp = temp->right;
        }

        c++;

    }

}

int getMinItem(struct treeNode * node){     ///opt 10
                                            //returns the minimum item in the tree
    struct treeNode * temp = node;
    int val = -1;
    while(temp!=0){
        val= temp->item;
        temp = temp->left;

    }

    return val;


}

int getMaxItem(struct treeNode * node){     ///opt 11
                                            //returns the maximum item in the tree
    struct treeNode * temp = node;
    int val = -1;
    while(temp!=0){
        val= temp->item;
        temp = temp->right;

    }

    return val;



}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound){     ///opt 12
                                                                            //returns number of items in the
    if(node == 0){
        return 0;
    }

    else if(node->item<leftBound){
        return rangeSearch(node->right, leftBound, rightBound);
    }


    else if(node->item>rightBound){
        return rangeSearch(node->left, leftBound, rightBound);
    }

    else{

        return 1 + rangeSearch(node->left, leftBound, rightBound) + rangeSearch(node->right, leftBound, rightBound);

    }


}


int main(void){

    initializeTree();
    while(1){

        printf("1. Insert Item.     2. Delete Item.         3. Search Item. \n");
        printf("4. Height of tree.  5. Height of an item.   6. PrintInOrder. \n");
        printf("7. Get Size.        8. Node Depth.          9. Item Depth. \n");
        printf("10.Min Item.        11.Max Item.            12.Range Search. \n");
        printf("13.Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1){

            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2){

            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch==3){

            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4){

            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5){

            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6){

            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==7){
            int s = getSize(root);
            printf("Size of the Tree is = %d", s);

        }
        else if(ch==8){
            int item;
            scanf("%d", &item);
            struct treeNode * node = searchItem(root, item);
            int depth = calcNodeDepth(node);
            printf("Depth of %d = %d\n", item, depth);


        }
        else if(ch==9){

            int item;
            scanf("%d", &item);
            int depth = calcDepth(item);
            printf("Depth of %d = %d\n", item, depth);

        }
        else if(ch==10){
            printf("Minimum of tree is = %d", getMinItem(root));

        }
        else if(ch==11){
            printf("Maximum of tree is = %d", getMaxItem(root));

        }
        else if(ch==12){
            int l,u, n ;
            scanf("%d %d", &l, &u);

            n = rangeSearch(root,l,u);

            printf("Number of items within given range = %d" , n);


        }
        else if(ch==13){

            break;
        }

        else{
            printf("Invalid Input\n");

        }


            printf("\n--------------------------------\n");
            printInOrder(root, calcNodeHeight(root));
            printf("--------------------------------\n");
            printf("\n");




    }

}
