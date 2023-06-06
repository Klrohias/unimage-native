//
// Created by Twiiz on 2023/5/26.
//

#ifndef UNIMAGE_STATICFORLOOP_HPP
#define UNIMAGE_STATICFORLOOP_HPP

// from https://stackoverflow.com/questions/13816850/is-it-possible-to-develop-static-for-loop-in-c
template <int First, int Last>
struct static_for
{
    template <typename Fn>
    void operator()(Fn const& fn) const
    {
        if (First < Last)
        {
            fn(First);
            static_for<First+1, Last>()(fn);
        }
    }
};

template <int N>
struct static_for<N, N>
{
    template <typename Fn>
    void operator()(Fn const& fn) const
    { }
};


#endif //UNIMAGE_STATICFORLOOP_HPP
