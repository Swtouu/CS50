#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int population;
    int endPopulation;

    do
    {
        population = get_int("Total start population (input not less than 9): ");
    }
    while (population < 9);

    // TODO: Prompt for end size
    do
    {
        endPopulation = get_int("Total end population: ");
    }
    while (endPopulation < population);

    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (population < endPopulation)
    {
        population = population + (population / 3) - (population / 4);
        years++;
    }

    // TODO: Print number of years
    printf("Years: %d\n", years);
}
