#include <stdio.h>   // Include stdio.h for input/output functions
#include <time.h>    // Include time.h for date and time functions



#define MAX_ENTRIES 100  // Define maximum number of entries

struct daily_entry   // Define a structure to hold daily entry data
{   char day[20];
    char date[20];
    float weight;
    char protein;
    char workout;
    char practice;
    float sprint;
};

struct daily_entry records[MAX_ENTRIES];  // Array to hold daily entries
int count = 0;  // Variable to keep track of the number of entries

void set_date_and_day()     // Function to set the current date and day in the daily entry  
{
    time_t now;
    struct tm *current_time;

    now =time(NULL);
    current_time = localtime(&now);

    strftime(records[count].date, sizeof(records[count].date), "%d-%m-%y", current_time); 
    strftime(records[count].day, sizeof(records[count].day), "%A", current_time);

}

void load_data()    // Function to load existing data from file into the records array
{
    FILE *fp = fopen("athlete_data.txt", "r");

    if (fp == NULL)
    {
        return;
    }

    while (count < MAX_ENTRIES &&
           fscanf(fp, "%s %s %f %c %c %c %f",
                  records[count].date,
                  records[count].day,
                  &records[count].weight,
                  &records[count].protein,
                  &records[count].workout,
                  &records[count].practice,
                  &records[count].sprint) == 7)
    {
        count++;
    }

    fclose(fp);
}

void add_daily_entry()   //function to add daily entry with input validation and save to file
{
    if (count >= MAX_ENTRIES)
    {
        printf("Maximum entries reached.\n");
        return;
    }
      
    set_date_and_day();

    do
    {
        printf("Enter weight: ");
        scanf("%f", &records[count].weight);

        if (records[count].weight <= 10 || records[count].weight > 200)
            printf("Invalid weight. Try again.\n");

    } while (records[count].weight <= 10 || records[count].weight > 200);

    do
    {
        printf("Did you meet your protein goal? (y/n): ");
        scanf(" %c", &records[count].protein);

        if (records[count].protein != 'y' && records[count].protein != 'Y' &&
            records[count].protein != 'n' && records[count].protein != 'N')
            printf("Invalid input. Enter y or n only.\n");

    } while (records[count].protein != 'y' && records[count].protein != 'Y' &&
             records[count].protein != 'n' && records[count].protein != 'N');

    do
    {
        printf("Did you do your workout? (y/n): ");
        scanf(" %c", &records[count].workout);

        if (records[count].workout != 'y' && records[count].workout != 'Y' &&
            records[count].workout != 'n' && records[count].workout != 'N')
            printf("Invalid input. Enter y or n only.\n");

    } while (records[count].workout != 'y' && records[count].workout != 'Y' &&
             records[count].workout != 'n' && records[count].workout != 'N');

    do
    {
        printf("Did you do your Kabaddi practice? (y/n): ");
        scanf(" %c", &records[count].practice);

        if (records[count].practice != 'y' && records[count].practice != 'Y' &&
            records[count].practice != 'n' && records[count].practice != 'N')
            printf("Invalid input. Enter y or n only.\n");

    } while (records[count].practice != 'y' && records[count].practice != 'Y' &&
             records[count].practice != 'n' && records[count].practice != 'N');

    do
    {
        printf("Enter your sprint time: ");
        scanf("%f", &records[count].sprint);

        if (records[count].sprint <= 0 || records[count].sprint > 30)
            printf("Invalid sprint time. Try again.\n");

    } while (records[count].sprint <= 0 || records[count].sprint > 30);

    FILE *fp = fopen("athlete_data.txt", "a");   //FILE HANDLIMG TO APPEND DATA TO FILE
  
    if (fp == NULL)
    {
        perror("Error opening file for saving");
        return;
    }

    fprintf(fp, "%s %s %.2f %c %c %c %.2f\n",
            records[count].date,
            records[count].day,
            records[count].weight,
            records[count].protein,
            records[count].workout,
            records[count].practice,
            records[count].sprint);

    fclose(fp);

    count++;

    printf("Entry saved successfully.\n");
}

void view_all_entries()    // Function to display all entries in a readable format
{
    if (count == 0)
    {
        printf("No entries found.\n");
        return;
    }

    int i;

    for (i = 0; i < count; i++)
    {
        printf("\nEntry %d\n", i + 1);
        printf("DATE: %s\n", records[i].date);
        printf("DAY: %s\n", records[i].day);
        printf("Weight      : %.2f kg\n", records[i].weight);
        printf("Protein     : %c\n", records[i].protein);
        printf("Workout     : %c\n", records[i].workout);
        printf("Practice    : %c\n", records[i].practice);
        printf("Sprint Time : %.2f sec\n", records[i].sprint);
    }
}

void show_best_sprint()   // fumction to calculate and display the best sprint time from the records
{
    if (count == 0)
    {
        printf("No entries to show.\n");
        return;
    }

    float best_sprint = records[0].sprint;
    int i;

    for (i = 1; i < count; i++)
    {
        if (records[i].sprint < best_sprint)
        {
            best_sprint = records[i].sprint;
        }
    }

    printf("Best Sprint Time: %.2f sec\n", best_sprint);
}

void show_discipline()  // Function to calculate and display the discipline score based on protein, workout, and practice records   
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

    float percentage = (total_score * 100.0f) / max_score;

    printf("Discipline Score: %.2f%%\n", percentage);
}

void show_weight_progress() // function to calculate and display the weight progress from the first entry to the most recent entry
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

int main() // main function to display menu and handle user choices for different functionalities of the athlete tracker
{
    int choice;

    load_data();

    do
    {
        printf("\n===== ATHLETE TRACKER =====\n");
        printf("1. Add Daily Entry\n");
        printf("2. View All Entries\n");
        printf("3. Show Best Sprint\n");
        printf("4. Show Discipline\n");
        printf("5. Show Weight Progress\n");
        printf("6. Exit\n");

        do
        {
            printf("Enter your Choice: ");
            scanf("%d", &choice);

            if (choice < 1 || choice > 6)
                printf("Invalid choice. Enter 1 to 6 only.\n");

        } while (choice < 1 || choice > 6);

        switch (choice)
        {
        case 1:
            add_daily_entry();
            break;

        case 2:
            view_all_entries();
            break;

        case 3:
            show_best_sprint();
            break;

        case 4:
            show_discipline();
            break;

        case 5:
            show_weight_progress();
            break;

        case 6:
            printf("Exiting...\n");
            break;
        }

    } while (choice != 6);

    return 0;
}
