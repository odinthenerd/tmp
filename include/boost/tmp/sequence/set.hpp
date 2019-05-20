#pragma once
#include "../algorithm/fold_left.hpp"
namespace boost{
    namespace tmp{
        namespace detail{
            template<typename T>
            struct unique_magic_type;

            struct unique_super_base{
                static constexpr bool contains(void*){
                    return false;
                }
            };

            template<typename Tail, typename T>
            struct unique_base : Tail{
                static constexpr bool contains(unique_magic_type<T>*){
                    return true;
                }
                using Tail::contains;
            };

            template<typename T, typename U>
            using is_in_set = bool_<T::contains(static_cast<detail::unique_magic_type<U>*>(0))>;
            using unique_push_if = if_<lift_<is_in_set>,front_<>,lift_<detail::unique_base>>;

        }
        using make_unique = push_front_<detail::unique_super_base,fold_left_<detail::unique_push_if>>;
    }
}