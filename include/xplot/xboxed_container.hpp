/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XBOXED_CONTAINER_HPP
#define XBOXED_CONTAINER_HPP

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "nlohmann/json.hpp"

#include "xeus/xjson.hpp"

namespace nl = nlohmann;

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
        template <class T>
        xboxed_container(const T& c);
        xboxed_container(container_type&& c);

        xboxed_container& operator=(const_reference c);
        xboxed_container& operator=(container_type&& c);
        template <class T>
        xboxed_container& operator=(const T& c);

        operator reference() noexcept;
        operator const_reference() const noexcept;

    private:

        container_type m_container;
    };

    template <class C>
    void to_json(nl::json& j, const xboxed_container<C>& o);
    template <class C>
    void from_json(const nl::json& j, xboxed_container<C>& o);

    template <class T>
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
    template <class T>
    inline xboxed_container<C>::xboxed_container(const T& c)
        : m_container(c.begin(), c.end())
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
    template <class T>
    inline xboxed_container<C>& xboxed_container<C>::operator=(const T& c)
    {
        m_container.resize(c.size());
        std::copy(c.begin(), c.end(), m_container.begin());
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
    inline void to_json(nl::json& j, const xboxed_container<C>& o)
    {
        using container_type = typename xboxed_container<C>::container_type;
        j["values"] = container_type(o);
        j["type"] = type_to_string<typename container_type::value_type>();
    }

    template <class C>
    inline void from_json(const nl::json& j, xboxed_container<C>& o)
    {
        using container_type = typename xboxed_container<C>::container_type;
        container_type& values = o;
        values = j.at("values").get<container_type>();
    }

    template <>
    inline std::string type_to_string<double>() noexcept
    {
        return "float";
    }

    template <>
    inline std::string type_to_string<std::vector<double>>() noexcept
    {
        return "float";
    }

    template <>
    inline std::string type_to_string<std::string>() noexcept
    {
        return "<U5";
    }
}

#endif
