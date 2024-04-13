#include <iostream>
#include <vector>
#include <map>
#include <climits>

using namespace std;
template<typename T1, typename T2>
struct Pair {
    T1 first;
    T2 second;
    Pair(){}
    Pair(const T1& _first, const T2& _second) : first(_first), second(_second) {}
};

template <typename T>
class MyVector {
public:
    T* data;            // Pointer to dynamically allocated array
    size_t capacity;    // Total capacity of the array
    size_t size;        // Current number of elements in the array

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity]; // Allocate new array

        // Copy existing elements to the new array
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }

        delete[] data;      // Free memory of the old array
        data = newData;     // Point to the new array
        capacity = newCapacity; // Update capacity
    }

public:
    MyVector() : data(nullptr), capacity(0), size(0) {}
    MyVector(size_t initialCapacity) : data(new T[initialCapacity]), capacity(initialCapacity), size(0) {
        for (size_t i = 0; i < initialCapacity; ++i) {
        data[i] = T(); // Default initialize each element
    }
    }
    ~MyVector() { delete[] data; }

    // Конструктор копирования и оператор присваивания
    MyVector(const MyVector& other) : capacity(other.capacity), size(other.size) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] data; // Освобождение памяти текущего массива
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Метод для добавления элемента в конец массива
    void push_back(const T& value) {
        if (size >= capacity) {
            // Если массив полный, увеличиваем его ёмкость
            size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
            resize(newCapacity);
        }
        data[size++] = value; // Добавление элемента и увеличение размера
    }
    // Метод для доступа к размеру массива
    size_t getSize() const {
        return size;
    }

    // Оператор доступа к элементу по индексу
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
};
class Point {
public:
    Pair<int, int> start;
    MyVector<Pair<int, int>> end;

public:
    Point() : start(0, 0), end() {}
    Point(const Pair<int, int>& _start, size_t initialCapacity) : start(_start), end(initialCapacity) {}
    Point(const Pair<int, int>& _start, const MyVector<Pair<int, int>>& _end) : start(_start), end(_end) {}
    Point(const Pair<int, int>& _start) : start(_start), end() {}
    // Методы получения начальной и конечной точек
    Pair<int, int> getStart() const {
        return start;
    }

    const MyVector<Pair<int, int>>& getEnd() const {
        return end;
    }
    Pair<int, int>& getEndPoint(size_t index) {
        return end[index];
    }
    void print() const {
        std::cout << "Start: (" << start.first << ", " << start.second << ") End: ";
        for (size_t i = 0; i < end.getSize(); ++i) {
            std::cout << "(" << end[i].first << ", " << end[i].second << ")";
            if (i < end.getSize() - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    void addEndPoint(const Pair<int, int>& endPoint) {
        end.push_back(endPoint);
    }
};


vector<Point> createPointsVector(){

    vector <Point> points(49);

    // Заполняем массив данными вручную
    points[0] = Point(Pair<int, int>(0, 2));
    points[0].addEndPoint(Pair<int, int>(0, 4));
    points[0].addEndPoint(Pair<int, int>(0, 6));
    points[0].addEndPoint(Pair<int, int>(1, 3));
    points[0].addEndPoint(Pair<int, int>(2, 4));

    points[1] = Point(Pair<int, int>(0, 4));
    points[1].addEndPoint(Pair<int, int>(0, 2));
    points[1].addEndPoint(Pair<int, int>(0, 6));
    points[1].addEndPoint(Pair<int, int>(2, 4));
    points[1].addEndPoint(Pair<int, int>(1, 4));

    points[2] = Point(Pair<int, int>(0, 6));
    points[2].addEndPoint(Pair<int, int>(0, 4));
    points[2].addEndPoint(Pair<int, int>(0, 2));
    points[2].addEndPoint(Pair<int, int>(1, 5));
    points[2].addEndPoint(Pair<int, int>(2, 4));

    points[3] = Point(Pair<int, int>(1, 3));
    points[3].addEndPoint(Pair<int, int>(0, 2));
    points[3].addEndPoint(Pair<int, int>(1, 4));
    points[3].addEndPoint(Pair<int, int>(1, 6));
    points[3].addEndPoint(Pair<int, int>(2, 4));
    points[3].addEndPoint(Pair<int, int>(3, 5));

    points[4] = Point(Pair<int, int>(1, 4));
    points[4].addEndPoint(Pair<int, int>(0, 4));
    points[4].addEndPoint(Pair<int, int>(1, 3));
    points[4].addEndPoint(Pair<int, int>(1, 5));
    points[4].addEndPoint(Pair<int, int>(2, 4));
    points[4].addEndPoint(Pair<int, int>(3, 4));

    points[5] = Point(Pair<int, int>(1, 5));
    points[5].addEndPoint(Pair<int, int>(0, 6));
    points[5].addEndPoint(Pair<int, int>(1, 4));
    points[5].addEndPoint(Pair<int, int>(2, 4));
    points[5].addEndPoint(Pair<int, int>(3, 3));
    points[5].addEndPoint(Pair<int, int>(1, 3));

    points[6] = Point(Pair<int, int>(2, 0));
    points[6].addEndPoint(Pair<int, int>(3, 1));
    points[6].addEndPoint(Pair<int, int>(4, 0));
    points[6].addEndPoint(Pair<int, int>(6, 0));
    points[6].addEndPoint(Pair<int, int>(4, 2));

    points[7] = Point(Pair<int, int>(2, 2));
    points[7].addEndPoint(Pair<int, int>(2, 3));
    points[7].addEndPoint(Pair<int, int>(2, 4));
    points[7].addEndPoint(Pair<int, int>(3, 2));
    points[7].addEndPoint(Pair<int, int>(3, 3));
    points[7].addEndPoint(Pair<int, int>(4, 3));
    points[7].addEndPoint(Pair<int, int>(4, 4));

    points[8] = Point(Pair<int, int>(2, 3));
    points[8].addEndPoint(Pair<int, int>(2, 2));
    points[8].addEndPoint(Pair<int, int>(2, 4));
    points[8].addEndPoint(Pair<int, int>(2, 5));
    points[8].addEndPoint(Pair<int, int>(3, 3));
    points[8].addEndPoint(Pair<int, int>(4, 3));

    points[9] = Point(Pair<int, int>(2, 4));
    points[9].addEndPoint(Pair<int, int>(0, 2));
    points[9].addEndPoint(Pair<int, int>(0, 4));
    points[9].addEndPoint(Pair<int, int>(0, 6));
    points[9].addEndPoint(Pair<int, int>(1, 3));
    points[9].addEndPoint(Pair<int, int>(1, 4));
    points[9].addEndPoint(Pair<int, int>(1, 5));
    points[9].addEndPoint(Pair<int, int>(2, 2));
    points[9].addEndPoint(Pair<int, int>(2, 3));
    points[9].addEndPoint(Pair<int, int>(2, 5));
    points[9].addEndPoint(Pair<int, int>(2, 6));
    points[9].addEndPoint(Pair<int, int>(3, 3));
    points[9].addEndPoint(Pair<int, int>(3, 4));
    points[9].addEndPoint(Pair<int, int>(3, 5));
    points[9].addEndPoint(Pair<int, int>(4, 2));
    points[9].addEndPoint(Pair<int, int>(4, 4));
    points[9].addEndPoint(Pair<int, int>(4, 6));

    points[10] = Point(Pair<int, int>(2, 5));
    points[10].addEndPoint(Pair<int, int>(2, 3));
    points[10].addEndPoint(Pair<int, int>(2, 4));
    points[10].addEndPoint(Pair<int, int>(2, 6));
    points[10].addEndPoint(Pair<int, int>(3, 5));
    points[10].addEndPoint(Pair<int, int>(4, 5));

    points[11] = Point(Pair<int, int>(2, 6));
    points[11].addEndPoint(Pair<int, int>(2, 5));
    points[11].addEndPoint(Pair<int, int>(2, 4));
    points[11].addEndPoint(Pair<int, int>(3, 5));
    points[11].addEndPoint(Pair<int, int>(3, 4));
    points[11].addEndPoint(Pair<int, int>(3, 6));
    points[11].addEndPoint(Pair<int, int>(4, 6));

    points[12] = Point(Pair<int, int>(2, 8));
    points[12].addEndPoint(Pair<int, int>(3, 7));
    points[12].addEndPoint(Pair<int, int>(4, 6));
    points[12].addEndPoint(Pair<int, int>(4, 8));
    points[12].addEndPoint(Pair<int, int>(6, 8));

    points[13] = Point(Pair<int, int>(3, 1));
    points[13].addEndPoint(Pair<int, int>(2, 0));
    points[13].addEndPoint(Pair<int, int>(4, 1));
    points[13].addEndPoint(Pair<int, int>(5, 1));
    points[13].addEndPoint(Pair<int, int>(4, 2));
    points[13].addEndPoint(Pair<int, int>(5, 3));

    points[14] = Point(Pair<int, int>(3, 2));
    points[14].addEndPoint(Pair<int, int>(2, 2));
    points[14].addEndPoint(Pair<int, int>(3, 3));
    points[14].addEndPoint(Pair<int, int>(3, 4));
    points[14].addEndPoint(Pair<int, int>(4, 2));
    points[14].addEndPoint(Pair<int, int>(5, 2));

    points[15] = Point(Pair<int, int>(3, 3));
    points[15].addEndPoint(Pair<int, int>(2, 2));
    points[15].addEndPoint(Pair<int, int>(2, 3));
    points[15].addEndPoint(Pair<int, int>(2, 4));
    points[15].addEndPoint(Pair<int, int>(3, 2));
    points[15].addEndPoint(Pair<int, int>(3, 4));
    points[15].addEndPoint(Pair<int, int>(4, 4));
    points[15].addEndPoint(Pair<int, int>(4, 3));
    points[15].addEndPoint(Pair<int, int>(4, 2));
    points[15].addEndPoint(Pair<int, int>(3, 5));
    points[15].addEndPoint(Pair<int, int>(1, 5));
    points[15].addEndPoint(Pair<int, int>(5, 5));
    points[15].addEndPoint(Pair<int, int>(5, 1));
    points[15].addEndPoint(Pair<int, int>(5, 3));

    points[16] = Point(Pair<int, int>(3, 4));
    points[16].addEndPoint(Pair<int, int>(2, 4));
    points[16].addEndPoint(Pair<int, int>(3, 3));
    points[16].addEndPoint(Pair<int, int>(3, 5));
    points[16].addEndPoint(Pair<int, int>(4, 4));
    points[16].addEndPoint(Pair<int, int>(1, 4));
    points[16].addEndPoint(Pair<int, int>(3, 2));
    points[16].addEndPoint(Pair<int, int>(3, 6));
    points[16].addEndPoint(Pair<int, int>(5, 4));

    points[17] = Point(Pair<int, int>(3, 5));
    points[17].addEndPoint(Pair<int, int>(2, 4));
    points[17].addEndPoint(Pair<int, int>(2, 5));
    points[17].addEndPoint(Pair<int, int>(2, 6));
    points[17].addEndPoint(Pair<int, int>(3, 4));
    points[17].addEndPoint(Pair<int, int>(3, 6));
    points[17].addEndPoint(Pair<int, int>(3, 3));
    points[17].addEndPoint(Pair<int, int>(4, 4));
    points[17].addEndPoint(Pair<int, int>(4, 5));
    points[17].addEndPoint(Pair<int, int>(4, 6));
    points[17].addEndPoint(Pair<int, int>(5, 3));
    points[17].addEndPoint(Pair<int, int>(5, 5));
    points[17].addEndPoint(Pair<int, int>(5, 7));
    points[17].addEndPoint(Pair<int, int>(1, 3));

    points[18] = Point(Pair<int, int>(3, 6));
    points[18].addEndPoint(Pair<int, int>(3, 4));
    points[18].addEndPoint(Pair<int, int>(3, 5));
    points[18].addEndPoint(Pair<int, int>(2, 6));
    points[18].addEndPoint(Pair<int, int>(4, 6));
    points[18].addEndPoint(Pair<int, int>(5, 6));

    points[19] = Point(Pair<int, int>(3, 7));
    points[19].addEndPoint(Pair<int, int>(4, 7));
    points[19].addEndPoint(Pair<int, int>(2, 8));
    points[19].addEndPoint(Pair<int, int>(4, 6));
    points[19].addEndPoint(Pair<int, int>(5, 5));
    points[19].addEndPoint(Pair<int, int>(5, 7));

    points[20] = Point(Pair<int, int>(4, 0));
    points[20].addEndPoint(Pair<int, int>(2, 0));
    points[20].addEndPoint(Pair<int, int>(4, 1));
    points[20].addEndPoint(Pair<int, int>(4, 2));
    points[20].addEndPoint(Pair<int, int>(6, 0));

    points[21] = Point(Pair<int, int>(4, 1));
    points[21].addEndPoint(Pair<int, int>(4, 0));
    points[21].addEndPoint(Pair<int, int>(4, 2));
    points[21].addEndPoint(Pair<int, int>(4, 3));
    points[21].addEndPoint(Pair<int, int>(3, 1));
    points[21].addEndPoint(Pair<int, int>(5, 1));

    points[22] = Point(Pair<int, int>(4, 2));
    points[22].addEndPoint(Pair<int, int>(3, 1));
    points[22].addEndPoint(Pair<int, int>(3, 2));
    points[22].addEndPoint(Pair<int, int>(3, 3));
    points[22].addEndPoint(Pair<int, int>(4, 3));
    points[22].addEndPoint(Pair<int, int>(5, 3));
    points[22].addEndPoint(Pair<int, int>(5, 2));
    points[22].addEndPoint(Pair<int, int>(5, 1));
    points[22].addEndPoint(Pair<int, int>(4, 1));
    points[22].addEndPoint(Pair<int, int>(4, 0));
    points[22].addEndPoint(Pair<int, int>(2, 0));
    points[22].addEndPoint(Pair<int, int>(2, 2));
    points[22].addEndPoint(Pair<int, int>(2, 4));
    points[22].addEndPoint(Pair<int, int>(4, 4));
    points[22].addEndPoint(Pair<int, int>(6, 4));
    points[22].addEndPoint(Pair<int, int>(6, 2));
    points[22].addEndPoint(Pair<int, int>(6, 0));

    points[23] = Point(Pair<int, int>(4, 3));
    points[23].addEndPoint(Pair<int, int>(4, 2));
    points[23].addEndPoint(Pair<int, int>(3, 3));
    points[23].addEndPoint(Pair<int, int>(4, 5));
    points[23].addEndPoint(Pair<int, int>(5, 3));
    points[23].addEndPoint(Pair<int, int>(4, 1));
    points[23].addEndPoint(Pair<int, int>(2, 3));
    points[23].addEndPoint(Pair<int, int>(4, 6));
    points[23].addEndPoint(Pair<int, int>(6, 3));

    points[24] = Point(Pair<int, int>(4, 4));
    points[24].addEndPoint(Pair<int, int>(4, 3));
    points[24].addEndPoint(Pair<int, int>(3, 3));
    points[24].addEndPoint(Pair<int, int>(3, 4));
    points[24].addEndPoint(Pair<int, int>(3, 5));
    points[24].addEndPoint(Pair<int, int>(4, 5));
    points[24].addEndPoint(Pair<int, int>(5, 5));
    points[24].addEndPoint(Pair<int, int>(5, 4));
    points[24].addEndPoint(Pair<int, int>(5, 3));
    points[24].addEndPoint(Pair<int, int>(4, 2));
    points[24].addEndPoint(Pair<int, int>(2, 2));
    points[24].addEndPoint(Pair<int, int>(2, 4));
    points[24].addEndPoint(Pair<int, int>(2, 6));
    points[24].addEndPoint(Pair<int, int>(4, 6));
    points[24].addEndPoint(Pair<int, int>(6, 6));
    points[24].addEndPoint(Pair<int, int>(6, 4));
    points[24].addEndPoint(Pair<int, int>(6, 2));

    points[25] = Point(Pair<int, int>(4, 5));
    points[25].addEndPoint(Pair<int, int>(4, 4));
    points[25].addEndPoint(Pair<int, int>(3, 5));
    points[25].addEndPoint(Pair<int, int>(5, 5));
    points[25].addEndPoint(Pair<int, int>(5, 6));
    points[25].addEndPoint(Pair<int, int>(4, 3));
    points[25].addEndPoint(Pair<int, int>(4, 7));
    points[25].addEndPoint(Pair<int, int>(2, 5));
    points[25].addEndPoint(Pair<int, int>(6, 5));

    points[26] = Point(Pair<int, int>(4, 6));
    points[26].addEndPoint(Pair<int, int>(4, 5));
    points[26].addEndPoint(Pair<int, int>(3, 5));
    points[26].addEndPoint(Pair<int, int>(3, 6));
    points[26].addEndPoint(Pair<int, int>(3, 7));
    points[26].addEndPoint(Pair<int, int>(4, 7));
    points[26].addEndPoint(Pair<int, int>(5, 7));
    points[26].addEndPoint(Pair<int, int>(5, 6));
    points[26].addEndPoint(Pair<int, int>(5, 5));
    points[26].addEndPoint(Pair<int, int>(2, 4));
    points[26].addEndPoint(Pair<int, int>(2, 6));
    points[26].addEndPoint(Pair<int, int>(2, 8));
    points[26].addEndPoint(Pair<int, int>(4, 8));
    points[26].addEndPoint(Pair<int, int>(6, 8));
    points[26].addEndPoint(Pair<int, int>(6, 6));
    points[26].addEndPoint(Pair<int, int>(6, 4));
    points[26].addEndPoint(Pair<int, int>(4, 4));

    points[27] = Point(Pair<int, int>(4, 7));
    points[27].addEndPoint(Pair<int, int>(4, 6));
    points[27].addEndPoint(Pair<int, int>(3, 7));
    points[27].addEndPoint(Pair<int, int>(4, 8));
    points[27].addEndPoint(Pair<int, int>(5, 7));
    points[27].addEndPoint(Pair<int, int>(4, 5));

    points[28] = Point(Pair<int, int>(4, 8));
    points[28].addEndPoint(Pair<int, int>(4, 7));
    points[28].addEndPoint(Pair<int, int>(2, 8));
    points[28].addEndPoint(Pair<int, int>(6, 8));
    points[28].addEndPoint(Pair<int, int>(4, 6));

    points[29] = Point(Pair<int, int>(5, 1));
    points[29].addEndPoint(Pair<int, int>(6, 0));
    points[29].addEndPoint(Pair<int, int>(4, 1));
    points[29].addEndPoint(Pair<int, int>(3, 1));
    points[29].addEndPoint(Pair<int, int>(4, 2));
    points[29].addEndPoint(Pair<int, int>(3, 3));

    points[30] = Point(Pair<int, int>(5, 2));
    points[30].addEndPoint(Pair<int, int>(6, 2));
    points[30].addEndPoint(Pair<int, int>(5, 3));
    points[30].addEndPoint(Pair<int, int>(5, 4));
    points[30].addEndPoint(Pair<int, int>(4, 2));
    points[30].addEndPoint(Pair<int, int>(3, 2));

    points[31] = Point(Pair<int, int>(5, 3));
    points[31].addEndPoint(Pair<int, int>(6, 2));
    points[31].addEndPoint(Pair<int, int>(6, 3));
    points[31].addEndPoint(Pair<int, int>(6, 4));
    points[31].addEndPoint(Pair<int, int>(5, 2));
    points[31].addEndPoint(Pair<int, int>(5, 4));
    points[31].addEndPoint(Pair<int, int>(4, 4));
    points[31].addEndPoint(Pair<int, int>(4, 3));
    points[31].addEndPoint(Pair<int, int>(4, 2));
    points[31].addEndPoint(Pair<int, int>(5, 5));
    points[31].addEndPoint(Pair<int, int>(7, 5));
    points[31].addEndPoint(Pair<int, int>(3, 5));
    points[31].addEndPoint(Pair<int, int>(3, 1));
    points[31].addEndPoint(Pair<int, int>(3, 3));

    points[32] = Point(Pair<int, int>(5, 4));
    points[32].addEndPoint(Pair<int, int>(6, 4));
    points[32].addEndPoint(Pair<int, int>(5, 3));
    points[32].addEndPoint(Pair<int, int>(5, 5));
    points[32].addEndPoint(Pair<int, int>(4, 4));
    points[32].addEndPoint(Pair<int, int>(7, 4));
    points[32].addEndPoint(Pair<int, int>(5, 2));
    points[32].addEndPoint(Pair<int, int>(5, 6));
    points[32].addEndPoint(Pair<int, int>(3, 4));

    points[33] = Point(Pair<int, int>(5, 5));
    points[33].addEndPoint(Pair<int, int>(6, 4));
    points[33].addEndPoint(Pair<int, int>(6, 5));
    points[33].addEndPoint(Pair<int, int>(6, 6));
    points[33].addEndPoint(Pair<int, int>(5, 4));
    points[33].addEndPoint(Pair<int, int>(5, 6));
    points[33].addEndPoint(Pair<int, int>(5, 3));
    points[33].addEndPoint(Pair<int, int>(4, 4));
    points[33].addEndPoint(Pair<int, int>(4, 5));
    points[33].addEndPoint(Pair<int, int>(4, 6));
    points[33].addEndPoint(Pair<int, int>(3, 3));
    points[33].addEndPoint(Pair<int, int>(3, 5));
    points[33].addEndPoint(Pair<int, int>(3, 7));
    points[33].addEndPoint(Pair<int, int>(7, 3));

    points[34] = Point(Pair<int, int>(5, 6));
    points[34].addEndPoint(Pair<int, int>(5, 4));
    points[34].addEndPoint(Pair<int, int>(5, 5));
    points[34].addEndPoint(Pair<int, int>(6, 6));
    points[34].addEndPoint(Pair<int, int>(4, 6));
    points[34].addEndPoint(Pair<int, int>(3, 6));

    points[35] = Point(Pair<int, int>(5, 7));
    points[35].addEndPoint(Pair<int, int>(4, 7));
    points[35].addEndPoint(Pair<int, int>(6, 8));
    points[35].addEndPoint(Pair<int, int>(4, 6));
    points[35].addEndPoint(Pair<int, int>(3, 5));
    points[35].addEndPoint(Pair<int, int>(3, 7));
    points[36] = Point(Pair<int, int>(6, 0));
    points[36].addEndPoint(Pair<int, int>(5, 1));
    points[36].addEndPoint(Pair<int, int>(4, 0));
    points[36].addEndPoint(Pair<int, int>(2, 0));
    points[36].addEndPoint(Pair<int, int>(4, 2));

    points[37] = Point(Pair<int, int>(6, 2));
    points[37].addEndPoint(Pair<int, int>(6, 3));
    points[37].addEndPoint(Pair<int, int>(6, 4));
    points[37].addEndPoint(Pair<int, int>(5, 2));
    points[37].addEndPoint(Pair<int, int>(5, 3));
    points[37].addEndPoint(Pair<int, int>(4, 3));
    points[37].addEndPoint(Pair<int, int>(4, 4));

    points[38] = Point(Pair<int, int>(6, 3));
    points[38].addEndPoint(Pair<int, int>(6, 2));
    points[38].addEndPoint(Pair<int, int>(6, 4));
    points[38].addEndPoint(Pair<int, int>(6, 5));
    points[38].addEndPoint(Pair<int, int>(5, 3));
    points[38].addEndPoint(Pair<int, int>(4, 3));

    points[39] = Point(Pair<int, int>(6, 4));
    points[39].addEndPoint(Pair<int, int>(8, 2));
    points[39].addEndPoint(Pair<int, int>(8, 4));
    points[39].addEndPoint(Pair<int, int>(8, 6));
    points[39].addEndPoint(Pair<int, int>(7, 3));
    points[39].addEndPoint(Pair<int, int>(7, 4));
    points[39].addEndPoint(Pair<int, int>(7, 5));
    points[39].addEndPoint(Pair<int, int>(6, 2));
    points[39].addEndPoint(Pair<int, int>(6, 3));
    points[39].addEndPoint(Pair<int, int>(6, 5));
    points[39].addEndPoint(Pair<int, int>(6, 6));
    points[39].addEndPoint(Pair<int, int>(5, 3));
    points[39].addEndPoint(Pair<int, int>(5, 4));
    points[39].addEndPoint(Pair<int, int>(5, 5));
    points[39].addEndPoint(Pair<int, int>(4, 2));
    points[39].addEndPoint(Pair<int, int>(4, 4));
    points[39].addEndPoint(Pair<int, int>(4, 6));

    points[40] = Point(Pair<int, int>(6, 5));
    points[40].addEndPoint(Pair<int, int>(6, 3));
    points[40].addEndPoint(Pair<int, int>(6, 4));
    points[40].addEndPoint(Pair<int, int>(6, 6));
    points[40].addEndPoint(Pair<int, int>(5, 5));
    points[40].addEndPoint(Pair<int, int>(4, 5));

    points[41] = Point(Pair<int, int>(6, 6));
    points[41].addEndPoint(Pair<int, int>(6, 5));
    points[41].addEndPoint(Pair<int, int>(6, 4));
    points[41].addEndPoint(Pair<int, int>(5, 5));
    points[41].addEndPoint(Pair<int, int>(5, 4));
    points[41].addEndPoint(Pair<int, int>(5, 6));
    points[41].addEndPoint(Pair<int, int>(4, 6));

    points[42] = Point(Pair<int, int>(6, 8));
    points[42].addEndPoint(Pair<int, int>(5, 7));
    points[42].addEndPoint(Pair<int, int>(4, 6));
    points[42].addEndPoint(Pair<int, int>(4, 8));
    points[42].addEndPoint(Pair<int, int>(2, 8));

    points[43] = Point(Pair<int, int>(7, 3));
    points[43].addEndPoint(Pair<int, int>(8, 2));
    points[43].addEndPoint(Pair<int, int>(7, 4));
    points[43].addEndPoint(Pair<int, int>(7, 6));
    points[43].addEndPoint(Pair<int, int>(6, 4));
    points[43].addEndPoint(Pair<int, int>(5, 5));

    points[44] = Point(Pair<int, int>(7, 4));
    points[44].addEndPoint(Pair<int, int>(8, 4));
    points[44].addEndPoint(Pair<int, int>(7, 3));
    points[44].addEndPoint(Pair<int, int>(7, 5));
    points[44].addEndPoint(Pair<int, int>(6, 4));
    points[44].addEndPoint(Pair<int, int>(5, 4));

    points[45] = Point(Pair<int, int>(7, 5));
    points[45].addEndPoint(Pair<int, int>(8, 6));
    points[45].addEndPoint(Pair<int, int>(7, 4));
    points[45].addEndPoint(Pair<int, int>(6, 4));
    points[45].addEndPoint(Pair<int, int>(5, 3));
    points[45].addEndPoint(Pair<int, int>(7, 3));

    points[46] = Point(Pair<int, int>(8, 2));
    points[46].addEndPoint(Pair<int, int>(8, 4));
    points[46].addEndPoint(Pair<int, int>(8, 6));
    points[46].addEndPoint(Pair<int, int>(7, 3));
    points[46].addEndPoint(Pair<int, int>(6, 4));

    points[47] = Point(Pair<int, int>(8, 4));
    points[47].addEndPoint(Pair<int, int>(8, 2));
    points[47].addEndPoint(Pair<int, int>(8, 6));
    points[47].addEndPoint(Pair<int, int>(6, 4));
    points[47].addEndPoint(Pair<int, int>(7, 4));

    points[48] = Point(Pair<int, int>(8, 6));
    points[48].addEndPoint(Pair<int, int>(8, 4));
    points[48].addEndPoint(Pair<int, int>(8, 2));
    points[48].addEndPoint(Pair<int, int>(7, 5));
    points[48].addEndPoint(Pair<int, int>(6, 4));

    return points;
}
const int SIZE = 9;
int fullyDefCells[9][9] = { {0, 0, 1, 0, 0, 1, 0, 0, 0 },
                            {0, 0, 0, 0, 0, 0, 0, 0, 0 },
                            {1, 0, 1, 0, 0, 0, 1, 0, 1 },
                            {0, 0, 0, 0, 0, 0, 0, 0, 0 },
                            {0, 0, 0, 0, 0, 0, 0, 0, 0 },
                            {0, 0, 0, 0, 0, 0, 0, 0, 0 },
                            {1, 0, 1, 0, 0, 0, 1, 0, 1 },
                            {0, 0, 0, 0, 0, 0, 0, 0, 0 },
                            {0, 0, 1, 0, 0, 0, 1, 0, 0 } };


const int WHITE_SOLDIER = 20;
const int RED_SOLDIER = 20;
const int DEF_BONUS = 5;
const int FULLY_DEF_BONUS = 10;

const int RED_SOLDIER_CH = 1;
const int WHITE_SOLDIER_CH = 2;
const int VOID_CELL = -1;

bool isWhiteSoldier(int soldier) {             //white soldiers
    return WHITE_SOLDIER == soldier;
}

bool isRedSoldier(int soldier) {               //red soldiers
    return RED_SOLDIER == soldier;
}
int isInFullyDef(int** matrix, int ch) {
    int bonus = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (matrix[i][j] == ch && matrix[i][j] == fullyDefCells[i][j]) {
                bonus += FULLY_DEF_BONUS;
            }
        }
    }

    return bonus;
}
int mainDiagonalParallel(int** matrix, int ch) {
    int localBonus = 0;
    int bonus = 0;
    
    for (int i = 1; i < SIZE+1; ++i) {                                //main diagonal
       
        if(matrix[i-1][i-1] == matrix[i][i] && matrix[i][i] == ch && matrix[i-1][i-1] == ch){
            localBonus += DEF_BONUS;
            
        }
    }
    bonus += localBonus;
    

    localBonus = 0;
    for (int i = 1; i < SIZE - 2 + 1; ++i) {                            //higher diagonal
        
        if(matrix[i-1][i+2-1] == matrix[i][i+2] && matrix[i][i + 2] == ch && matrix[i - 1][i + 2 - 1])
            localBonus += DEF_BONUS;
    }
    bonus += localBonus;
   
    
    localBonus = 0; 
    for (int i = 3; i < SIZE + 1; ++i) {                                //lower diagonal
        
        if (matrix[i - 1][i - 2 - 1] == matrix[i][i - 2] && matrix[i - 1][i - 2 - 1] == ch && matrix[i][i - 2] == ch) {
            localBonus += DEF_BONUS;
        }
    }
    bonus += localBonus;
    
    return bonus;
}
int sideDiagonalParallel(int** matrix, int ch) {
    int bonus = 0;
    int localBonus = 0;
   
    for (int i = 1; i < SIZE + 1; ++i) {                                //side diagonal
        
        if (matrix[i][SIZE - i] == matrix[i-1][SIZE - i] && matrix[i - 1][SIZE - i] == ch && matrix[i][SIZE - i]) {
            localBonus += DEF_BONUS;
        }
    }
    bonus += localBonus;
   
    

    localBonus=0;
    for (int i = 1; i < SIZE - 2 + 1; ++i) {                            //hegher diagonal
      
        if (matrix[i - 1][SIZE - i - 3 + 1] == matrix[i][SIZE - i - 3] && matrix[i - 1][SIZE - i - 3 + 1] == ch && matrix[i][SIZE - i - 3] == ch) {
            localBonus += DEF_BONUS;
        }
    }
    bonus += localBonus;
    
    
    
    localBonus=0;
    for (int i = 3; i < SIZE + 1; ++i) {                                //lower diagonal
        
        if (matrix[i - 1][SIZE - i + 3 - 1] == matrix[i][SIZE - i + 1] && matrix[i - 1][SIZE - i + 3 - 1] == ch && matrix[i][SIZE - i + 1] == ch) {
            localBonus += DEF_BONUS;
        }
    }
    bonus += localBonus;
    
      
    return bonus;
}
int columnCalc(int** matrix, int ch) {
    int localBonus = 0;
    int bonus = 0;
   
    for (int j = 0; j < SIZE; ++j) {
        for (int i = 1; i < SIZE + 1; ++i) {
           
            if(i != 2 || i != 7) {
                if (matrix[i - 1][j] == matrix[i][j] && matrix[i - 1][j] == ch && matrix[i][j] == ch) {
                    localBonus+=DEF_BONUS;
                }
            }
            if(j == 0 || j == 8) {
                if (matrix[i - 2][j] == matrix[i][j] && matrix[i - 2][j] == ch && matrix[i][j] == ch) {
                    localBonus += DEF_BONUS;
                }
            }
        }
        
        bonus += localBonus;
        localBonus = 0; 
    }
    return bonus;    
}
int rowCalc(int** matrix, int ch) {
    int localBonus = 0;
    int bonus = 0;
   
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 1; j < SIZE + 1; ++j) {
           
            if(j != 2 || j != 7) {
                if(matrix[i][j-1] == matrix[i][j] && matrix[i][j-1] == ch && matrix[i][j] == ch){
                    localBonus+=DEF_BONUS;
                }
            }
            if (i == 0 || i == 8) {
                if (matrix[i][j - 2] == matrix[i][j] && matrix[i][j - 2] == ch && matrix[i][j] == ch) {
                    localBonus += DEF_BONUS;
                }
            }
        }
       
        bonus +=  localBonus;
        localBonus = 0;
    }
    return bonus;
    
}
int calculate(int** matrix) {
    int white = 0, red = 0;    
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (matrix[i][j] == 1) {
                red += RED_SOLDIER;
            }
            if (matrix[i][j] == 2) {
                white += WHITE_SOLDIER;
            }
        }
    }
    return white-red;
}
int Evalutate(int** matrix) {
    int white = 0, red = 0;
    white += rowCalc(matrix, WHITE_SOLDIER_CH);
    white += columnCalc(matrix, WHITE_SOLDIER_CH);
    white += mainDiagonalParallel(matrix, WHITE_SOLDIER_CH);
    white += sideDiagonalParallel(matrix, WHITE_SOLDIER_CH);
    red += rowCalc(matrix, RED_SOLDIER_CH);
    red += columnCalc(matrix, RED_SOLDIER_CH);
    red += mainDiagonalParallel(matrix, RED_SOLDIER_CH);
    red += sideDiagonalParallel(matrix, RED_SOLDIER_CH);
    return  white - red + calculate(matrix) + (isInFullyDef(matrix, WHITE_SOLDIER_CH) - isInFullyDef(matrix, RED_SOLDIER_CH));
}
int checkWinner(int matrix[9][9]) {
    int redSoldiersCount = 0;
    int whiteSoldiersCount = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (matrix[i][j] == RED_SOLDIER_CH) {
                ++redSoldiersCount;
            }
            if (matrix[i][j] == WHITE_SOLDIER_CH) {
                ++whiteSoldiersCount;
            }
        }
    }
    if (redSoldiersCount == 0) {
        std::cout << "White Won" << std::endl;
        return 1;
    }
    if (whiteSoldiersCount == 0) {
        std::cout << "Red Won" << std::endl;
        return 2;
    }
    return 0;
}
// Метод для перемещения солдата
int** simulateMove(int matrix[][9], const Pair<int, int>& start, const Pair<int, int>& end) {
    int** newMatrix = new int*[9];
    for (int i = 0; i < 9; ++i) {
        newMatrix[i] = new int[9];
        for (int j = 0; j < 9; ++j) {
            newMatrix[i][j] = matrix[i][j];
        }
    }

    if (start.first < 0 || start.first >= 9 || start.second < 0 || start.second >= 9 ||
        end.first < 0 || end.first >= 9 || end.second < 0 || end.second >= 9) {
        std::cout << "Invalid move: Coordinates out of bounds." << std::endl;
        return newMatrix;
    }

    if (newMatrix[end.first][end.second] != 0) {
        std::cout << "Invalid move: End point is occupied." << std::endl;
        return newMatrix;
    }

    newMatrix[end.first][end.second] = newMatrix[start.first][start.second];
    newMatrix[start.first][start.second] = 0;

    std::cout << "Move successful: Soldier moved from (" << start.first << ", " << start.second << ") to ("
        << end.first << ", " << end.second << ")." << std::endl;

    return newMatrix;
}

std::vector<Pair<Pair<int, int>, Pair<int, int>>> getAllAvailableMoves_(const int matrix[][9], const std::vector<Point>& points) {
    std::vector<Pair<Pair<int, int>, Pair<int, int>>> availableMoves;

    // Loop through each point on the board
    for (const Point& point : points) {
        Pair<int, int> start = point.getStart();

        int currentPlayer = matrix[start.first][start.second];
        if (currentPlayer == 0) continue;
        if ((currentPlayer == 1 && start.first < 5) || (currentPlayer == 2 && start.first > 3))
            continue;

        const MyVector<Pair<int, int>>& endPoints = point.getEnd();
        for (size_t j = 0; j < endPoints.getSize(); ++j) {
            Pair<int, int> end = endPoints[j];
            if (matrix[end.first][end.second] == 0) {
                availableMoves.push_back(Pair<Pair<int, int>, Pair<int, int>>(start, end));
            }
        }
    }

    return availableMoves;
}

bool isValidMove(const int matrix[][9], const Pair<int, int>& start, const Pair<int, int>& end) {
    if (start.first < 0 || start.first >= 9 || start.second < 0 || start.second >= 9 ||
        end.first < 0 || end.first >= 9 || end.second < 0 || end.second >= 9) {
        return false;
    }

    return (matrix[end.first][end.second] == 0);
}

int** eatSoldier(int matrix[][9], const Pair<int, int>& start, const Pair<int, int>& end) {
    int** newMatrix = simulateMove(matrix, start, end);

    int oppositeSoldier = (newMatrix[start.first][start.second] == 1) ? 2 : 1;
    if (newMatrix[end.first][end.second] == oppositeSoldier) {
        newMatrix[end.first][end.second] = 0;
        std::cout << "Soldier at (" << end.first << ", " << end.second << ") eaten!" << std::endl;
    }

    return newMatrix;
}
int minimax(int** matrix, int depth, bool isMaximizingPlayer) {
    int score = Evalutate(matrix);
    if (depth == 0) {
        return score;
    }

    std::vector<Pair<Pair<int, int>, Pair<int, int>>> availableMoves = getAllAvailableMoves_(matrix, points);
    if (isMaximizingPlayer) {
        int bestScore = -9999;
        for (const auto& move : availableMoves) {
            int** newMatrix = simulateMove(matrix, move.first, move.second);
            int newScore = minimax(newMatrix, depth - 1, false);
            bestScore = std::max(bestScore, newScore);
            
        }
        return bestScore;
    } else {
        int bestScore = 9999;
        for (const auto& move : availableMoves) {
            int** newMatrix = simulateMove(matrix, move.first, move.second);
            int newScore = minimax(newMatrix, depth - 1, true);
            bestScore = std::min(bestScore, newScore);
            
        }
        return bestScore;
    }
}

int main() {
    int** matrix; // Определите матрицу игровой доски

    // Заполните матрицу
    int initialMatrix[9][9] = { {-1, -1, 1, -1, 1, -1, 1, -1, -1},
                                 {-1, -1, -1, 1, 1, 1, -1, -1, -1},
                                 {0, -1, 1, 1, 1, 1, 1, -1, 0},
                                 {-1, 0, 1, 1, 0, 1, 1, 0, -1},
                                 {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                 {-1, 0, 2, 2, 1, 2, 2, 0, -1},
                                 {0, -1, 2, 2, 2, 2, 2, -1, 0},
                                 {-1, -1, -1, 2, 2, 2, -1, -1, -1},
                                 {-1, -1, 2, -1, 2, -1, 2, -1, -1} };
    matrix = new int*[9];
    for (int i = 0; i < 9; ++i) {
        matrix[i] = new int[9];
        for (int j = 0; j < 9; ++j) {
            matrix[i][j] = initialMatrix[i][j];
        }
    }

    // Создайте вектор точек points
    std::vector<Point> points = createPointsVector();

    // Получите доступные ходы
    std::vector<Pair<Pair<int, int>, Pair<int, int>>> availableMoves = getAllAvailableMoves_(matrix, points);

    // Выберите лучший ход с помощью минимакс алгоритма
    int depth = 3; // Установите глубину в соответствии с вашими потребностями
    bool isMaximizingPlayer = true; // Предположим, что максимизирующий игрок - это компьютерный игрок
    int bestScore = -9999;
    Pair<Pair<int, int>, Pair<int, int>> bestMove;
    for (const auto& move : availableMoves) {
        int** newMatrix = simulateMove(matrix, move.first, move.second);
        int score = minimax(newMatrix, depth - 1, false);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
        // Освободить память для newMatrix
        for (int i = 0; i < SIZE; ++i) {
            delete[] newMatrix[i];
        }
        delete[] newMatrix;
    }

    // Выведите лучший ход
    std::cout << "Best move: (" << bestMove.first.first << ", " << bestMove.first.second << ") -> ("
              << bestMove.second.first << ", " << bestMove.second.second << ")" << std::endl;

    // Освободить память для matrix
    for (int i = 0; i < 9; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
