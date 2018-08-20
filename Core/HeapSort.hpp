
template<typename T>
__device__ void swap(T *p, T *q)
{
    T t;

    t = *p;
    *p = *q;
    *q = t;
}

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
template<typename T>
__device__ void heapify(T arr[], int n, int i)
{
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[largest] < arr[l])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[largest] < arr[r])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
template<typename T>
__device__ void heapSort(T arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        // Move current root to end
        swap(&arr[0], &arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
