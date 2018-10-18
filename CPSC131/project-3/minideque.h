//
//  minideque.h
//  minidequeproject
//

#ifndef minideque_h
#define minideque_h

#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <iostream>


template <typename T>
class minideque {
private:
  std::vector<T> fronthalf_;
  std::vector<T> backhalf_;

public:
  minideque() = default;                                   // do not change, C++ defaults are ok
  minideque(const minideque<T>& other) = default;          // rule of three
  minideque& operator=(const minideque<T>& other) = default;
  ~minideque() = default;

  /**
   * Gets size of both halves
   * @return - size of the deque
   */
  size_t size() const
  {
      size_t totalSize = fronthalf_.size() + backhalf_.size(); // Add up the two vector sizes

      return totalSize;
  }

  /**
   * Gets size of the front half
   * @return - size of the fronthalf_ vector
   */
  size_t fronthalfsize() const
  {
      size_t frontSize = fronthalf_.size(); // Get the size from the fronthalf

      return frontSize;
  }

  /**
   * Gets size of the back half
   * @return - size of the backhalf_ vector
   */
  size_t backhalfsize() const
  {
      size_t backSize = backhalf_.size(); // Get the size from the backhalf

      return backSize;
  }

  /**
   * Checks to see if the deque is empty
   * @return - True if both halves are empty or False if one or more is not empty
   */
  bool empty() const
  {
      bool isEmpty = fronthalf_.empty() && backhalf_.empty(); // Both vectors have to be empty to return true

      return isEmpty;
  }

  // balance queue across both vectors if pop_front/back is requested on an empty vector
  // e.g., minideque has this:                  | ABCDEFG
  // after pop_front                        BCD | EFG (A discarded)
  // symmetric logic for converse case: ABCDEFG | ===> ABC | DEF (G discarded) after pop_back
  /**
   * Removes the element at the front of the deque
   * Also balances the halves after front half is empty
   *
   * Balance Example:
   *    Before:     ABCDEFG |
   *     After:     ABC     | DEF (G discarded)
   */
  void pop_front() {
      if (fronthalf_.empty()) // Balancing logic
      {
          std::vector<T> tempBack; // Initialize a temporary vector to hold new back values
          size_t halfBack = backhalf_.size() / 2; // Split by half

          /* Push new values to temp vector */
          for (size_t i = halfBack + 1; i < backhalf_.size(); i++)
          {
              tempBack.push_back(backhalf_[i]);
          }

          /* Copy half of the elements from the back to front, excluding the first element */
          for (size_t i = halfBack; i > 0; i--)
          {
              push_front(backhalf_[i]);
          }

          backhalf_ = tempBack; // Replace backhalf contents with new ones
      } else // No need for balancing
          fronthalf_.pop_back(); // Remove element from front
  }

  /**
    * Removes the element at the back of the deque
    * Also balances the halves after back half is empty
    *
    * Balance Example:
    *    Before:         | ABCDEFG
    *     After:     BCD | EFG (A discarded)
    */
  void pop_back() { // TODO: find a way to test
      if (backhalf_.empty())
      {
          std::vector<T> tempFront;
          size_t halfFront = fronthalf_.size() / 2;

          for (size_t i = halfFront + 1; i < fronthalf_.size(); i++)
          {
              tempFront.push_back(fronthalf_[i]);
          }

          for (size_t i = halfFront; i > 0; i--)
          {
              push_front(fronthalf_[i]);
          }

          fronthalf_ = tempFront;
      } else
          backhalf_.pop_back();
  }

  /**
   * Pushes element to the front of the deque
   * @param value - the user given element to push
   */
  void push_front(const T& value) {
      fronthalf_.push_back(value); // Add value to front half
  }

  /**
   * Pushes element to the back of the deque
   * @param value - the user given element to push
   */
  void push_back(const T& value) {
      backhalf_.push_back(value); // Add value to back half
  }

  /**
   * Finds and returns the front element of the const deque
   * @return - value of the front
   */
  const T& front() const {
      /* If there are no elements in the front half, return front of back half */
      if (fronthalf_.empty())
          return backhalf_.front();

      return fronthalf_.back(); // Return back of front half
  }

  /**
   * Finds and returns the back element of the const deque
   * @return - value of the back
   */
  const T& back() const {
    /* If there are no elements in the back half, return back of front half */
    if (backhalf_.empty())
        return fronthalf_.back();

    return backhalf_.back();
  }

  /**
   * Finds and returns the front element of the deque
   * @return - value of the front
   */
  T& front() {
    /* If there are no elements in the back half, return back of front half */
      if (fronthalf_.empty())
          return backhalf_.front();

      return fronthalf_.back();
  }

  /**
   * Finds and returns the back element of the deque
   * @return - value of the back
   */
  T& back() {
    /* If there are no elements in the front half, return front of back half */
    if (backhalf_.empty())
        return fronthalf_.front();

    return backhalf_.back();
  }

  /**
   * Gets the element from the const deque
   * @param index - user given index of value
   * @return - value at the given index
   */
  const T& operator[](size_t index) const {
      if (fronthalfsize() == 0)
          return backhalf_[index];

      if (index <= fronthalfsize())
          return fronthalf_[index];

      size_t newIndex = fronthalfsize() - index;

      return backhalf_[index];
  }

  /**
   * Gets the element from the deque
   * @param index - user given index of value
   * @return - value at the given index
   */
  T& operator[](size_t index) {
      /* If there are no elements in the front, grab element from back */
      if (fronthalf_.empty())
          return backhalf_[index];

      /* If the index given does not exceed the front half size, grab element from front */
      if (index <= fronthalf_.size())
          return fronthalf_[index];

      /* If the index given does exceed the front half size, grab element from back */
      size_t newIndex = fronthalf_.size() - index;

      return backhalf_[index];
  }

  /**
   * Clears the entire deque
   */
  void clear() {
      fronthalf_.clear();
      backhalf_.clear();
  }

  friend std::ostream& operator<<(std::ostream& os, const minideque<T>& dq) {    // do not change
    if (dq.empty()) { return os << "minideque is empty"; }

    dq.printFronthalf(os);
    os << "| ";
    dq.printBackhalf(os);
    os << ", front:" << dq.front() << ", back:" << dq.back() << ", size:" << dq.size();
    return os;
  }

  void printFronthalf(std::ostream& os=std::cout) const {                    // do not change
    if (empty()) { std::cout << "fronthalf vector is empty"; }

    for (typename std::vector<T>::const_reverse_iterator crit = fronthalf_.crbegin();
         crit != fronthalf_.crend(); ++crit) {
      os << *crit << " ";
    }
  }

  void printBackhalf(std::ostream& os=std::cout) const {                     // do not change
    if (empty()) { os << "backhalf vector is empty"; }

    for (typename std::vector<T>::const_iterator cit = backhalf_.cbegin();
         cit != backhalf_.cend(); ++cit) {
      os << *cit << " ";
    }
  }
};

#endif /* minideque_h */
