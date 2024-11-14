#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdexcept>
#include <utility> // for std::swap

class Vector {
public:
    Vector() = default;
    Vector(const Vector &other);
    Vector(Vector &&other) noexcept;

    friend void swap(Vector &v1, Vector &v2);

    Vector &operator=(const Vector &other);
    Vector &operator=(Vector &&other) noexcept;

    ~Vector();

    int GetSize() const;
    int GetCapacity() const;

    int At(int index) const;

    void Append(int value);
    void InsertAt(int index, int value);
    void UpdateAt(int index, int value);
    void RemoveAt(int index);
    void Join(const Vector &other);

private:
    void Resize();

private:
    int m_Size = 0;
    int m_Capacity = 0;
    int* m_Data = nullptr;
};

#endif
