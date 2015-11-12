//
// Created by barry on 11/4/15.
//

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "Server.h"

int addItem(list **listInstance, void *item) {
    listItem *currentItem = *listInstance;

    if (item == NULL) {
        fprintf(stderr, "routing_table_row is NULL in addNode()\n");
        return -1;
    }

    //create a new list item
    listItem *newItem = (listItem *)malloc(sizeof(listItem));
    newItem->item = item;
    newItem->next = NULL;

    //insert list item at the head
    if (*listInstance == NULL) {
        *listInstance = newItem;
        (*listInstance)->next = NULL;
        //printf("adding head\n");
    }
    else {
        //insert list item later than head
        while (currentItem->next != NULL) {
            currentItem = currentItem->next;
        }
        currentItem->next = newItem;
        //currentItem->next->next = NULL;
        //printf("adding other nodes\n");
    }
    return 0;
}

int printList(list *listInstance, char * listType) {
    listItem *currentItem = listInstance;
    if (currentItem == NULL) {
        fprintf(stdout, "List is empty\n");
        return 0;
    }
    else {
        if(strcmp(listType, "routing_table_row") == 0)
        {
            do {
                //specific to routing_table_row struct
                routing_table_row *currentRow = (routing_table_row *) currentItem->item;
                printf("ID: %u IP: %s Port: %u Cost: %u Next_hop_ID: %u\n", currentRow->id, currentRow->ipAddress,
                       currentRow->port, currentRow->cost, currentRow->next_hop_id);
                currentItem = currentItem->next;
            }while (currentItem != NULL);
        }
        else if(strcmp(listType, "neighbour") == 0)
        {
            do {
                //specific to neighbour struct
                neighbour *currentNeighbour = (neighbour *) currentItem->item;
                printf("Neighbour ID: %d Timer FD: %d\n", currentNeighbour->id, currentNeighbour->timeoutFD);
                currentItem = currentItem->next;
            }while (currentItem != NULL);
        }
        else
        {
            fprintf(stderr, "Unknown listType give to printLis().\n");
        }

    }
    return 0;
}

void *findRowByID(list *listInstance, int id) {
    listItem *currentItem = listInstance;
    if (currentItem == NULL) {
        fprintf(stdout, "List is empty\n");
        return NULL;
    }
    else {
        do {
            routing_table_row *currentRow = (routing_table_row *) currentItem->item;
            if (currentRow->id == id)
                return currentRow;
            currentItem = currentItem->next;
        } while (currentItem != NULL);
        fprintf(stdout, "Id not found\n");
        return NULL;
    }
}

void *findRowByIPandPort(list *listInstance, char *ip, uint16_t port) {
    listItem *currentItem = listInstance;
    if (currentItem == NULL) {
        fprintf(stdout, "List is empty\n");
        return NULL;
    }
    else {
        do {
            routing_table_row *currentRow = (routing_table_row *) currentItem->item;
            if (strcmp(currentRow->ipAddress, ip) ==0 && currentRow->port== port)
                return currentRow;
            currentItem = currentItem->next;
        } while (currentItem != NULL);
        fprintf(stdout, "ipAddress and port combination not found.\n");
        return NULL;
    }
}


int getSize(list *listInstance)
{
    int size = 0;
    listItem *currentItem = listInstance;
    while (currentItem != NULL)
    {
        size++;
        currentItem = currentItem->next;
    }
    return size;
}