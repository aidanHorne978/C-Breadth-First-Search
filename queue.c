#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "queue.h"

/* creates a queue structure
 */
struct queue{
    int *items;/* change to char for strings */
    int head;
    int capacity;
    int num_items;
};

/*creates a new queue
  @param size is the size of the queue
  @return an emalloced queue
*/
queue queue_new(int size){
    queue result = emalloc(sizeof *result);
    result->capacity = size;
    result->head = 0;
    result->num_items = 0;
    result->items = emalloc(result->capacity *sizeof result->items[0]);
    return result;
}

/*adds an item to the queue
  @param q is the queue to be added to. item is the item to be added
*/
void enqueue(queue q, double item){
    if (q->num_items < q->capacity){
        q->items[(q->head+q->num_items++) % q->capacity] = item;
        return;
    }
    return;
}

/* removes the first item off the queue
   @param g is the queue to be removed from
   @return the item that was taken off the queue
*/
double dequeue(queue q){
    double dequeue;
    if (q->num_items > 0){
        dequeue = q->items[q->head];
        q->head++;
        q->num_items--;
        return dequeue;
    } else {
        return EXIT_FAILURE;
    }
}

/*prints the queue to stdout
  @param q is the queue to be printed
*/
void queue_print(queue q){
    int i = q->head;
    do{
        printf("%.2d\n", q->items[i]);
        i = (i+1)%q->capacity;
    } while (i!=(q->head + q->num_items)%q->capacity);
    return;
}

/* prints out the information about a queue
   @param queue to be printed
*/
void queue_print_info(queue q) {
    int i;
    printf("capacity %d, num_items %d, head %d\n[", q->capacity,
           q->num_items, q->head);
    for (i = 0; i < q->capacity; i++) {
        printf("%s%.2d", i == 0 ? "" : ", ", q->items[i]);
    }
    printf("]\n");
}

/* returns the size of the queue
   @param queue is the queue
   @return the size of the queue
*/
int queue_size(queue q){
    return q->num_items;
}

/* frees the memory allocated
   @param queue to be freed
   @return the freed queue
*/
queue queue_free(queue q){
    free(q->items);
    free(q);
    return q;
}
