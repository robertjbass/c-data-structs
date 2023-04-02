
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

void delete_array(struct Array **arr) {
  // free the memory from the heap when we are done with it
  assert(*arr != NULL);

  free((*arr)->values);
  free(*arr);

  *arr = NULL;
}

void push(struct Array *arr, int value) {
  arr->size++;

  // does the array have enough space to add a new value?
  // if not, we need to allocate more memory
  if (arr->capacity <= arr->size * sizeof(int)) {
    arr->values = realloc(arr->values, sizeof(int) * arr->size * 2);
  }

  arr->values[arr->size - 1] = value;
}

int pop(struct Array *arr) {
  int last_value;

  for (int i = 0; i < arr->size; i++) {
    if (i == arr->size - 1) {
      last_value = arr->values[i];
    }
  }

  arr->size--;

  if (arr->capacity >= arr->size * sizeof(int) * 2) {
    arr->values = realloc(arr->values, sizeof(int) * arr->size * 2);
  }

  return last_value;
}

void print_array(struct Array *arr) {
  for (int i = 0; i < arr->size; i++) {
    printf("%d ", arr->values[i]);
  }
  printf("\n");
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

  if (arr->capacity >= arr->size * sizeof(int) * 2) {
    arr->values = realloc(arr->values, sizeof(int) * arr->size * 2);
  }

}



int main() {
    int values[] = {1, 2, 3, 4, 5};
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

    delete_array(&arr_struct);

    return 0;
}
