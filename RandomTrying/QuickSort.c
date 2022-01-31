int Partition (int arr[], int low, int high) {        
    int pivotkey;
    pivotkey = arr[low];
    while (low<high) {
        while (low<high && (arr[high] > pivotkey) --high;
        arr[low] = arr[high];
        while (low<high && (arr[low] < pivotkey) ++low;
        arr[high] = arr[low];
    }
    arr[low] = pivotkey;
    return low;
}

void QSort (int arr[], int low, int high) {  
    int pivotloc;
    if(low<high) {
        pivotloc = Partition(arr, low, high);
        QSort(arr, low, pivotloc-1);
        QSort(arr, pivotloc+1, high);
    }
    return;
}
