#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct queue
{
    char name[20];
    int priority;
    struct queue *next;
} queue;

// Global Variables
queue *head, *indexer, *tail = NULL;

// Function prototypes
int getCount(int priority);
void enqueue(char name[], int priority);
void enqueueBetween(queue *node, int priority);
void dequeue();
void printQueue();
void actionSelectionMenu();
void subjectSelectionMenu();

int main()

{
    enqueue("Eda", 2);   // #4
    enqueue("Yusuf", 3); // #6
    enqueue("Deniz", 1); // #1
    enqueue("Merve", 3); // #7
    enqueue("Cem", 1);   // #3
    while (1)
    {
        actionSelectionMenu();
    }
    return 1;
}

void actionSelectionMenu()
{
    fflush(stdin);
    system("cls");

    printf("Select the action:\n\n");
    printf("1) Enqueue\n");
    printf("2) Dequeue\n\n\n\n\n\n");
    printQueue();

    switch (getchar())
    {
    case '1':
        subjectSelectionMenu();
        break;
    case '2':
        if (head == NULL)
        {
            printf("\nQueue is empty!");
            Sleep(1200);
            actionSelectionMenu();
        }
        else
        {
            dequeue();
        }

        break;
    default:
        printf("\nWrong Input!");
        Sleep(1200);
        actionSelectionMenu();
        break;
    }
}

void subjectSelectionMenu()
{
    fflush(stdin);
    system("cls");

    printf("Select the subject:\n\n");
    printf("1) Open A Bank Account \n");
    printf("2) Deposit & Withdraw\n");
    printf("3) Get Info\n\n");
    printf("4) Back\n\n\n");
    printQueue();

    int priority;
    switch (getchar())
    {
    case '1':
        priority = 1;
        break;
    case '2':
        priority = 2;
        break;
    case '3':
        priority = 3;
        break;
    case '4':
        actionSelectionMenu();
        break;
    default:
        printf("\nWrong Input!");
        Sleep(1200);
        subjectSelectionMenu();
        break;
    }
    fflush(stdin);
    system("cls");

    char name[20];
    printf("Enter the name: ");
    scanf("%s", name);

    enqueue(name, priority);
}

void enqueue(char name[], int priority)
{
    if (head == NULL)
    {
        queue *node = (queue *)malloc(sizeof(queue));

        strcpy(node->name, name);
        node->priority = priority;
        node->next = NULL;

        head = tail = node;
    }
    else
    {
        queue *node = (queue *)malloc(sizeof(queue));

        strcpy(node->name, name);
        node->priority = priority;
        node->next = NULL;

        if (priority < head->priority) // is node new head ?
        {
            node->next = head;
            head = node;
        }
        else if (priority >= tail->priority) // is node new tail ?
        {
            tail->next = node;
            tail = node;
        }
        else // otherwise the item should be somewhere in the queue
        {
            enqueueBetween(node, priority);
        }
    }
}

void enqueueBetween(queue *node, int priority)
{
    int countInputPriority = getCount(priority);

    if (countInputPriority == 0)
    {
        int countPrevPriority = getCount(priority - 1);

        indexer = head;
        while (indexer != NULL)
        {
            if (indexer->priority == (priority - 1))
            {
                countPrevPriority--;

                if (countPrevPriority == 0)
                {
                    node->next = indexer->next;
                    indexer->next = node;
                }
            }
            indexer = indexer->next;
        }
    }
    else
    {
        indexer = head;
        while (indexer != NULL)
        {
            if (indexer->priority == priority)
            {
                countInputPriority--;
                if (countInputPriority == 0)
                {
                    node->next = indexer->next;
                    indexer->next = node;
                }
            }
            indexer = indexer->next;
        }
    }
}

void dequeue()
{
    queue *temp = head->next;
    free(head);
    head = temp;
}

int getCount(int priority)
{
    int count = 0;

    if (priority == 0) // to get queue's total count
    {
        indexer = head;
        while (indexer != NULL)
        {
            count++;
            indexer = indexer->next;
        }
    }
    else
    {
        indexer = head;
        while (indexer != NULL)
        {
            if (indexer->priority == priority)
            {
                count++;
            }

            indexer = indexer->next;
        }
    }

    return count;
}

void printQueue()
{
    printf("   Queue | %d\n", getCount(0));
    printf("_____________\n\n");

    indexer = head;

    while (indexer != NULL)
    {
        printf("   %s\n", indexer->name);
        indexer = indexer->next;
    }
    printf("\n\n\n");
}
