/* generic_list.c */

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
           default : error("Unsupported operation"))

#define set_struct(x) \
  _Generic((x),         \
          int64_t : struct list_int64_t,  \
          double: struct list_double,  \
          default : error("aaa"))
          
void int64_t_print(int64_t i) { printf("%" PRId64, i); }
void double_print(double d) { printf("%lf", d); }
void newline_print() { puts(""); }

#define DEFINE_LIST(type)                                               \
  struct list_##type {                                                  \
    type value;                                                         \
    struct list_##type* next;                                           \
  };                                                                    

#define DEFINE_ADD(type)                                              \
  void list_##type##_push (struct list_##type** old, type value) {             \
     struct list_##type* next = malloc(sizeof(struct list_##type));       \
     next -> value = value;                                   \
     next -> next = NULL;                                     \
    if (*old == NULL) {                              \
      *old = next;                                  \
      return;                                       \
    }                                               \
    struct list_##type* tmp = *old;                \
    while (tmp -> next != NULL) tmp = tmp -> next;  \
    tmp -> next = next;                             \
                                         \
  }                                                 \
  void list_##type##_print (struct list_##type* list) {    \
    while(list != NULL) {                           \
      _print(type, list-> value);                    \
      newline_print();                              \
      list = list -> next;                          \
    }                                                \
    newline_print();                                 \
  }

#define list_push(list, value) \
  _Generic((list),                 \
      struct list_int64_t**: list_int64_t_push(list, value), \
      struct list_double**: list_double_push(list, value), \
      default: error("sfdg"))
      
#define list_print(list) \
  _Generic((list),                 \
      struct list_int64_t*: list_int64_t_print(list), \
      struct list_double*: list_double_print(list), \
      default: error("sfdg"))
  
DEFINE_LIST(int64_t)
DEFINE_ADD(int64_t)
DEFINE_LIST(double)
DEFINE_ADD(double)

int main() {
  struct list_int64_t* l = NULL;
  list_push(&l, 1);
  list_push(&l, 2);
  list_push(&l, 3);
  list_print(l);
  
  newline_print();
  
  struct list_double* ld = NULL;
  list_push(&ld, 1.1);
  list_push(&ld, 1.2);
  list_push(&ld, 2.3);
  list_print(ld);
  return 0;
}
