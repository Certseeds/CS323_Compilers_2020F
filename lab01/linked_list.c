/*
 * @Github: https://github.com/Certseeds/CS323_Compilers
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-09-08 19:12:02
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-09-09 08:18:52
 */
#include "linked_list.h"
#ifdef __cplusplus
extern "C" {
#endif

// this is based on C standard 11
// compiler command is `gcc linked_list.c --shared -fPIC -o libll.so`
// environment is ubuntu20.04.01 LTS-wsl; gcc9.3.0; python3.8.3
node *linked_list_init_value(int value) {
    node *head = (node *) malloc(sizeof(node));
    head->count = value;
    head->next = nullptr;
    return head;
}

node *linked_list_init() {
    return linked_list_init_value(0);
}

void linked_list_free(node *head) {
    node *cur = head;
    node *last;
    while (cur != nullptr) {
        last = cur;
        cur = cur->next;
        free(last);
    }
}

char linked_list_string[0x10000];

char *linked_list_tostring(node *head) {
    node *cur = head->next;
    char *position;
    int length = 0;
    while (cur != nullptr) {
        position = linked_list_string + length;
        length += sprintf(position, "%d", cur->value);
        cur = cur->next;
        if (cur != nullptr) {
            position = linked_list_string + length;
            length += sprintf(position, "->");
        }
    }
    position = linked_list_string + length;
    length += sprintf(position, "%c", '\0');
    return linked_list_string;
}

int linked_list_size(node *head) {
    return head->count;
}

void linked_list_append(node *head, int val) {
    node *cur = head;
    node *new_node;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    new_node = (node *) malloc(sizeof(node));
    new_node->value = val;
    new_node->next = nullptr;
    cur->next = new_node;
    head->count++;
}

/* insert val at position index */
void linked_list_insert(node *head, int val, int index) {
    if (index > head->count) {
        return;
    }
    node *will_insert = linked_list_init_value(val);
    // node will insert prepare ok
    node *cur = head->next;
    while (cur != nullptr) {
        index--;
        if (index == 0) {
            will_insert->next = cur->next;
            cur->next = will_insert;
            break;
        }
        cur = cur->next;
    }
    head->count++;
}

/* delete node at position index */
void linked_list_delete(node *head, int index) {
    if (index < 0 || index >= head->count) {
        return;
    }
    node *cur = head->next;
    node *temp;
    while (cur != nullptr) {
        index--;
        if (index == 0) {
            temp = cur->next;
            if (temp != nullptr) {
                cur->next = temp->next;
                temp->next = nullptr;
            }
            free(temp);
            break;
        }
        cur = cur->next;
    }
    head->count--;
}

/* remove the first occurence node of val */
void linked_list_remove(node *head, int val) {
    int index = 0;
    node *cur = head->next;
    while (cur != nullptr) {
        if (cur->value == val) {
            linked_list_delete(head, index);
            return;
        }
        index++;
        cur = cur->next;
    }
}

/* remove all occurences of val */
void linked_list_remove_all(node *head, int val) {
    int *address = (int *) malloc(sizeof(int) * head->count);
    int count_remove_number = 0;
    int index = 0;
    node *cur = head->next;
    while (cur != nullptr) {
        if (cur->value == val) {
            address[count_remove_number] = index;
            count_remove_number++;
        }
        index++;
        cur = cur->next;
    }
    for (; count_remove_number >= 0; --count_remove_number) {
        linked_list_delete(head, address[count_remove_number]);
    }
    free(address);
}

/* get value at position index */
int linked_list_get(node *head, int index) {
    if (index >= head->count) {
        return 0x80000000;
    }
    node *cur = head->next;
    while (cur != nullptr) {
        if (index == 0) {
            return cur->value;
        }
        cur = cur->next;
        index--;
    }
    return 0x80000000;
}

/* search the first index of val */
int linked_list_search(node *head, int val) {
    int index = 0;
    node *cur = head->next;
    while (cur != nullptr) {
        if (cur->value == val) {
            return index;
        }
        index++;
        cur = cur->next;
    }
    return -1;
}

/* search all indexes of val */
node *linked_list_search_all(node *head, int val) {
    int *indexs = (int *) malloc(sizeof(int) * head->count);
    for (int i = 0; i < head->count; ++i) {
        indexs[i] = -1;
    }
    int count_remove_number = 0;
    int index = 0;
    node *cur = head->next;
    while (cur != nullptr) {
        if (cur->value == val) {
            indexs[count_remove_number] = index;
            count_remove_number++;
        }
        index++;
        cur = cur->next;
    }
    node *head_willreturn = linked_list_init();
    for (int temp = 0; temp < count_remove_number; ++temp) {
        linked_list_append(head_willreturn, indexs[temp]);
    }
    free(indexs);
    return head_willreturn;
}

#ifdef __cplusplus
}
#endif
/* your implementation goes here */

