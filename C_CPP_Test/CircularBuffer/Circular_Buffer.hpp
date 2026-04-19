/**
 * @file Circular_Buffer.hpp
 * @brief A template-based circular (ring) buffer implementation
 * 
 * This file defines a generic CircularBuffer class that efficiently manages a fixed-size
 * buffer in FIFO (First-In-First-Out) manner, wrapping around when reaching capacity.
 * The buffer uses a head and tail pointer to track insertion and extraction points,
 * optimizing memory usage with O(1) time complexity for push, pop, and peek operations.
 */

#pragma once

#include <array>          // For std::array - fixed-size contiguous container
#include <optional>       // For std::optional - represents optional values
#include <utility>        // For std::forward - perfect forwarding support
#include <cstddef>        // For size_t - standard size type

/**
 * @class CircularBuffer
 * @brief A fixed-size circular buffer template class
 * 
 * @tparam T The type of elements stored in the buffer
 * @tparam Size The maximum capacity of the buffer (must be > 0)
 * 
 * Key features:
 * - FIFO data structure with wraparound behavior
 * - O(1) time complexity for push, pop, and peek operations
 * - Move semantics and perfect forwarding support
 * - Returns std::optional for safe value retrieval
 * - Compile-time size enforcement
 */ 
 /* The buffer uses a head and tail pointer to track insertion and extraction points,
 * optimizing memory usage with O(1) time complexity for push, pop, and peek operations.
 */

#pragma once

#include <array>          // For std::array - fixed-size contiguous container
#include <optional>       // For std::optional - represents optional values
#include <utility>        // For std::forward - perfect forwarding support
#include <cstddef>        // For size_t - standard size type

/**
 * @class CircularBuffer
 * @brief A fixed-size circular buffer template class
 * 
 * @tparam T The type of elements stored in the buffer
 * @tparam Size The maximum capacity of the buffer (must be > 0)
 * 
 * Key features:
 * - FIFO data structure with wraparound behavior
 * - O(1) time complexity for push, pop, and peek operations
 * - Move semantics and perfect forwarding support
 * - Returns std::optional for safe value retrieval
 * - Compile-time size enforcement
 */
template <typename T, size_t Size>
class CircularBuffer {

private:
    /**
     * @brief Internal implementation for push operations
     * @tparam U The forwarded type of the item to push
     * @param item The item to insert (passed by perfect forwarding)
     * @return true if item was inserted, false if buffer is full
     * 
     * Uses perfect forwarding to accept both lvalue and rvalue references,
     * enabling move semantics and optimal copy elision.
     */
    template <typename U>
    bool pushImpl(U&& item) {
        if (full()) return false;
        data_[head_] = std::forward<U>(item);
        advanceHead();
        return true;
    }

    /**
     * @brief Advances the head pointer to the next position
     * 
     * Updates head_ using modulo arithmetic to wrap around at Size boundary.
     * Sets full_ flag when head catches up to tail_ after advancement.
     * No exceptions thrown (noexcept).
     */
    void advanceHead() noexcept {
        head_ = (head_ + 1) % Size;
        full_ = (head_ == tail_);
    }

    std::array<T, Size> data_{};
    size_t head_ = 0;
    size_t tail_ = 0;
    bool full_ = false;

    
public:
    static_assert(Size > 0, "CircularBuffer size must be greater than zero");

    using value_type = T;
    using size_type = size_t;

    /// Default constructor - initializes buffer with zero-initialized data
    CircularBuffer() = default;
    
    /// Default destructor - no special cleanup needed for trivial types
    ~CircularBuffer() = default;

    /**
     * @brief Push an item into the buffer (lvalue reference overload)
     * @param item Const reference to item to insert
     * @return true if insertion succeeded, false if buffer is full
     */
    bool push(const T& item) {
        return pushImpl(item);
    }

    /**
     * @brief Push an item into the buffer (rvalue reference overload)
     * @param item Rvalue reference to item to insert (enables move semantics)
     * @return true if insertion succeeded, false if buffer is full
     */
    bool push(T&& item) {
        return pushImpl(std::move(item));
    }

    /**
     * @brief Construct and insert an item in-place
     * @tparam Args Variable template arguments for perfect forwarding
     * @param args Arguments to forward to T's constructor
     * @return true if insertion succeeded, false if buffer is full
     * 
     * Constructs the item directly at the buffer position, avoiding
     * temporary object creation and unnecessary copies.
     */
    template <typename... Args>
    bool emplace(Args&&... args) {
        if (full()) return false;
        data_[head_] = T(std::forward<Args>(args)...);
        advanceHead();
        return true;
    }

    /**
     * @brief Remove and return the front item from the buffer
     * @return std::optional containing the oldest item, or std::nullopt if empty
     * 
     * Advances tail_ pointer using modulo arithmetic and clears full_ flag.
     * Uses move semantics to efficiently transfer item ownership.
     */
    std::optional<T> pop() {
        if (empty()) return std::nullopt;

        T item = std::move(data_[tail_]);
        full_ = false;
        tail_ = (tail_ + 1) % Size;
        return item;
    }

    /**
     * @brief View the front item without removing it
     * @return std::optional containing a copy of the oldest item, or std::nullopt if empty
     * 
     * Non-destructive read operation. Does not modify buffer state.
     */
    std::optional<T> peek() const {
        if (empty()) return std::nullopt;
        return data_[tail_];
    }

    /**
     * @brief Clear the buffer and reset to initial state
     * 
     * Resets both head and tail pointers to zero and clears the full flag.
     * Existing elements are not explicitly destroyed (relying on array reinitialization).
     */
    void reset() noexcept {
        head_ = 0;
        tail_ = 0;
        full_ = false;
    }

    /**
     * @brief Check if the buffer is empty
     * @return true if no items in buffer, false otherwise
     * 
     * Condition: buffer is empty when head == tail AND not full.
     * (When head == tail && full, the buffer is actually full, not empty)
     */
    bool empty() const noexcept {
        return !full_ && (head_ == tail_);
    }

    /**
     * @brief Check if the buffer is at maximum capacity
     * @return true if no space for additional items
     */
    bool full() const noexcept {
        return full_;
    }

    /**
     * @brief Get the current number of items in the buffer
     * @return Number of elements currently stored
     * 
     * Handles wraparound case where tail_ > head_ by adding Size offset.
     * Time complexity: O(1)
     */
    size_t size() const noexcept {
        if (full_) return Size;              // If full, size is always Size
        if (head_ >= tail_) return head_ - tail_; // Normal case: head hasn't wrapped
        return Size + head_ - tail_;         // Wraparound case: head has wrapped past tail
    }

    /**
     * @brief Get the maximum capacity of the buffer (compile-time constant)
     * @return Maximum number of items the buffer can hold
     * 
     * This is a compile-time constant specified in the template parameter.
     */
    constexpr size_t capacity() const noexcept {
        return Size;
    }

    /**
     * @brief Get the number of empty slots available for insertion
     * @return Number of items that can still be pushed before buffer is full
     * 
     * Calculated as: capacity() - size()
     */
    size_t available() const noexcept {
        return capacity() - size();
    }


};
