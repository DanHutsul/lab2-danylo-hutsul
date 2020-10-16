#include "my_library.h"

//!===============================================================
//!Creating and destroying the string
//!===============================================================
//!Done
int my_str_create(my_str_t* str, size_t buf_size) {
    if(!str) {
        return NULL_PTR_ERR;
    }

    str->size_m = 0;
    str->capacity_m = buf_size+1;
    str->data = (char *) malloc((str->capacity_m) + 1);

    if(!str->data) {
        return MEMORY_ALLOCATION_ERR;
    }
    return 0;
}

//!Done
int my_str_free(my_str_t* str) {
    if(str) {
        str->capacity_m = 0;
        str->size_m = 0;
        free(str->data);
        str->data = NULL;
    }

    return 0;
}

//!Done
size_t c_strlen(const char* str) {
    const char *s;
    for (s = str; *s; ++s);
    return (s - str);
}
//!Done
int my_str_from_cstr(my_str_t* str, const char* cstr, size_t buf_size) {
    if(!str || !cstr) {
        return NULL_PTR_ERR;
    }
    size_t str_length = c_strlen(cstr);
    str->capacity_m = buf_size+1;
    str->data = (char *) malloc((str->capacity_m) + 1);
    if(buf_size == 0) {
        my_str_reserve(str, str_length);
    } else if (buf_size < str_length) {
        return BUFF_SIZE_ERR;
    } else if (str->capacity_m < str_length) {
        my_str_reserve(str, buf_size);
    }
    if (str->capacity_m < 0) {
        return MEMORY_ALLOCATION_ERR;
    }
    str->size_m = str_length;
    str->data = cstr;
    return 0;
}

//!===============================================================
//!Information about string
//!===============================================================
//!Done
size_t my_str_size(const my_str_t* str) {
    if(!str){
        return 0;
    }
    return str->size_m;
}

//!Done
size_t my_str_capacity(const my_str_t* str) {
    if(!str){
        return 0;
    }
    return str->capacity_m;
}

//!Done
int my_str_empty(const my_str_t* str) {
    if(!str) {
        return 1;
    }
    if(str->size_m > 0) {
        return 0;
    }
    return 1;
}

//!===============================================================
//! Access to string's symbols
//!===============================================================
//!Done
int my_str_getc(const my_str_t* str, size_t index) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if(index > str->size_m-1) {
        return RANGE_ERR;
    }
    return str->data[index];
}

//!Done
int my_str_putc(my_str_t* str, size_t index, char c) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if (index > str->capacity_m) {
        return RANGE_ERR;
    }
    str->data[index] = c;
    return 0;
}

//!Done
const char* my_str_get_cstr(my_str_t* str) {
    if(!str) {
        return NULL;
    }
    if(str->capacity_m == str->size_m+1) {
        my_str_putc(str, str->size_m-1, '\0');
    }
    return str->data;
}

//!===============================================================
//! String Modification
//!===============================================================
//!Done
int my_str_copy(const my_str_t* from,  my_str_t* to, int reserve) {
    if(!from || !to) {
        return NULL_PTR_ERR;
    }
    if(reserve) {
        if(from->size_m > to->capacity_m) {
            return BUFF_SIZE_ERR;
        } else {
            to->size_m = from->size_m;
            to->data = from->data;
        }
    } else {
        if(from->size_m > to->capacity_m) {
            my_str_reserve(to, from->size_m+1);
            to->data = from->data;
        } else {
            to->size_m = from->size_m;
            to->data = from->data;
        }
        return 0;
    }
}

//!Done
int my_str_clear(my_str_t* str) {
    if(str) {
        char* new_data = '\0';
        free(str->data);
        str->data = new_data;
        str->size_m = 0;
    }
    return 0;
}

//!Done
int my_str_insert_c(my_str_t* str, char c, size_t pos) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if(!str->data) {
        return MEMORY_ALLOCATION_ERR;
    }
    if(str->size_m + 1 >= str->capacity_m) {
        my_str_reserve(str, str->capacity_m+1);
    }
    memmove(str->data+pos+1, str->data+pos, str->size_m-pos);
    str->data[pos] = c;
    str->size_m++;
    return 0;
}

//!Done
int my_str_insert(my_str_t* str, const my_str_t* from, size_t pos) {
    if(!str || !from) {
        return NULL_PTR_ERR;
    }
    if(!str->data || !from->data) {
        return MEMORY_ALLOCATION_ERR;
    }
    if(str->size_m + from->size_m >= str->capacity_m) {
        my_str_reserve(str, str->capacity_m+from->size_m);
    }
    memmove(str->data+pos+from->size_m, str->data+pos, str->size_m-pos);
    memmove(str->data+pos, from->data, from->size_m);
    str->size_m += from->size_m;
    return 0;
}

//!Done
int my_str_insert_cstr(my_str_t* str, const char* from, size_t pos) {
    if(!str || !from) {
        return NULL_PTR_ERR;
    }
    if(!str->data) {
        return MEMORY_ALLOCATION_ERR;
    }
    if(str->size_m + sizeof(from) >= str->capacity_m) {
        my_str_reserve(str, str->capacity_m+sizeof(from));
    }
    memmove(str->data+pos+sizeof(from), str->data+pos, str->size_m-pos);
    memmove(str->data+pos, from, sizeof(from));
    str->size_m += sizeof(from);
    return 0;
}

//!Done
int my_str_append(my_str_t* str, const my_str_t* from) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if(!str->data) {
        return MEMORY_ALLOCATION_ERR;
    }
    if(str->size_m + from->size_m >= str->capacity_m) {
        my_str_reserve(str, str->capacity_m+from->size_m);
    }
    for(size_t i=0; i<=sizeof(from); i++) {
        my_str_append_c(str, my_str_getc(from, i));
    }
    str->size_m += from->size_m;
    return 0;
}
//!Done
int my_str_append_cstr(my_str_t* str, const char* from) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if(!str->data) {
        return MEMORY_ALLOCATION_ERR;
    }
    if(str->size_m + sizeof(from) >= str->capacity_m) {
        my_str_reserve(str, str->capacity_m+sizeof(from));
    }
    for(size_t i=0; i<=sizeof(from); i++) {
        my_str_append_c(str, from[i]);
    }
    str->size_m += sizeof(from);
    return 0;
}
//!Done
int my_str_append_c(my_str_t* str, char c) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if(!str->data) {
        return MEMORY_ALLOCATION_ERR;
    }
    if(str->size_m + 1 >= str->capacity_m) {
        my_str_reserve(str, str->capacity_m+1);
    }
    my_str_insert_c(str, c, str->size_m);
    str->size_m++;
    return 0;
}
//!Done
int my_str_substr(const my_str_t* from, my_str_t* to, size_t beg, size_t end) {
    if(!from || !to) {
        return NULL_PTR_ERR;
    }
    if(!from->data || !to->data) {
        return MEMORY_ALLOCATION_ERR;
    }
    if(end-beg > to->capacity_m) {
        my_str_reserve(to, end-beg);
    }
    if(end > from->size_m) {
        end = from->size_m;
    }
    memmove(to->data, from->data + beg, end-beg);
    to->size_m += end-beg;
    return 0;
}
//!Done
int my_str_substr_cstr(const my_str_t* from, char* to, size_t beg, size_t end) {
    if(!from || !to) {
        return NULL_PTR_ERR;
    }
    if(!from->data) {
        return MEMORY_ALLOCATION_ERR;
    }
    if(end > from->size_m) {
        end = from->size_m;
    }
    memmove(to, from->data + beg, end-beg);
    return 0;
}
//!Done
int my_str_erase(my_str_t* str, size_t beg, size_t end) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if(!str->data) {
        return MEMORY_ALLOCATION_ERR;
    }
    if(beg > str->size_m) {
        return RANGE_ERR;
    }
    if(end > str->size_m) {
        end = str->size_m;
    }
    memmove(str->data+beg, str->data+end, str->size_m-end);
    str->size_m -= end-beg;
    return 0;
}
//!Done
int my_str_popback(my_str_t* str) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if(str->size_m == 0) {
        return RANGE_ERR;
    }
    char popped = my_str_getc(str, str->size_m-1);
    my_str_putc(str, str->size_m-1, '\0');
    str->size_m --;
    return popped;
}

//!Done
int my_str_reserve(my_str_t* str, size_t buf_size) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if(buf_size > str->capacity_m) {
        char *new_data = malloc(buf_size + 1);
        if(!new_data) {
            return MEMORY_ALLOCATION_ERR;
        }
        memcpy(new_data, str->data, str->size_m);
        if(str->data) {
            free(str->data);
        }
        str->capacity_m = buf_size+1;
        free(str->data);
        str->data = new_data;
    }
    return 0;
}

//!Done
int my_str_shrink_to_fit(my_str_t* str) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if(str->capacity_m < 0) {
        return MEMORY_ALLOCATION_ERR;
    }
    str->capacity_m = str->size_m+1;
    return 0;
}

//! Size manipulation
//!Done
int my_str_resize(my_str_t* str, size_t new_size, char sym) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if(str->capacity_m < 0) {
        return MEMORY_ALLOCATION_ERR;
    }
    if(new_size > str->capacity_m) {
        my_str_reserve(str, new_size+1);
    }
    if(new_size < str->size_m) {
        char* new_data = malloc(new_size+1);
        for(int i=0; i < str->size_m; i++) {
            new_data[i] = str->data[i];
        }
        free(str->data);
        str->data = new_data;
    }
    else if(new_size > str->size_m) {
        char* new_data = malloc(new_size+1);
        for(int i=0; i < str->size_m; i++) {
            new_data[i] = str->data[i];
        }
        for(int i=str->size_m; i < new_size; i++) {
            new_data[i] = sym;
        }
        free(str->data);
        str->data = new_data;
    }
    str->size_m = new_size;
    return 0;
}

//! Search and comparison
size_t my_str_find(const my_str_t* str, const my_str_t* tofind, size_t from) {
    if(!str || !tofind) {
        return NULL_PTR_ERR;
    }
    if(!str->data) {
        return NULL_PTR_ERR;
    }
    if(!tofind->data || from>str->size_m) {
        return NOT_FOUND_CODE;
    }
    for(int i = from; i < str->size_m; i++) {
        if(str->data[i] == tofind->data[i]) {
            for(int j = i; j < tofind->size_m; j++) {
                if(str->data[j] != tofind->data[j]){
                    break;
                }
                if(j == tofind->data-1){
                    return i;
                }
            }
        }
    }
    return NOT_FOUND_CODE;
}

//!Done
int my_str_cmp(const my_str_t* str1, const my_str_t* str2) {
    if(!str1 || !str2) {
        return NULL_PTR_ERR;
    }
    if(!str1->data || !str2->data) {
        return MEMORY_ALLOCATION_ERR;
    }
    if(str1->size_m != str2->size_m) {
        return RANGE_ERR;
    }
    for(int i = 0; i < str1->size_m; i++) {
        if(str1->data[i] != str2->data[i]) {
            if((int) str1->data[i] > (int) str2->data[i]) {
                return -1;
            } else {
                return 1;
            }
        }
    }
    return 0;
}

//!Done
int my_str_cmp_cstr(const my_str_t* str1, const char* cstr2) {
    if(!str1 || !cstr2) {
        return NULL_PTR_ERR;
    }
    if(!str1->data) {
        return MEMORY_ALLOCATION_ERR;
    }
    if(str1->size_m != sizeof(cstr2)) {
        return RANGE_ERR;
    }
    for(int i = 0; i < str1->size_m; i++) {
        if(str1->data[i] != cstr2[i]) {
            if((int) str1->data[i] > (int) cstr2[i]) {
                return -1;
            } else {
                return 1;
            }
        }
    }
    return 0;
}

//!Done
size_t my_str_find_c(const my_str_t* str, char tofind, size_t from) {\
    if(!str || !tofind) {
        return NULL_PTR_ERR;
    }
    if(!str->data) {
        return MEMORY_ALLOCATION_ERR;
    }
    if(from > str->size_m) {
        return (size_t)(-1);
    }
    for(int i = 0; i < str->size_m; i++) {
        if(str->data[i] == tofind) {
            return (size_t) i;
        }
    }
    return (size_t)(-1);
}

//!Done
size_t my_str_find_if(const my_str_t* str, size_t beg, int (*predicat)(int)) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if(!(*predicat)) {
        return (size_t)(-1);
    }
    if(beg >= str->size_m) {
        return (size_t)(-1);
    }
    for(int i = beg; i < str->size_m; i++) {
        if((*predicat)(str->data[i])) {
            return (size_t) i;
        }
    }
    return (size_t)(-1);
}

//! Input / Output
//!Done
int my_str_read_file(my_str_t* str, FILE* file) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if(!file) {
        return IO_READ_ERR;
    }
    free(str->data);
    fgets(str->data, str->size_m, file);
    return 0;
}
//!Done
int my_str_read(my_str_t* str) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    free(str->data);
    fgets(str->data, str->size_m, stdin);
    return 0;
}
//!Done
int my_str_read_file_delim(my_str_t* str, FILE* file, char delimiter) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if(!file) {
        return IO_READ_ERR;
    }
    if(delimiter > str->capacity_m) {
        my_str_reserve(str, delimiter+1);
    }
    free(str->data);
    fgets(str->data, delimiter, file);
    return 0;
}
//!Done
int my_str_write_file(const my_str_t* str, FILE* file) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    if(!file) {
        return IO_WRITE_ERR;
    }
    file = fopen(file, "w");
    fprintf(file, str->data, str->size_m);
    fclose(file);
}
//!Done
int my_str_write(const my_str_t* str) {
    if(!str) {
        return NULL_PTR_ERR;
    }
    printf("%s\n", str->data);
    return 0;
}