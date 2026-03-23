#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int seats[5][10]={0};

struct Booking
{
    int bookingID;
    char name[50];
    int show;
    int seat;
    int price;
};

struct Booking bookings[100];

int bookingCount=0;
int bookingCounter=1;

void displayMovies();
void showSeats();
void bookTicket();
void viewBookings();
void occupancyReport();
void saveToFile();
void loadFromFile();
int getSeatPrice(int seat);

int main()
{
    int choice;

    loadFromFile();

    while(1)
    {
        printf("\n===== MOVIE TICKET BOOKING SYSTEM =====\n");
        printf("1. Display Movies\n");
        printf("2. Show Seat Layout\n");
        printf("3. Book Ticket\n");
        printf("4. View Booking\n");
        printf("5. Occupancy Report\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                displayMovies();
                break;

            case 2:
                showSeats();
                break;

            case 3:
                bookTicket();
                break;

            case 4:
                viewBookings();
                break;

            case 5:
                occupancyReport();
                break;

            case 6:
                saveToFile();
                printf("Data saved. Thank you!\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void displayMovies()
{
    printf("\nAvailable Shows:\n");
    printf("1. Avengers - 10:00 AM\n");
    printf("2. Interstellar - 1:00 PM\n");
    printf("3. Batman - 4:00 PM\n");
    printf("4. Spiderman - 7:00 PM\n");
}

void showSeats()
{
    int i,j;
    int seatNumber=1;

    printf("\n====== THEATRE SEAT LAYOUT ======\n");

    for(i=0;i<5;i++)
    {
        for(j=0;j<10;j++)
        {
            if(seats[i][j]==0)
                printf("%3d ",seatNumber);
            else
                printf(" X  ");

            seatNumber++;
        }
        printf("\n");
    }

    printf("\nSeat Price Chart:\n");
    printf("Seats 1-10   : Rs.200\n");
    printf("Seats 11-20  : Rs.350\n");
    printf("Seats 21-30  : Rs.500\n");
    printf("Seats 31-40  : Rs.700\n");
    printf("Seats 41-50  : Rs.900\n");
}

int getSeatPrice(int seat)
{
    if(seat<=10)
        return 200;
    else if(seat<=20)
        return 350;
    else if(seat<=30)
        return 500;
    else if(seat<=40)
        return 700;
    else
        return 900;
}

void bookTicket()
{
    char name[50];
    int show;
    int seat;
    int price;

    printf("\nEnter your name: ");
    scanf("%s",name);

    displayMovies();

    printf("Select show (1-4): ");
    scanf("%d",&show);

    if(show<1 || show>4)
    {
        printf("Invalid show selection!\n");
        return;
    }

    showSeats();

    printf("Enter seat number (1-50): ");
    scanf("%d",&seat);

    if(seat<1 || seat>50)
    {
        printf("Invalid seat number!\n");
        return;
    }

    int row=(seat-1)/10;
    int col=(seat-1)%10;

    if(seats[row][col]==1)
    {
        printf("Seat already booked!\n");
        return;
    }

    seats[row][col]=1;

    price=getSeatPrice(seat);

    bookings[bookingCount].bookingID=bookingCounter;
    strcpy(bookings[bookingCount].name,name);
    bookings[bookingCount].show=show;
    bookings[bookingCount].seat=seat;
    bookings[bookingCount].price=price;

    bookingCount++;
    bookingCounter++;

    printf("\n===== BOOKING CONFIRMED =====\n");
    printf("Booking ID    : %d\n",bookingCounter-1);
    printf("Customer Name : %s\n",name);
    printf("Seat Number   : %d\n",seat);
    printf("Show Selected : %d\n",show);
    printf("Ticket Price  : Rs.%d\n",price);
}

void viewBookings()
{
    int i;

    if(bookingCount==0)
    {
        printf("\nNo bookings found!\n");
        return;
    }

    printf("\n====== ALL BOOKINGS ======\n");

    for(i=0;i<bookingCount;i++)
    {
        printf("\nBooking ID : %d\n",bookings[i].bookingID);
        printf("Name       : %s\n",bookings[i].name);
        printf("Show       : %d\n",bookings[i].show);
        printf("Seat       : %d\n",bookings[i].seat);
        printf("Price      : Rs.%d\n",bookings[i].price);
    }
}

void occupancyReport()
{
    int i,j;
    int booked=0;

    for(i=0;i<5;i++)
    {
        for(j=0;j<10;j++)
        {
            if(seats[i][j]==1)
                booked++;
        }
    }

    printf("\n===== OCCUPANCY REPORT =====\n");
    printf("Total Seats  : 50\n");
    printf("Booked Seats : %d\n",booked);
    printf("Available    : %d\n",50-booked);
}

void saveToFile()
{
    FILE *fp=fopen("bookings.txt","w");
    int i;

    for(i=0;i<bookingCount;i++)
    {
        fprintf(fp,"%d %s %d %d %d\n",
        bookings[i].bookingID,
        bookings[i].name,
        bookings[i].show,
        bookings[i].seat,
        bookings[i].price);
    }

    fclose(fp);
}

void loadFromFile()
{
    FILE *fp=fopen("bookings.txt","r");

    if(fp==NULL)
        return;

    while(fscanf(fp,"%d %s %d %d %d",
        &bookings[bookingCount].bookingID,
        bookings[bookingCount].name,
        &bookings[bookingCount].show,
        &bookings[bookingCount].seat,
        &bookings[bookingCount].price)==5)
    {
        int seat=bookings[bookingCount].seat;
        int row=(seat-1)/10;
        int col=(seat-1)%10;

        seats[row][col]=1;

        bookingCount++;
        bookingCounter++;
    }

    fclose(fp);
}