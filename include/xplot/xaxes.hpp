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

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

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

        template <class S, class = enable_xscale_t<S>>
        xaxis(std::shared_ptr<S> ptr);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using axis = xw::xmaterialize<xaxis>;

    using axis_generator = xw::xgenerator<xaxis>;

    template <class T, class R = void>
    struct enable_xaxis
    {
        using type = std::enable_if_t<std::is_base_of<xaxis<T>, T>::value, R>;
    };

    template <class T, class R = void>
    using enable_xaxis_t = typename enable_xaxis<T, R>::type;

    /***************************
     * xcolor_axis declaration *
     ***************************/

    template <class D>
    class xcolor_axis : public xaxis<D>
    {
    public:

        using base_type = xaxis<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

    protected:

        template <class S>
        xcolor_axis(const xcolor_scale<S>&);

        template <class S>
        xcolor_axis(xcolor_scale<S>&&);

        template <class S, class = enable_xscale_t<S>>
        xcolor_axis(std::shared_ptr<S> ptr);

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
    inline void xaxis<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        xw::set_property_from_patch(orientation, patch, buffers);
        xw::set_property_from_patch(side, patch, buffers);
        xw::set_property_from_patch(label, patch, buffers);
        xw::set_property_from_patch(tick_format, patch, buffers);
        xw::set_property_from_patch(scale, patch, buffers);
        xw::set_property_from_patch(num_ticks, patch, buffers);
        xw::set_property_from_patch(tick_values, patch, buffers);
        xw::set_property_from_patch(offset, patch, buffers);
        xw::set_property_from_patch(label_location, patch, buffers);
        xw::set_property_from_patch(label_color, patch, buffers);
        xw::set_property_from_patch(grid_lines, patch, buffers);
        xw::set_property_from_patch(grid_color, patch, buffers);
        xw::set_property_from_patch(color, patch, buffers);
        xw::set_property_from_patch(label_offset, patch, buffers);
        xw::set_property_from_patch(visible, patch, buffers);
    }

    template <class D>
    inline void xaxis<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xw::set_patch_from_property(orientation, state, buffers);
        xw::set_patch_from_property(side, state, buffers);
        xw::set_patch_from_property(label, state, buffers);
        xw::set_patch_from_property(tick_format, state, buffers);
        xw::set_patch_from_property(scale, state, buffers);
        xw::set_patch_from_property(num_ticks, state, buffers);
        xw::set_patch_from_property(tick_values, state, buffers);
        xw::set_patch_from_property(offset, state, buffers);
        xw::set_patch_from_property(label_location, state, buffers);
        xw::set_patch_from_property(label_color, state, buffers);
        xw::set_patch_from_property(grid_lines, state, buffers);
        xw::set_patch_from_property(grid_color, state, buffers);
        xw::set_patch_from_property(color, state, buffers);
        xw::set_patch_from_property(label_offset, state, buffers);
        xw::set_patch_from_property(visible, state, buffers);
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
    template <class S, class>
    inline xaxis<D>::xaxis(std::shared_ptr<S> s)
        : base_type()
    {
        set_defaults();

        this->scale() = s;
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
    inline void xcolor_axis<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
    }

    template <class D>
    inline void xcolor_axis<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
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
    template <class S, class>
    inline xcolor_axis<D>::xcolor_axis(std::shared_ptr<S> s)
        : base_type(s)
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
