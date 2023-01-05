#include <stdio.h>
#include <stdbool.h>



void control_panel(char floors[], int number_of_floors);
int array_length(char array[]);
int floor_input(int current_location, int number_of_floors, char floors[]);
int input_parsing(char input, int number_of_floors, int current_location, char floors[]);
int move(int target, int current, char floors[]);

int main()
{
    char floors[6] = {'P', '1', '2', '3', '4', '5'};
    const int number_of_floors = array_length(floors);
    int current_location = 0;

    printf("floor %c\n", floors[current_location]);

    while (1)
    {
        printf("\n");
        control_panel(floors, number_of_floors);
        int target_floor;
        target_floor = floor_input(current_location, number_of_floors, floors);
        printf("\n▉▉\n\n");
        current_location = move(target_floor, current_location, floors);
        printf("Arrived at floor %c\n\n", floors[current_location]);
        printf("| |\n");
    }
    
}

int move(int target, int current, char floors[])
{
    if (current < target)
    {
        while (current != target)
        {
            printf("current floor: %i\n↑\n", current);
            current++;
        }
        return current;
    }
    if (current > target)
    {
        while (current != target)
        {
            printf("current floor: %i\n↓\n", current);
            current--;
        }
        return current;
    }
    else {printf("you're already here, bozo\n");}
    return current;
}

int input_parsing(char input, int number_of_floors, int current_location, char floors[])
{
    for (int i = 0; i < number_of_floors; i++)
    {
        if (input == floors[i]){return i;}
    }

    printf("invalid input");

    floor_input(current_location, number_of_floors, floors);
}

int floor_input(int current_location, int number_of_floors, char floors[])
{
    char selected_floor;
    printf("\nselect floor: ");
    scanf("%c", &selected_floor);
    return input_parsing(selected_floor, number_of_floors, current_location, floors); //kje v arrayu nadstropij je ciljno nadstropje
}

int array_length(char array[])
{
    int i = 0;
    while (1)
    {
        if(array[i] == NULL){ return i;}
        else{i++;}
    }
}

void control_panel(char floors[], int number_of_floors)
{
    for (int i = number_of_floors-1; i >= 0; i--)
    {
        printf("%c\n", floors[i]);
    }
}