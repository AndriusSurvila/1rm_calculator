#include "rm_calculator.h"
#include <stdio.h>
#include <string.h>

double calculate_epley(double weight, int reps)
{
    if (reps <= 0) return weight;
    return weight * (1.0 + 0.0333 * reps);
}

double calculate_brzycki(double weight, int reps)
{
    if (reps <= 0 || reps >= 37) return weight;
    return weight * (36.0 / (37.0 - reps));
}

double calculate_1rm(double weight, int reps)
{
    double epley = calculate_epley(weight, reps);
    double brzycki = calculate_brzycki(weight, reps);
    return (epley + brzycki) / 2.0;
}

void double_to_string(double value, char *buffer, int precision)
{
    if (precision == 0) {
        sprintf(buffer, "%.0f", value);
    } else if (precision == 1) {
        sprintf(buffer, "%.1f", value);
    } else if (precision == 2) {
        sprintf(buffer, "%.2f", value);
    } else {
        sprintf(buffer, "%g", value);
    }
}

void int_to_string(int value, char *buffer)
{
    sprintf(buffer, "%d", value);
}

int read_exercise(Exercise *exercise)
{
    printf("Enter exercise name (or 'done' to finish): ");
    if (fgets(exercise->name, sizeof(exercise->name), stdin) == NULL) {
        return -1;
    }
    
    size_t len = strlen(exercise->name);
    if (len > 0 && exercise->name[len - 1] == '\n') {
        exercise->name[len - 1] = '\0';
    }
    
    if (strcmp(exercise->name, "done") == 0) {
        return 0;
    }
    
    printf("Enter weight (kg): ");
    if (scanf("%lf", &exercise->weight) != 1) {
        return -1;
    }
    
    printf("Enter repetitions: ");
    if (scanf("%d", &exercise->reps) != 1) {
        return -1;
    }
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    exercise->one_rm = calculate_1rm(exercise->weight, exercise->reps);
    
    return 1;
}

int read_exercises(Exercise exercises[], int max_count)
{
    int count = 0;
    
    printf("\n=== 1RM Calculator - Enter Exercise Data ===\n\n");
    
    while (count < max_count) {
        int result = read_exercise(&exercises[count]);
        
        if (result == -1) {
            printf("Error reading input!\n");
            return -1;
        } else if (result == 0) {
            break;
        }
        
        count++;
        printf("\n");
    }
    
    return count;
}