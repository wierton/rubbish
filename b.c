#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 创建新节点
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        perror("malloc failed");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// 添加节点到链表尾部
void append_node(Node** head, int data) {
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* curr = *head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
}

// 打印链表
void print_list(Node* head) {
    Node* curr = head;
    while (curr) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

// 释放链表内存
void free_list(Node* head) {
    Node* curr = head;
    while (curr) {
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
}

// 示例用法
int main() {
    Node a, b, c;
    a.next = &b;
    b.next = &c;
    c.next = NULL;
    a.data = 123;
    b.data = 456;
    c.data = 789;
    return 0;
}

