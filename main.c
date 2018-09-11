#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
** TODO:
**     finish runSim() and bestResult()
**     implement runSim() into main()
**     output best time
**     save results to CSV file
*/

typedef struct Race{
    //User Inputs
    float start_lap;
    float end_lap;
    float stint_lap;
    float pit_in_lap;
    float pit_out_lap;
    float gal_lap;
    float gal_tank;

    //Calculated Variables
    float drop_lap;
    int total_laps;
}Race;

void getInputs(Race *race)
{
    printf("Start Lap: ");
    scanf("%f", &race->start_lap);
    printf("End Lap: ");
    scanf("%f", &race->end_lap);
    printf("Stint Lap: ");
    scanf("%f", &race->stint_lap);
    printf("Pit in Lap: ");
    scanf("%f", &race->pit_in_lap);
    printf("Pit out Lap: ");
    scanf("%f", &race->pit_out_lap);
    printf("Gallons per Lap: ");
    scanf("%f", &race->gal_lap);
    printf("Gallons per Tank: ");
    scanf("%f", &race->gal_tank);
}

void setCalculatedVars(Race *race)
{
    race->drop_lap = (race->end_lap - race->start_lap) / race->stint_lap;
    race->total_laps = (int)floor((race->gal_tank / race->gal_lap));

}

//for testing purposes
void printRace(Race *race)
{
    //print user input
    printf("Start Lap: %f\nGallons Per Lap: %f\nPit in Lap: %f\n", race->start_lap, race->gal_lap, race->pit_in_lap);
    //print calculated variables
    printf("Drop Lap: %f\nTotal Laps: %d\n", race->drop_lap, race->total_laps);

}

float runSim(Race *race, int interval)
{
    return 100.0;
}

int bestResult(int *results)
{
    return 12345;
}

int main()
{
    Race *race = malloc(sizeof(Race));

    getInputs(race);
    setCalculatedVars(race);

    int initial_interval;
    printf("Smallest gap between pit stops: ");
    scanf("%d", &initial_interval);

    int end_interval;
    printf("Largest gap between pit stops: ");
    scanf("%d", &end_interval);

    int incrementor;
    printf("Laps to increase per test (whole number): ");
    scanf("%d", &incrementor);

    int results[end_interval];

    //run sim for no pit stops
    runSim(race, (race->total_laps + 1)); // pit stops > total laps in race.

    for(int i = initial_interval; i <= end_interval; i += incrementor){
        printf("%d\n", i);
    }

    int best_time = bestResult(results);

    //TESTING
    //printRace(race);

    free(race);
    return 0;
}
