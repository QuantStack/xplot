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

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xobject.hpp"

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

        xplot();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

    private:

        void set_defaults();
    };

    /************************
     * xplot implementation *
     ************************/

    template <class D>
    inline xplot<D>::xplot()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xplot<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
    }

    template <class D>
    inline xeus::xjson xplot<D>::get_state() const
    {
        return base_type::get_state();
    }

    template <class D>
    inline void xplot<D>::set_defaults()
    {
        this->_model_module() = "bqplot";
        this->_model_module_version() = "^0.3.0-alpha.6";
        this->_view_module() = "bqplot";
        this->_view_module_version() = "^0.3.0-alpha.6";
    }
}

#endif
