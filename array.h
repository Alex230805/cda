#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define ARRAY_DEFAULT_CAPACITY 64

/*
 *	Every array declaration must be a struct 
 *	compatible with the following fields. 
 */

typedef struct{
	uintptr_t** elem;
	size_t tracker;
	size_t size;
}Array_Example;

void da_append_imp(void* array,  uintptr_t *elem);
uintptr_t* da_get_at_imp(void* array, size_t i);
uintptr_t* da_pop_last_imp(void* array);
void da_insert_imp(void* array, uintptr_t* elem, size_t index);
uintptr_t* da_pop_at_imp(void* array, size_t index);
void da_destroy_imp(void* array);

#define da_append(array, elem, elem_size)								\
	do{																	\
		uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t)*elem_size);	\
		memcpy(buffer, (uint8_t*)&elem, elem_size);						\
		da_append_imp(&array, (uintptr_t*)buffer);						\
	}while(0)															\

#define da_get_at(array, index) da_get_at_imp(&array, index)
#define da_pop_last(array) da_pop_last_imp(&array)

#define da_pop_at(array, index) da_pop_at_imp(&array, index)			
#define da_insert(array, elem, elem_size, index)						\
	do{																	\
		uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t)*elem_size);	\
		memcpy(buffer, (uint8_t*)&elem, elem_size);						\
		da_insert_imp(&array, (uintptr_t*)buffer, index);				\
	}while(0)															\

#define da_destroy(array) da_destroy_imp(&array);

#ifdef ARRAY_IMP

void da_append_imp(void* array, uintptr_t* elem){
	assert(array != NULL && elem != NULL);
	if(((Array_Example*)array)->size < ARRAY_DEFAULT_CAPACITY){
		((Array_Example*)array)->elem = (uintptr_t**)malloc(sizeof(uintptr_t*)*ARRAY_DEFAULT_CAPACITY);
		((Array_Example*)array)->size = ARRAY_DEFAULT_CAPACITY;
		((Array_Example*)array)->tracker = 0;
	}
	if(((Array_Example*)array)->tracker+1 > ((Array_Example*)array)->size){
		((Array_Example*)array)->elem = (uintptr_t**)realloc(((Array_Example*)array)->elem, sizeof(uintptr_t*)*((Array_Example*)array)->size*2);
		assert(((Array_Example*)array)->elem != NULL);
		((Array_Example*)array)->size *= 2; 
	}
	((Array_Example*)array)->elem[((Array_Example*)array)->tracker] = elem;
	((Array_Example*)array)->tracker += 1;
	return;   
}

uintptr_t* da_get_at_imp(void* array, size_t i){
	assert(array != NULL);
	if(i >= ((Array_Example*)array)->tracker || ((Array_Example*)array)->size < ARRAY_DEFAULT_CAPACITY) return NULL;
	return ((Array_Example*)array)->elem[i];
}

uintptr_t* da_pop_last_imp(void* array){
	assert(array != NULL);
	if(((Array_Example*)array)->tracker == 0 || ((Array_Example*)array)->size < ARRAY_DEFAULT_CAPACITY) return NULL;
	uintptr_t *e = ((Array_Example*)array)->elem[((Array_Example*)array)->tracker-1];
	((Array_Example*)array)->tracker -= 1;
	return e;
}

void da_insert_imp(void* array, uintptr_t* elem, size_t index){
	assert(array != NULL && elem != NULL);
	if(((Array_Example*)array)->size < ARRAY_DEFAULT_CAPACITY){
		((Array_Example*)array)->elem = (uintptr_t**)malloc(sizeof(uintptr_t*)*ARRAY_DEFAULT_CAPACITY);
		((Array_Example*)array)->tracker = 0;
	}
	if(index >= ((Array_Example*)array)->size){
		size_t new_cap = ((Array_Example*)array)->size;
		while(index >= new_cap) new_cap *= 2;
		((Array_Example*)array)->elem = (uintptr_t**)realloc(((Array_Example*)array)->elem, sizeof(uintptr_t*)*new_cap);
		assert(((Array_Example*)array)->elem != NULL);
		((Array_Example*)array)->size = new_cap;
		((Array_Example*)array)->elem[index] = elem;
		((Array_Example*)array)->tracker = index+1;
	}else{
		if(((Array_Example*)array)->tracker+1 > ((Array_Example*)array)->size){
			((Array_Example*)array)->elem = (uintptr_t**)realloc(((Array_Example*)array)->elem, sizeof(uintptr_t*)*((Array_Example*)array)->size*2);
			assert(((Array_Example*)array)->elem != NULL);
			((Array_Example*)array)->size *= 2; 
		}
		for(int i=((Array_Example*)array)->tracker-1; i >= ((Array_Example*)array)->tracker - index-1; i--){
			((Array_Example*)array)->elem[i+1] = ((Array_Example*)array)->elem[i]; 
		}
		((Array_Example*)array)->elem[index] = elem;
		if(index >= ((Array_Example*)array)->tracker){
			((Array_Example*)array)->tracker = index+1;
		}else{
			((Array_Example*)array)->tracker += 1;
		}
	}
	return;
}

uintptr_t* da_pop_at_imp(void* array, size_t index){
	assert(array != NULL);
	if(index >= ((Array_Example*)array)->tracker || ((Array_Example*)array)->size < ARRAY_DEFAULT_CAPACITY) return NULL;
	uintptr_t* elem = ((Array_Example*)array)->elem[index];
	for(int i = index; i < ((Array_Example*)array)->tracker; i++){
		((Array_Example*)array)->elem[i] = ((Array_Example*)array)->elem[i+1];
	}
	((Array_Example*)array)->tracker -= 1;
	return elem;
}


void da_destroy_imp(void* array){
	assert(array != NULL);
	if(((Array_Example*)array)->size < ARRAY_DEFAULT_CAPACITY) return;
	if(((Array_Example*)array)->tracker == 0) return;

	for(size_t i=0;i<((Array_Example*)array)->tracker; i++){
		if(((Array_Example*)array)->elem[i] != NULL){
			free(((Array_Example*)array)->elem[i]);
			((Array_Example*)array)->elem[i] = NULL;
		}
	}
	((Array_Example*)array)->tracker = 0;
	((Array_Example*)array)->size = 0;
	if(((Array_Example*)array)->elem){
		free(((Array_Example*)array)->elem);
		((Array_Example*)array)->elem  = NULL;
	}
}


#endif
#endif // ARRAY_H
