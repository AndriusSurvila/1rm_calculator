#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "html_templater.h"
#include "rm_calculator.h"

#define MAX_EXERCISES 20

int main()
{
    list_node *exercises[MAX_EXERCISES];
    int count = 0;
    
    char name_buffers[MAX_EXERCISES][50];
    char weight_buffers[MAX_EXERCISES][20];
    char reps_buffers[MAX_EXERCISES][20];
    char rm_buffers[MAX_EXERCISES][20];
        
    while (count < MAX_EXERCISES) {
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
        
        printf("Enter weight (kg): ");
        if (scanf("%lf", &input_weight) != 1) {
            printf("Error reading weight!\n");
            break;
        }
        
        printf("Enter repetitions: ");
        if (scanf("%d", &input_reps) != 1) {
            printf("Error reading repetitions!\n");
            break;
        }
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
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
        
        count++;
        printf("\n");
    }
    
    if (count == 0) {
        printf("No exercises entered.\n");
        return 1;
    }
    
    printf("\n=== Generating HTML Report ===\n");
    
    FILE *output_file = fopen("output.html", "w");
    if (output_file == NULL) {
        printf("Error: Could not create output file!\n");
        for (int i = 0; i < count; i++) {
            free_chain(exercises[i]);
        }
        return 1;
    }
    
    if (copy_template_to_html("templates/start.html", output_file) != 0) {
        printf("Error: Could not read start.html template!\n");
        fclose(output_file);
        for (int i = 0; i < count; i++) {
            free_chain(exercises[i]);
        }
        return 1;
    }
    
    for (int i = 0; i < count; i++) {
        if (write_to_html("templates/row_template.html", output_file, exercises[i]) != 0) {
            printf("Error: Could not write exercise row!\n");
            fclose(output_file);
            for (int j = 0; j < count; j++) {
                free_chain(exercises[j]);
            }
            return 1;
        }
    }
    
    if (copy_template_to_html("templates/end.html", output_file) != 0) {
        printf("Error: Could not read end.html template!\n");
        fclose(output_file);
        for (int i = 0; i < count; i++) {
            free_chain(exercises[i]);
        }
        return 1;
    }
    
    fclose(output_file);
    
    for (int i = 0; i < count; i++) {
        free_chain(exercises[i]);
    }
    
    printf("\nSuccess! HTML report generated: output.html\n");
    printf("Total exercises processed: %d\n", count);
    
    return 0;
}
