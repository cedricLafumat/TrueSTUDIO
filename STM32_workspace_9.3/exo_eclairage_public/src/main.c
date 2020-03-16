#include<stdio.h>
#include<stdbool.h>

bool is_day;
bool partial_night;
int hour;
int light_intensity;

int night_light(bool partial_night, int local_hour){
	if ((local_hour > 0) && (local_hour < 300)){
		light_intensity = 70;
		return light_intensity;
	}
	else if(partial_night == true){
		light_intensity = 50;
		return light_intensity;
	}
	else{
		light_intensity = 100;
		return light_intensity;
	}
	return light_intensity;
}

int main(int argc, char* argv[]){
	int sunrise;
	int sunset;
	printf("Saisissez l'heure de lever du soleil : ");
	scanf("%d", &sunrise);
	printf("Saisissez l'heure de coucher du soleil : ");
	scanf("%d", &sunset);
	while (true){
		light_intensity = 0;
		is_day = false;
		partial_night = false;
		printf("Saisissez l'heure en minute entre 0(0h00) et 1439(23h59) : ");
		scanf("%d", &hour);
		if ((hour >= sunrise) && (hour <= sunset)){
			is_day = true;
		}
		if ((hour >= (sunrise - 30) && (hour < sunrise)) || (hour <= (sunset + 30) && (hour <sunset))){
			partial_night = true;
		}
		if (is_day == false){
			light_intensity = night_light(partial_night, hour);
		}
		printf("Heure en minute : %d, intensité de lumière %d %%\n", hour, light_intensity);
	}
	return 0;
}
