#include<iostream>
using namespace std;

// 堆化函数，调整堆
void heapfy(int arr[], int n, int i) {
    int largest = i;        // 假设当前节点最大
    int left = 2 * i + 1;   // 左子节点
    int right = 2 * i + 2;  // 右子节点

    // 如果左子节点比当前节点大
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // 如果右子节点比当前节点大
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // 如果最大值不是当前节点，交换并递归堆化
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapfy(arr, n, largest); // 递归调整
    }
}

// 堆排序函数
void heapSort(int arr[], int n) {
    // 建立最大堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapfy(arr, n, i);
    }

    // 逐个交换堆顶元素与末尾元素，并重新堆化
    for (int i = n - 1; i >= 1; i--) {
        swap(arr[0], arr[i]);     // 将最大元素交换到末尾
        heapfy(arr, i, 0);         // 重新调整堆
    }
}

// 打印数组函数
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    // 测试数据
    int arr[] = {4, 10, 3, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);  // 计算数组长度

    cout << "原数组: ";
    printArray(arr, n);

    heapSort(arr, n);  // 执行堆排序

    cout << "排序后的数组: ";
    printArray(arr, n);

    return 0;
}
