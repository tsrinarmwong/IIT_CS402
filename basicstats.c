#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#define INITIAL_CAPACITY 20

typedef struct { //Mode can have multiple values
    float value;
    int count;
} Mode;

float calculate_mean(const float *data, int count);
Mode* calculate_modes(float *data, int count, int* mode_count);
float calculate_geometric_mean(const float *data, int count);
float calculate_harmonic_mean(const float *data, int count);
float calculate_median(float *data, int count);
float calculate_stddev(const float *data, int count, float mean);
float custom_sqrt(float number); 
float custom_pow(float base, int exponent);
float nth_root(float product, int n); //for geometric
void copy_array(float *dest, const float *src, int count);
void print_mode(const Mode* modes, int mode_count, int total_count);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Initial Allocation
    int capacity = INITIAL_CAPACITY;
    float *data = malloc(capacity * sizeof(float)); 
    if (data == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    // Read content
    int count = 0;
    bool has_negative_num = false;
    float temp;
    while (fscanf(file, "%f", &temp) == 1) {
        //Negative checker
        if (temp < 0) {
            has_negative_num = true;
        }
        // Array Expansion
        if (count == capacity) { 
            int new_capacity = capacity * 2;
            float *new_data = malloc(new_capacity * sizeof(float));
            if (new_data == NULL) {
                perror("Memory allocation failed");
                free(data);
                fclose(file);
                return 1;
            }
            copy_array(new_data, data, count);
            free(data);
            data = new_data;
            capacity = new_capacity;
        }

        data[count++] = temp;
    }

    // If file is empty
    if (count == 0) {
        printf("No data was read from the file.\n");
        free(data);
        fclose(file);
        return 0;
    }

    // Done reading file
    fclose(file);

    // Statistics calculation
    int mode_count = 0;
    float mean = calculate_mean(data, count);
    Mode* modes = calculate_modes(data, count, &mode_count);    
    float median = calculate_median(data, count);
    float stddev = calculate_stddev(data, count, mean);
    float geometric_mean;
    float harmonic_mean;
    
    if (has_negative_num == true) {
        printf("*!!! Negative value detected. !!!*\nGeometric and Harmony Mean calculation will be skipped.\n");   
    } else {
        geometric_mean = calculate_geometric_mean(data, count);
        harmonic_mean = calculate_harmonic_mean(data, count);
    }

    // Print statistics
    printf("Results:\n");
    printf("--------\n");
    printf("Num values:\t %d\n", count);
    printf("Mean:\t\t %.3f\n", mean);
    print_mode(modes, mode_count, count);
    free(modes);
    if (has_negative_num == false){
        printf("Geometric Mean:\t %.3f\n", geometric_mean);
        printf("Harmonic Mean:\t %.3f\n", harmonic_mean);
    } else {
        printf("Geometric Mean:\t INVALID\n");
        printf("Harmonic Mean:\t INVALID\n");
    }
    printf("Median:\t\t %.3f\n", median);
    printf("Stddev:\t\t %.3f\n", stddev);

    printf("Unused array capacity:\t %d\n", capacity - count);
    free(data);
    return 0;
}

void copy_array(float *dest, const float *src, int count) {
    for (int i = 0; i < count; i++) {
        dest[i] = src[i];
    }
}

float calculate_mean(const float *data, int count) {
    float sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += data[i];
    }

    // Avg
    return sum / count;
}

int compare_floats(const void *a, const void *b) {
    float fa = *(const float*)a;
    float fb = *(const float*)b;
    return (fa > fb) - (fa < fb);
}

Mode* calculate_modes(float *data, int count, int* mode_count) {

    qsort(data, count, sizeof(float), compare_floats); // Sort the array first

    int maxCount = 1;
    int currentCount = 1;
    Mode* modes = NULL; // Delayed allocation to save space

    for (int i = 1; i < count; ++i) {
        if (data[i] == data[i - 1]) {
            currentCount++;
            if (currentCount > maxCount) {
                maxCount = currentCount;
                if (modes == NULL) {
                    modes = malloc(count * sizeof(Mode));
                    if (modes == NULL) {
                        *mode_count = 0;
                        return NULL; // Memory allocation failure
                    }
                }
                *mode_count = 1;
                modes[0] = (Mode){data[i], currentCount};
            } else if (currentCount == maxCount) {
                if (modes != NULL) {
                    modes[*mode_count].value = data[i];
                    modes[*mode_count].count = currentCount;
                    (*mode_count)++;
                }
            }
        } else {
            currentCount = 1; // Reset for a new number
        }
    }

    if (maxCount == 1) {
        // All numbers are unique, return NULL to let printer handle
        *mode_count = count;
        return NULL;
    }

    // every number are mode, return NULL to let printer handle
    if (modes == NULL) {
        *mode_count = count;
    }

    return modes;
}

void print_mode(const Mode* modes, int mode_count, int total_count) {
    printf("Mode:\t\t ");
    if (mode_count == total_count) {
        // If mode_count is equal to total_count, all numbers are unique and are considered modes
        printf("All numbers appear once; Hence, all numbers are mode.\n");
    } else if (mode_count > 0) {
        // Print the identified modes
        for (int i = 0; i < mode_count; ++i) {
            printf("%.3f", modes[i].value);
            if (i < mode_count - 1) { // If not the last mode, print a separator
                printf(", ");
            }
            if ((i + 1) % 5 == 0 && i < mode_count - 1) { // Maintain alignment
                printf("\n\t\t ");
            }
        }
        printf("\n");
    } else {
        // If mode_count is 0, no distinct mode is found
        printf("None\n");
    }
}

float nth_root(float product, int n) {
    if (n <= 0 || product <= 0) {
        return 0.0; // can't be 0
    }

    float guess = 1.0;
    float error = 0.00001; // Precision to 5 decimals
    float delta;

    //iterate through untill reached precision
    do {
        float previous_guess = guess;
        guess = (1.0 / n) * ((n - 1) * previous_guess + product / custom_pow(previous_guess, n - 1));
        delta = guess > previous_guess ? guess - previous_guess : previous_guess - guess;
    } while (delta > error);

    return guess;
}

float calculate_geometric_mean(const float *data, int count) {
    
    //nth_root(X1,X2,...,Xn)
    //n is the number of numbers in the set 
    //and X1...Xn are the numbers from the first to the n-th. 
    //An alternative way to write the formula is (X1 * X2 ... * Xn)^1/n 

    float product = 1.0;
    for (int i = 0; i < count; ++i) {
        float root = nth_root(data[i], count);
        if (root <= 0) {
            return 0;
        }
        product *= root;
    }

    return product;
}

float custom_pow(float base, int exponent) {
    //base^exponent
    float result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

float calculate_harmonic_mean(const float *data, int count) {

    //To put it simply, all you need to do is divide the number of items in the set by the sum of their reciprocals.
    
    float sum_reciprocals = 0.0;
    for (int i = 0; i < count; i++) {
        sum_reciprocals += 1.0 / data[i];
    }

    return count / sum_reciprocals;
}

int compare(const void *a, const void *b) {
    return (*(float *)a - *(float *)b);
}

float calculate_median(float *data, int count) {
    // Sort the data in ascending order
    qsort(data, count, sizeof(float), compare);

    if (count % 2 == 1) {
        // If odd, return the middle element
        return data[count / 2];
    } else {
        // If even, return the average of the two middle elements
        float mid1 = data[count / 2 - 1];
        float mid2 = data[count / 2];
        return (mid1 + mid2) / 2.0;
    }
}

float calculate_stddev(const float *data, int count, float mean) {
    if (count <= 1) {
        return 0; // Standard deviation is not meaningful for 1 or fewer elements
    }

    float sum_sq_diff = 0.0;
    for (int i = 0; i < count; i++) {
        sum_sq_diff += (data[i] - mean) * (data[i] - mean);
    }

    return custom_sqrt(sum_sq_diff / count);
}

float custom_sqrt(float number) {
    if (number <= 0) {
        return 0; // Square root of non-positive numbers is not defined in real numbers.
    }

    float error = 0.00001;  // Precision to 5 decimals
    float s = number;

    while ((s - number / s) > error) {
        s = (s + number / s) / 2;
    }

    return s;
}
