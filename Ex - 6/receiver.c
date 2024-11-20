#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
    int i, j, n, r1 = 0, errorPos = 0;

    // Example received Hamming code (this should include data + parity bits)
    char received[] = "011100101010";  // Example with a 12-bit Hamming code

    n = strlen(received);  // Length of the received code
    int receivedArr[n];

    // Convert the received string into an integer array
    for(i = 0; i < n; i++) {
        receivedArr[i] = received[i] - '0';
    }

    // Determine the number of parity bits (r1)
    while((1 << r1) < n) {
        r1++;
    }

    printf("Number of parity bits: %d\n", r1);

    // Calculate the parity bits from the received code
    for(i = 0; i < r1; i++) {
        int count = 0;
        int pos = (1 << i);  // Position of the parity bit

        for(j = 1; j <= n; j++) {
            if(j & pos) {
                if(receivedArr[n - j] == 1) {
                    count++;
                }
            }
        }

        // Determine if there's an error based on the parity bit
        if(count % 2 != 0) {
            errorPos += pos;
        }
    }

    // Check if an error was detected
    if(errorPos > 0) {
        printf("Error detected at position: %d\n", errorPos);
        
        // Correct the error
        receivedArr[n - errorPos] = receivedArr[n - errorPos] == 0 ? 1 : 0;

        printf("Corrected Hamming code: ");
        for(i = 0; i < n; i++) {
            printf("%d", receivedArr[i]);
        }
        printf("\n");
    } else {
        printf("No error detected.\n");
    }

    // Extract the original data (excluding parity bits)
    int k = 1;
    printf("Original data: ");
    for(i = 1; i <= n; i++) {
        if(i != (1 << (k - 1))) {
            printf("%d", receivedArr[n - i]);
        } else {
            k++;
        }
    }
    printf("\n");

    return 0;
}