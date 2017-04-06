//
// Created by Danial Dervovic on 06/04/2017.
//

#include "Biclique.h"
#include <algorithm>

Biclique::Biclique(const std::vector<std::vector<int>> &incidence_matrix) : BipartiteGraph(incidence_matrix) {

    // Check all-ones matrix
    for (int i = 0; i < incidence_matrix.size(); i++) {
        auto row = incidence_matrix[i];
        for (int j = 0; j < row.size(); j++) {
            if(incidence_matrix[i][j] != 1) {
                throw std::runtime_error("Biclique: Incidence matrix must be all ones to be a biclique.");
            }
        }
    }

    inc_mat_ = incidence_matrix;

    check_input(incidence_matrix);

    const int left_start = 1;
    const int right_start = (const int) (incidence_matrix.size() + 1);
    const std::vector<std::vector<int>> transposed = transpose(incidence_matrix);

    // Left vertices
    for (int i = 0; i < incidence_matrix.size(); i++) {
        Vertex left_v = Vertex(left_start + i);
        left_nodes_.push_back(left_v);
    }

    // Right vertices
    for (int i = 0; i < transposed.size(); i++) {
        Vertex right_v = Vertex(right_start + i);
        right_nodes_.push_back(right_v);
    }

    // Make edges
    for (int i = 0; i < incidence_matrix.size(); i++) {
        Vertex left_v = left_nodes_[i];
        std::vector<int> row = incidence_matrix[i];

        for (int j = 0; j < row.size(); j++){
            if (incidence_matrix[i][j] == 1){
                Vertex& left = left_nodes_[i];
                Vertex& right = right_nodes_[j];
                Vertex::add_edge(left, right);
            }
        }
    }

    // Left neighbours_
    for (int i = 0; i < incidence_matrix.size(); i++) {
        Vertex left_v = left_nodes_[i];
        left_neighbours_.push_back(left_v.get_neighbours());
    }

    // Right neighbours_
    for (int i = 0; i < transposed.size(); i++) {
        Vertex right_v = right_nodes_[i];
        right_neighbours_.push_back(right_v.get_neighbours());

    }
}

Biclique::Biclique(const std::vector<Vertex> &left_vertices, const std::vector<Vertex> &right_vertices) {

    left_nodes_ = left_vertices;
    right_nodes_ = right_vertices;

    // Check for duplicate vertices
    std::vector<Vertex> all_nodes = left_nodes_;
    all_nodes.insert(all_nodes.end(), right_nodes_.begin(), right_nodes_.end());
    std::sort(all_nodes.begin(), all_nodes.end());
    for (int i = 0; i < all_nodes.size() - 1; i++) {
        if (all_nodes[i] == all_nodes[i+1]) {
            throw std::runtime_error("Biclique::Biclique - Vertex " + std::to_string(i) + " is duplicated.");
        }
    }

    for (int i = 0; i < left_vertices.size(); i++) {
        for (int j = 0; j < right_vertices.size(); j++) {

        }
    }

    // Make edges
    for (int i = 0; i < left_nodes_.size(); i++) {
        for (int j = 0; j < right_nodes_.size(); j++){
            Vertex& left = left_nodes_[i];
            Vertex& right = right_nodes_[j];
            try {
                Vertex::add_edge(left, right);
            }
            catch (const std::runtime_error& e){}
            //TODO: Will I need to remove neighbours not in biclique here...?
        }
    }

    // Left neighbours_
    for (int i = 0; i < left_nodes_.size(); i++) {
        Vertex left_v = left_nodes_[i];
        left_neighbours_.push_back(left_v.get_neighbours());
    }

    // Right neighbours_
    for (int i = 0; i < right_nodes_.size(); i++) {
        Vertex right_v = right_nodes_[i];
        right_neighbours_.push_back(right_v.get_neighbours());

    }

}
