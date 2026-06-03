#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct daily_entry
{
    float weight;
    char protein;
    char workout;
    char practice;
    float sprint;
};

struct daily_entry records[100];
int count = 0;
 

// Function to add a daily entry
void add_daily_entry() {
    if (count < 100) {
        printf("Enter weight:\n");
        scanf("%f", &records[count].weight);
        printf("Did you meet your protein goal? (y/n):\n");
        scanf(" %c", &records[count].protein);
        printf("Did you do your workout? (y/n):\n");
        scanf(" %c", &records[count].workout);
        printf("Did you do your Kabaddi practice? (y/n):\n");
        scanf(" %c", &records[count].practice);
        printf("Enter your sprint time(100m):\n");
        scanf("%f", &records[count].sprint);
        count++;
    } else {
        printf("Maximum entries reached.\n");
    }
}
void view_all_entries(){
    int i = 0;
    for(i = 0; i < count; i++) {
        printf("Entry %d:\n", i + 1);
        printf("Weight: %.2f\n", records[i].weight);
        printf("Protein Goal: %c\n", records[i].protein);
        printf("Workout: %c\n", records[i].workout);
        printf("Practice: %c\n", records[i].practice);
        printf("Sprint Time: %.2f\n", records[i].sprint);
    }
}
void show_best_sprint()
 
{
    if (count==0)
    {
        printf("No entries to show.\n"); 
        return;
    }
    else
    {
        float best_sprint=records[0].sprint;
        int i;
    for(i = 1; i < count; i++)   
    {
        if(records[i].sprint < best_sprint)
        {
            best_sprint = records[i].sprint;
        }
    }
    printf("Best Sprint Time: %.2f\n", best_sprint);
    } 
}
void show_discipline()
{
    if (count == 0)
    {
        printf("No entries to calculate discipline.\n");
        return;
    }

    int total_score = 0;
    int max_score = count * 3;
    int i;

    for (i = 0; i < count; i++)
    {
        if (records[i].protein == 'y' || records[i].protein == 'Y')
            total_score++;

        if (records[i].workout == 'y' || records[i].workout == 'Y')
            total_score++;

        if (records[i].practice == 'y' || records[i].practice == 'Y')
            total_score++;
    }

    float percentage = (total_score * 100.0) / max_score;

    printf("Discipline Score: %.2f%%\n", percentage);
}
void show_weight_progress()
{
    if (count == 0)
    {
        printf("No entries to show weight progress.\n");
        return;
    }

    float start_weight = records[0].weight;
    float current_weight = records[count - 1].weight;
    float change = current_weight - start_weight;

    printf("Starting Weight: %.2f kg\n", start_weight);
    printf("Current Weight : %.2f kg\n", current_weight);
    printf("Weight Change  : %.2f kg\n", change);
}
int main()
{
  int choice;
    do{

        printf("\n===== ATHLETE TRACKER =====\n");
        printf("1. Add Daily Entry\n");
        printf("2. View All Entries\n");
        printf("3. Show Best Sprint\n");
        printf("4. Show Discipline\n");
        printf("5. Show Weight Progress\n");
        printf("6. Exit\n");

        printf("Enter your Choice: ");
        scanf("%d", &choice);
    

        switch(choice) {
        case 1:
        printf("Add Daily Entry\n");
        add_daily_entry(); // Code to add daily entry
            break;
        case 2:
        printf("View All Entries\n");
        view_all_entries(); // Code to view all entries
            break;              
        case 3:
        printf("Show Best Sprint\n");
        show_best_sprint(); // Code to show best sprint
            break;
        case 4:
        printf("Show Discipline \n");
            show_discipline(); // Code to show discipline percentage
            break;
        case 5:
        printf("Show Weight Progress\n");
            show_weight_progress(); // Code to show weight progress
            break;
        case 6:
        printf("Exiting...\n");
            break;
        default:
        printf("Invalid Choice. Please try again.\n");   
        }
    }

    while(choice != 6);
    return 0;
}

   