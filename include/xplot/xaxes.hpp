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

#include "nlohmann/json.hpp"

#include "xtl/xoptional.hpp"

#include "xwidgets/xeither.hpp"

#include "xplot.hpp"
#include "xscales.hpp"
#include "xinteracts.hpp"

namespace nl = nlohmann;

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

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, orientation, "horizontal", XEITHER("horizontal", "vertical"));
        XPROPERTY(xtl::xoptional<std::string>, derived_type, side, xtl::missing<std::string>(), XEITHER_OPTIONAL("bottom", "top", "left", "right"));
        XPROPERTY(std::string, derived_type, label, "");
        XPROPERTY(std::string, derived_type, grid_lines, "solid", XEITHER("none", "solid", "dashed"));
        XPROPERTY(xtl::xoptional<std::string>, derived_type, tick_format);
        XPROPERTY(scale_type, derived_type, scale);
        XPROPERTY(xtl::xoptional<int>, derived_type, num_ticks);
        XPROPERTY(::nl::json, derived_type, tick_values, nl::json::array());
        XPROPERTY(::nl::json, derived_type, offset, ::nl::json::object());
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

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

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

    /***********************
     * axis implementation *
     ***********************/

    template <class D>
    inline void xaxis<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(orientation, patch, buffers);
        set_property_from_patch(side, patch, buffers);
        set_property_from_patch(label, patch, buffers);
        set_property_from_patch(tick_format, patch, buffers);
        set_property_from_patch(scale, patch, buffers);
        set_property_from_patch(num_ticks, patch, buffers);
        set_property_from_patch(tick_values, patch, buffers);
        set_property_from_patch(offset, patch, buffers);
        set_property_from_patch(label_location, patch, buffers);
        set_property_from_patch(label_color, patch, buffers);
        set_property_from_patch(grid_lines, patch, buffers);
        set_property_from_patch(grid_color, patch, buffers);
        set_property_from_patch(color, patch, buffers);
        set_property_from_patch(label_offset, patch, buffers);
        set_property_from_patch(visible, patch, buffers);
    }

    template <class D>
    inline void xaxis<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(orientation, state["orientation"], buffers);
        xwidgets_serialize(side, state["side"], buffers);
        xwidgets_serialize(label, state["label"], buffers);
        xwidgets_serialize(tick_format, state["tick_format"], buffers);
        // xwidgets_serialize(scale, state["scale"], buffers);
        xwidgets_serialize(num_ticks, state["num_ticks"], buffers);
        xwidgets_serialize(tick_values, state["tick_values"], buffers);
        xwidgets_serialize(offset, state["offset"], buffers);
        xwidgets_serialize(label_location, state["label_location"], buffers);
        xwidgets_serialize(label_color, state["label_color"], buffers);
        xwidgets_serialize(grid_lines, state["grid_lines"], buffers);
        xwidgets_serialize(grid_color, state["grid_color"], buffers);
        xwidgets_serialize(color, state["color"], buffers);
        xwidgets_serialize(label_offset, state["label_offset"], buffers);
        xwidgets_serialize(visible, state["visible"], buffers);
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
    inline void xcolor_axis<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
    }

    template <class D>
    inline void xcolor_axis<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
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

    extern template class xw::xmaterialize<xpl::xcolor_axis>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xcolor_axis>>;
#endif

#endif
