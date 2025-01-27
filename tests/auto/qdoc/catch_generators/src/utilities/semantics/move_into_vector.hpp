/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the tools applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#pragma once

#include "../../namespaces.hpp"

#include <vector>
#include <tuple>

namespace QDOC_CATCH_GENERATORS_UTILITIES_ABSOLUTE_NAMESPACE {

    namespace QDOC_CATCH_GENERATORS_TRAITS_NAMESPACE {

        /*!
         * Returns the type of the first element of Args.
         *
         * Args is expected to have at least one
         */
        template<typename... Args>
        using first_from_pack_t = std::tuple_element_t<0, std::tuple<Args...>>;

    } // end QDOC_CATCH_GENERATORS_TRAITS_NAMESPACE


    /*!
     * Builds an std::vector by moving \a movables into it.
     *
     * \a movables must be made of homogenous types.
     *
     * This function is intended to allow the construction of an
     * std::vector<T>, where T is a move only type, as an expression,
     * to lighten the idiom.
     *
     * For example, Catch's GeneratorWrapper<T> adapts a
     * std::unique_ptr, which is move only, making it impossible to
     * build a std::vector from them in place.
     *
     * Then, everywhere this is needed, a more complex approach of
     * generating the collection of objects, generating a vector of a
     * suitable size and iterating the objects to move-emplace them in
     * the vector is required.
     *
     * This not only complicates the code but is incompatible with a
     * GENERATE expression, making it extremely hard, noisy and error
     * prone to use them together.
     *
     * In those cases, then, a call to move_into_vector can be used as
     * an expression to circumvent the problem.
     */
    template<typename... MoveOnlyTypes>
    inline auto move_into_vector(MoveOnlyTypes... movables) {
        std::vector<QDOC_CATCH_GENERATORS_TRAITS_NAMESPACE::first_from_pack_t<MoveOnlyTypes...>>
            moved_into_vector;
        moved_into_vector.reserve(sizeof...(movables));

        (moved_into_vector.emplace_back(std::move(movables)), ...);

        return moved_into_vector;
    }

} // end QDOC_CATCH_GENERATORS_UTILITIES_ABSOLUTE_NAMESPACE
