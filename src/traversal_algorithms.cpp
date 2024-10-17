#include "test_graph.hpp"
#include<iostream>

using namespace std;

void call_queue::reset(){
    while(head){
        call_node* temp = head;        
        head = head->next;
        delete temp;
    }
}

call_queue::~call_queue(){
    this->reset();
}

void call_queue::enqueue(int i){
    call_node* ptr = new call_node;
    ptr->value = i;
    if(!head){
        head = ptr;
        tail = head;
    }
    else{
        tail->next = ptr;
        ptr->prev = tail;
        tail = ptr;
    }
}

int call_queue::dequeue(){
    if(!head){
        return -1;
    }
    else{
        int out = head->value;
        call_node* temp = head;
        if(head->next){
            head->next->prev = nullptr;        
        }
        else{
            tail = nullptr;
        }
        head = head->next;
        delete temp;
        return out;        
    }
}

void traversal_algorithms::rec_list_dfs(test_graph& in, int start, int& counter){
    if(counter == in.size){
        return;
    }
    else{
        counter++;        
    }

    vertex_node* temp1 = in.vertices;
    edge_node* temp2 = in.edges;
    while(temp1->value != start){
        temp1 = temp1->next;
    }
    if(!temp1){
        return;
    }
    temp1->selected = true;

    //cout << start << " ";        
    while(temp2){
        if(temp2->value.from == start){
            temp1 = in.vertices;
            while(temp1->value != temp2->value.to){
                temp1 = temp1->next;
            }
            if(!temp1){
                return;
            }
            if(!temp1->selected){
                traversal_algorithms::rec_list_dfs(in, temp2->value.to, counter);
            }
        }
        temp2 = temp2->next;
    }
}

void traversal_algorithms::rec_list_bfs(test_graph& in, call_queue& q){
    int start = q.dequeue();
    if(start == -1){
        return;
    }
    vertex_node* temp1 = in.vertices;
    edge_node* temp2 = in.edges;
    while(temp1->value != start){
        temp1 = temp1->next;
    }
    if(!temp1){
        return;
    }
    temp1->selected = true;
    //cout << start << " ";
    while(temp2){
        if(temp2->value.from == start){
            temp1 = in.vertices;
            while(temp1->value != temp2->value.to){
                temp1 = temp1->next;
            }
            if(!temp1){
                return;
            }
            if(!temp1->selected){
                temp1->selected = true;
                q.enqueue(temp1->value);
            }
        }
        temp2 = temp2->next;
    }
    traversal_algorithms::rec_list_bfs(in, q);
}

void traversal_algorithms::rec_matrix_dfs(sq_matrix& in, int start, int& counter){
    if(counter == in.size){
        return;
    }
    else{
        counter++;        
    }

    //cout << start << " ";

    for(int i = 0; i < in.size; i++){
        in.arr[i][start] = 0;
    }
    for(int i = 0; i < in.size; i++){
        if(in.arr[start][i] == 1){
            traversal_algorithms::rec_matrix_dfs(in, i, counter);
        }
    }
}

void traversal_algorithms::rec_matrix_bfs(sq_matrix& in, call_queue& q){
    int start = q.dequeue();
    if(start == -1){
        return;
    }
    for(int i = 0; i < in.size; i++){
        in.arr[i][start] = 0;
    }
    //cout << start << " ";

    for(int i = 0; i < in.size; i++){
        if(in.arr[start][i] == 1){
        for(int j = 0; j < in.size; j++){
            in.arr[j][i] = 0;
        }
            q.enqueue(i);
        }
    }
    traversal_algorithms::rec_matrix_bfs(in, q);    
}