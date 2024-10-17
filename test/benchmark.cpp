#include "test_graph.hpp"
#include<iostream>
#include<chrono>

using namespace std;

int main(){
    chrono::microseconds total_bfs_l;
    chrono::microseconds total_dfs_l;
    chrono::microseconds total_bfs_m;
    chrono::microseconds total_dfs_m;
    call_queue queue;
    int counter;

    for(int i = 50; i <= 250; i += 50){
        test_graph graph(i);
        for(int j = 25; j <= 100; j += 25){
            total_bfs_l = chrono::microseconds(0);
            total_dfs_l = chrono::microseconds(0);
            total_bfs_m = chrono::microseconds(0);
            total_dfs_m = chrono::microseconds(0);
            for(int k = 0; k < 1000; k++){
                graph.random_graph(1, 1, j);
                sq_matrix origin = graph.to_matrix();
                sq_matrix temp1(origin);
                sq_matrix temp2(origin);

                graph.reset_selected();
                queue.reset();
                queue.enqueue(0);
                auto start = chrono::high_resolution_clock::now();
                    traversal_algorithms::rec_list_bfs(graph, queue);
                auto end = chrono::high_resolution_clock::now();
                total_bfs_l += chrono::duration_cast<chrono::microseconds>(end - start);

                graph.reset_selected();
                counter = 0;
                start = chrono::high_resolution_clock::now();
                    traversal_algorithms::rec_list_dfs(graph, 0, counter);
                end = chrono::high_resolution_clock::now();
                total_dfs_l += chrono::duration_cast<chrono::microseconds>(end - start);

                queue.reset();
                queue.enqueue(0);
                start = chrono::high_resolution_clock::now();
                    traversal_algorithms::rec_matrix_bfs(temp1, queue);
                end = chrono::high_resolution_clock::now();
                total_bfs_m += chrono::duration_cast<chrono::microseconds>(end - start);

                counter = 0;
                start = chrono::high_resolution_clock::now();
                    traversal_algorithms::rec_matrix_dfs(temp2, 0, counter);
                end = chrono::high_resolution_clock::now();
                total_dfs_m += chrono::duration_cast<chrono::microseconds>(end - start);
                if(k%100 == 0){
                    cout << k/10 << "% ";
                }
            }
            cout << "100%\n";
            cout << "List BFS test for " << i << " vertices with density " << j << "%: " << total_bfs_l.count()/1000 << "\n"
            << "List DFS test for " << i << " vertices with density " << j << "%: " << total_dfs_l.count()/1000 << "\n"
            << "Matrix BFS test for " << i << " vertices with density " << j << "%: " << total_bfs_m.count()/1000 << "\n"
            << "Matrix DFS test for " << i << " vertices with density " << j << "%: " << total_dfs_m.count()/1000 << "\n\n";
        }
    }
    return 0;
}
