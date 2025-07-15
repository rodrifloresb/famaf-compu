#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


#include "weather_utils.h"
#include "array_helpers.h"

static char *mes(int numero_mes) {

    if (numero_mes > MONTHS - 1)
    {
        printf("\ninvalid month \n");
        exit(EXIT_FAILURE);
    }
    
  switch (numero_mes) {
    case 0: return "January";
    case 1: return "February";
    case 2: return "March";
    case 3: return "April";
    case 4: return "May";
    case 5: return "June";
    case 6: return "July";
    case 7: return "August";
    case 8: return "September";
    case 9: return "October";
    case 10: return "November";
    case 11: return "December";
    default: return "Invalid month";
  }

}

void min_temp(WeatherTable weather) {
    int res = weather[0][0][0]._min_temp;

    for (unsigned int year = 0u; year < YEARS; year++)
    {
        for (unsigned int months = 0u; months < MONTHS; months++)
        {
            for (unsigned int day = 0u; day < DAYS; day++)
            {
                if (weather[year][months][day]._min_temp < res)
                {
                    res = weather[year][months][day]._min_temp;
                }
            }
            
        }
        
    }

    float dato = res/10.0;
    printf("\nMin_Temp historica : %.2fºC \n", dato);
}

void max_temp_anual(WeatherTable weather, int array[YEARS]) {

    for (unsigned int year = 0u; year < YEARS; year++)
    {
        int max_tmp = weather[year][0][0]._max_temp;

        for (unsigned int months = 0u; months < MONTHS; months++)
        {
            for (unsigned int day = 0u; day < DAYS; day++)
            {
                if (weather[year][months][day]._max_temp > max_tmp)
                {
                    array[year] = weather[year][months][day]._max_temp;
                }
            }
            
        }        
    }

    for (unsigned int year = 0u; year < YEARS; year++)
    {
        float dato =  (array[year])/10.0;
        printf("Max temp en %u : %.2fºC \n", (year+FST_YEAR), dato);
    }
    
}

void mounth_rainfall(WeatherTable weather, int array[YEARS]) {


    for (unsigned int year = 0u; year < YEARS; year++)
    {
        unsigned int max_tmp = 0;
        unsigned int month_tmp = 0;

        for (unsigned int months = 0u; months < MONTHS; months++)
        {
            unsigned int total_rainfall = 0;

            for (unsigned int day = 0u; day < DAYS; day++)
            {
                total_rainfall = total_rainfall + weather[year][months][day]._rainfall;
            }

            if (total_rainfall > max_tmp)
            {
                max_tmp = total_rainfall;
                month_tmp = months;
            }
        }        

        array[year] = month_tmp;
    }

    for (unsigned int year = 0u; year < YEARS; year++)
    {
        char *tmp = mes(array[year]);
        printf("month with the most rainfall  %u : %s \n", (year+FST_YEAR), tmp);
    }
    
}

