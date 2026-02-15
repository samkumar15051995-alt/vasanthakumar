#include <stdio.h>
#include <string.h>

int formate_date(char[]);
int formate_month(char[]);
int formate_year(char[]);
int measure_past_day_same_year(int, int, int, int, int, int[]);
int measure_past_year(int, int, int, int, int, int[]);
int measure_future_year(int, int, int, int, int, int[]);
void find_day(int day_number);

int main()
{
    char calender[50];
    printf("Enter the date(dd-mm-yyyy):  ");
    scanf("%[^\n]", calender);
    int date, month, year;
    date = formate_date(calender);
    month = formate_month(calender);
    year = formate_year(calender);
    printf("Date of the year: %d\n", date);
    printf("Month of the year: %d\n", month);
    printf("Year is %d\n", year);

    int real_date = 31;
    int real_month = 12;
    int real_year = 2025;
    int day_number;
    int day_find = 0;

    int month_dates[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((real_year == year) && (real_month == month))
    {
        if (real_date == date)
        {
            printf("The date of day is Wednesday...!\n");
            return 0;
        }

        else if (real_date >= date)
        {
            int day = ((real_date - date) % 7);
            day_find = 7 - day;
        }
    }

    else if (real_year == year && real_month != month)
    {
        day_number = measure_past_day_same_year(date, month, year, real_month, real_year, month_dates);
        day_find = day_number;
    }

    else if (real_year >= year)
    {
        day_number = measure_past_year(date, month, year, real_month, real_year, month_dates);
        day_find = day_number;
        /* code */
    }

    else if (real_year <= year)
    {
        day_number = measure_future_year(date, month, year, real_month, real_year, month_dates);
        day_find = day_number;
        /* code */
    }

    find_day(day_find);

    printf("\n****************THANK YOU********************\n");

    return 0;
}
int formate_date(char date[])
{
    int n = strlen(date);
    int temp = 0;
    for (int i = 0; i < 2; i++)
    {
        temp = (temp * 10) + (date[i] - '0');
    }
    return temp;
}
int formate_month(char month[])
{
    int n = strlen(month);
    int j, m = 0, k = 0;

    for (int i = 0; i < n; i++)
    {
        int c = 0;
        if (month[i] == '-')
        {
            c = 1;
            k = i + 1;
        }

        if (c)
        {
            break;
        }
    }
    m = ((month[k] - '0') * 10) + (month[k + 1] - '0');
    return m;
}
int formate_year(char year[])
{
    int n = strlen(year);
    int k = 0, Y = 0;
    for (int i = n; i > 0; i--)
    {
        if (year[i] == '-')
        {
            k = i;
            break;
        }
    }

    for (int i = k + 1; i < n; i++)
    {
        Y = (Y * 10) + (year[i] - '0');
    }
    return Y;
}
int measure_past_day_same_year(int date, int month, int year, int f_month, int f_year, int month_dates[])
{
    int day_number = 0;
    for (int i = f_month - 1; i >= month; i--)
    {
        day_number = day_number + month_dates[i];
        // printf("\n%d", day_number);
    }

    day_number += (month_dates[month - 1] - date);

    // printf("\nTotal number of days : %d\n", day_number);
    int day_name = day_number % 7;

    // printf("\nday of the week: %d\n", day_name);
    return day_name = 7 - day_name;
}
int measure_past_year(int date, int month, int year, int real_month, int real_year, int month_dates[])
{
    int i = year, total_days = 0;
    int leap = 0;
    int year_days = 365;
    int leap_month_dates[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int j = real_year; j > year; j--)
    {
        if ((j % 4 == 0 && j % 100 != 0) || (j % 400 == 0))
        {
            leap++;
        }
        total_days += year_days;
        // printf("\n%d year days %d\n", j, total_days);
    }

    if (year % 4 == 0)
    {
        for (int k = (real_month - 1); k >= (month - 1); k--)
        {
            // printf("%d month of days %d", k + 1, leap_month_dates[k]);
            total_days += leap_month_dates[k];
            // printf("Total of days %d\n", total_days);
        }
    }

    else if (year % 4 != 0)
    {
        for (int k = (real_month - 1); k >= (month - 1); k--)
        {
            // printf("%d month of days %d", k + 1, month_dates[k]);
            total_days += month_dates[k];
            // printf("Total of days %d\n", total_days);
        }
    }

    total_days += leap;

    // if (year <= 1900)
    // {
    //     total_days -= 1;
    // }

    total_days -= date;

    int return_day = total_days % 7;

    return_day = 7 - return_day;

    // printf("Return day of total number: %d\n", return_day);
    return return_day;
}
int measure_future_year(int date, int month, int year, int real_month, int real_year, int month_dates[])
{
    int leap, total_days = 0;
    int leap_month_dates[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int i = real_year + 1; i < year; i++)
    {
        leap = 0;
        if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
        {
            leap = 1;
        }

        total_days += (365 + leap);
        // printf("%d year total days: %d", i, total_days);
    }

    if (year % 4 == 0)
    {
        for (int i = 0; i < month - 1; i++)
        {
            total_days += leap_month_dates[i];
            // printf("month total days: %d\n", i + 1);
        }
    }
    else if (year % 4 != 0)
    {
        for (int i = 0; i < month - 1; i++)
        {
            total_days += month_dates[i];
            // printf("month total days: %d\n", total_days);
        }
    }

    total_days += date;
    if (total_days <= 7)
    {
        return total_days;
    }
    else if (total_days > 7)
    {
        total_days = total_days % 7;
        // printf("\nTotal days: %d\n", total_days);
        //  int final_day = ((7 - total_days) - 7);
        //  printf("\nFinal day: %d\n", final_day);
        return total_days;
    }
}
void find_day(int day_number)
{
    switch (day_number)
    {
    case 4:
        printf("This date of day is Sunday...!\n");
        break;

    case 5:
        printf("This date of day is Monday...!\n");
        break;

    case 6:
        printf("This date of day is Tuesday...!\n");
        break;

    case 0:
        printf("This date of day is Wednesday...!\n");
        break;

    case 1:
        printf("This date of day is Thursday...!\n");
        break;

    case 2:
        printf("This date of day is Friday...!\n");
        break;

    case 3:
        printf("This date of day is Saturday...!\n");
        break;

    case 7:
        printf("This date of day is Wednesday...!\n");
        break;
    }
}
