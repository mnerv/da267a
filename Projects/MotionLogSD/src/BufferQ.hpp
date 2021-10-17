/**
 * @file   BufferQ.hpp
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Buffer Queue
 * @date   2021-10-17
 *
 * @copyright Copyright (c) 2021
 */
#ifndef BUFFER_Q_HPP_
#define BUFFER_Q_HPP_

#include <cstdint>

template <typename T, std::size_t size>
class BufferQ {
   public:
    bool IsEmpty() const { return m_entries == 0; }
    bool IsFull() const { return m_entries == m_max; }
    bool Enqueue(T value) {
        if (IsFull()) return false;
        m_buffer[m_tail] = value;
        m_entries++;
        m_tail = (m_tail + m_max - 1) % m_max;
        return true;
    }
    T Dequeue() {
        T value = m_buffer[m_head];
        if (!IsEmpty()) {
            m_head = (m_head + m_max - 1) % m_max;
            m_entries--;
        }
        return value;
    }

   private:
    std::size_t m_tail = 0;
    std::size_t m_head = 0;
    std::size_t m_max  = size;
    std::size_t m_entries = 0;
    T m_buffer[size];
};

#endif

