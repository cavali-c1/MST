#ifndef DISJOINT_SETS_H
#define DISJOINT_SETS_H

#include <vector>
#include <memory>
#include <iostream>

class DSU {
    private:
        struct Node;

        struct Set {
            std::shared_ptr<Node> set_head;
            std::weak_ptr<Node> set_tail;
            int size;
            
            Set(void) : size(1) {}
            ~Set(void) {}
        };
        struct Node {
            std::shared_ptr<Set> node_head; //ptr to Set for ownership
            std::weak_ptr<Node> node_tail;
            int idx;

            Node(int i) : idx(i) {}
            ~Node(void) {}
        };
        std::vector<std::shared_ptr<Node>> arr;
    public:
        DSU(int n);
        ~DSU(void) {}

        int find_(int index) const;
        void union_(int a, int b);
};

#endif