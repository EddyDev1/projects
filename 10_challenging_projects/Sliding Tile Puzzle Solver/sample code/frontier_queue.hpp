#ifndef FRONTIER_QUEUE_HPP
#define FRONTIER_QUEUE_HPP

// TODO add necessary includes

template <typename T>
class frontier_queue {
public:

  /* Returns true if the frontier is empty, else false
   */
  bool empty();

  /* push a State with value p, cost, and heuristic into the frontier.
   * This should be a O(log n) operation
   */
  void push(const T &p, std::size_t cost, std::size_t heur);

  /* pop the state from the frontier with the smallest f-cost
   * This should be a O(log n) operation
   */
  State<T> pop();

  /* Returns true if the T p is in the frontier
   * This may be at most an O(log n) operation
   */
  bool contains(const T &p);

  /* Replaces a state in the container if the path cost is lower.
   * The frontier should be updated to reflect the new value.
   * This should be at most a O(n) operation.
   */
  void replaceif(const T &p, std::size_t cost);

private:

  // TODO
  
};

#include "frontier_queue.tpp"

#endif
