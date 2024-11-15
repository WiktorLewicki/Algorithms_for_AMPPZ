#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& tab, vector<int>& left, vector<int>& right) {
    int R = right.size(), L = left.size();
    int r = 0, l = 0, t = 0;
    while(r < R && l < L) {
        if(left[l] <= right[r])
            tab[t++] = left[l++];
        else 
            tab[t++] = right[r++];
    }
    while(r < R) 
        tab[t++] = right[r++];

    while(l < L)
        tab[t++] = left[l++];
}

void mergeSort(vector<int>& tab) {
    if(tab.size() < 2) return;

    vector<int> left(tab.begin(), tab.begin() + tab.size()/2);
    vector<int> right(tab.begin()+tab.size()/2, tab.end());
    mergeSort(left);
    mergeSort(right);

    merge(tab, left, right);
}

int main() {
    vector<int> arr = {64, 34, 22, 12, 11, 90, 43, 12, 122};

    mergeSort(arr);
    for(auto i: arr) {
        cout<<i<<' ';
    }
}
