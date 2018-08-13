#ifndef BOOST_TMP_PACK_HPP_INCLUDED
#define BOOST_TMP_PACK_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "detail/capabilities.hpp"
#include "detail/dispatch.hpp"
#include "lift.hpp"
#include "sequence/zip_with_index.hpp"

namespace boost {
	namespace tmp {
#ifdef BOOST_TMP_CPP14
		namespace fusion {
			template <typename... Bs>
			struct pack : Bs... {
				constexpr pack(Bs &&... as) : Bs{std::move(as)}... {
				}
			};

			template <>
			struct rebind<listify_> {
				using type = listify_;
			};

			namespace detail {
				template <typename I, typename T>
				struct base {
					T data;
					using type = T;
					constexpr const T &get() const & {
						return data;
					}
					constexpr const T &&get() const && {
						return std::move(data);
					}
					constexpr T &&get() && {
						return std::move(data);
					}
				};

				template <typename I, typename T>
				struct base<I, T &&> {
					T &&data;
					using type = T;
					constexpr const T &get() const & {
						return data;
					}
					constexpr const T &&get() const && {
						return std::move(data);
					}
					constexpr T &&get() && {
						return std::move(data);
					}
				};

				template <typename I, typename T>
				struct base<I, T &> {
					T data;
					using type = T;
					constexpr const T &get() const {
						return data;
					}
				};
				/*
				                template <typename... Bs, typename P>
				                auto pack_from_bases_r(list_<Bs...>, P &&p) {
				                    return fast_pack<Bs...>{static_cast<Bs &&>(p)...};
				                };
				                template <typename... Bs, typename P>
				                auto pack_from_bases_l(list_<Bs...>, P &p) {
				                    return fast_pack<Bs...>{static_cast<Bs &>(p)...};
				                };*/

				template <typename... Ts, typename... Bs, typename... Us>
				constexpr fusion::pack<Bs...> pack_impl(list_<Bs...>, Us &&... as) {
					return fusion::pack<Bs...>{Bs{std::forward<Us>(as)}...};
				};
			} // namespace detail
		} // namespace fusion

		template <typename... Ts>
		constexpr auto pack_(Ts &&... args) {
			return fusion::detail::pack_impl(call_<zip_with_index_<lift_<fusion::detail::base>>,
													 decltype(std::forward<Ts>(args))...>{},
											 std::forward<Ts>(args)...);
		}
		template <typename... Ts>
		constexpr auto val_pack_(Ts... args) {
			return fusion::detail::pack_impl(
					call_<zip_with_index_<lift_<fusion::detail::base>>, Ts...>{},
					std::move(args)...);
		}

		//older clang wordaround for empty packs
		constexpr fusion::pack<> pack_() {
			return fusion::pack<>{};
		}
		constexpr fusion::pack<> val_pack_() {
			return fusion::pack<>{};
		}
#endif
	} // namespace tmp
} // namespace boost
#endif
