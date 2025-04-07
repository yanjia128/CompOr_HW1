#include <stdio.h>

int arraySearch(int *p_a, int arr_size, int target)
{
    int result = -1;

    asm volatile(
        "li t0, 0            \n\t"
        "loop_start:         \n\t" 
        "bge t0, %2, end_loop \n\t" // if i >= arr_size, exit loop

        "slli t1, t0, 2      \n\t" // t1 = i * 4 (size of int)
        "add t1, %0, t1      \n\t" // t1 = p_a + i * 4
        "lw t3, 0(t1)        \n\t" // load the value at p_a[i] into t3
        "beq t3, %3, found   \n\t" // if p_a[i] == target, jump to found
        "addi t0, t0, 1      \n\t" // i++
        "j loop_start        \n\t" // jump to the start of the loop

        "found:              \n\t"
        "mv %0, t0           \n\t" // result = i
        "j end_loop          \n\t" // jump to end_loop
        "end_loop:           \n\t"


        :"=r"(result)
        :"r"(p_a), "r"(arr_size), "r"(target)
        :"t0","t1","t3"
        );


    return result;
}

// Main function to test the implementation
int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }
    int arr_size;
    fscanf(input, "%d", &arr_size);
    int arr[arr_size];

    // Read integers from input file into the array
    for (int i = 0; i < arr_size; i++) {
        int data;
        fscanf(input, "%d", &data);
        arr[i] = data;
    }
    int target;
    fscanf(input, "%d", &target);
    fclose(input);

    int *p_a = &arr[0];

    int index = arraySearch(p_a, arr_size, target);

    // Print the result
    printf("%d ", index);
    printf("\n");

    return 0;
}
