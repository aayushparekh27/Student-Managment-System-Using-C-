#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Branch-related data
char branches[5][100] = {"Information Technology (IT)", 
                         "Computer Programming (CP)", 
                         "Mechanical (MC)", 
                         "Electronics & Communication (EC)",
                         "Chemical Engineering"};

char hods[5][100] = {"Dr. N N GONDALIYA", 
                     "Dr. MAULIKA PATEL", 
                     "Dr. HEMANT THAKKAR", 
                     "Dr. HITESH SHAH",
                     "Dr. MATHURKUMAR BHAKHAR"};

char subjects[5][100] = {"Data Structures, Web Development, AI", 
                         "C++, Java, Python Programming", 
                         "Thermodynamics, Machine Design", 
                         "Circuit Analysis, Communication Systems",
                         "Economics, Chemical, Thermodynamics, Plant Research, Mathematics, Chemistry"};

float fees[5] = {50000, 45000, 60000, 55000, 60000}; // Fees per year in INR
int total_seats[5] = {60, 60, 60, 60, 60}; // Total available seats

// Student-related data
char students[100][100];
int branch_ids[100]; 
int student_count = 0;

// Function prototypes
void display_menu();
void view_branches();
void new_admission();
void view_admissions();
void cancel_admission();
void branch_information(); // New function

int main() {
    int choice;

    do {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_branches();
                break;
            case 2:
                new_admission();
                break;
            case 3:
                view_admissions();
                break;
            case 4:
                cancel_admission();
                break;
            case 5:
                branch_information();  // New option
                break;
            case 6:
                printf("\nThank you for using the system!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void display_menu() {
    system("cls");  // Use "clear" on Linux/Mac
    printf("============= STUDENT ADMISSION SYSTEM =============\n");
    printf("1. View Branch List\n");
    printf("2. New Admission\n");
    printf("3. View Admissions\n");
    printf("4. Cancel Admission\n");
    printf("5. Branch Information\n");  // New option in the menu
    printf("6. Exit\n");
    printf("===================================================\n");
}

void view_branches() {
    system("cls");
    printf("============= AVAILABLE BRANCHES =============\n");
    for (int i = 0; i < 5; i++) {
        printf("[%d] %s\n", i + 1, branches[i]);
    }
    printf("=============================================\n");
    printf("Press any key to return to the main menu...");
    getchar(); getchar(); 
}

void new_admission() {
    char name[100];
    int branch;
    FILE *file;  // File pointer

    system("cls");
    printf("============= NEW ADMISSION =============\n");
    printf("Enter student name: ");
    getchar(); // Consume any leftover newline character from previous input
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove the newline character at the end

    view_branches();
    printf("Select a branch (1-5): ");
    scanf("%d", &branch);

    if (branch < 1 || branch > 5) {
        printf("Invalid branch selection!\n");
        return;
    }

    // Store the new admission in memory
    strcpy(students[student_count], name);
    branch_ids[student_count] = branch - 1;  
    student_count++;

    // Save the new admission to a file
    file = fopen("admissions.txt", "a");  // Open file in append mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "Student: %s, Branch: %s\n", name, branches[branch - 1]);
    fclose(file);  // Close the file

    printf("Admission successful and saved to file!\n");
    printf("Press any key to return to the main menu...");
    getchar(); getchar();
}

void view_admissions() {
    system("cls");
    printf("============= ADMISSION LIST =============\n");

    if (student_count == 0) {
        printf("No admissions yet.\n");
    } else {
        for (int i = 0; i < student_count; i++) {
            printf("Student %d: %s - %s\n", 
                   i + 1, students[i], branches[branch_ids[i]]);
        }
    }

    printf("Press any key to return to the main menu...");
    getchar(); getchar(); 
}

void cancel_admission() {
    int admission_no;

    system("cls");
    printf("============= CANCEL ADMISSION =============\n");
    if (student_count == 0) {
        printf("No admissions to cancel.\n");
        printf("Press any key to return to the main menu...");
        getchar(); getchar(); 
        return;
    }

    printf("Enter the admission number to cancel (1-%d): ", student_count);
    scanf("%d", &admission_no);

    if (admission_no < 1 || admission_no > student_count) {
        printf("Invalid admission number!\n");
    } else {
        for (int i = admission_no - 1; i < student_count - 1; i++) {
            strcpy(students[i], students[i + 1]);
            branch_ids[i] = branch_ids[i + 1];
        }
        student_count--;
        printf("Admission cancelled successfully.\n");
    }

    printf("Press any key to return to the main menu...");
    getchar(); getchar(); 
}

void branch_information() {
    int branch;

    system("cls");
    printf("============= BRANCH INFORMATION =============\n");
    view_branches();
    printf("Select a branch (1-5) to view details: ");
    scanf("%d", &branch);

    if (branch < 1 || branch > 5) {
        printf("Invalid branch selection!\n");
    } else {
        branch--;  // Adjust for 0-based indexing
        printf("\nBranch: %s\n", branches[branch]);
        printf("HOD: %s\n", hods[branch]);
        printf("Subjects: %s\n", subjects[branch]);
        printf("Fees: INR %.2f per year\n", fees[branch]);
        printf("Total Seats: %d\n", total_seats[branch]);
    }

    printf("\nPress any key to return to the main menu...");
    getchar(); getchar(); 
}
