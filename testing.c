#include "my_library.h"
#include <assert.h>
void test_my_str_create() {
    my_str_t* new_str;
    size_t buf_size = 5;
    char* new_data = malloc(buf_size + 2);
    my_str_create(new_str, buf_size);
    assert(new_str->data == new_data);
    printf("new_str->data is created correctly");
    assert(new_str->size_m == 0);
    printf("new_str->size_m is created correctly");
    assert(new_str->capacity_m == buf_size+1);
    printf("new_str->capacity_m is created correctly");
    my_str_free(new_str);
}

void test_my_str_free() {
    my_str_t* new_str;
    size_t buf_size = 5;
    my_str_create(new_str, buf_size);
    my_str_free(new_str);
    assert(new_str->data == NULL);
    printf("new_str->data is freed correctly");
    assert(new_str->size_m == 0);
    printf("new_str->size_m is freed correctly");
    assert(new_str->capacity_m == 0);
    printf("new_str->capacity_m is freed correctly");
}

void test_my_str_from_cstr(){
    char* new_cstr = malloc(5);
    new_cstr = "hello";
    my_str_t* new_str;
    my_str_from_cstr(new_str, new_cstr, 5);
    assert(new_str->data == new_cstr);
    printf("new_str->data is created correctly");
    assert(new_str->size_m == 5);
    printf("new_str->size_m is created correctly");
    assert(new_str->capacity_m == 6);
    printf("new_str->capacity_m is created correctly");
    my_str_free(new_str);
}

void test_info() {
    char* new_cstr = malloc(5);
    new_cstr = "hello";
    my_str_t* new_str;
    my_str_from_cstr(new_str, new_cstr, 6);

    assert(my_str_size(new_str) == 5);
    printf("my_str_size works properly");

    assert(my_str_capacity(new_str) == 7);
    printf("my_str_capacity works properly");

    assert(my_str_empty(new_str) == 0);
    printf("my_str_empty works properly");

    my_str_free(new_str);
}

void test_access() {
    char* new_cstr = malloc(5);
    new_cstr = "hello";
    my_str_t* new_str;
    my_str_from_cstr(new_str, new_cstr, 6);

    assert(my_str_getc(new_str, 0) == 'h');
    printf("my_str_getc works properly");

    my_str_putc(new_str, 0, 'l');
    assert(new_str->data == "lello");
    printf("my_str_putc works properly");


    assert(my_str_get_cstr(new_str) == new_cstr);
    printf("my_str_get_cstr works properly");

}

void test_modification() {
    char* new_cstr = malloc(5);
    new_cstr = "hello";
    my_str_t* new_str;
    my_str_from_cstr(new_str, new_cstr, 6);

    my_str_t* new_str2;
    size_t buf_size2 = 6;
    my_str_create(new_str2, buf_size2);

    my_str_copy(new_str,  new_str2, 0);
    assert(new_str2->data == new_str->data);
    printf("my_str_copy works properly");

    my_str_free(new_str2);
    my_str_from_cstr(new_str2, new_cstr, 6);

    my_str_insert_c(new_str, 'e', 1);
    assert(new_str->data == "heello");
    printf("my_str_insert_c works properly");

    my_str_insert(new_str, new_str2, 1);
    assert(new_str->data == "hhelloeello");
    printf("my_str_insert works properly");

    my_str_insert_cstr(new_str, new_cstr, 1);
    assert(new_str->data == "hhellohelloeello");
    printf("my_str_insert_cstr works properly");

    my_str_append(new_str, new_str2);
    assert(new_str->data == "hhellohelloeellohello");
    printf("my_str_append works properly");

    my_str_append_cstr(new_str, new_cstr);
    assert(new_str->data == "hhellohelloeellohellohello");
    printf("my_str_append_cstr works properly");

    my_str_append_c(new_str, 'e');
    assert(new_str->data == "hhellohelloeellohellohelloe");
    printf("my_str_append_c works properly");

    my_str_substr(new_str, new_str2, 0, 5);
    assert(new_str2->data == "hhell");
    printf("my_str_substr works properly");

    my_str_substr_cstr(new_str, new_cstr, 0, 6);
    assert(new_cstr == "hehhello");
    printf("my_str_substr_cstr works properly");

    my_str_erase(new_str, 1, 27);
    assert(new_str->data == "h");
    printf("my_str_erase works properly");

    assert(my_str_popback(new_str) == 'h');
    printf("my_str_popback works properly");

    char* new_data = '\0';
    my_str_clear(new_str2);
    assert(new_str2->data == new_data);
    printf("my_str_clear works properly");

    my_str_free(new_str);
    my_str_free(new_str2);
}

void test_buffer_manipulation() {
    char* new_cstr = malloc(5);
    new_cstr = "hello";
    my_str_t* new_str;
    my_str_from_cstr(new_str, new_cstr, 20);

    my_str_shrink_to_fit(new_str);

    assert(new_str->capacity_m == new_str->size_m+1);
    printf("my_str_shrink_to_fit works properly");
    my_str_free(new_str);
}

void test_size_manipulation() {
    char* new_cstr = malloc(5);
    new_cstr = "hello";
    my_str_t* new_str;
    my_str_from_cstr(new_str, new_cstr, 6);

    my_str_resize(new_str, 10, 'a');

    assert(new_str->data == "helloaaaaa");
    printf("my_str_resize works properly");
    my_str_free(new_str);
}

void test_search(){
    char* new_cstr = malloc(5);
    new_cstr = "hello";
    my_str_t* new_str;
    my_str_from_cstr(new_str, new_cstr, 6);

    char* new_cstr2 = malloc(2);
    new_cstr2 = "he";
    my_str_t* new_str2;
    my_str_from_cstr(new_str2, new_cstr, 3);

    char* new_cstr3 = malloc(5);
    new_cstr2 = "hella";
    my_str_t* new_str3;
    my_str_from_cstr(new_str3, new_cstr, 3);

    assert(my_str_find(new_cstr, new_cstr2, 0) == 0);
    printf("my_str_find works properly");

    assert(my_str_cmp(new_str, new_str3) == 1);
    printf("my_str_cmp works properly");

    assert(my_str_cmp_cstr(new_str, new_cstr3) == 1);
    printf("my_str_cmp_cstr works properly");

    assert(my_str_find_c(new_str, 'e', 0) == 1);
    printf("my_str_find_c works properly");

    //! I don't know how to test my_str_find_if
    my_str_free(new_str);
    my_str_free(new_str2);
    my_str_free(new_str3);
}

void test_input_output() {
    char* new_cstr = malloc(1);
    my_str_t* new_str;
    my_str_create(new_str, 2);

    my_str_read_file(new_str, "list_POK_2020.txt");
    assert(new_str->data == "1");
    printf("my_str_read_file works properly");

    my_str_clear(new_str);

    my_str_read_file_delim(new_str, "list_POK_2020.txt", 1);
    assert(new_str->data == "1");
    printf("my_str_read_file_delim works properly");

    my_str_write_file(new_str, "list_POK_2020.txt");
    my_str_write(new_str);
}
