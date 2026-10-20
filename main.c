#include <stdio.h>
#include <stdlib.h>
#define ARRAY_IMP
#include "array.h"
#include <string.h>

typedef struct{
	int a;
	char* t;
	float b;
}Token;

typedef struct{
	Token** token;
	size_t tracker;
	size_t size;
}Tokens;

Tokens local_token_array = {0};

int main(){
	printf("======================================================\n");
	printf("Appending elements\n");
	Token t1 = {.a = 50, .t = "Hello world", .b = 69.420};
	Token t2 = {.a = 51, .t = "Hello world", .b = 69.420};
	Token t3 = {.a = 52, .t = "Hello world", .b = 69.420};
	da_append(local_token_array, t1, sizeof(Token));
	da_append(local_token_array, t2, sizeof(Token));
	da_append(local_token_array, t3, sizeof(Token));
	for(int i=0;i<local_token_array.tracker; i++){
		Token* l = local_token_array.token[i];
		printf("a = %d, t = %s, b = %f\n", l->a, l->t, l->b);
	}
	printf("======================================================\n");
	Token* popped = (Token*)da_pop_last(local_token_array);
	for(int i=0;i<local_token_array.tracker; i++){
		Token* l = local_token_array.token[i];
		printf("a = %d, t = %s, b = %f\n", l->a, l->t, l->b);
	}
	printf("Token popped: %d, %s, %f\n", popped->a, popped->t, popped->b);
	printf("======================================================\n");
	da_destroy(local_token_array);
	printf("Appending new elements after destroy\n");
	Token t4 = {.a = 34, .t = "Foo", .b = 69.0};
	Token t5 = {.a = 35, .t = "Bar", .b = 69.1};
	Token t6 = {.a = 1337, .t = "Baz", .b = 69.2};
	da_append(local_token_array, t4, sizeof(Token));
	da_append(local_token_array, t5, sizeof(Token));
	da_append(local_token_array, t6, sizeof(Token));
	printf("======================================================\n");
	for(int i=0;i<local_token_array.tracker; i++){
		Token* l = local_token_array.token[i];
		printf("a = %d, t = %s, b = %f\n", l->a, l->t, l->b);
	}
	printf("======================================================\n");
	printf("Destrying the array\n");
	da_destroy(local_token_array);
	printf("======================================================\n");
	printf("Testing precise insert\n");
	da_append(local_token_array, t1, sizeof(Token));
	da_append(local_token_array, t2, sizeof(Token));
	da_append(local_token_array, t3, sizeof(Token));
	for(int i=0;i<local_token_array.tracker; i++){
		Token* l = local_token_array.token[i];
		printf("a = %d, t = %s, b = %f\n", l->a, l->t, l->b);
	}
	printf("======================================================\n");
	printf("Adding new token between others and outside boundaries\n");
	Token tok = {.a = 44, .t = "Custom token", .b = 44.0};
	Token far_tok = {.a = 67, .t = "token very far away", .b = 0};
	da_insert(local_token_array, tok, sizeof(Token), 1);
	da_insert(local_token_array, far_tok, sizeof(Token), 10);
	printf("======================================================\n");
	for(int i=0;i<local_token_array.tracker; i++){
		Token* l = local_token_array.token[i];
		if(l == NULL){
			printf("Empty\n");
		}else{
			printf("a = %d, t = %s, b = %f\n", l->a, l->t, l->b);
		}
	}
	printf("======================================================\n");
	printf("Popping last addedd token\n");
	da_pop_last(local_token_array);
	printf("======================================================\n");
	for(int i=0;i<local_token_array.tracker; i++){
		Token* l = local_token_array.token[i];
		if(l == NULL){
			printf("Empty\n");
		}else{
			printf("a = %d, t = %s, b = %f\n", l->a, l->t, l->b);
		}
	}
	printf("======================================================\n");
	printf("Testing pop between elements. Before popping at index 3: \n");
	for(int i=0;i<local_token_array.tracker; i++){
		Token* l = local_token_array.token[i];
		if(l == NULL){
			printf("Empty\n");
		}else{
			printf("a = %d, t = %s, b = %f\n", l->a, l->t, l->b);
		}
	}
	printf("\nAfter popping:\n");
	popped = (Token*)da_pop_at(local_token_array, 3);
	for(int i=0;i<local_token_array.tracker; i++){
		Token* l = local_token_array.token[i];
		if(l == NULL){
			printf("Empty\n");
		}else{
			printf("a = %d, t = %s, b = %f\n", l->a, l->t, l->b);
		}
	}
	printf("Token popped: %d, %s, %f\n", popped->a, popped->t, popped->b);
	printf("======================================================\n");
	da_destroy(local_token_array);
	return 0;
}
