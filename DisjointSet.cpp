#include "DisjointSet.h"
#include <stdexcept>

DSU::DSU(int n) {
    if (n < 0)
        throw std::invalid_argument("DSU constructor - Invalid Size");

    arr.reserve(n);

    for (int i=0; i < n; ++i) {
        auto node = std::make_shared<Node>(i);
        arr.push_back(node);

        auto set = std::make_shared<Set>();
        node->node_head = set;
        node->node_tail.reset();
        set->set_head = node;
        set->set_tail = node;
    }
}

int DSU::find_(int index) const {
    /*
    Runtime Complexity: O(1)
    */
    if (index < 0 || index >= (int)arr.size())
        throw std::invalid_argument("DSU find - Invalid Index");
    
    return arr[index]->node_head->set_head->idx;
}

void DSU::union_(int a, int b) {
    /*
    Runtime Complexity: O(size of M where M is the smaller set of the union)
    */
    if (a < 0 || a >= (int)arr.size() || b < 0 || b >= (int)arr.size())
        throw std::invalid_argument("DSU union - Invalid Index");

    int a_idx = find_(a);
    int b_idx = find_(b);

    if (a_idx == b_idx)
        return;

    std::shared_ptr<Node> root_a = arr[a_idx];
    std::shared_ptr<Node> root_b = arr[b_idx];

    if (root_a->node_head->size < root_b->node_head->size)
        std::swap(root_a, root_b);

    std::shared_ptr<Node> last = root_a->node_head->set_tail.lock();

    if (last)
        last->node_tail = root_b->node_head->set_head;
    
    std::shared_ptr<Node> curr = root_b->node_head->set_head;

    while (curr) {
        curr->node_head = root_a->node_head;
        last = curr;
        curr = curr->node_tail.lock();
    }
    root_a->node_head->size += root_b->node_head->size;
    root_a->node_head->set_tail = last;
}