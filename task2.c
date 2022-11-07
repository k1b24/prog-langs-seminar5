/* generic_list.c */

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define _print(type, x) type##_print(x)

void int64_t_print(int64_t i) { printf("%" PRId64, i); }
void double_print(double d) { printf("%lf", d); }
void newline_print() { puts(""); }

#define DEFINE_LIST(type)                                               \
  struct list_##type {                                                  \
    type value;                                                         \
    struct list_##type* next;                                           \
  };\
\
void list_##type##_push (struct list_##type** head, type value) {             \
	struct list_##type* next = malloc(sizeof(struct list_##type));       \
    next -> value = value;                                   \
    next -> next = NULL;                                     \
    if (*head == NULL) {                              \
		*head = next;                                  \
		return;                                       \
    }                                               \
    struct list_##type* tmp = *head;                \
    while (tmp -> next != NULL) tmp = tmp -> next;  \
    tmp -> next = next;                             \
  }                                                 \
\
void list_##type##_print(struct list_##type* head) { \
	struct list_##type *node = head; \
	while (node != NULL) {\
		_print(type, node->value);\
		_print(newline, "");\
		node = node->next;\
	}\
}\

DEFINE_LIST(int64_t)
DEFINE_LIST(double)

int main() {
	struct list_int64_t* l = NULL;
	list_int64_t_push(&l, 1);
	list_int64_t_push(&l, 2);
	list_int64_t_push(&l, 3);
	list_int64_t_print(l);

	struct list_double* ld = NULL;
	list_double_push(&ld, 4);
	list_double_push(&ld, 5);
	list_double_push(&ld, 6);
	list_double_print(ld);
	return 0;
}
