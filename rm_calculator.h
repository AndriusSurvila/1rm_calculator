#ifndef RM_CALCULATOR_H
#define RM_CALCULATOR_H

typedef struct{
    char name[50];
    double weight;
    int reps;
    double one_rm;
} Exercise;

double calculate_epley(double weight, int reps);
double calculate_brzycki(double weight, int reps);
double calculate_1rm(double weight, int reps);
void double_to_string(double value, char *buffer, int precision);
void int_to_string(int value, char *buffer);
int read_exercise(Exercise *exercise);
int read_exercises(Exercise exercises[], int max_count);

#endif