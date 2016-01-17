/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/
#include <stdio.h>
struct transaction {
	int amount;
	char date[11];
	char description[20];
};

int isLegit(char *date, int *d, int * m, int *y)
{
	int count = 0;
	*d = 0;
	*m = 0;
	*y = 0;
	for (int i = 0; date[i] != '\0'; i++)
	{
		if (count == 0)
		{
			if (date[i] == '/' || date[i] == '-')
				count++;
			
			else
				*d = *d * 10 + (date[i] - '0');
		}
		else if (count == 1)
		{
			if (date[i] == '/' || date[i] == '-')
				count++;
			else
				*m = *m * 10 + (date[i] - '0');
		}
		else
			*y = *y * 10 + (date[i] - '0');
		
	}
	if (*d < 0 || *d > 31 || *m < 0 || *m > 12 || *y < 0 || *y > 9999)
		return 0;

	int legitFlag = 0, leap = 0;
	int maxDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (*y % 400 == 0 || (*y % 100 != 0 && *y % 4 == 0)) //leap year
		leap = 1;

	if (leap == 1)
		maxDays[1]++;

	if (*d <= maxDays[*m - 1])
	{
		legitFlag = 1;
	}

	return legitFlag;
}

int countGreaterNumbers(struct transaction *Arr, int len, char *date) 
{
	int dday, dmon, dyear;
	if (len < 1 || !Arr || !isLegit(date, &dday, &dmon, &dyear))
		return NULL;

	int day, mon, year, count = 0;
	for (int i = 0; i < len; i++)
	{
		if (isLegit(Arr[i].date, &day, &mon, &year))
		{
			if ( year > dyear || (year == dyear && mon > dmon) || (year == dyear && mon == dmon && day > dday))
			{
				count = len - i;
				break;
			}
		}
		else
			return NULL;
	}
	return count;

}

