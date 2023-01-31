#ifndef STATISTICS_H
#define STATISTICS_H

#include <inttypes.h>
#include <cstdlib>
#include <stdio.h>
#include <bits/stdc++.h>

class Statistics
{
private:
    static void swap(int16_t* a, int16_t* b);
    static int partition(int16_t arr[], int l, int r);
    static int randomPartition(int16_t arr[], int l, int r);
    static void medianUtil(int16_t arr[], int l, int r, int k, int16_t& a, int16_t& b);

public:
    Statistics();
    // Find median using Quick Select Method
    static double findMedian(int16_t arr[], int n);
    // Find median sorting data
    static double findMedian2(int16_t arr[], int n);
};

#endif // STATISTICS_H
