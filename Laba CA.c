#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>


typedef struct _tab{
    unsigned long int time;
    double num;
} tab;

typedef struct _tnode{
    tab data;
    struct _tnode *left;
    struct _tnode *right;
} tnode;
double TIMEquick,TIMEbubble,TIMEshake,TIMEheap;
double TIMESline,TIMESbin,TIMEStree,TIMESint;
unsigned long int CMPRquick,CMPRbubble,CMPRshake,CMPRheap;
unsigned long int ITERquick,ITERbubble,ITERshake,ITERheap;
unsigned long int ITERSline,ITERSbin,ITERStree,ITERSint;
unsigned long int treesearch(tab *mas,unsigned long int numtofind,unsigned long int length);
unsigned long int linesearch(tab * mas,unsigned long int numtos,unsigned long int length);
unsigned long int binarysearch(tab *mas,unsigned long int numtos,unsigned long int length);
unsigned long int interpolationsearch(tab *mas, unsigned long int numtofind,unsigned long int length);
int bubblesort(tab *mas,int length);
int quicksort(tab *mas, int length);
int shakersort(tab *mas,int length);
int heapsort(tab *mas, int length);
void quicksortfunc(tab *mas,int low, int high);

tab* createarray(int length);
tab* copyarray(tab *mas,int length);
tnode* treeaddnode(tnode * tree, tab elem);
void treearrscan(tab * mas,tnode * tree, int lflag);
void deletetree(tnode *tree);

int main(){
    int i,flag=10,infflag=0;
    unsigned long int length,datemin,datemax,numtofind,smallestindex,lineindex=0,binindex=0,treeindex=0,interindex=0;
    double smallestnum=1.0;
    char c,name[100];
    FILE *f;
    tab *mas1,*mas2;
    struct tm m_time;
    while (flag){
        flag=10;
        numtofind=0;
        length=0;
        smallestindex=0;
        smallestnum=1.0;
        printf("%s","The way of creating array:\n1. Random array.\n2. Read from csv.\n3. Enter the array.\n0. Exit.\n");
        scanf("%d",&flag);
        fflush(stdin);
        system("CLS");
        switch (flag) {
        case 3: {
            printf("%s","Enter the length:\n");
            scanf("%lu",&length);
            fflush(stdin);
            printf("ENTER THE NUMBER AND TIME  %lu TIMES:\n",length);
            mas1=(tab*)malloc(length*sizeof(tab));
            for (i=0; i<length; ++i){
                scanf("%lf %lu",&mas1[i].num,&mas1[i].time);
                fflush(stdin);
            }
            flag=10;
            break;
        }
        case 1:
{
            printf("%s","Enter the length:\n");
            scanf("%lu",&length);
            fflush(stdin);
            mas1=createarray(length);
            flag=10;
            break;
        }
        case 2:{
            printf("%s","Enter the name:\n");
            gets(name);
            fflush(stdin);
            while ((f=fopen(name,"r"))==0){
                system("CLS");
                printf("Enter the correct name:\n");
                gets(name);
                fflush(stdin);
            }
            while ((c=fgetc(f))!=EOF)
                if (c=='\n') ++length;
            mas1=(tab*)malloc(length*sizeof(tab));
            fseek(f,0,SEEK_SET);
            for (i=0; fscanf(f,"%lf,%lu\n",&mas1[i].num,&mas1[i].time)!=EOF; ++i);
            flag=10;
            break;
        }
        case 0:{
            return 0;
        }
        default:{
            system("CLS");
            printf("%s","Wrong command!\n");
            flag=10;
            continue;
            break;
        }
        }
        m_time.tm_sec = 0;
        m_time.tm_min = 0;
        m_time.tm_hour = 0;
        m_time.tm_mday = 1;
        m_time.tm_mon = 0;
        m_time.tm_year = 80;
        datemin=mktime(&m_time);

        m_time.tm_sec = 0;
        m_time.tm_min = 0;
        m_time.tm_hour = 0;
        m_time.tm_mday = 31;
        m_time.tm_mon = 11;
        m_time.tm_year = 84;
        datemax=mktime(&m_time);

        for (i=0; i<length; ++i)
            if ((mas1[i].time<datemax)&&(mas1[i].time>datemin)&&(mas1[i].num<smallestnum)){
                smallestnum=mas1[i].num;
                smallestindex=i;
            }
        infflag=1;
        system("CLS");

        mas2=copyarray(mas1,length);
        if ((f=fopen("Array.txt","w"))==0){
            printf("STRANGE ERROR IN CREATING FILE!!\n");
            return(-1);
        }
        else{
            for (i=0; i<length; ++i)
                fprintf(f,"%4d) %.9lf %11lu %s",i+1,mas2[i].num,mas2[i].time,ctime(&mas2[i].time));
            fclose(f);
            f=0;
        }
        if (bubblesort(mas2,length)){
            printf("ERROR WHILE BUBBLESORTING");
            return (-1);
        }

        if ((f=fopen("Sorted Array.txt","w"))==0){
            printf("STRANGE ERROR IN CREATING FILE!!\n");
            return(-1);
        }
        else{
            for (i=0; i<length; ++i)
                fprintf(f,"%4d) %.9lf %11lu %s",i+1,mas2[i].num,mas2[i].time,ctime(&mas2[i].time));
            fclose(f);
            f=0;
        }

        free(mas2);
        mas2=copyarray(mas1,length);
        if (shakersort(mas2,length)){
            printf("ERROR WHILE INSERTIONSORTING");
            return (-1);
        }

        free(mas2);
        mas2=copyarray(mas1,length);
        if (heapsort(mas2,length)){
            printf("ERROR WHILE HEAPSORTING");
            return (-1);
        }

        free(mas2);
        mas2=copyarray(mas1,length);
        if (quicksort(mas2,length)){
            printf("ERROR WHILE QUICKSORTING");
            return (-1);
        }

        system("CLS");
        printf("Array size: %lu\n\n",length);
        printf("Quicksort:\nReplacements: %lu\nComparisons: %lu\nTime: %.3lf\n\n",ITERquick,CMPRquick,TIMEquick);
        printf("Heapsort:\nReplacements: %lu\nComparisons: %lu\nTime: %.3lf\n\n",ITERheap,CMPRheap,TIMEheap);
        printf("Bubblesort:\nReplacements: %lu\nComparisons: %lu\nTime: %.3lf\n\n",ITERbubble,CMPRbubble,TIMEbubble);
        printf("Shakersort:\nReplacements: %lu\nComparisons: %lu\nTime: %.3lf\n\n",ITERshake,CMPRshake,TIMEshake);
        printf("Minimal element between 1 Jan 1980 and 31 Dec 1984: %.9lf (index: %d in not sorted)\n",smallestnum,smallestindex);
        system("PAUSE");
        system("CLS");
        while (1){
            printf("%s","FIND:\n1. Random number,\n2. Number from keyboard.\n0. Exit.\n");
            scanf("%d",&flag);
            fflush(stdin);
            switch(flag){
            case 1:{
                numtofind=mas2[(rand()%length)].time;
                flag=10;
                break;
            }
            case 2:{
                printf("ENTER NUMBER:\n");
                scanf("%lu",&numtofind);
                fflush(stdin);
                flag=10;
                break;
            }
            case 3:{
                flag=15;
                break;
            }
            case 0:{
                return 0;
            }
            default:{
                system("CLS");
                printf("%s","NO SUCH COMMAND!\n");
                continue;
                break;
            }
            }
            if (flag==15){
                flag=10;
                system("CLS");
                break;
            }
            else{
                lineindex=linesearch(mas2,numtofind,length);
                printf("f1");
                binindex=binarysearch(mas2,numtofind,length);
                printf("f2");
                treeindex=lineindex;
                treesearch(mas1,numtofind,length);
                printf("f3");
                interindex=interpolationsearch(mas2,numtofind,length);
                printf("f4");
                system("CLS");
                printf("Array size: %d\nNumber to find: %lu\n\n",length,numtofind);
                printf("Linesearch:\nIterations: %lu\nElement index: %.lu\nTime: %.3lf\n\n",ITERSline,lineindex+1,TIMESline);
                printf("Treesearch:\nIterations: %lu\nElement index: %lu\nTime: %.3lf\n\n",ITERStree,treeindex+1,TIMEStree);
                printf("Interpolationsearch:\nIterations: %lu\nElement index: %lu\nTime: %.3lf\n\n",ITERSint,interindex+1,TIMESint);
                printf("Binarysearch:\nIterations: %lu\nElement index: %lu\nTime: %.3lf\n\n",ITERSbin,binindex+1,TIMESbin);
                system("PAUSE");
                system("CLS");
            }
        }

    }
    return 0;
}



unsigned long int treesearch(tab *mas,unsigned long int numtofind,unsigned long int length){
    int i;
    tnode *tree;
    TIMEStree=clock();
    ITERStree=0;
    tree=0;
    for (i=0; i<length; ++i)
        tree=treeaddnode(tree,mas[i]);
    while (tree->data.time!=numtofind){
        ++ITERStree;
        if (tree->data.time>numtofind){
            if(tree->left)
                tree=tree->left;
            else{
                TIMEStree=(clock()-TIMEStree)/(double)CLOCKS_PER_SEC;
                return(-1);
            }
        }
        else{
            if(tree->right)
                tree=tree->right;
            else{
                TIMEStree=(clock()-TIMEStree)/(double)CLOCKS_PER_SEC;
                return(-1);
            }
        }
    }
    TIMEStree=(clock()-TIMEStree)/(double)CLOCKS_PER_SEC;
    deletetree(tree);
    return 0;
}

tab* copyarray(tab *mas,int length){
    int i;
    tab *temp;
    temp=(tab*)malloc(length * sizeof(tab));
    for (i=0; i<length; ++i){
        temp[i].time=mas[i].time;
        temp[i].num=mas[i].num;
    }
    return temp;
}

tab* createarray(int length){
    int i;
    tab *temp;
    temp=(tab*)malloc(length*sizeof(tab));
    srand(time(0));
    for (i=0; i<length; ++i){
        temp[i].time=rand()%38142*54933+1;
        temp[i].num=rand()%9873*0.000051264+0.0000001261324;
    }
    return temp;
}

int shakersort(tab *mas,int length){
    int left,right,i;
    ITERshake=0;
    CMPRshake=0;
    TIMEshake=clock();
    tab temp;
    for ( left = 0, right = length - 1; left < right;){
        for ( i = left; i < right; i++){
            ++CMPRshake;
            if (mas[i + 1].time < mas[i].time){
                ++ITERshake;
                mas[i]=temp;
                mas[i]=mas[i+1];
                mas[i+1]=temp;
            }
        }
        right--;

        for ( i = right; i > left; i--){
            ++CMPRshake;
            if (mas[i - 1].time >  mas[i].time){
                ++ITERshake;
                mas[i]=temp;
                mas[i]=mas[i-1];
                mas[i-1]=temp;
            }
        }
        left++;
    }
    TIMEshake=(clock()-TIMEshake)/(double)CLOCKS_PER_SEC;
    return 0;
}


int bubblesort(tab *mas,int length){
    int i,j;
    tab temp;
    ITERbubble=0;
    CMPRbubble=0;
    TIMEbubble=clock();
    for (i=0; i<length-1; ++i){
        for (j=0; j<length-1-i; ++j){
            if (mas[j].time>mas[j+1].time){
                temp = mas[j];
                mas[j]=mas[j+1];
                mas[j+1]=temp;
                ++ITERbubble;
            }
            ++CMPRbubble;
        }
    }
    TIMEbubble=(clock()-TIMEbubble)/(double)CLOCKS_PER_SEC;
    return 0;
}

int heapsort(tab *mas, int length){
    int i;
    tnode *tree;
    ITERheap=0;
    CMPRheap=0;
    tree=0;
    TIMEheap=clock();
    for (i=0; i<length; ++i)
        tree=treeaddnode(tree,mas[i]);
    treearrscan(mas,tree,1);
    TIMEheap=(clock()-TIMEheap)/(double)CLOCKS_PER_SEC;
    deletetree(tree);
    return 0;
}



int quicksort(tab *mas, int length){
    CMPRquick=0;
    ITERquick=0;
    TIMEquick=clock();
    quicksortfunc(mas,0,length-1);
    TIMEquick=(clock()-TIMEquick)/(double)CLOCKS_PER_SEC;
    return 0;
}


void quicksortfunc(tab *mas,int low, int high){
    int l=low,r=high;
    static int i,min,max;
    static unsigned long int sred;
    tab temp;
    min=l;
    max=r;
    for (i=l; i<r; ++i){
        if (mas[i].time > mas[max].time){
            max=i;
        }
        if (mas[i].time < mas[min].time){
            min=i;
        }
    }
    sred=(mas[max].time + mas[min].time)/2;
    while (l <= r){
        ++CMPRquick;
        while (mas[l].time < sred){
            ++CMPRquick;
            ++l;
        }
        while (mas[r].time > sred){
            ++CMPRquick;
            --r;
        }
        if (l <= r){
            ++ITERquick;
            ++CMPRquick;
            temp=mas[l];
            mas[l]=mas[r];
            mas[r]=temp;
            --r;
            ++l;
        }
    }
    if (low < r){
        ++CMPRquick;
        quicksortfunc(mas,low,r);
    }
    if (high > l){
        ++CMPRquick;
        quicksortfunc(mas,l,high);
    }
}

unsigned long int binarysearch(tab *mas,unsigned long int numtofind, unsigned long int length){
    unsigned long int l,r,m;
    extern unsigned long int ITERSbin;
    extern double TIMESbin;
    l=0;
    r=length-1;
    ITERSbin=0;
    TIMESbin=clock();
    while (l<=r){
        m=(l+r)/2;
        ++ITERSbin;
        if (numtofind<mas[m].time){
            if (m==0)
                return -1;
            r=m-1;
        }
        else if (numtofind>mas[m].time)
            l=m+1;
        else{
            TIMESbin=(clock()-TIMESbin)/(double)CLOCKS_PER_SEC;
            return (m);
        }
    }
    TIMESbin=(clock()-TIMESbin)/(double)CLOCKS_PER_SEC;
    return -1;
}

unsigned long int interpolationsearch(tab *mas, unsigned long int numtofind,unsigned long int length){
    unsigned long int left=0,right=length-1,mid;
    ITERSint=0;
    TIMESint=clock();
    while ((mas[left].time < numtofind)&&(numtofind<mas[right].time)){
        ++ITERSint;
        mid = left + (numtofind - mas[left].time) * (right - left) / (mas[right].time - mas[left].time);
        if (mas[mid].time < numtofind)
            left = mid + 1;
        else if (mas[mid].time > numtofind)
            right = mid - 1;
        else{
            TIMESint=(clock()-TIMESint)/(double)CLOCKS_PER_SEC;
            return (mid);
        }
    }
    if (mas[left].time == numtofind){
        TIMESint=(clock()-TIMESint)/(double)CLOCKS_PER_SEC;
        return (left);
    }
    else if (mas[right].time == numtofind){
        TIMESint=(clock()-TIMESint)/(double)CLOCKS_PER_SEC;
        return (right);
    }
    else{
        TIMESint=(clock()-TIMESint)/(double)CLOCKS_PER_SEC;
        return (-1);
    }
}

unsigned long int linesearch(tab * mas,unsigned long int numtofind,unsigned long int length){
    int i;
    extern unsigned long int ITERSline;
    extern double TIMESline;
    ITERSline=0;
    TIMESline=clock();
    for (i=0; i<length; ++i){
        ++ITERSline;
        if (numtofind==mas[i].time){
            TIMESline=(clock()-TIMESline)/(double)CLOCKS_PER_SEC;
            return (i);
        }
    }
    TIMESline=(clock()-TIMESline)/(double)CLOCKS_PER_SEC;
    return(-1);
}
void treearrscan(tab * mas,tnode * tree, int lflag){
    static int i;
    if (tree){
        if (tree->left){
            treearrscan(mas,tree->left,0);
        }
        mas[i++]=tree->data;
        ++ITERheap;
        if (tree->right){
            treearrscan(mas,tree->right,0);
        }
    }
    if (lflag) i=0;
}

tnode* treeaddnode(tnode * tree, tab elem){
    if (tree){
        if ((elem.time)<((tree->data).time)){
            ++CMPRheap;
            tree->left=treeaddnode(tree->left, elem);
        }
        else{
            ++CMPRheap;
            tree->right=treeaddnode(tree->right, elem);
        }
    }
    else{
        ++ITERheap;
        tree=(tnode*)malloc(sizeof(tnode));
        tree->data=elem;
        tree->left=0;
        tree->right=0;
    }
    return (tree);
}

void deletetree(tnode *tree){
    if (tree){
        deletetree(tree->left);
        deletetree(tree->right);
        free(tree);
    }
}
