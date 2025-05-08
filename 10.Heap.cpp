#include<iostream>
using namespace std;

void Max_Heap(int *arr, int m, int n) {
    int j, t;
    t = arr[m];
    j = 2 * m;

    while (j <= n) {
        if (j < n && arr[j + 1] > arr[j]) {
            j = j + 1;
        }
        if (t > arr[j])
            break;
        else {
            arr[j / 2] = arr[j];
            j = 2 * j;
        }
    }
    arr[j / 2] = t;
}

void Build_heap(int *arr, int n) {
    for (int k = n / 2; k >= 1; k--) {
        Max_Heap(arr, k, n);
    }
}

int main() {
    int n;
    cout << "\nEnter no. of students: ";
    cin >> n;

    int arr[30]; // safer size for heap (1-based indexing)

    for (int i = 1; i <= n; i++) {
        cout << "\nEnter marks of student " << i << " : ";
        cin >> arr[i];
    }

    cout << "\nMarks of students: ";
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << " ";
    }

    Build_heap(arr, n);

    cout << "\nMax heap: ";
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}
