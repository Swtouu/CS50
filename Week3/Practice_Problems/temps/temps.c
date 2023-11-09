#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
} avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);
void swap(avg_temp *x, avg_temp *y); // Update the function signature

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;
    sort_cities(); // Sort the cities in descending order

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// Function to sort cities by temperature in descending order
void sort_cities(void)
{
    int i, j;
    int n = NUM_CITIES;

    // Use selection sort to sort in descending order
    for (i = 0; i < n - 1; i++)
    {
        int max_idx = i;
        for (j = i + 1; j < n; j++)
        {
            // Compare the temperature values
            if (temps[j].temp > temps[max_idx].temp)
            {
                max_idx = j;
            }
        }

        // Swap the elements to sort in descending order
        swap(&temps[max_idx], &temps[i]);
    }
}

// Function to swap avg_temp structures
void swap(avg_temp *x, avg_temp *y)
{
    avg_temp temp = *x;
    *x = *y;
    *y = temp;
}
