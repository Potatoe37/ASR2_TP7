struct queue; /* Structure opaque, à définir dans queue.c */

struct queue* queue_new(void);
void queue_free(struct queue *queue);
void queue_push(struct queue *q,void *valeur);
void* queue_pop(struct queue *q);
void* queue_pop_blocking(struct queue *q);
