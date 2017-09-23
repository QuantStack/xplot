/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XBOXED_CONTAINER_HPP
#define XBOXED_CONTAINER_HPP

#include <string>

#include "xeus/xjson.hpp"

namespace xpl
{

    /********************************
     * xboxed_container declaration *
     ********************************/

    template <class C>
    class xboxed_container
    {
    public:

        using container_type = C;
        using reference = container_type&;
        using const_reference = const container_type&;

        xboxed_container() = default;
        ~xboxed_container() = default;

        xboxed_container(const xboxed_container&) = default;
        xboxed_container(xboxed_container&&) = default;

        xboxed_container& operator=(const xboxed_container&) = default;
        xboxed_container& operator=(xboxed_container&&) = default;

        xboxed_container(const_reference c);
        xboxed_container(container_type&& c);

        xboxed_container& operator=(const_reference c);
        xboxed_container& operator=(container_type&& c);

        operator reference() noexcept;
        operator const_reference() const noexcept;

    private:

        container_type m_container;
    };

    template <class C>
    void to_json(xeus::xjson& j, const xboxed_container<C>& o);
    template <class C>
    void from_json(const xeus::xjson& j, xboxed_container<C>& o);

    template<class T>
    std::string type_to_string() noexcept;

    /***********************************
     * xboxed_container implementation *
     ***********************************/

    template <class C>
    inline xboxed_container<C>::xboxed_container(const_reference c)
        : m_container(c)
    {
    }

    template <class C>
    inline xboxed_container<C>::xboxed_container(container_type&& c)
        : m_container(std::move(c))
    {
    }

    template <class C>
    inline xboxed_container<C>& xboxed_container<C>::operator=(const_reference c)
    {
        m_container = c;
        return *this;
    }

    template <class C>
    inline xboxed_container<C>& xboxed_container<C>::operator=(container_type&& c)
    {
        m_container = std::move(c);
        return *this;
    }

    template <class C>
    inline xboxed_container<C>::operator reference() noexcept
    {
        return m_container;
    }

    template <class C>
    inline xboxed_container<C>::operator const_reference() const noexcept
    {
        return m_container;
    }

    template <class C>
    inline void to_json(xeus::xjson& j, const xboxed_container<C>& o)
    {
        using container_type = typename xboxed_container<C>::container_type;
        j["values"] = container_type(o);
        j["type"] = type_to_string<typename container_type::value_type>();
    }

    template <class C>
    inline void from_json(const xeus::xjson& j, xboxed_container<C>& o)
    {
    }

    template<>
    inline std::string type_to_string<double>() noexcept
    {
        return "float";
    }

    template<>
    inline std::string type_to_string<std::vector<double>>() noexcept
    {
        return "float";
    }
}

#endif