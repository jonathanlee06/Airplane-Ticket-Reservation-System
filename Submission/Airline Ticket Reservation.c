#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//GLOBAL VARIABLES
static int businessClass[5][4] = { NULL };
static int economyClass[5][6] = { NULL };
int daysPerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int rows = 0;
int columns = 0;
int rowResponse;
int columnResponse;
int NumOfTicket[50] = { NULL };
int selection;			//flight select
int date;
int day = 0;
int month = 0;
int year = 0;
char seatClass;
char choice;			//post booking choice
char flightOrigin;
char flightDestination;
char flightNo;
char name[100] = { NULL };

//FUNCTION PROTOTYPE
void mainMenu();
void selectBusiness();
void selectEconomy();
void business_class();
void economy_class();
void userInfo();
void doneBooking();
void ticket();
void flights();
void selectFlight(char menuChoose);
void saveInformation();

struct tarikh {
	int month;
	int day;
	int year;
};

// Retrieved from GitHub (https://www.github.com) on 7 July 2018
// To check whether date is a leap year
int leapyear(int year) {
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// To validate the date
int validdate(struct tarikh now) {
	int daysmon;
	if (now.year <= 1582)
		return 0;
	if (now.month < 1 || now.month > 12)
		return 0;
	daysmon = daysPerMonth[now.month - 1];
	if (leapyear(now.year) && now.month == 2)
		daysmon++;
	if (now.day < 1 || now.day > daysmon)
		return 0;
	return 1;
}

// Retrieved from Code Projects (https://www.code-projects.org) on 7 July 2018
// To find date of tomorrow, and date of the day after tomorrow
struct tarikh bumpdate(struct tarikh now) {
	int daysmon = daysPerMonth[now.month - 1];
	if (leapyear(now.year) && now.month == 2)
		daysmon++;
	if (++now.day > daysmon) {
		now.day = 1;
		if (++now.month > 12) {
			now.month = 1;
			now.year++;
		}
	}
	return now;
};



int main()
{

	mainMenu();

	return 0;
}

void mainMenu()
{
	char menuChoice;

	printf("========================= Welcome to the Airline Ticket Reservation Application =========================\n\n\n");

	printf("\t\t\t\t\tPress P to Purchase a ticket\n");
	printf("\t\t\t\t\tPress V to Print Boarding Pass\n");
	printf("\t\t\t\t\tPress Q to Quit Application\n");
	scanf(" %c", &menuChoice);
	selectFlight(menuChoice);
}

void selectFlight(char menuChoose)
{
	menuChoose = toupper(menuChoose);

	switch (menuChoose)
	{
	case 'P':
	{

		flights();
		scanf("%d", &selection);

		if (selection == 1 || selection == 2 || selection == 3 || selection == 4 || selection == 5 || selection == 6)
		{
			for (;;) {
				printf("\t\t========================= Purchasing Module =========================\n\n\n");
				printf("\t\t\t\t\tPress B for Business Class\n");
				printf("\t\t\t\t\tPress E for Economy Class\n");
				printf("\t\t\t\t\tPress M to return to main menu\n");
				scanf(" %c", &seatClass);

				seatClass = toupper(seatClass);

				{
					switch (seatClass)
					{
					case 'B':
					{

						printf("\n\t\t\t\t\t Select a seat Business Class\n");
						selectBusiness();

						break;
					}

					case 'E':
					{
						printf("\n\t\t\t\t\t Select a seat Economy Class\n");
						selectEconomy();
						break;
					}

					case 'M':
					{
						printf("\n\t\t\t\t\t Returning to main menu\n\n\t\t\t\t\t Returning to main menu...\n\n");
						mainMenu();
						break;
					}

					default:
					{
						printf("\n\t\t\t\t\t Invalid input, please try again!\n\n\t\t\t\t\t Returning to menu...\n\n");
						selectFlight(menuChoose);
						break;
					}
					}

				}
				break;
			}

		}
		else
			printf("\n\t\t\t\t\t Invalid input, please try again!\n\n\t\t\t\t\t Returning to main menu...\n\n");
			mainMenu();
		break;

	}
	case 'V':
	{
		ticket();
		break;
	}
	case 'Q':
	{
		exit(0);
	}
	default:
	{
		printf("\n\t\t\t\t\t Invalid input, please try again!\n\n\t\t\t\t\t Returning to main menu...\n\n");
		mainMenu();
		break;
	}
	}
}

void flights()
{
	// Retrieved from stackoverflow (https://goo.gl/DmDi9r) on 11 July 2018
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	struct tarikh fday = { NULL }, secday = { NULL }, thiday = { NULL };

	fday.day = tm.tm_mday;
	fday.month = tm.tm_mon + 1;
	fday.year = tm.tm_year + 1900;

	secday = bumpdate(fday);
	thiday = bumpdate(secday);

	printf("\n\t\t\t\t\tChoose Your Flight\n");
	printf("=========================================================================================================\n");
	printf("\t\t\t\t\tDATE : %d-%d-%d\n", fday.day, fday.month, fday.year);
	printf("\t\t\tPress 1 - Kuala Lumpur (KUL) -> Kuching (KCH) [AK021]\n\t\t\t\t  Departure: 8:00A.M. -> Arrival: 10:00A.M.\n");
	printf("\n\t\t\tPress 2 - Kuching (KCH) -> Kuala Lumpur (KUL) [AK021]\n\t\t\t\t  Departure: 8:00P.M. -> Arrival: 10:00P.M.\n\n");
	printf("\n");

	printf("\t\t\t\t\tDATE : %d-%d-%d\n", secday.day, secday.month, secday.year);
	printf("\t\t\tPress 3 - Kuala Lumpur (KUL) -> Kuching (KCH) [AK021]\n\t\t\t\t  Departure: 8:00A.M. -> Arrival: 10:00A.M.\n");
	printf("\n\t\t\tPress 4 - Kuching (KCH) -> Kuala Lumpur (KUL) [AK021]\n\t\t\t\t  Departure: 8:00P.M. -> Arrival: 10:00P.M.\n\n");
	printf("\n");

	printf("\t\t\t\t\tDATE : %d-%d-%d\n", thiday.day, thiday.month, thiday.year);
	printf("\t\t\tPress 5 - Kuala Lumpur (KUL) -> Kuching (KCH) [AK021]\n\t\t\t\t  Departure: 8:00A.M. -> Arrival: 10:00A.M.\n");
	printf("\n\t\t\tPress 6 - Kuching (KCH) -> Kuala Lumpur (KUL) [AK021]\n\t\t\t\t  Departure: 8:00P.M. -> Arrival: 10:00P.M.\n\n");
	printf("\n");


}

void business_class()
{
	//Display seat arrangement in Business class
	printf("\n\n\t\t\t\t\t   Seat arrangement\n");
	printf("\t\t\t\t  ==================================\n\n");
	printf("\n\t\t\t\t\t    1	  2  3	  4 ");
	for (rows = 0; rows < 5; rows++)
	{
		printf("\n\t\t\t\t\t %d ", rows + 1);
		for (columns = 0; columns < 4; columns++)
		{
			if (businessClass[rows][columns] == 0 && columns == 1)
				printf("[ ]");
			else if (businessClass[rows][columns] != 1)
				printf("[ ]	 ");
			else if (businessClass[rows][columns] != 0 && columns == 1)
				printf("[X]");
			else if (businessClass[rows][columns] != 0)
				printf("[X]	 ");


		}
		printf("\n");
	}
}

void economy_class()
{
	//Display seat arrangement in Economy class
	printf("\n\n\t\t\t\t\t      Seat arrangement\n");
	printf("\t\t\t\t    ==================================\n\n");
	printf("\t\t\t\t\t    1  2  3	 4  5  6  ");
	for (rows = 0; rows < 5; rows++)
	{
		printf("\n\t\t\t\t\t %d ", rows + 1);
		for (columns = 0; columns < 6; columns++)
		{
			if (economyClass[rows][columns] == 0 && columns == 2)
			{
				printf("[ ]	");
			}
			else if (economyClass[rows][columns] == 0)
			{
				printf("[ ]");
			}
			else if (economyClass[rows][columns] != 0)
			{
				printf("[X]");
			}
			else if (economyClass[rows][columns] != 0 && columns == 2)
			{
				printf("[X]	");
			}


		}
		printf("\n");
	}
}

void selectBusiness()
{
	for (;;) {

		business_class();

		printf("\n\t\t\t\t\t Select your seat row:");
		scanf("%d", &rowResponse);
		printf("\n\t\t\t\t\t Select your seat column:");
		scanf("%d", &columnResponse);

		if (rowResponse > 5 || rowResponse < 1)
		{
			printf("\n\t\t\t\t\t Your input is invalid, Please try again!\n");
			selectBusiness();
		}
		else if (columnResponse > 4 || columnResponse < 1)
		{
			printf("\n\t\t\t\t\t Your input is invalid, Please try again!");
			selectBusiness();
		}
		else
		{
			if (businessClass[rowResponse - 1][columnResponse - 1] == 1)
				printf("\n\t\t\t\t\t Seat already occupied!");
			else
			{
				businessClass[rowResponse - 1][columnResponse - 1] = 1;
				break;
			}
		}
	}

	userInfo();
}

void selectEconomy()
{
	for (;;) {

		economy_class();

		printf("\n\t\t\t\t\t Select your seat row:");
		scanf("%d", &rowResponse);
		printf("\n\t\t\t\t\t Select your seat column:");
		scanf("%d", &columnResponse);

		if (rowResponse > 5 || rowResponse < 1)
		{
			printf("\n\t\t\t\t\t Your input is invalid, Please try again!\n");
			selectEconomy();
		}
		else
			if (columnResponse > 6 || columnResponse < 1)
			{
				printf("\n\t\t\t\t\t Your input is invalid, Please try again!");
				selectEconomy();
			}
			else
				if (economyClass[rowResponse - 1][columnResponse - 1] == 1)
					printf("\n\t\t\t\t\t Seat already occupied!");
				else
				{
					economyClass[rowResponse - 1][columnResponse - 1] = 1;
					break;
				}
	}

	userInfo();
}

void userInfo()
{
	{
		// Prompt user for name
		printf("\t\t\t\t\tEnter passenger name: ");
		getchar();
		gets(name);
		doneBooking();
	}


}

void doneBooking()
{
	saveInformation();
	printf("\n\t========================= You've successfully made a booking! =========================\n\n\n");
	printf("\t\t\t\t    Press V to print boarding pass\n");
	printf("\t\t\t\t    Press M to go back to main menu\n");
	printf("\t\t\t\t    Press Q to quit program");
	printf("\n\n");
	scanf(" %c", &choice);

	choice = toupper(choice);

	switch (choice)
	{
	case 'V':
	{
		ticket();
		break;
	}
	case 'M':
	{
		mainMenu();
		break;
	}
	case 'Q':
	{
		exit(0);
		break;
	}
	default:
	{
		printf("\n\t\t\t\t\t Your input is invalid, Please try again!\n");
		doneBooking();
		break;
	}
	}
}

void saveInformation()
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	struct tarikh fday, secday, thiday;

	fday.day = tm.tm_mday;
	fday.month = tm.tm_mon + 1;
	fday.year = tm.tm_year + 1900;


	FILE *pTicket;

	char srow[5], scolumn[5], sdate[15], fullname[150] = { NULL }, seatnumber[50] = { NULL };
	char sday[5], smonth[5], syear[5], date[50] = { NULL };

	pTicket = fopen("ticket.txt", "w+");
	fputs("\n\n Flight number: AK021\n", pTicket);
	fprintf(pTicket, "\n  Passenger name: %s", name);

	if (seatClass == 'B')
		fputs("\n   Seat Class: Business Class\n", pTicket);
	else if (seatClass == 'E')
		fputs("\n   Seat Class: Economy Class\n", pTicket);

	itoa(rowResponse, srow, 10);
	itoa(columnResponse, scolumn, 10);
	strcat(seatnumber, ("\n  Seat number: "));
	strcat(seatnumber, (srow));
	strcat(seatnumber, (scolumn));
	fputs(seatnumber, pTicket);

	if (selection == 1 || selection == 2) {
		itoa(fday.day, sday, 10);
		itoa(fday.month, smonth, 10);
		itoa(fday.year, syear, 10);
		strcat(date, ("\n   Date of Departure: "));            //saving date
		strcat(date, (sday));
		strcat(date, ("-"));
		strcat(date, (smonth));
		strcat(date, ("-"));
		strcat(date, (syear));
		strcat(date, ("\n"));
		fputs(date, pTicket);
	}
	else if (selection == 3 || selection == 4) {
		secday = bumpdate(fday);
		itoa(secday.day, sday, 10);
		itoa(secday.month, smonth, 10);
		itoa(secday.year, syear, 10);
		strcat(date, ("\n   Date of Departure: "));            //saving date
		strcat(date, (sday));
		strcat(date, ("-"));
		strcat(date, (smonth));
		strcat(date, ("-"));
		strcat(date, (syear));
		strcat(date, ("\n"));
		fputs(date, pTicket);
	}
	else if (selection == 5 || selection == 6) {
		secday = bumpdate(fday);
		thiday = bumpdate(secday);
		itoa(thiday.day, sday, 10);
		itoa(thiday.month, smonth, 10);
		itoa(thiday.year, syear, 10);
		strcat(date, ("\n   Date of Departure: "));            //saving date
		strcat(date, (sday));
		strcat(date, ("-"));
		strcat(date, (smonth));
		strcat(date, ("-"));
		strcat(date, (syear));
		strcat(date, ("\n"));
		fputs(date, pTicket);
	}

	if (selection == 1 || selection == 3 || selection == 5) {
		fputs("   Depart from: Kuala Lumpur (KUL) \n", pTicket);
		fputs("   Departure time: 8.00a.m\n", pTicket);
		fputs("   Arrive at: Kuching (KCH) \n", pTicket);
		fputs("   Estimated arrival time: 10.00a.m\n", pTicket);
	}
	else if (selection == 2 || selection == 4 || selection == 6) {
		fputs("   Depart from: Kuching (KCH) \n", pTicket);
		fputs("   Departure time: 8.00p.m\n", pTicket);
		fputs("   Arrive at: Kuala Lumpur (KUL) \n", pTicket);
		fputs("   Estimated arrival time: 10.00p.m\n", pTicket);
	}

	fclose(pTicket);
}

void ticket()
{
	// Retrieved from stackoverflow (https://www.stackoverflow.com) on 22 July 2018
	if (fopen("ticket.txt", "r") == NULL) {
		printf("\nYou've not purchased a ticket yet!\n");
	}
	else {
		FILE *pTicket;
		char singleLine[255];
		printf("\t\t\t\t\tPrinting Boarding Pass\n");
		pTicket = fopen("ticket.txt", "r");

		while (!feof(pTicket))            //print until end of file
		{
			fgets(singleLine, 255, pTicket);        //print line
			printf(" %s\n", singleLine);
		}
		fclose(pTicket);
	}

	printf("\n\t\t\t\t\tReturning to main menu...\n");
	mainMenu();
}
