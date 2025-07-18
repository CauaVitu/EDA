#ifndef Comparator_HPP
#define Comparator_HPP
template <typename T>
struct Comparator {
    bool operator()(const T& a, const T& b) const {
        return std::less<T>()(a,b); // Define a comparação padrão para o tipo T
    }
};


template <typename T,typename U>
struct Comparator<std::pair<T,U>> {
     bool operator()(const std::pair<T, U>& a, const std::pair<T, U>& b) const {
        return std::less<T>()(a.first, b.first);
    }
};
#endif // COMPARATOR_HPP