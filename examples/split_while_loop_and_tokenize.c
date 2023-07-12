#define SV_IMPLEMENTATION
#include "sv.h"

#include <errno.h>
#include <stdio.h>

typedef enum token_type {
  STRING,
  NUMBER,
} token_type;

typedef struct token {
  string_view str;
  token_type type;
  struct token* next;
  struct token* prev;
} token;

typedef struct token_list {
  token* head;
  token* tail;
} token_list;

int sv_tokenize(string_view sv, void* arg);

int main() {
  string_view input = sv(" There is a man   \n  named         Dalton  and  \n he loved to go outside. Not!  ");

  string_view t;
  string_view sv = sv_split_next(input, sv(" \n"), &t);
  while (!sv_is_empty(sv)) {
    printf("'" sv_fmt "' ", sv_arg(t));
    sv = sv_split_next(sv, sv(" \n"), &t);
  }
  if (!sv_is_empty(t)) { // one last token was consumed
    printf("'" sv_fmt "' ", sv_arg(t));
  }
  printf("\n");

  input = sv(" There are 22 men on board in 1924\nI am 27 years old in 2023");

  token_list list = {0};
  if (!sv_for_split_by(input, sv(" \n"), sv_tokenize, &list)) {
    printf("Failed to tokenized!\n");
    return 1;
  }

  token* current = list.head;
  while (current != NULL) {
    printf("(str: '" sv_fmt "', type: %s)\n", sv_arg(current->str), current->type == NUMBER ? "NUMBER" : "STRING");
    current = current->next;
  }
  printf("\n");

  current = list.head;
  while (current != NULL) {
    token* tmp = current;
    current    = current->next;
    free(tmp);
  }

  return 0;
}

int sv_tokenize(string_view sv, void* arg) {
  token_list* list = (token_list*)arg;

  token* t = malloc(sizeof(token));
  if (t == NULL) return 0;

  t->str = sv;
  if (sv_find_first_not_of(sv, sv("0123456789"), 0) == SV_NPOS) {
    t->type = NUMBER;
  } else {
    t->type = STRING;
  }

  if (list->head == NULL && list->tail == NULL) {
    list->head       = t;
    list->tail       = t;
    list->head->next = NULL;
    list->head->prev = NULL;
    list->tail->next = NULL;
    list->tail->prev = NULL;
    return 1;
  }

  if (list->tail->prev == NULL) {
    list->tail       = t;
    list->tail->next = NULL;
    list->tail->prev = list->head;
    list->head->next = list->tail;
    return 1;
  }

  list->tail->next = t;
  t->prev          = list->tail;
  list->tail       = t;

  return 1;
}