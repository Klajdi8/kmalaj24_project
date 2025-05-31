#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define ticket structure (linked list node)
struct Ticket {
    int ticketID;
    char movieName[50];
    int seatNumber;
    struct Ticket* next;
};

// Function to create a new ticket
struct Ticket* createTicket(int id, char* movie, int seat) {
    struct Ticket* newTicket = (struct Ticket*)malloc(sizeof(struct Ticket));
    newTicket->ticketID = id;
    strcpy(newTicket->movieName, movie);
    newTicket->seatNumber = seat;
    newTicket->next = NULL;
    return newTicket;
}

// Add ticket to the end of the list
void bookTicket(struct Ticket** head, int id, char* movie, int seat) {
    struct Ticket* newTicket = createTicket(id, movie, seat);
    if (*head == NULL) {
        *head = newTicket;
    } else {
        struct Ticket* current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = newTicket;
    }
    printf("Ticket booked successfully!\n");
}

// Display all booked tickets
void viewTickets(struct Ticket* head) {
    if (head == NULL) {
        printf("No tickets booked yet.\n");
        return;
    }

    printf("\n--- Booked Tickets ---\n");
    struct Ticket* current = head;
    while (current != NULL) {
        printf("Ticket ID: %d | Movie: %s | Seat: %d\n",
               current->ticketID, current->movieName, current->seatNumber);
        current = current->next;
    }
}

// Cancel ticket by ID
void cancelTicket(struct Ticket** head, int id) {
    struct Ticket* current = *head;
    struct Ticket* prev = NULL;

    while (current != NULL && current->ticketID != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Ticket with ID %d not found.\n", id);
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Ticket cancelled successfully.\n");
}

// Free memory
void freeTickets(struct Ticket* head) {
    struct Ticket* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Main program
int main() {
    struct Ticket* ticketList = NULL;
    int choice, id, seat;
    char movie[50];
    int nextID = 1;

    while (1) {
        printf("\n===== Cinema Ticket System =====\n");
        printf("1. Book Ticket\n");
        printf("2. View Tickets\n");
        printf("3. Cancel Ticket\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                printf("Enter Movie Name: ");
                fgets(movie, sizeof(movie), stdin);
                movie[strcspn(movie, "\n")] = 0; // Remove newline
                printf("Enter Seat Number: ");
                scanf("%d", &seat);
                bookTicket(&ticketList, nextID++, movie, seat);
                break;
            case 2:
                viewTickets(ticketList);
                break;
            case 3:
                printf("Enter Ticket ID to cancel: ");
                scanf("%d", &id);
                cancelTicket(&ticketList, id);
                break;
            case 4:
                freeTickets(ticketList);
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}

