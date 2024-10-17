#include "test_graph.hpp"
#include<iostream>
#include<random>
#include<algorithm>

using namespace std;

test_graph::test_graph(int size){
    for(int i = 0; i < size; i++){
        add_vertex(i);
    }
    this->size = size;
    edges = nullptr;
}

void test_graph::reset_edges(){
    while(edges){
        edge_node* temp = edges;
        edges = edges->next;
        delete temp;
    }
}

void test_graph::reset_vertices(){
    while(vertices){
        vertex_node* temp = vertices;
        vertices = vertices->next;
        delete temp;
    }
}

void test_graph::reset_selected(){
    vertex_node* temp = vertices;
    while(temp){
        temp->selected = false;
        temp = temp->next;
    }
}

test_graph::~test_graph(){
    this->reset_edges();
    this->reset_vertices();
}

bool edge::operator==(edge& in){
    return((this->from == in.from)
    &&(this->to == in.to)
    &&(this->weight == in.weight));
}

edge edge::redirect(){
    edge res;
    res.from = this->to;
    res.to = this->from;
    res.weight = this->weight;
    return res;
}

void test_graph::add_vertex(int i){
    vertex_node* ptr = new vertex_node;
    ptr->value = i;
    if(vertices){
        vertices->prev = ptr;
        ptr->next = vertices;
    }
    vertices = ptr;
}

void test_graph::add_sort_edge(edge e){
    if(!sorted){
        throw invalid_argument("Existing edges are unsorted");
    }
    else{
        edge_node* node = new edge_node();
        edge_node* rev_node = new edge_node();
        node->value = e;
        rev_node->value = e.redirect();

        node->prev = rev_node;
        rev_node->next = node;
        
        if(edges){
            edge_node* temp = edges;
            if(temp->value.weight >= e.weight){
                edges->prev = node;
                node->next = edges;
                edges = rev_node;
            }
            else{
                while(temp->next){
                    if(temp->next->value.weight < e.weight){
                        temp = temp->next;
                    }
                    else{
                        break;
                    }
                }
                edge_node* temp_poi = temp->next;
                temp->next = rev_node;
                rev_node->prev = temp;        
                if(temp_poi){
                    temp_poi->prev = node;
                    node->next = temp_poi;            
                }            
            }
        }
        else{
            edges = rev_node;
        }        
    }
}

void test_graph::add_edge(edge e){
    sorted = false;
    edge_node* node = new edge_node();
    edge_node* rev_node = new edge_node();
    node->value = e;
    rev_node->value = e.redirect();

    node->prev = rev_node;
    rev_node->next = node;

    if(edges){
        edges->prev = node;
        node->next = edges;
        edges = rev_node;
    }

    else{
        edges = rev_node;
    }
}

void test_graph::random_graph(int min_weight, int max_weight, int probability){
    this->reset_edges();
    random_device rd;
    mt19937 mt (rd());
    uniform_int_distribution<int> dist_w (min_weight, max_weight);
    uniform_int_distribution<int> dist_pr (1, 100);
    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
            if(dist_pr(mt) <= probability){
                this->add_sort_edge({i, j, dist_w(mt)});
            }
        }
    }
}

sq_matrix::sq_matrix(int s): size(s), arr(new int*[s]){
    for(int i = 0; i < size; i++){
        arr[i] = new int[size]();
    }
}

sq_matrix::sq_matrix(sq_matrix&& other): arr(other.arr), size(other.size){
    other.arr = nullptr;
    other.size = 0;
}

sq_matrix::sq_matrix(sq_matrix& other): size(other.size), arr(new int*[other.size]){
    for(int i = 0; i < size; i++){
        arr[i] = new int[size]();
        for(int j = 0; j < size; j++){
            arr[i][j] = other.arr[i][j];
        }
    }
}

sq_matrix::~sq_matrix(){
    if(arr){
        for(int i = 0; i < size; i++){
            delete[] arr[i];
        }
    }
    delete[] arr;
}

sq_matrix& sq_matrix::operator=(sq_matrix&& other){
    if(this == &other){
        return *this;
    }
    else{
        if(arr){
            for(int i = 0; i < size; i++){
                delete[] arr[i];
            }
        }
        delete[] arr;

        size = other.size;
        arr = other.arr;
        other.size = 0;
        other.arr = nullptr;

        return *this;
    }
}

sq_matrix test_graph::to_matrix(){
    sq_matrix  adj_matrix(size);
    edge_node* temp = edges;
    while(temp){
        edge value = temp->value;
        adj_matrix.arr[value.from][value.to] = 1;
        temp = temp->next;
    }
    return adj_matrix;
}