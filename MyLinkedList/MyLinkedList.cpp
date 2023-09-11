#include <iostream>
#include <list>
#include <functional>
#include <algorithm>

template<class T>
class Node
{
    public:
        T value;
        Node* NextElement = nullptr;
        Node* PrevElement = nullptr;
};

template<class T>
class LinkedList 
{
    private:
        Node<T>* head = nullptr;
        Node<T>* tail = nullptr;
        std::size_t sizeoflist = 0;
        
    public:
        class Iterator
        {
        public:
            void operator++(int)
            {
                ptr = ptr->NextElement;
            }
            void operator++()
            {
                ptr = ptr->NextElement;
            }
            Iterator operator+(int amount)
            {
                auto* tempptr = ptr;
                int i = 0;
                while (i != amount)
                {
                    tempptr = tempptr->NextElement;
                    i++;
                }
                
                Iterator iterator;
                iterator.setPtr(tempptr);
                return iterator;
            }
            void operator=(Node<T>* newptr)
            {
                ptr->value = newptr->value;
                ptr->NextElement = newptr->NextElement;

            }
            
            bool operator!=(const Iterator& temp) const
            {
                return ptr != temp.ptr;
            }
            T& operator*()
            {
                return ptr->value;
            }
            void operator+=(int amount)
            {
                int i = 0;
                while (i != amount)
                {
                    ptr = ptr->NextElement;
                    i++;
                }
            }
            void setPtr(Node<T>* setPtr)
            {
                this->ptr = setPtr;
            }
        private:
            Node<T>* ptr = nullptr;
        };

        Iterator begin()
        {
            Iterator iter;
            iter.setPtr(head);
            return iter;
        }

        Iterator end()
        {
            Iterator iter;
            iter.setPtr(tail + 1);
            return iter;
        }
        

        LinkedList() = default;

        LinkedList(const LinkedList<T>& other)
        {  
            Node<T>* elements;
            elements = head;
            while (elements != nullptr)
            {
                push_back(elements->value);
                elements = elements->NextElement;
            }
        }
        
        void push_front(T value)
        {
            Node<T>* newNode = new Node<T>;
            newNode -> value = value;
            newNode -> NextElement = head;
            head = newNode;
            sizeoflist++;
        }
        void push_back(T value)
        {
            if (isEmpty())
            {
                head = new Node<T>;
                head -> value = value;
                head -> NextElement = nullptr;
                tail = head;
            }
            else
            {
                Node<T>* backNode = new Node<T>();
                backNode -> value = value;
                backNode ->NextElement = nullptr;
                tail ->NextElement = backNode;
                tail = backNode;
            }
            sizeoflist++;
        }
        Node<T>* get(int number)
        {
            int i = 0;
            Node<T>* elements;
            elements = head;
            while (elements != nullptr)
            {
                if (i == number)
                    return elements;
                elements = elements ->NextElement;
                i++;
            }
            return nullptr;
        }
        Node<T>* operator[](int number)
        {
            return get(number);
        }
        void pop_front()
        {
            if (isEmpty())
                return;

            Node<T>* tempor = head;
            head = head -> NextElement;
            delete tempor;
            sizeoflist--;
        }
        void pop_back()
        {
            Node<T>* tempor = head;
            while (tempor ->NextElement != tail)
                tempor = tempor ->NextElement;
            delete tail;
            tail = tempor;
            tempor ->NextElement = nullptr;
        }
        int size()
        {
            return sizeoflist;
        }
    
        void clear()
        {
            Node<T>* current = head;
            while (current != nullptr)
            {
                head = head ->NextElement;
                delete current;
                current = head;
            }
            sizeoflist = 0;
            head = nullptr;
            tail = nullptr;
        }
        bool isEmpty()
        {
            return !sizeoflist;
        }
        
        ~LinkedList()
        {
            clear();
        }
        void iterateOverNodes(std::function<void(Node<T>&)> callback)
        {
            Node<T>* elements;
            elements = head;
            while (elements != nullptr)
            {
                callback(*elements);
                elements = elements->NextElement;
            }
            return;
        }
        void iterate(std::function<void(T&)> callback)
        {
            iterateOverNodes([&](auto& node) {callback(node.value); });

        }
};

int main()
{
    
    LinkedList<int> listOfInt;
    LinkedList<int> listOfInt1(listOfInt);
    listOfInt.push_back(3293);
    listOfInt.push_back(3294);
    listOfInt.push_back(3295);
    listOfInt.push_back(3296);
    listOfInt.push_back(3297);


  


    auto print = [](const int& n) { std::cout << n << ' '; };

    std::for_each(listOfInt.begin(), listOfInt.end(), print);

    
    std::cout << std::endl;
    auto it = listOfInt.begin();
    //*it = 3534;
    it = it + 3;
    std::cout << *it << std::endl;
    std::cout << std::endl;
    listOfInt.iterateOverNodes([]
    (auto& node)
        { std::cout << node.value << " "; }
    );

}

