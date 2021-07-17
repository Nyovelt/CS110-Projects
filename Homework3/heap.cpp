#include <bits/stdc++.h>
#define MAXN 1000006

long long int n, ans, ans1, siz;
int heap[MAXN];
int flag[MAXN];


void push(int e)
{
    int j = ++siz;
    for (; j != 1 && e < heap[j / 2]; j /= 2)
    {
        heap[j] = heap[j / 2];
    }
    heap[j] = e;
}

int pop()
{
    int ans = heap[1];
    heap[1] = heap[siz--];

    // for (int i = siz / 2; i > 0; i--)
    //     min_heapify( i, siz);
    
    int i = 1;
    while(i*2  <= siz){
        int j = i * 2;
        if(heap[j] > heap[j+1] && j+1<=siz){
            j++;
        }
        if (heap[j] > heap[i]) break;
        std::swap(heap[i], heap[j]);
        i = j;
    }

    //min_heapify(siz/2, siz);
    return ans;
}

int main()
{
    for (int i=0; i<32; i++){
        int a = 0;
        scanf("%d", &a);
        push(a);
    } 
    for (int i=0; i<32; i++){
        printf("%d ", heap[i+1]);
    } 
}