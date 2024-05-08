#include "MaxHeap.h"


//funkcja zwracajaca indeks elementu w kopcu
void MaxHeap::insert(int e, int p) {
    heap.push_back({e, p});
    heapifyUp(heap.size() - 1);
}
//funkcja usuwajaca element z kopca
std::pair<int, int> MaxHeap::extractMax() {
    if (heap.empty()) throw std::runtime_error("Heap is empty");
    //zamiana miejscami elementow
    std::swap(heap[0], heap.back());
    auto maxElement = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return maxElement;
}

//funkcja zwracajaca maksymalny element kopca
std::pair<int, int> MaxHeap::findMax() const {
    if (heap.empty()) throw std::runtime_error("Heap is empty");
    return heap[0];
}

//funkcja zmieniajaca priorytet elementu
void MaxHeap::modifyKey(int e, int newP) {
    //znalezienie indeksu elementu
    int index = findIndex(e);
    if (index == -1) throw std::runtime_error("Element not found");
    //zmiana priorytetu elementu
    heap[index].second = newP;
    //naprawienie kopca
    heapifyUp(index);
    heapifyDown(index);
}

//funkcja zwracajaca rozmiar kopca
size_t MaxHeap::returnSize() const {
    return heap.size();
}

//funkcja
void MaxHeap::heapifyUp(int index) {
    while (index > 0 && heap[index].second > heap[(index - 1) / 2].second) {
        std::swap(heap[index], heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

//funkcja naprawiajaca kopiec
void MaxHeap::heapifyDown(int index) {
    //indeksy lewego i prawego dziecka
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;
    //sprawdzenie czy lewe dziecko jest wieksze od rodzica
    if (left < heap.size() && heap[left].second > heap[largest].second) {
        largest = left;
    }
    if (right < heap.size() && heap[right].second > heap[largest].second) {
        largest = right;
    }
    if (largest != index) {
        //zamiana miejscami elementow
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}
//funkcja zwracajaca indeks elementu w kopcu
int MaxHeap::findIndex(int e) {
    for (int i = 0; i < heap.size(); i++) {
        if (heap[i].first == e) return i;
    }
    return -1;
}
//funkcja wypisujaca kopiec
void MaxHeap::print() const {
    for (const auto& elem : heap) {
        std::cout << elem.first << " " << elem.second << std::endl;
    }
}
//funkcja czyszczaca kopiec
void MaxHeap::clearHeap() {
    heap.clear();
}