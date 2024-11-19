#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
    int i, b = 0;
    char a[] = "10101010";  // Example binary input
    int n = strlen(a);      // Length of the binary input
    printf("Length of input: %d\n", n);
   
    int arr[n];
    int index = 0;
   
    // Convert the string of binary digits to an integer array
    for(i = n - 1; i >= 0; i--) {
        arr[i] = a[i] - '0';
        printf("%d", arr[i]);
    }
    printf("\n");

    // Calculate the number of parity bits required
    if(n > 4) {
        int k = n, r1 = 1, two = 2;
        while(two < k + r1 + 1) {
            two *= 2;
            r1++;
        }
        printf("Number of parity bits: %d\n", r1);

        // Create a new array to include both the data and parity bits
        int arr1[n + r1];
        for(i = 0; i < n + r1; i++) {
            arr1[i] = 0;  // Initialize the array
        }
       
        // Insert data bits and mark positions for parity bits
        two = 1;
        int pos = 0;
        for(int i = 1; i < n + r1 + 1; i++) {
            if(i == two) {
                two *= 2;
                arr1[n + r1 - i] = -1;  // Mark parity bit positions
            } else {
                arr1[n + r1 - i] = arr[pos++];  // Insert data bits
            }
        }

        printf("Array with data and placeholders for parity bits:\n");
        for(i = 0; i < r1 + n; i++) {
            printf("%d ", arr1[i]);
        }
        printf("\n");

        // Calculate parity bits
        int r[r1];
        index = 0;
        for(i = 0; i < r1; i++) {
            int count = 0;
            for(int j = 0; j < n + r1; j++) {
                if(((j + 1) & (1 << i)) && arr1[n + r1 - 1 - j] == 1) {
                    count++;
                }
            }
            r[index++] = (count % 2 == 0) ? 0 : 1;
        }

        // Insert parity bits into their positions
        two = 1;
        index = 0;
        for(int i = 1; i < n + r1 + 1; i++) {
            if(i == two) {
                arr1[n + r1 - i] = r[index++];
                two *= 2;
            }
        }

        printf("Final array with data and parity bits:\n");
        for(i = 0; i < n + r1; i++) {
            printf("%d ", arr1[i]);
        }
        printf("\n");
    }
}