
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


struct Array {
  int *values;
  int size;
  int capacity;
};


struct Array *create_array(int *values, int size) {
  // allocate memory on the heap
  struct Array *arr_struct = malloc(sizeof(struct Array));

  int capacity = sizeof(int) * size * 2;

  arr_struct->values = malloc(capacity);
  arr_struct->size = size;
  arr_struct->capacity = capacity;

  for (int i = 0; i < size; i++) {
    arr_struct->values[i] = values[i];
  }

  return arr_struct;
}


void print_array(struct Array *arr) {
  for (int i = 0; i < arr->size; i++) {
    printf("%d ", arr->values[i]);
  }
  printf("\n");
}


void reallocate(struct Array *arr) {
  // does the array have too much or too little space?
  int too_much = arr->capacity > arr->size * sizeof(int) * 2;
  int too_little = arr->capacity < arr->size * sizeof(int);

  if (too_much || too_little) {
    arr->values = realloc(arr->values, sizeof(int) * arr->size * 2);
  }
}


void delete_array(struct Array **arr) {
  // free the memory from the heap when we are done with it
  assert(*arr != NULL);

  free((*arr)->values);
  free(*arr);

  *arr = NULL;
}


void push(struct Array *arr, int value) {
  arr->size++;
  reallocate(arr);
  arr->values[arr->size - 1] = value;
}


int pop(struct Array *arr) {
  int last_value = arr->values[arr->size - 1];

  arr->size--;
  reallocate(arr);

  return last_value;
}


void remove_value(struct Array *arr, int value) {
  for (int i = 0; i < arr->size; i++) {
    if (arr->values[i] == value) {
      arr->size--;
      for (int j = i; j < arr->size; j++) {
        arr->values[j] = arr->values[j + 1];
      }
    }
  }

  reallocate(arr);
}

void sort(struct Array *arr) {
  int temp, current_value, next_value, i;
  int is_sorted = 1;

  for (i = 0; i < arr->size - 1; i++) {
    if (i != arr->size - 1) {
      current_value = arr->values[i];
      next_value = arr->values[i + 1];
      if (next_value < current_value) {
        is_sorted = 0;
        temp = arr->values[i];
        arr->values[i] = arr->values[i + 1];
        arr->values[i + 1] = temp;
      }
    }
  }

  if (!is_sorted) sort(arr);
}


int main() {
  int values[] = {5, 3, 2, 1, 4};
  int size = sizeof(values) / sizeof(int);

  struct Array *arr_struct = create_array(values, size);

  int *arr_values = arr_struct -> values;

  print_array(arr_struct);
  push(arr_struct, 6);
  print_array(arr_struct);

  int removed_value = pop(arr_struct);
  printf("Removed value (pop): %d\n", removed_value);
  print_array(arr_struct);

  int value_to_remove = 3;
  remove_value(arr_struct, value_to_remove);
  printf("Removed value (remove): %d\n", value_to_remove);
  print_array(arr_struct);

  printf("sorting array...\n");
  sort(arr_struct);
  print_array(arr_struct);

  delete_array(&arr_struct);

  return 0;
}
