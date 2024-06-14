#ifndef GUARD_TRAIT_H
#define GUARD_TRAIT_H
#include <concepts>
namespace asyncruino
{
    template <typename guard_t>
    concept Guard = requires (guard_t m_guard){
        {m_guard.lock()}->std::same_as<void>;
        {m_guard.unlock()}->std::same_as<void>;
    };
}


#endif//GUARD_TRAIT_H