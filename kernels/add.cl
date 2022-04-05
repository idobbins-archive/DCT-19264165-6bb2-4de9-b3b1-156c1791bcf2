__kernel void add(__global const int *a, __global const int *b, __global int *r) {

    // Get the index of the current element to be processed
    int i = get_global_id(0);

    // Do the operation
    r[i] = a[i] + b[i];
}