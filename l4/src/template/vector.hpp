#include "iostream"
#include <iterator>

/** This is the class vector. Iterator is implemented.
 *  
 * It's a sequence container that encapsulates dynsmic
 * size arrays.
 * All the elements stored one by one, however there's
 * an opportunity for a really resourceful users, to 
 * get the access to any element.
 *
 * The "length" of Vec always increases, when you push
 * new elements to it's back.
 *
 * Time complexity is:
 *   random access: O(1)
 *   insertion is O(1)( O(n) if there's no reserved space)
 *
 * Template parameters
 *   T must be copyAssignable, copyConstructible
 *
*/
template<typename T>
class Vec{
    private:
        T* p_array; //!< simple array 
        unsigned int a_size; //!< Unsigned integer type
    public:
        /**
         *  Iterator Class for vector.
         *
         *  Bidirectional iterator.
         */
        class vec_iterator{
            public:
                using iterator_category = std::bidirectional_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = T;
                using pointer           = T*;
                using reference         = T&; 

                explicit vec_iterator(pointer p):p_ptr(p){}
                T& operator*() const { return *p_ptr; }
                T* operator->() { return p_ptr; }

                vec_iterator& operator++(){p_ptr++; return *this;}
                vec_iterator& operator--(){p_ptr--; return *this;}
                vec_iterator operator++(int) { vec_iterator tmp = *this; ++(*this); return tmp;}
                vec_iterator operator--(int) { vec_iterator tmp = *this; --(*this); return tmp;}
                friend bool operator==(const vec_iterator& a, const vec_iterator& b) { return a.p_ptr == b.p_ptr; }
                friend bool operator!=(const vec_iterator& a, const vec_iterator& b) { return a.p_ptr != b.p_ptr; }

             private:
                pointer p_ptr;
        };


        explicit Vec(unsigned int n = 0) : p_array(new T [n]), a_size(n){} //!< Simple constructor, that creates an empty vector of size n.
        Vec(const Vec& copy); //!< Copy constructor. 
        Vec(Vec&& move);    //!< Move constructor. 
        explicit Vec(const T* vals, int n);
        ~Vec(){delete[] p_array;} //!< Destructs the vector 

        friend bool operator==(const Vec& a, const Vec&b) {return a==b;}; //!< Comparing the values of vectors
        friend bool operator!=(const Vec& a, const Vec&b) {return a!=b;}  //!< Comparing the values of vectors
        bool operator==(const Vec& r);//!< Comparing the values of vectors
        bool operator!=(const Vec& r);//!< Comparing the values of vectors


        Vec& operator=(const Vec& cp); //!< Copy assignment
        Vec& operator=(Vec&& mv); //!< Move assignment
        
        const unsigned int size()const{return a_size;} //!< Returns an amount of elements

        const T& operator[](int num) const;  //!< Access specified element
        T& operator[](int num); //!< Access + Update

        void pushBack(const T& x); //!adds an element to the end
        
        vec_iterator begin() { return vec_iterator(p_array);} //!< returns the iterator to the begining
        vec_iterator end() { return vec_iterator(p_array + a_size);} //!< returns the iterator to the end
};

/**<  fulfilles the new vector with the copy of other vector contents
 *    Complexity: O(n)
 */
template<typename T>
Vec<T>::Vec(const Vec<T>& copy):a_size(copy.a_size){
    p_array = new T [a_size];
    std::copy(copy.p_array, copy.p_array+a_size, p_array);
}


/**<  fulfilles the new vector with literally other vector contents
 *    Complexity: O(1)
 */
template<typename T>
Vec<T>::Vec(Vec<T>&& move):a_size(move.a_size){
    p_array = move.p_array;
    move.p_array = nullptr;
}


/**< fulfilles the new vector with the copy of c-like array contents
 *   Complexity: O(n)
 */
template<typename T>
Vec<T>::Vec(const T* vals, int n){
    if(n < 0){
        throw std::invalid_argument("bad size");
    }
    a_size = n;
    p_array = new T [a_size];
    std::copy(vals, vals+n, p_array);
}

template<typename T>
bool Vec<T>::operator==(const Vec<T>& r){
    if(this == &r){
        return true;
    }
    if(a_size != r.a_size){
        return false;
    }
    for(int i = 0; i < a_size; i++){
        if(p_array[i] != r.p_array[i]){
            return false;
        }
    }
    return true;
}

template<typename T>
bool Vec<T>::operator!=(const Vec<T>& r){
    if(this == &r){
        return false;
    }
    if(a_size != r.a_size){
        return true;
    }
    for(int i = 0; i < a_size; i++){
        if(p_array[i] != r.p_array[i]){
            return true;
        }
    }
    return false;
}

/**< replaces the contents of the vector with a copy of the contents of other
 *   Complexity: O(n)?
*/
template<typename T>
Vec<T>& Vec<T>::operator=(const Vec<T>& cp){
    if(this != &cp){
        a_size = cp.a_size;
        delete[] p_array;
        std::copy(cp.p_array, cp.p_array + a_size, p_array);
    }
    return *this;
}

/**< replaces the contents of the vector with a copy of the contents of other, erasing the contents in other 
 *   Complexity: O(1)?
 */
template<typename T>
Vec<T>& Vec<T>::operator=(Vec<T>&& mv){
    if(this != &mv){
        a_size = mv.a_size;
        delete[] p_array;
        p_array = mv.p_array;
        mv.p_array = nullptr;
    }
    return *this;
}

/**< returns the constant reference to the element at specified location pos. Bounds are checked.
 *   Complexity: O(1)
 */
template<typename T>
const T& Vec<T>::operator[](int num) const{
    if(num < 0 || num >= a_size){
        throw std::out_of_range("out of range");
    }
    return p_array[num];
}

/**< returns the reference to the element at specified location pos. Bounds are checked. 
 *   complexity: O(1)
 */
template<typename T>
T& Vec<T>::operator[](int num){
    if(num < 0 || num >= a_size){
        throw std::out_of_range("out of range");
    }
    return p_array[num];
}

/** inserts new element to the end of the vector, allocating new memory every time 
 *  complexity: O(n)
 */
template<typename T>
void Vec<T>::pushBack(const T& x){
    T* tmp = new T [a_size+1];
    std::copy(p_array, p_array+a_size, tmp);
    delete[] p_array;
    p_array = tmp;
    a_size++;
    p_array[a_size-1] = x;
}
