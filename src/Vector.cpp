#include "Vector.hpp"
#include <algorithm> // for std::copy, std::copy_backward

Vector::Vector(const Vector &other)
    : m_Size(other.m_Size),
      m_Capacity(other.m_Capacity),
      m_Data(other.m_Capacity ? new int[other.m_Capacity] : nullptr) {
    std::copy(other.m_Data, other.m_Data + other.m_Size, m_Data);
}

Vector::Vector(Vector &&other) noexcept
    : m_Size(0), m_Capacity(0), m_Data(nullptr) {
    swap(*this, other);
}

void swap(Vector &v1, Vector &v2) {
    std::swap(v1.m_Size, v2.m_Size);
    std::swap(v1.m_Capacity, v2.m_Capacity);
    std::swap(v1.m_Data, v2.m_Data);
}

Vector &Vector::operator=(const Vector &other) {
    if (this != &other) { // Self-assignment protection
        Vector tmp(other);
        swap(*this, tmp);
    }
    return *this;
}

Vector &Vector::operator=(Vector &&other) noexcept {
    if (this != &other) { // Self-assignment protection
        swap(*this, other);
    }
    return *this;
}

Vector::~Vector() {
    delete[] m_Data;
}

int Vector::GetSize() const {
    return m_Size;
}

int Vector::GetCapacity() const {
    return m_Capacity;
}

int Vector::At(int index) const {
    if (index < 0 || index >= m_Size) {
        throw std::out_of_range("[Class: Vector][Method: At] message: out of range");
    }
    return m_Data[index];
}

void Vector::Append(int value) {
    if (m_Size >= m_Capacity) {
        Resize();
    }
    m_Data[m_Size++] = value;
}

void Vector::InsertAt(int index, int value) {
    if (index < 0 || index > m_Size) { // Allow insertion at `m_Size`
        throw std::out_of_range("[Class: Vector][Method: InsertAt] message: out of range");
    }
    if (m_Size >= m_Capacity) {
        Resize();
    }
    // Shift elements to the right
    std::copy_backward(m_Data + index, m_Data + m_Size, m_Data + m_Size + 1);
    m_Data[index] = value;
    m_Size++;
}

void Vector::UpdateAt(int index, int value) {
    if (index < 0 || index >= m_Size) {
        throw std::out_of_range("[Class: Vector][Method: UpdateAt] message: out of range");
    }
    m_Data[index] = value;
}

void Vector::RemoveAt(int index) {
    if (index < 0 || index >= m_Size) {
        throw std::out_of_range("[Class: Vector][Method: RemoveAt] message: out of range");
    }
    // Shift elements to the left
    std::copy(m_Data + index + 1, m_Data + m_Size, m_Data + index);
    m_Size--;
}

void Vector::Join(const Vector &other) {
    for (int i = 0; i < other.m_Size; ++i) {
        Append(other.At(i));
    }
}

void Vector::Resize() {
    // Calculate new capacity
    m_Capacity = (m_Capacity == 0) ? 4 : m_Capacity * 2;

    // Allocate new array
    int* newData = new int[m_Capacity];

    // Copy old data to new array
    std::copy(m_Data, m_Data + m_Size, newData);

    // Delete old array
    delete[] m_Data;

    // Update data pointer
    m_Data = newData;
}
