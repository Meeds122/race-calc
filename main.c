#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
** TODO:
**     [DONE]finish runSim() and bestResult()
**     [DONE]implement runSim() into main()
**     [DONE]output best time
**     [DONE]debug main(). There is an issue :(
**     [DONE]add logic to cancel pit stop if within 5 laps
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

float runSim(Race *race, int interval, int number_of_laps)
{
    float time = race->start_lap;
    float prev_time = race->start_lap;
    //start at zero or one for the modulo test?
    for(int i = 1; i <= number_of_laps; i++){
        if(((i % interval) == 0) && ((number_of_laps - i) > 5)){
            //pit stop
            time = ((race->pit_in_lap - prev_time) + (race->pit_out_lap - prev_time) + prev_time) + time;
            prev_time = race->start_lap; // reset lap time to initial times
        }
        else{
            prev_time = prev_time + race->drop_lap;
            time = prev_time + time;
        }
    }
    return time;
}

int bestResult(float *results, int length_of_array, int initial_interval, int end_interval, int incrementor)
{
    /*
    returns the position of the best time in the array.
    */
    int best_time_pos = initial_interval;
    for(int i = initial_interval; i <= end_interval; i += incrementor){
        if(results[best_time_pos] > results[i]){
            best_time_pos = i;
        }
    }
    return best_time_pos;
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

    int laps;
    printf("Laps in race: ");
    scanf("%d", &laps);

    float results[end_interval];

    //run sim for no pit stops
    //results[0] = runSim(race, (race->total_laps + 1)); // pit stops > total laps in race.

    printf("Laps between pit stops: Time\n");

    for(int i = initial_interval; i <= end_interval; i += incrementor){
        results[i] = runSim(race, i, laps);
        printf("%d: %f\n", i, results[i]);
    }

    int best_time_pos = bestResult(results, end_interval, initial_interval, end_interval, incrementor);
    printf("Best time (%f) resulted with %d laps between pit stops\n", results[best_time_pos], best_time_pos);

    //TESTING
    //printRace(race);

    free(race);

    //WINDOWS SPECIFIC
    system("PAUSE");

    return 0;
}
