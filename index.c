#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ORDERS 100
#define NAME_LENGTH 50
#define ORDER_DETAILS_LENGTH 100

typedef enum {
    PENDING,
    PREPARING,
    COMPLETED
} OrderStatus;

typedef struct {
    int orderID;
    char customerName[NAME_LENGTH];
    char orderDetails[ORDER_DETAILS_LENGTH];
    OrderStatus status;
} Order;


void addOrder(Order orders[], int *count);
void updateOrderStatus(Order orders[], int count);
void viewOrders(const Order orders[], int count);
void searchOrders(const Order orders[], int count);
const char* getStatusText(OrderStatus status);
void toUpperCase(char *str);

int main() {
    Order orders[MAX_ORDERS];
    int orderCount = 0;
    int choice;

    printf("=== Fast-Food Restaurant Customer Order Tracking System ===\n");

    while (1) {
        printf("\n--- Main Menu ---\n");
        printf("1. Add New Order\n");
        printf("2. Update Order Status\n");
        printf("3. View All Orders\n");
        printf("4. Search Orders\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
        
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number between 1 and 5.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addOrder(orders, &orderCount);
                break;
            case 2:
                updateOrderStatus(orders, orderCount);
                break;
            case 3:
                viewOrders(orders, orderCount);
                break;
            case 4:
                searchOrders(orders, orderCount);
                break;
            case 5:
                printf("Exiting the system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please select between 1 and 5.\n");
        }
    }

    return 0;
}


void addOrder(Order orders[], int *count) {
    if (*count >= MAX_ORDERS) {
        printf("Order limit reached. Cannot add more orders.\n");
        return;
    }

    Order newOrder;
    newOrder.orderID = (*count) + 1; 

    printf("Enter Customer Name: ");
    
    while (getchar() != '\n');
    fgets(newOrder.customerName, NAME_LENGTH, stdin);
    
    newOrder.customerName[strcspn(newOrder.customerName, "\n")] = 0;

    printf("Enter Order Details: ");
    fgets(newOrder.orderDetails, ORDER_DETAILS_LENGTH, stdin);
    
    newOrder.orderDetails[strcspn(newOrder.orderDetails, "\n")] = 0;

    newOrder.status = PENDING;

    orders[*count] = newOrder;
    (*count)++;

    printf("Order added successfully! Order ID: %d\n", newOrder.orderID);
}


void updateOrderStatus(Order orders[], int count) {
    if (count == 0) {
        printf("No orders to update.\n");
        return;
    }

    int id;
    printf("Enter Order ID to update: ");
    if (scanf("%d", &id) != 1) {
        while (getchar() != '\n');
        printf("Invalid input. Order ID should be a number.\n");
        return;
    }

    
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (orders[i].orderID == id) {
            found = 1;
            printf("Current Status: %s\n", getStatusText(orders[i].status));
            printf("Select new status:\n");
            printf("1. Pending\n");
            printf("2. Preparing\n");
            printf("3. Completed\n");
            printf("Enter your choice: ");
            int statusChoice;
            if (scanf("%d", &statusChoice) != 1) {
                while (getchar() != '\n');
                printf("Invalid input. Status not updated.\n");
                return;
            }

            switch (statusChoice) {
                case 1:
                    orders[i].status = PENDING;
                    break;
                case 2:
                    orders[i].status = PREPARING;
                    break;
                case 3:
                    orders[i].status = COMPLETED;
                    break;
                default:
                    printf("Invalid status choice. Status not updated.\n");
                    return;
            }

            printf("Order ID %d status updated to %s.\n", id, getStatusText(orders[i].status));
            return;
        }
    }

    if (!found) {
        printf("Order with ID %d not found.\n", id);
    }
}


void viewOrders(const Order orders[], int count) {
    if (count == 0) {
        printf("No orders to display.\n");
        return;
    }

    printf("\n--- All Orders ---\n");
    printf("%-10s %-20s %-30s %-15s\n", "Order ID", "Customer Name", "Order Details", "Status");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-10d %-20s %-30s %-15s\n",
               orders[i].orderID,
               orders[i].customerName,
               orders[i].orderDetails,
               getStatusText(orders[i].status));
    }
}

// Function to search orders by Customer Name or Order ID
void searchOrders(const Order orders[], int count) {
    if (count == 0) {
        printf("No orders to search.\n");
        return;
    }

    printf("Search by:\n");
    printf("1. Customer Name\n");
    printf("2. Order ID\n");
    printf("Enter your choice: ");
    int searchChoice;
    if (scanf("%d", &searchChoice) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }

    if (searchChoice == 1) {
        char searchName[NAME_LENGTH];
        printf("Enter Customer Name to search: ");
        while (getchar() != '\n');
        fgets(searchName, NAME_LENGTH, stdin);
        searchName[strcspn(searchName, "\n")] = 0;
        toUpperCase(searchName);

        int found = 0;
        printf("\n--- Search Results ---\n");
        printf("%-10s %-20s %-30s %-15s\n", "Order ID", "Customer Name", "Order Details", "Status");
        printf("-------------------------------------------------------------------------------\n");
        for (int i = 0; i < count; i++) {
            char tempName[NAME_LENGTH];
            strcpy(tempName, orders[i].customerName);
            toUpperCase(tempName);
            if (strstr(tempName, searchName) != NULL) {
                printf("%-10d %-20s %-30s %-15s\n",
                       orders[i].orderID,
                       orders[i].customerName,
                       orders[i].orderDetails,
                       getStatusText(orders[i].status));
                found = 1;
            }
        }

        if (!found) {
            printf("No orders found for customer name containing \"%s\".\n", searchName);
        }

    } else if (searchChoice == 2) {
        int searchID;
        printf("Enter Order ID to search: ");
        if (scanf("%d", &searchID) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            return;
        }

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (orders[i].orderID == searchID) {
                printf("\n--- Order Details ---\n");
                printf("Order ID: %d\n", orders[i].orderID);
                printf("Customer Name: %s\n", orders[i].customerName);
                printf("Order Details: %s\n", orders[i].orderDetails);
                printf("Status: %s\n", getStatusText(orders[i].status));
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("No order found with ID %d.\n", searchID);
        }

    } else {
        printf("Invalid search choice.\n");
    }
}


const char* getStatusText(OrderStatus status) {
    switch (status) {
        case PENDING:
            return "Pending";
        case PREPARING:
            return "Preparing";
        case COMPLETED:
            return "Completed";
        default:
            return "Unknown";
    }
}

void toUpperCase(char *str) {
    for (int i = 0; str[i]; i++) {
        if ('a' <= str[i] && str[i] <= 'z') {
            str[i] -= 32;
        }
    }
}
