#include "statistics.h"

Statistics::Statistics()
{

}

void Statistics::swap(int16_t* a, int16_t* b)
{
    int16_t temp = *a;
    *a = *b;
    *b = temp;
}

int Statistics::partition(int16_t arr[], int l, int r)
{
    int16_t lst=arr[r];
    int i=l, j=l;
    while (j < r) {
        if (arr[j] < lst) {
            swap(&arr[i], &arr[j]);
            i++;
        }
        j++;
    }
    swap(&arr[i], &arr[r]);
    return i;
}

int Statistics::randomPartition(int16_t arr[], int l, int r)
{
    int n = r - l + 1;
    int pivot = rand() % n;
    swap(&arr[l + pivot], &arr[r]);
    return partition(arr, l, r);
}

void Statistics::medianUtil(int16_t arr[], int l, int r, int k, int16_t& a, int16_t& b)
{
    if (l <= r) {
        int partitionIndex = randomPartition(arr, l, r);

        if (partitionIndex == k) {
            b = arr[partitionIndex];
            if (a != -1)
                return;
        }

        else if (partitionIndex == k - 1) {
            a = arr[partitionIndex];
            if (b != -1)
                return;
        }

        if (partitionIndex >= k)
            return medianUtil(arr, l, partitionIndex - 1, k, a, b);
        else
            return medianUtil(arr, partitionIndex + 1, r, k, a, b);
    }

    return;
}

double Statistics::findMedian(int16_t arr[], int n)
{
    double ans;
    int16_t a = -1, b = -1;

    if (n % 2 == 1) {
        medianUtil(arr, 0, n - 1, n / 2, a, b);
        ans = (double)b;
    }
    else {
        medianUtil(arr, 0, n - 1, n / 2, a, b);
        ans = (double)((a + b) / 2.0);
    }

    return ans;
}

double Statistics::findMedian2(int16_t arr[], int n)
{
    std::sort(arr, arr + n);

    double ans;
    if (n % 2 == 1) {
        ans = (double)arr[n/2];
    }
    else {
        ans = (double)(arr[n/2] + arr[n/2 - 1])/2.0;
    }

    return ans;
}
