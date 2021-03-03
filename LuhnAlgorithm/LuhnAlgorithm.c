/**
 * @file Assignment-c_language.c
 * @author Alireza Nik (alireza.hossein-zadeh-nik@yaelev.se)
 * @brief Implementation of a program to read personal identity numbers (personnummer) in the format of YYMMDD-nnnC from the terminal 
 * and check if the personnummer is correct or not. If the calculated one and the one entered by the user are the same, it means that
 *  the personnummer is correct. Otherwise the entered personnummer is not a valid personnummer.
 * @version 0.1
 * @date 2021-03-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#define FORMAT "YYMMDD-nnnC"
#define MONTH_MIN 01U
#define MONTH_MAX 12U
#define DAY_MIN 01U
#define FEBRUARY 2U

int digit_slicer(int number);
int int_val(int number);

// a function to check if the result of product is greater than 9 or not
// this function is used inside digit_slicer function

int int_val(int number)
{
    int sum = 0;
    if (number>9)
    {
        sum = (number / 10) + (number % 10);
    }
    else
    {
        sum = number;
    }

    return sum;
}

// a function to Sum all the digits in each product

int digit_slicer(int number)
{
    int count = 0;
    int sum = 0;

    count = floor(log10(abs(number))) + 1;
    if (count == 3)
    {
        sum = int_val((number / 100) * 2) + int_val((number % 100) / 10) + int_val((number % 10) * 2);
    }
    else
    {
        sum = int_val((number / 10) * 2) + int_val((number % 10));
    }
    return sum;
}

int main(void)
{
    char format[] = FORMAT;
    char string[sizeof(FORMAT)] = {0};

    printf("Enter date and time in the format of %s: ", format);

    // Read date and time from the terminal
    uint8_t i = 0;
    while (i < sizeof(FORMAT) - 1)
    {
        char chr = getchar();
        if ((chr == '\n') || (chr == EOF))
        {
            break;
        }
        string[i++] = chr;
    }

    bool status = true; // We assume that the format of entered date and time is OK

    i = 0;
    while (i < sizeof(FORMAT) - 1)
    {
        if (isalpha(format[i])) // If the character in format[i] is a letter, the character in string[i] shall be a digit
        {
            if (!isdigit(string[i]))
            {
                status = false;
                break;
            }
        }
        else
        {
            if (format[i] != string[i]) // If the character in format[i] is not a letter, we should have the same character in string[i]
            {
                status = false;
                break;
            }
        }
        i++;
    }

    if (status)
    {
        unsigned int year = 0, month = 0, day = 0, b_date = 0, c_bit = 0;

        // Extract year, month, day, Birth_date, control_bit from the entered date 
        sscanf(string, "%02u%02u%02u-%03u%01u", &year, &month, &day, &b_date, &c_bit);

        if ((month < MONTH_MIN) || (month > MONTH_MAX) || (day < DAY_MIN))
        {
            status = false;
        }
        else
        {
            uint8_t days[MONTH_MAX] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

            if (day > days[month - 1])
            {
                status = false;

                if (month == FEBRUARY)
                {
                    if (year % 4 == 0) // If the year is a leap year
                    {
                        if (day == days[month - 1] + 1) // In february we can have 29 days
                        {
                            status = true;
                        }
                    }
                }
            }
        }

        unsigned int values[5] = {year, month, day, b_date, c_bit};
        int sum = 0;
        int control_digit = 0;

        for (int i = 0; i < 4; i++)
        {
            sum += digit_slicer(values[i]);
        }

        control_digit = (10 - (sum % 10)) % 10;
        if (control_digit == c_bit)
        {
            printf("The personnummer is valid");
        }
        else 
        {
            printf("The personnummer is NOT valid");
        }
    }

    if (status == false)
    {
        printf("The entered personnummer is not in the correct format!\n");
    }
    
    return 0;
}
