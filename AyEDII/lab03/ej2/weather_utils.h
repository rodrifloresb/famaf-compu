
#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H

#include "array_helpers.h"


void min_temp(WeatherTable weather);

void max_temp_anual(WeatherTable weather, int array[YEARS]);

void mounth_rainfall(WeatherTable weather, int array[YEARS]);

#endif
