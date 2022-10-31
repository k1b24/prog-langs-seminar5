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
struct list_##type* list_##type##_push(struct list_##type* head, type x) { \
	struct list_##type *node = (struct list_##type*) malloc(sizeof(struct list_##type));\
	node->value = x;\
	node->next = head;\
	return node;\
}\
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
	struct list_int64_t* head = NULL;
	head = list_int64_t_push(head, 2);
	head = list_int64_t_push(head, 3);
	list_int64_t_print(head);
	//Тут еще можно по аналогии сделать всяких списочков 
}
