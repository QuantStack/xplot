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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

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
    inline void xtooltip<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
        xw::set_property_from_patch(fields, patch, buffers);
        xw::set_property_from_patch(formats, patch, buffers);
        xw::set_property_from_patch(labels, patch, buffers);
        xw::set_property_from_patch(show_labels, patch, buffers);
    }

    template <class D>
    inline void xtooltip<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
        xw::set_patch_from_property(fields, state, buffers);
        xw::set_patch_from_property(formats, state, buffers);
        xw::set_patch_from_property(labels, state, buffers);
        xw::set_patch_from_property(show_labels, state, buffers);
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
