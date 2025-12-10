#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "html_templater.h"
#include "rm_calculator.h"

#define INITIAL_CAPACITY 10

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int is_empty_string(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

int main()
{
    printf("\n=== 1RM Calculator - Enter Exercise Data ===\n\n");
    
    int capacity = INITIAL_CAPACITY;
    int count = 0;
    
    list_node **exercises = malloc(capacity * sizeof(list_node*));
    char (*name_buffers)[50] = malloc(capacity * sizeof(char[50]));
    char (*weight_buffers)[20] = malloc(capacity * sizeof(char[20]));
    char (*reps_buffers)[20] = malloc(capacity * sizeof(char[20]));
    char (*rm_buffers)[20] = malloc(capacity * sizeof(char[20]));
    
    if (!exercises || !name_buffers || !weight_buffers || !reps_buffers || !rm_buffers) {
        printf("Error: Memory allocation failed!\n");
        free(exercises);
        free(name_buffers);
        free(weight_buffers);
        free(reps_buffers);
        free(rm_buffers);
        return 1;
    }
    
    while (1) {
        if (count >= capacity) {
            capacity *= 2;
            
            list_node **new_exercises = realloc(exercises, capacity * sizeof(list_node*));
            char (*new_names)[50] = realloc(name_buffers, capacity * sizeof(char[50]));
            char (*new_weights)[20] = realloc(weight_buffers, capacity * sizeof(char[20]));
            char (*new_reps)[20] = realloc(reps_buffers, capacity * sizeof(char[20]));
            char (*new_rms)[20] = realloc(rm_buffers, capacity * sizeof(char[20]));
            
            if (!new_exercises || !new_names || !new_weights || !new_reps || !new_rms) {
                printf("Error: Memory reallocation failed!\n");
                goto cleanup;
            }
            
            exercises = new_exercises;
            name_buffers = new_names;
            weight_buffers = new_weights;
            reps_buffers = new_reps;
            rm_buffers = new_rms;
        }
        
        char input_name[50];
        double input_weight;
        int input_reps;
        
        printf("Enter exercise name (or 'done' to finish): ");
        if (fgets(input_name, sizeof(input_name), stdin) == NULL) {
            printf("Error reading input!\n");
            break;
        }
        
        size_t len = strlen(input_name);
        if (len > 0 && input_name[len - 1] == '\n') {
            input_name[len - 1] = '\0';
        }
        
        if (strcmp(input_name, "done") == 0) {
            break;
        }
        
        if (is_empty_string(input_name)) {
            printf("Error: Exercise name cannot be empty!\n\n");
            continue;
        }
        
        printf("Enter weight (kg): ");
        if (scanf("%lf", &input_weight) != 1) {
            printf("Error: Invalid weight input!\n\n");
            clear_input_buffer();
            continue;
        }
        
        if (input_weight <= 0) {
            printf("Error: Weight must be positive!\n\n");
            clear_input_buffer();
            continue;
        }
        
        if (input_weight > 1000) {
            printf("Warning: Weight seems unusually high. Please verify.\n");
            printf("Continue with this weight? (y/n): ");
            clear_input_buffer();
            char confirm;
            scanf("%c", &confirm);
            if (confirm != 'y' && confirm != 'Y') {
                clear_input_buffer();
                printf("\n");
                continue;
            }
        }
        
        printf("Enter repetitions: ");
        if (scanf("%d", &input_reps) != 1) {
            printf("Error: Invalid repetitions input!\n\n");
            clear_input_buffer();
            continue;
        }
        
        if (input_reps <= 0) {
            printf("Error: Repetitions must be positive!\n\n");
            clear_input_buffer();
            continue;
        }
        
        if (input_reps >= 37) {
            printf("Error: Repetitions must be less than 37 (formula limitation)!\n\n");
            clear_input_buffer();
            continue;
        }
        
        if (input_reps > 20) {
            printf("Warning: High rep count. Results may be less accurate.\n");
        }
        
        clear_input_buffer();
        
        // Вычисление 1RM
        double one_rm = calculate_1rm(input_weight, input_reps);
        
        exercises[count] = create_exercise_chain(
            input_name, 
            input_weight, 
            input_reps, 
            one_rm,
            name_buffers[count],
            weight_buffers[count],
            reps_buffers[count],
            rm_buffers[count]
        );
        
        if (exercises[count] == NULL) {
            printf("Error: Memory allocation failed!\n");
            break;
        }
        
        printf("Exercise added successfully!\n\n");
        count++;
    }
    
    if (count == 0) {
        printf("\nNo exercises entered. Exiting.\n");
        goto cleanup;
    }
    
    printf("\n=== Generating HTML Report ===\n");
    
    FILE *output_file = fopen("output.html", "w");
    if (output_file == NULL) {
        printf("Error: Could not create output file!\n");
        goto cleanup;
    }
    
    if (copy_template_to_html("templates/start.html", output_file) != 0) {
        printf("Error: Could not read start.html template!\n");
        fclose(output_file);
        goto cleanup;
    }
    
    for (int i = 0; i < count; i++) {
        if (write_to_html("templates/row_template.html", output_file, exercises[i]) != 0) {
            printf("Error: Could not write exercise row!\n");
            fclose(output_file);
            goto cleanup;
        }
    }
    
    if (copy_template_to_html("templates/end.html", output_file) != 0) {
        printf("Error: Could not read end.html template!\n");
        fclose(output_file);
        goto cleanup;
    }
    
    fclose(output_file);
    
    printf("\nSuccess! HTML report generated: output.html\n");
    printf("Total exercises processed: %d\n\n", count);

cleanup:
    for (int i = 0; i < count; i++) {
        free_chain(exercises[i]);
    }
    
    free(exercises);
    free(name_buffers);
    free(weight_buffers);
    free(reps_buffers);
    free(rm_buffers);
    
    return 0;
}