#ifndef BOOST_TMP_EXPRESSION_HPP_INCLUDED
#define BOOST_TMP_EXPRESSION_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <type_traits>
#include "capabilities.hpp"
#include "../always.hpp"
#include "../pack.hpp"

namespace boost {
	namespace tmp {
#ifdef BOOST_TMP_CPP14
		namespace fusion {

			template <typename H, typename T>
			struct ast;
			// an expression and an ast are both linked lists of expressions however, the AST hast
			// been reversed (and can be executed)
			template <typename H, typename T>
			struct expr {
				H head;
				T tail;

				constexpr ast<T, H> reverse() {
					return {tail, head};
				}
				template <typename U>
				constexpr ast<T, ast<H, U>> reverse(U &&u) {
					return {std::move(tail), {std::move(head), std::move(u)}};
				};
			};
			template <typename H, typename EH, typename ET>
			struct expr<H, expr<EH, ET>> {
				H head;
				expr<EH, ET> tail;
				template <typename U>
				constexpr auto reverse(U &&out) {
					return tail.reverse(ast<H, U>{std::move(head), std::move(out)});
				}
				constexpr auto reverse() {
					return tail.reverse(ast<H, identity_>{std::move(head), {}});
				}
			};
			template <typename H, typename T>
			struct ast {
				H head;
				T tail;
			};

			namespace detail {
				template <typename T>
				struct exec_callable {
					template <typename...>
					using exec = int;
					T fun;
					template <typename X, typename... Ts>
					constexpr auto f(X, pack<Ts...> &&p) {
						return fun(static_cast<Ts &>(p).data...);
					};
				};

				template <typename T, typename = void>
				struct make_expr {
					template <typename L, typename R>
					constexpr expr<exec_callable<T>, L> operator()(L l, R r) {
						return {{r}, l};
					}
				};

				template <typename T>
				struct voider {
					using type = void;
				};

				template <typename T>
				struct make_expr<T, typename voider<typename rebind<T>::type>::type> {
					template <typename L, typename R>
					constexpr expr<typename rebind<T>::type, L> operator()(L l, R r) {
						return {{}, l};
					}
				};
			} // namespace detail
		} // namespace fusion
#endif
	} // namespace tmp
} // namespace boost
#endif
