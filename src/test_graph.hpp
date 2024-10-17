struct edge{
    int from;
    int to;
    int weight;

    bool operator==(edge&);
    edge redirect();
};

struct edge_node{
    edge value;
    edge_node* next = nullptr;
    edge_node* prev = nullptr;
};

struct vertex_node{
    int value;
    bool selected = false;
    vertex_node* next = nullptr;
    vertex_node* prev = nullptr;
};

struct call_node{
    int value;
    call_node* next = nullptr;
    call_node* prev = nullptr;
};

class call_queue{
public:
    call_node* head = nullptr;
    call_node* tail = nullptr;
    void enqueue(int i);
    int dequeue();
    void reset();

    ~call_queue();
};

struct sq_matrix{
    int** arr = nullptr;
    int size = 0;
    sq_matrix(int s = 0);
    sq_matrix(sq_matrix&&);
    sq_matrix(sq_matrix&);
    sq_matrix& operator=(sq_matrix&&);
    ~sq_matrix();
};

class test_graph{
private:
    int size;
    vertex_node* vertices = nullptr;
    edge_node* edges = nullptr;
    bool sorted = true;
public:

    test_graph(int size = 0);
    ~test_graph();

    sq_matrix to_matrix();
    void reset_selected();
    void reset_edges();
    void reset_vertices();
    void add_vertex(int);
    void add_sort_edge(edge);
    void add_edge(edge);
    void random_graph(int min_weight, int max_weight, int probability);

    friend class traversal_algorithms;
};

class traversal_algorithms{
public:
    static void rec_list_dfs(test_graph& in, int start, int& counter);
    static void rec_matrix_dfs(sq_matrix& in, int start, int& counter);

    static void rec_list_bfs(test_graph& in, call_queue& q);
    static void rec_matrix_bfs(sq_matrix& in, call_queue& q);
};