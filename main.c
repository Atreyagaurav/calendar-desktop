#include "aesthetics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DISPLAY_PREVIOUS_WEEKS 1
#define DISPLAY_TOTAL_WEEKS 4
#define DISPLAY_MAX_WIDTH 7*4-1

struct date {
  int year;
  int month;
  int day;
  int weekday;
};

int main(int argc, char *argv[]) {
  int active = 1, weekend = 0;
  time_t now, start;
  struct tm *timeinfo, date_today;
  time(&now);
  date_today = *localtime(&now);

  start = now -
          (date_today.tm_wday + 1 + 7 * DISPLAY_PREVIOUS_WEEKS) * 24 * 60 * 60;

  int i, j;
  printf("%3s ", COLOR_NORMAL_INACTIVE DAY_IND_SUN COLOR_RESET);
  printf("%3s ", COLOR_WEEKLY_EVENT_INACTIVE DAY_IND_MON COLOR_RESET);
  printf("%3s ", COLOR_WEEKLY_EVENT_INACTIVE DAY_IND_TUE COLOR_RESET);
  printf("%3s ", COLOR_WEEKLY_EVENT_INACTIVE DAY_IND_WED COLOR_RESET);
  printf("%3s ", COLOR_WEEKLY_EVENT_INACTIVE DAY_IND_THU COLOR_RESET);
  printf("%3s ", COLOR_WEEKLY_EVENT_INACTIVE DAY_IND_FRI COLOR_RESET);
  printf("%3s \n", COLOR_NORMAL_INACTIVE DAY_IND_SAT COLOR_RESET);
  for (i = 0; i < DISPLAY_TOTAL_WEEKS; ++i) {
    for (j = 0; j < 7; ++j) {
      start += 24 * 60 * 60;
      timeinfo = localtime(&start);
      active = (timeinfo->tm_mon != date_today.tm_mon) ? 0 : 1;
      weekend = (timeinfo->tm_wday == 0 || timeinfo->tm_wday == 6) ? 1 : 0;

      if (timeinfo->tm_mday == date_today.tm_mday) {
        printf("%s", COLOR_TODAY);
      } else if (weekend) {
        /* will add more options here later */
        printf("%s", active ? COLOR_NORMAL_ACTIVE : COLOR_NORMAL_INACTIVE);
      } else {
        printf("%s", active ? COLOR_WEEKLY_EVENT_ACTIVE
                            : COLOR_WEEKLY_EVENT_INACTIVE);
      }
      printf("%3d ", timeinfo->tm_mday);
      printf("%s", COLOR_RESET);
    }
    printf("\n");
  }

  /* piped contents will be shown here. */
  /* I use remind to pipe some contents, for example following command
     will make nice [tag] Event from remind for today.

   * remind -s ~/.reminder/ |
   * grep `date +"%Y/%m/%d"` |
   * awk '{x=$3;$1=$2=$3=$4=$5="";$0=$0;$1=$1; print "["x"] "$0}'
   
  */
  if (!isatty(fileno(stdin))) {
    printf(COLOR_SPECIAL_EVENT_ACTIVE);
    char ch;
    int col=0;
    while ((ch = getc(stdin)) != EOF) {
      putc(ch, stdout);
      if (ch == '\n'){
	col = 0;
      } else if (++col>DISPLAY_MAX_WIDTH){
	printf("\n  ");
	col = 2;
      }
    }
    printf(COLOR_RESET "\n");
  }
  return 0;
}
