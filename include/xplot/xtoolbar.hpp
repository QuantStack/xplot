/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_TOOLBAR_HPP
#define XPLOT_TOOLBAR_HPP

#include "xwidgets/xholder_id.hpp"
#include "xwidgets/xwidget.hpp"

#include "xfigure.hpp"
#include "xinteracts.hpp"

namespace xpl
{
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
        XPROPERTY(xw::xholder<xpan_zoom>, derived_type, panzoom);

    protected:

        xtoolbar();

    private:

        void set_defaults();
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
    inline xtoolbar<D>::xtoolbar()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xtoolbar<D>::set_defaults()
    {
        this->_view_name() = "Toolbar";
        this->_model_module() = "bqplot";
        this->_model_module_version() = "^0.3.0-alpha.6";
        this->_model_name() = "ToolbarModel";
        this->_view_module() = "bqplot";
        this->_view_module_version() = "^0.3.0-alpha.6";
    }
}
#endif
