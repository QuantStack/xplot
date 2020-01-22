/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_PLOT_HPP
#define XPLOT_PLOT_HPP

#include <string>

#include "nlohmann/json.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xobject.hpp"

#include "xplot_config.hpp"

namespace nl = nlohmann;

namespace xpl
{
    using color_type = std::string;

    /*********************
     * xplot declaration *
     *********************/

    template <class D>
    class xplot : public xw::xobject<D>
    {
    public:

        using base_type = xw::xobject<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

    protected:

        xplot();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    /************************
     * xplot implementation *
     ************************/

    template <class D>
    inline void xplot<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
    }

    template <class D>
    inline void xplot<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
    }

    template <class D>
    inline xplot<D>::xplot()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xplot<D>::set_defaults()
    {
        this->_model_module() = "bqplot";
        this->_model_module_version() = bqplot_semver();
        this->_view_module() = "bqplot";
        this->_view_module_version() = bqplot_semver();
    }
}

#endif
