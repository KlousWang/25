#include <iostream>
using namespace std;

// 合并两个已排序的子数组
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;  // 左子数组的大小
    int n2 = right - mid;     // 右子数组的大小

    // 创建临时数组来存储左、右子数组的元素
    int leftArr[n1], rightArr[n2];

    // 拷贝数据到临时数组
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    // 合并临时数组
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // 拷贝剩余的元素
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// 归并排序的递归实现
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // 找到中点
        int mid = left + (right - left) / 2;

        // 对左右两部分进行归并排序
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // 合并已排序的两部分
        merge(arr, left, mid, right);
    }
}

// 打印数组函数
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    // 测试数组
    int arr[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "原数组: ";
    printArray(arr, size);

    // 调用归并排序
    mergeSort(arr, 0, size - 1);

    cout << "排序后的数组: ";
    printArray(arr, size);

    return 0;
}
