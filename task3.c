#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

void error(const char *s) {
  fprintf(stderr, "%s", s);
  abort();
}

#define _print(type, x) type##_print(x)

#define print(x)                                                        \
  _Generic((x),                                                         \
           int64_t : int64_t_print(x),                                  \
           double : double_print(x),                                    \
           default : error("Wrong type"))

#define set_struct(x) \
  _Generic((x),         \
          int64_t : struct list_int64_t,  \
          double: struct list_double,  \
          default : error("Wrong type"))


void int64_t_print(int64_t i) { printf("%" PRId64, i); }
void double_print(double d) { printf("%lf", d); }
void newline_print() { puts(""); }

#define DEFINE_LIST(type)                                               \
  struct list_##type {                                                  \
    type value;                                                         \
    struct list_##type* next;                                           \
  };\
\

#define DEFINE_FUNCS_FOR_TYPE(type)                                              \
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



#define list_push(list, value) \
  _Generic((list),                 \
      struct list_int64_t*: list_int64_t_push(list, value), \
      struct list_double*: list_double_push(list, value), \
      default: error("Wrong type"))
      
#define list_print(list) \
  _Generic((list),                 \
      struct list_int64_t*: list_int64_t_print(list), \
      struct list_double*: list_double_print(list), \
      default: error("error"))

DEFINE_LIST(int64_t)
DEFINE_FUNCS_FOR_TYPE(int64_t)
DEFINE_LIST(double)
DEFINE_FUNCS_FOR_TYPE(double)

int main() {
	struct list_int64_t* head = NULL;
	head = list_push(head, 1);
	head = list_push(head, 2);
	head = list_push(head, 3);
	list_print(head);
	//Тут еще можно по аналогии сделать всяких списочков 
}
