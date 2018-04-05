/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_AXES_HPP
#define XPLOT_AXES_HPP

#include <string>
#include <utility>
#include <vector>

#include "xtl/xoptional.hpp"

#include "xwidgets/xeither.hpp"

#include "xplot.hpp"
#include "xscales.hpp"
#include "xinteracts.hpp"

namespace xpl
{
    /********************
     * axis declaration *
     ********************/

    template <class D>
    class xaxis : public xplot<D>
    {
    public:

        using base_type = xplot<D>;
        using derived_type = D;

        using scale_type = xw::xholder<xscale>;
        using tick_values_type = std::vector<double>;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(std::string, derived_type, orientation, "horizontal", XEITHER("horizontal", "vertical"));
        XPROPERTY(xtl::xoptional<std::string>, derived_type, side, xtl::missing<std::string>(), XEITHER_OPTIONAL("bottom", "top", "left", "right"));
        XPROPERTY(std::string, derived_type, label, "");
        XPROPERTY(std::string, derived_type, grid_lines, "solid", XEITHER("none", "solid", "dashed"));
        XPROPERTY(xtl::xoptional<std::string>, derived_type, tick_format);
        XPROPERTY(scale_type, derived_type, scale);
        XPROPERTY(xtl::xoptional<int>, derived_type, num_ticks);
        XPROPERTY(::xeus::xjson, derived_type, tick_values, xeus::xjson::array());
        XPROPERTY(::xeus::xjson, derived_type, offset, ::xeus::xjson::object());
        XPROPERTY(std::string, derived_type, label_location, "middle", XEITHER("middle", "start", "end"));
        XPROPERTY(xtl::xoptional<color_type>, derived_type, label_color);
        XPROPERTY(xtl::xoptional<color_type>, derived_type, grid_color);
        XPROPERTY(xtl::xoptional<color_type>, derived_type, color);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, label_offset);
        XPROPERTY(bool, derived_type, visible, true);

    protected:

        template <class S>
        xaxis(const xscale<S>&);

        template <class S>
        xaxis(xscale<S>&&);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using axis = xw::xmaterialize<xaxis>;

    using axis_generator = xw::xgenerator<xaxis>;

    /***************************
     * xcolor_axis declaration *
     ***************************/

    template <class D>
    class xcolor_axis : public xaxis<D>
    {
    public:

        using base_type = xaxis<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

    protected:

        template <class S>
        xcolor_axis(const xcolor_scale<S>&);

        template <class S>
        xcolor_axis(xcolor_scale<S>&&);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using color_axis = xw::xmaterialize<xcolor_axis>;

    using color_axis_generator = xw::xgenerator<xcolor_axis>;

    /***********************
     * axis implementation *
     ***********************/

    template <class D>
    inline void xaxis<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(orientation, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(side, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(label, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(tick_format, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(scale, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(num_ticks, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(tick_values, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(offset, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(label_location, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(label_color, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(grid_lines, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(grid_color, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(color, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(label_offset, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(visible, patch);
    }

    template <class D>
    inline xeus::xjson xaxis<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(orientation, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(side, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(label, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(tick_format, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(scale, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(num_ticks, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(tick_values, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(offset, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(label_location, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(label_color, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(grid_lines, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(grid_color, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(color, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(label_offset, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(visible, state);
        return state;
    }

    template <class D>
    template <class S>
    inline xaxis<D>::xaxis(const xscale<S>& s)
        : base_type()
    {
        set_defaults();

        this->scale() = s;
    }

    template <class D>
    template <class S>
    inline xaxis<D>::xaxis(xscale<S>&& s)
        : base_type()
    {
        set_defaults();

        this->scale() = std::move(s);
    }

    template <class D>
    inline void xaxis<D>::set_defaults()
    {
        this->_model_name() = "AxisModel";
        this->_view_name() = "Axis";
    }

    /******************************
     * xcolor_axis implementation *
     ******************************/

    template <class D>
    inline void xcolor_axis<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
    }

    template <class D>
    inline xeus::xjson xcolor_axis<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();
        return state;
    }

    template <class D>
    template <class S>
    inline xcolor_axis<D>::xcolor_axis(const xcolor_scale<S>& s)
        : base_type(s)
    {
        set_defaults();
    }

    template <class D>
    template <class S>
    inline xcolor_axis<D>::xcolor_axis(xcolor_scale<S>&& s)
        : base_type(std::move(s))
    {
        set_defaults();
    }

    template <class D>
    inline void xcolor_axis<D>::set_defaults()
    {
        this->_view_name() = "ColorAxis";
        this->_model_name() = "ColorAxisModel";
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xpl::xaxis>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xaxis>>;
    extern template class xw::xgenerator<xpl::xaxis>;
    extern template class xw::xtransport<xw::xgenerator<xpl::xaxis>>;

    extern template class xw::xmaterialize<xpl::xcolor_axis>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xcolor_axis>>;
    extern template class xw::xgenerator<xpl::xcolor_axis>;
    extern template class xw::xtransport<xw::xgenerator<xpl::xcolor_axis>>;
#endif

#endif
