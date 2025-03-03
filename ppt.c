#include <stdio.h>
#include <stdlib.h>

// Function to calculate binomial coefficient C(n, k)
unsigned long long binomial_coefficient(int n, int k) {
    if (k > n - k)  // Use symmetry property C(n, k) = C(n, n-k)
        k = n - k;
    unsigned long long res = 1;
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

// Function to check if a number is a palindrome
int is_palindrome(unsigned long long num) {
    unsigned long long reversed = 0, original = num;
    while (num > 0) {
        reversed = reversed * 10 + (num % 10);
        num /= 10;
    }
    return original == reversed;
}

int main() {
    int limit;
    printf("Enter the number of rows for Pascal's Triangle: ");
    scanf("%d", &limit);

    FILE *file = fopen("palindromic_numbers.csv", "w");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(file, "Row,Position,Value\n"); // CSV header

    for (int n = 2; n <= limit; n++) { // Start from row 2, since row 1 only contains 1s
        int half = n / 2;  // Only process the first half of the row
        for (int k = 1; k <= half; k++) {  // Skip k=0 (edges)
            unsigned long long value = binomial_coefficient(n, k);
            if (value != 1 && is_palindrome(value)) { // Exclude only 1, allow other single digits
                fprintf(file, "%d,%d,%llu\n", n, k, value);
            }
        }
    }

    fclose(file);
    printf("Palindrome numbers stored in palindromic_numbers.csv\n");
    return 0;
}
