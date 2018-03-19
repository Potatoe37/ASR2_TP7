#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct queue_aux {
	void* elt;
	struct queue_aux* next;
};

struct queue {
	struct queue_aux* first;
	struct queue_aux* last;
};

struct queue* queue_new() {
	struct queue* file = malloc(sizeof(struct queue));
	file->first = NULL;
	file->last = NULL;
	return file;
};

void queue_free(struct queue* file) {
	pthread_mutex_lock(&mutex);
	struct queue_aux* elt = file->first;
	while (elt!=NULL) {
		struct queue_aux* suiv = elt->next;
		free(elt);
		elt = suiv;
	};
	free(file);
	pthread_mutex_unlock(&mutex);
};

void queue_push(struct queue* file, void* value) {
	pthread_mutex_lock(&mutex);
	struct queue_aux* new_last = malloc(sizeof(struct queue_aux));
	new_last->elt = value;
	new_last->next = NULL;
	if (file->first==NULL) {
		file->first=new_last;
		file->last=new_last;
	}
	else {
		(file->last)->next = new_last;
		file->last = new_last;
	}
	pthread_mutex_unlock(&mutex);
}; 

void* queue_pop(struct queue* file) {
	pthread_mutex_lock(&mutex);
	struct queue_aux* head = file->first;
	if (head==NULL) return NULL;
	if (file->first==file->last) file->last==NULL;
	void* el = head->elt;
	file->first=head->next;
	free(head);
	pthread_mutex_unlock(&mutex);
	return el;
};

void print_queue(struct queue* file) {
	struct queue_aux* tmp = file->first;
	while (tmp!=NULL) {
		struct queue_aux* suiv = tmp->next;
		int* el = tmp->elt;
		printf("%d ; ",*el);
		tmp = suiv;
	};
}

int main() {
	struct queue* q=queue_new();
	int a0=6;
	int* a=&a0;
	queue_push(q,a);
	int b0=7;
	int* b=&b0;
	queue_push(q,b);
	int* c;
	c=queue_pop(q);
	printf("%d\n",*c);
	print_queue(q);
	return 0;
}
