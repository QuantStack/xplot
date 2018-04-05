/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_TOOLBAR_HPP
#define XPLOT_TOOLBAR_HPP

#include <utility>

#include "xtl/xoptional.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xfigure.hpp"
#include "xinteracts.hpp"

namespace xpl
{
    template <class D>
    class xfigure;

    /************************
     * xtoolbar declaration *
     ************************/

    template <class D>
    class xtoolbar : public xw::xwidget<D>
    {
    public:

        using base_type = xw::xwidget<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(xw::xholder<xfigure>, derived_type, figure);
        XPROPERTY(bool, derived_type, panning);
        XPROPERTY(xtl::xoptional<xw::xmaterialize<xpan_zoom>>, derived_type, panzoom);

    protected:

        template <class S>
        xtoolbar(const xfigure<S>&);

        template <class S>
        xtoolbar(xfigure<S>&&);

        using base_type::base_type;

    private:

        void set_defaults();

        static int register_panzoom();
    };

    using toolbar = xw::xmaterialize<xtoolbar>;

    using toolbar_generator = xw::xgenerator<xtoolbar>;

    /***************************
     * xtoolbar implementation *
     ***************************/

    template <class D>
    inline void xtoolbar<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(figure, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(panning, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(panzoom, patch);
    }

    template <class D>
    inline xeus::xjson xtoolbar<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();
        XOBJECT_SET_PATCH_FROM_PROPERTY(figure, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(panning, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(panzoom, state);
        return state;
    }

    template <class D>
    template <class S>
    inline xtoolbar<D>::xtoolbar(const xfigure<S>& fig)
        : base_type()
    {
        static int init = register_panzoom();
        set_defaults();
        this->figure() = fig;
    }

    template <class D>
    template <class S>
    inline xtoolbar<D>::xtoolbar(xfigure<S>&& fig)
        : base_type()
    {
        set_defaults();
        this->figure() = std::move(fig);
    }

    template <class D>
    inline void xtoolbar<D>::set_defaults()
    {
        this->_view_name() = "Toolbar";
        this->_model_module() = "bqplot";
        this->_model_module_version() = "^0.3.0";
        this->_model_name() = "ToolbarModel";
        this->_view_module() = "bqplot";
        this->_view_module_version() = "^0.3.0";
    }

    template <class D>
    inline int xtoolbar<D>::register_panzoom()
    {
        xw::get_xfactory().register_maker("bqplot",
                                          "PanZoomModel",
                                          "bqplot",
                                          "PanZoom",
                                          xw::xmaker<xpan_zoom>);
        return 0;
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xpl::xtoolbar>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xtoolbar>>;
    extern template class xw::xgenerator<xpl::xtoolbar>;
    extern template class xw::xtransport<xw::xgenerator<xpl::xtoolbar>>;
#endif

#endif
