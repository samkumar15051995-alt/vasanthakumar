#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

int normal_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int leap_days[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void select_your_Date_of_birth(int *, int *, int *);
int current_year_days(int, int, int);
int total_years(int, int);
int Current_year(int, int, int);

int main()
{

    struct timeval my_time;

    setenv("TZ", "Asia/Kolkata", 1);
    tzset();

    gettimeofday(&my_time, NULL);

    struct tm *now = localtime(&my_time.tv_sec);

    int year, month, date, hour, min, sec;

    year = now->tm_year + 1900;
    month = now->tm_mon + 1;
    date = now->tm_mday;
    hour = now->tm_hour;
    min = now->tm_min;
    sec = now->tm_sec;

    int B_date, B_month, B_year;

    select_your_Date_of_birth(&B_date, &B_month, &B_year);
    int total_days = 0;
    int days_of_the_year = current_year_days(B_date, B_month, B_year);

    int days_of_total_years = total_years(B_year, year);

    int current_year_days = Current_year(date, month, year);

    total_days = days_of_the_year + days_of_total_years + current_year_days;

    printf("%d | %d | %d\n", B_date, B_month, B_year);

    printf("Total days: %d days ", total_days);
    printf("Hour : %d, Min : %d, Sec : %d\n", hour, min, sec);
    return 0;
}

void select_your_Date_of_birth(int *date, int *month, int *year)
{
    printf("Enter your birth date: ");
    scanf("%d", date);
    printf("Enter your birth month: ");
    scanf("%d", month);
    printf("Enter your birth year: ");
    scanf("%d", year);
}

int current_year_days(int date, int month, int year)
{
    int days = 0;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        for (int i = month; i <= 11; i++)
        {
            days += leap_days[i];
            // printf("Month %d days %d\n", i, leap_days[i]);
        }

        days = days + (leap_days[month - 1] - date + 1);
    }

    else
    {
        for (int i = month; i <= 11; i++)
        {
            days += normal_days[i];
            // printf("Month %d days %d\n", i, normal_days[i]);
        }

        days = days + (normal_days[month - 1] - date + 1);
    }

    return days;
}

int total_years(int B_year, int year)
{
    int days = 0;
    int leap = 0;
    int normal = 0;
    for (int i = B_year + 1; i < year; i++)
    {
        if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
        {
            days += 366;
            leap++;
        }
        else
        {
            days += 365;
            normal++;
        }
    }

    // printf("Leap year: %d \n Normal year: %d\n", leap, normal);

    return days;
}

int Current_year(int date, int month, int year)
{
    int days = 0;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        for (int i = 0; i < month - 1; i++)
        {
            days += leap_days[i];
            // printf("Month days: %d\n", leap_days[i]);
        }

        days += date;
    }

    else
    {
        for (int i = 0; i < month - 1; i++)
        {
            days += normal_days[i];
            // printf("Month days: %d\n", normal_days[i]);
        }

        days += date;
    }

    return days;
}