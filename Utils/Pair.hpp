//
// Created by 12695 on 2023/3/17.
//

#ifndef C_PAIR_HPP
#define C_PAIR_HPP

template<typename T1, typename T2>
class Pair {
public:
    const T1 first;
    const T2 second;

    Pair(T1 first, T2 second) : first(first), second(second) {}

};


#endif //C_PAIR_HPP
