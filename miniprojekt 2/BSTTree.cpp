#include "BSTTree.h"
//konstruktor
BSTTree::BSTTree() : root(nullptr), treeSize(0) {}
//destruktor
BSTTree::~BSTTree() {
    clear(root);
}

void BSTTree::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}
//funkcja dodajaca element do drzewa
void BSTTree::insert(int value, int priority) {
    Node* newNode = new Node(value, priority);
    if (!root) {
        root = newNode;
        treeSize++;
        return;
    }
    // Znalezienie miejsca do wstawienia nowego węzła
    Node* parent = nullptr;
    Node* current = root;
    while (current) {
        // Znaleziono miejsce do wstawienia nowego węzła
        parent = current;
        if (priority < current->priority) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    // Wstawienie nowego węzła
    if (priority < parent->priority) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    treeSize++;
}
//funkcja dodajaca element do drzewa
BSTTree::Node* BSTTree::insert(Node* node, int value, int priority) {
    // Znalezienie miejsca do wstawienia nowego węzła
    if (!node) return new Node(value, priority);
    // Wstawienie nowego węzła
    if (priority > node->priority) {
        Node* newNode = new Node(value, priority);
        newNode->left = node;  // Wstawienie nowego węzła jako korzenia
        return newNode;
        
    } else if (priority < node->priority) {
        // Rekurencyjne wstawienie nowego węzła
        node->left = insert(node->left, value, priority);
    } else {
        // Rekurencyjne wstawienie nowego węzła
        node->right = insert(node->right, value, priority);
    }
    return node;
}
//funkcja zwracajaca indeks elementu w drzewie
std::pair<int, int> BSTTree::extractMax() {
    if (!root) throw std::runtime_error("BST is empty");
    std::pair<int, int> max = {root->value, root->priority};
    Node* maxNode = extractMax(root);
    delete maxNode;
    treeSize--;
    return max;
}
//funkcja usuwajaca element z drzewa
BSTTree::Node* BSTTree::extractMax(Node*& node) {
    if (!node->right) {
        Node* temp = node;
        node = node->left;
        return temp;
    }
    return extractMax(node->right);
}
//funkcja zwracajaca maksymalny element drzewa
std::pair<int, int> BSTTree::findMax() const {
    Node* maxNode = findMax(root);
    if (!maxNode) throw std::runtime_error("BST is empty");
    return {maxNode->value, maxNode->priority};
}
//funkcja zwracajaca maksymalny element drzewa
BSTTree::Node* BSTTree::findMax(Node* node) const {
    while (node && node->right) node = node->right;
    return node;
}
//funkcja zmieniajaca priorytet elementu
void BSTTree::modifyKey(int value, int newPriority) {
    root = remove(root, value);
    insert(value, newPriority);
}
//funkcja usuwajaca element z drzewa
BSTTree::Node* BSTTree::remove(Node* root, int value) {
    // Znalezienie węzła do usunięcia
    Node* parent = nullptr;
    Node* current = root;
    while (current && current->value != value) {
        parent = current;
        // Przejście do lewego lub prawego poddrzewa
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    if (!current) return root; // Nie znaleziono wartości

    // Przypadek 1: Usuwany węzeł nie ma potomków (węzeł liści)
    if (!current->left && !current->right) {
        if (current != root) {
            if (parent->left == current) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        } else {
            root = nullptr;
        }
        delete current;
        treeSize--;
    }
    // Przypadek 2: Usuwany węzeł ma dwa potomki
    else if (current->left && current->right) {
        Node* successor = current->right;
        Node* successorParent = current;

        while (successor->left) {
            successorParent = successor;
            successor = successor->left;
        }

        current->value = successor->value;
        current->priority = successor->priority;

        if (successorParent != current) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }

        delete successor;
        treeSize--;
    }
    // Przypadek 3: Usuwany węzeł ma jednego potomka
    else {
        Node* child = (current->left) ? current->left : current->right;

        if (current != root) {
            if (current == parent->left) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        } else {
            root = child;
        }

        delete current;
        treeSize--;
    }

    return root;
}
//funkcja zwracajaca rozmiar drzewa
int BSTTree::returnSize() const {
    return treeSize;
}
//funkcja usuwajaca wszystkie elementy z drzewa
void BSTTree::clear() {
    clear(root);
    root = nullptr;
    treeSize = 0;
}
//funkcja wypisujaca drzewo
void BSTTree::print() const {
    print(root);
    std::cout << std::endl;
}

void BSTTree::print(Node* node) const {
    if (node) {
        print(node->left);
        std::cout << node->value << " " << node->priority << std::endl;
        print(node->right);
    }
}