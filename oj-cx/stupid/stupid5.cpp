#include <vector>
#include <iostream>
using namespace std;

#define MAX_NUM 100000

int recursion132(vector<vector<int>>& Arr, int s, int e) {

    if (e - s < 2)
        return 0;

    int mid = (s + e) / 2;
    int left = recursion132(Arr, s, mid);// 132 in the left
    int right = recursion132(Arr, mid, e);// 132 in the right
    int res = left + right;
    int i, j, k;
    int t = 0, q = 0;
    for (i = mid; i < e; i++)
        t += Arr[i][1];

    //1 in the left, 32 in the right;
    k = mid;
    for (i = s; i < mid; i++) {
        while (k < e && Arr[k][0] <= Arr[i][0])
            t -= Arr[k++][1];
        res += t;
    }

    // 13 in the left, 2 in the right
    t = 0;
    i = j = s;
    for (int k = mid; k < e; k++) {
        while (i < mid && Arr[i][0] < Arr[k][0])
            t += Arr[i++][3];
        while (j < mid && Arr[j][0] <= Arr[k][0])
            q += Arr[j++][2];
        res += t - q;
    }


    j = s;
    for (i = mid; i < e; i++) {// Update A[mid:e][1]
        while (j < mid && Arr[j][0] <= Arr[i][0])
            j++;
        Arr[i][1] += mid - j;
    }

    j = s;
    for (i = mid; i < e; i++) {// Update A[mid:e][2]
        while (j < mid && Arr[j][0] < Arr[i][0])
            j++;
        Arr[i][2] += j - s;
    }

    j = mid;
    for (i = s; i < mid; i++) {// Update A[s:mid][3]
        while (j < e && Arr[j][0] <= Arr[i][0])
            j++;
        Arr[i][3] += e - j;
    }


    //Merge sort
    vector<vector<int>> temp(e - s, vector<int>(4, 0));
    i = s, j = mid, k = 0;
    while (i < mid && j < e) {
        if (Arr[i][0] <= Arr[j][0])
            temp[k++] = Arr[i++];
        else
            temp[k++] = Arr[j++];
    }
    while (i < mid)
        temp[k++] = Arr[i++];
    while (j < e)
        temp[k++] = Arr[j++];

    for (int i = s; i < e; i++)
        Arr[i] = temp[i - s];
    return res;
}

int main(){
    int n;
    int a[MAX_NUM];
    // int b[MAX_NUM][4];
    vector<vector<int> >b(MAX_NUM,vector<int>(4,0));
    cin >> n;
    for (int i = 0;i < n;i++) {
        cin >> a[i];
        b[n - i - 1][0] = a[i];
    }

    cout << recursion132(b,0,n)<<endl;
}