#ifndef TEST_H
#define TEST_H

struct _CityA;
typedef struct _CityA* cityPosA;
typedef struct _CityA {
	int population;
	char name[30];
	cityPosA right;
	cityPosA left;
}CityA;

struct _CountryA;
typedef struct _CountryA* countryPosA;
typedef struct _CountryA {
	char name[30];
	countryPosA nextCountry;
	cityPosA tree;
}CountryA;

int cityImportA(cityPosA* temp, char name[]);
int countryImportA(countryPosA* head);
cityPosA insertTreeA(cityPosA, cityPosA);
int printCountrysA(countryPosA);
int printCitysA(cityPosA);
countryPosA freeCountrysA(countryPosA);
cityPosA freeCitysA(cityPosA);
int findCountryA(countryPosA);
int findCityA(cityPosA, int);

#endif