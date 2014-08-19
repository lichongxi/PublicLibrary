#ifndef __GW_UTILITY_LOCALSCOPE_HEADER__
#define __GW_UTILITY_LOCALSCOPE_HEADER__

#include <functional>
#include <cstdlib>
#include <cstdio>

class localscope 
{
public:
    explicit localscope( std::function<void()> exit_function )
        : local_exit_(exit_function), cancel_(false)
    { }

    ~localscope()
    {
        if(!cancel_)
        {
            local_exit_();
        }
    }

    void cancel_action()
    {
        cancel_ = true;
    }

private:
    std::function<void()> local_exit_;
    bool cancel_;

private: // noncopyable
    localscope(localscope const&);
    localscope& operator=(localscope const&);
};
//BOOST_SCOPE_EXIT

#define ON_SCOPE_EXIT(variable, callback) localscope variable##_GUARD([&variable]{callback})
#define CANCEL_EXIT_ACTION( variable ) variable##_GUARD.cancel_action()

#endif //__GW_UTILITY_LOCALSCOPE_HEADER__
