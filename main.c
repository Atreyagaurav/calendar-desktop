#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "aesthetics.h"

struct date {
  int year;
  int month;
  int day;
  int weekday;
};


int main(int argc, char *argv[])
{
  int active = 1;
  time_t now, start;
  struct tm *timeinfo, date_today;
  time(&now);
  now -= 19 *24 * 60 * 60;
  date_today = *localtime(&now);

  start = now - (date_today.tm_wday + 7) * 24 * 60 * 60;

  int i,j;
  printf("%3s ", COLOR_NORMAL_INACTIVE DAY_IND_SUN COLOR_RESET);
  printf("%3s ", DAY_IND_MON);
  printf("%3s ", DAY_IND_TUE);
  printf("%3s ", DAY_IND_WED);
  printf("%3s ", DAY_IND_THU);
  printf("%3s ", DAY_IND_FRI);
  printf("%3s \n", COLOR_NORMAL_INACTIVE DAY_IND_SAT COLOR_RESET);
  for (i = 0; i<3; ++i) {
    for (j=0; j<7; ++j) {
      start += 24 * 60 * 60;
      timeinfo = localtime(&start);
      if (timeinfo->tm_mon != date_today.tm_mon || timeinfo->tm_wday<2){
	active = 0;
      }else{
	active = 1;
      }
      if (active){
	if (timeinfo->tm_mday == date_today.tm_mday){
	  printf("%s", COLOR_TODAY);
	}else{
	  printf("%s", COLOR_NORMAL_ACTIVE);
	}
      }else{
	printf("%s", COLOR_NORMAL_INACTIVE);
      }

      printf("%3d ", timeinfo->tm_mday);
      printf("%s", COLOR_RESET);
    }
    printf("\n");
  }
  return 0;
}
