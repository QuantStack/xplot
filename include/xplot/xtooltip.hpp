/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_DEFAULT_TOOLTIP_HPP
#define XPLOT_DEFAULT_TOOLTIP_HPP

#include <string>
#include <vector>

#include "xwidgets/xwidget.hpp"

#include "xplot_config.hpp"

namespace xpl
{
    /************************
     * xtooltip declaration *
     ************************/

    template <class D>
    class xtooltip : public xw::xwidget<D>
    {
    public:

        using base_type = xw::xwidget<D>;
        using derived_type = D;

        using data_type = std::vector<xtl::xoptional<std::string>>;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(data_type, derived_type, fields);
        XPROPERTY(data_type, derived_type, formats);
        XPROPERTY(data_type, derived_type, labels);
        XPROPERTY(bool, derived_type, show_labels, true);

    protected:

        xtooltip();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using tooltip = xw::xmaterialize<xtooltip>;

    using tooltip_generator = xw::xgenerator<xtooltip>;

    /***************************
     * xtooltip implementation *
     ***************************/

    template <class D>
    inline void xtooltip<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(fields, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(formats, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(labels, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(show_labels, patch);
    }

    template <class D>
    inline xeus::xjson xtooltip<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();
        XOBJECT_SET_PATCH_FROM_PROPERTY(fields, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(formats, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(labels, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(show_labels, state);

        return state;
    }

    template <class D>
    inline xtooltip<D>::xtooltip()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xtooltip<D>::set_defaults()
    {
        this->_view_name() = "Tooltip";
        this->_model_module() = "bqplot";
        this->_model_module_version() = XBQPLOT_VERSION;
        this->_model_name() = "TooltipModel";
        this->_view_module() = "bqplot";
        this->_view_module_version() = XBQPLOT_VERSION;
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xpl::xtooltip>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xtooltip>>;
    extern template xw::xmaterialize<xpl::xtooltip>::xmaterialize();
    extern template class xw::xgenerator<xpl::xtooltip>;
    extern template xw::xgenerator<xpl::xtooltip>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xpl::xtooltip>>;
#endif

#endif
