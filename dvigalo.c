#include <stdio.h>
#include <stdbool.h>

void control_panel(char floors[], int number_of_floors);
int array_length(char array[]);
void floor_input(int current_location, int number_of_floors);
int input_parsing(char input, int number_of_floors, int current_location);
void move();

int main()
{
    char floors[6] = {'P', '1', '2', '3', '4', '5'};
    const int number_of_floors = array_length(floors);
    int current_location = 0;
    while (1)
    {
        printf("floor %c\n\n", floors[current_location]);
        control_panel(floors, number_of_floors);
        floor_input(current_location, number_of_floors);
    }
    
}

void move();

int input_parsing(char input, int number_of_floors, int current_location)
{
    for (int i = 0; i < number_of_floors; i++)
    {
        if (input == i)
        {
            return i;
        }
    }

    printf("invalid input");

    floor_input(current_location, number_of_floors);
}

void floor_input(int current_location, int number_of_floors)
{
    char selected_floor;
    scanf("%c", &selected_floor);
    int floor_location = input_parsing(selected_floor, number_of_floors, current_location);
}

int array_length(char array[]) //TODO:porpravi to, rezultat je prevelik za 2
{
    int array_size = sizeof(array);
    int int_size = sizeof(array[0]);

    int length = array_size/int_size;

    return length;
}

void control_panel(char floors[], int number_of_floors)
{
    for (int i = number_of_floors-1; i >= 0; i--)
    {
        printf("%c\n", floors[i]);
    }
    printf("\nselect floor:");
}