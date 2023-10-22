//
// Created by 12695 on 2023/3/17.
//

#ifndef C_TUPLE_HPP
#define C_TUPLE_HPP

template<typename T1, typename T2, typename T3>
class Tuple {
public:
    const T1 first;
    const T2 second;
    const T3 third;

    Tuple(T1 first, T2 second, T3 third) : first(first), second(second), third(third) {}
};


#endif //C_TUPLE_HPP
