#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

double V[MAXN];
long long count = 0;

void merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    double L[MAXN], R[MAXN];
    for(int i = 0; i < n1; i++) L[i] = V[left + i];
    for(int i = 0; i < n2; i++) R[i] = V[mid + 1 + i];
    
    int p = 0;
    for(int jj = 0; jj < n2; jj++) {
        while(p < n1 && L[p] <= 2 * R[jj]) p++;
        count += n1 - p;
    }
    
    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            V[k++] = L[i++];
        } else {
            V[k++] = R[j++];
        }
    }
    while(i < n1) V[k++] = L[i++];
    while(j < n2) V[k++] = R[j++];
}

void mergeSort(int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

int main() {
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; i++) scanf("%lf", &V[i]);
    count = 0;
    mergeSort(0, N - 1);
    printf("%lld\n", count);
    for(int i = 0; i < N; i++) {
        printf("%.2f ", V[i]);
    }
    printf("\n");
    return 0;
}
