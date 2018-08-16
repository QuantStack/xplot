/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_FIGURE_HPP
#define XPLOT_FIGURE_HPP

#include <string>
#include <vector>
#include <utility>

#include "xwidgets/xeither.hpp"
#include "xwidgets/xwidget.hpp"

#include "xaxes.hpp"
#include "xmarks.hpp"
#include "xplot_config.hpp"
#include "xscales.hpp"

namespace xpl
{
    /***********************
     * xfigure declaration *
     ***********************/

    template <class D>
    class xfigure : public xw::xwidget<D>
    {
    public:

        using base_type = xw::xwidget<D>;
        using derived_type = D;

        using axes_type = std::vector<xw::xholder<xaxis>>;
        using marks_type = std::vector<xw::xholder<xmark>>;
        using scales_type = xw::xholder<xscale>;
        using interaction_type = xw::xholder<xinteraction>;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, title);
        XPROPERTY(axes_type, derived_type, axes);
        XPROPERTY(marks_type, derived_type, marks);
        XPROPERTY(xtl::xoptional<interaction_type>, derived_type, interaction);
        XPROPERTY(scales_type, derived_type, scale_x);
        XPROPERTY(scales_type, derived_type, scale_y);
        XPROPERTY(::xeus::xjson, derived_type, title_style);
        XPROPERTY(::xeus::xjson, derived_type, background_style);
        XPROPERTY(double, derived_type, min_aspect_ratio, 1.);
        XPROPERTY(double, derived_type, max_aspect_ratio, 6.);
        XPROPERTY(::xeus::xjson, derived_type, fig_margin, xeus::xjson({
           {"top", 60}, {"bottom", 60}, {"left", 60}, {"right", 60}
        }));
        XPROPERTY(double, derived_type, padding_x, 0.);
        XPROPERTY(double, derived_type, padding_y, 0.025);
        XPROPERTY(std::string, derived_type, legend_location, "top-right", XEITHER("top-right", "top", "top-left", "left", "bottom-left", "bottom", "bottom-right", "right"));
        XPROPERTY(int, derived_type, animation_duration);

        template <class T>
        void add_mark(const xmark<T>& w);

        template <class T>
        void add_mark(xmark<T>&& w);

        template <class T>
        enable_xmark_t<T> add_mark(std::shared_ptr<T> w);

        template <class T>
        void remove_mark(const xmark<T>& w);

        void clear_marks();

        template <class T>
        void add_axis(const xaxis<T>& w);

        template <class T>
        void add_axis(xaxis<T>&& w);

        template <class T>
        enable_xaxis_t<T> add_axis(std::shared_ptr<T> w);

        template <class T>
        void remove_axis(const xaxis<T>& w);

        void clear_axes();

    protected:

        xfigure();

        using base_type::base_type;

    private:

        void set_defaults();
        void send_marks_patch() const;
        void send_axes_patch() const;
    };

    using figure = xw::xmaterialize<xfigure>;

    using figure_generator = xw::xgenerator<xfigure>;

    template <class T, class R = void>
    struct enable_xfigure
    {
        using type = std::enable_if_t<std::is_base_of<xfigure<T>, T>::value, R>;
    };

    template <class T, class R = void>
    using enable_xfigure_t = typename enable_xfigure<T, R>::type;

    /**************************
     * xfigure implementation *
     **************************/

    template <class D>
    inline void xfigure<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(title, patch, buffers);
        set_property_from_patch(axes, patch, buffers);
        set_property_from_patch(marks, patch, buffers);
        set_property_from_patch(interaction, patch, buffers);
        set_property_from_patch(scale_x, patch, buffers);
        set_property_from_patch(scale_y, patch, buffers);
        set_property_from_patch(title_style, patch, buffers);
        set_property_from_patch(background_style, patch, buffers);
        set_property_from_patch(min_aspect_ratio, patch, buffers);
        set_property_from_patch(max_aspect_ratio, patch, buffers);
        set_property_from_patch(fig_margin, patch, buffers);
        set_property_from_patch(padding_x, patch, buffers);
        set_property_from_patch(padding_y, patch, buffers);
        set_property_from_patch(legend_location, patch, buffers);
        set_property_from_patch(animation_duration, patch, buffers);
    }

    template <class D>
    inline void xfigure<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        using xw::set_patch_from_property;
        base_type::serialize_state(state, buffers);

        set_patch_from_property(title, state, buffers);
        set_patch_from_property(axes, state, buffers);
        set_patch_from_property(marks, state, buffers);
        set_patch_from_property(interaction, state, buffers);
        set_patch_from_property(scale_x, state, buffers);
        set_patch_from_property(scale_y, state, buffers);
        set_patch_from_property(title_style, state, buffers);
        set_patch_from_property(background_style, state, buffers);
        set_patch_from_property(min_aspect_ratio, state, buffers);
        set_patch_from_property(max_aspect_ratio, state, buffers);
        set_patch_from_property(fig_margin, state, buffers);
        set_patch_from_property(padding_x, state, buffers);
        set_patch_from_property(padding_y, state, buffers);
        set_patch_from_property(legend_location, state, buffers);
        set_patch_from_property(animation_duration, state, buffers);
    }

    template <class D>
    template <class T>
    inline void xfigure<D>::add_mark(const xmark<T>& w)
    {
        this->marks().emplace_back(xw::make_id_holder<xmark>(w.id()));
        send_marks_patch();
    }

    template <class D>
    template <class T>
    inline void xfigure<D>::add_mark(xmark<T>&& w)
    {
        this->marks().emplace_back(xw::make_owning_holder(std::move(w)));
        send_marks_patch();
    }

    template <class D>
    template <class T>
    inline enable_xmark_t<T> xfigure<D>::add_mark(std::shared_ptr<T> w)
    {
        this->marks().emplace_back(xw::make_shared_holder<xmark, T>(w));
        send_marks_patch();
    }

    template <class D>
    template <class T>
    inline void xfigure<D>::remove_mark(const xmark<T>& w)
    {
        this->marks().erase(
            std::remove_if(
                this->marks().begin(), this->marks().end(),
                [&w](const xw::xholder<xmark>& element) {
                    return element.id() == w.id();
                }
            ),
            this->marks().end()
        );
        send_marks_patch();
    }

    template <class D>
    inline void xfigure<D>::clear_marks()
    {
        this->marks() = {};
        send_marks_patch();
    }

    template <class D>
    template <class T>
    inline void xfigure<D>::add_axis(const xaxis<T>& w)
    {
        this->axes().emplace_back(xw::make_id_holder<xaxis>(w.id()));
        send_axes_patch();
    }

    template <class D>
    template <class T>
    inline void xfigure<D>::add_axis(xaxis<T>&& w)
    {
        this->axes().emplace_back(xw::make_owning_holder(std::move(w)));
        send_axes_patch();
    }

    template <class D>
    template <class T>
    inline enable_xaxis_t<T> xfigure<D>::add_axis(std::shared_ptr<T> w)
    {
        this->axes().emplace_back(xw::make_shared_holder<xaxis, T>(w));
        send_axes_patch();
    }

    template <class D>
    template <class T>
    inline void xfigure<D>::remove_axis(const xaxis<T>& w)
    {
        this->axes().erase(
            std::remove_if(
                this->axes().begin(), this->axes().end(),
                [&w](const xw::xholder<xaxis>& element) {
                    return element.id() == w.id();
                }
            ),
            this->axes().end()
        );
        send_axes_patch();
    }

    template <class D>
    inline void xfigure<D>::clear_axes()
    {
        this->axes() = {};
        send_axes_patch();
    }

    template <class D>
    inline xfigure<D>::xfigure()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xfigure<D>::set_defaults()
    {
        this->_model_name() = "FigureModel";
        this->_model_module() = "bqplot";
        this->_view_name() = "Figure";
        this->_view_module() = "bqplot";
        this->_model_module_version() = XBQPLOT_VERSION;
        this->_view_module_version() = XBQPLOT_VERSION;

        linear_scale sx;
        sx.min = 0.0;
        sx.max = 1.0;
        sx.allow_padding = false;

        linear_scale sy;
        sy.min = 0.0;
        sy.max = 1.0;
        sy.allow_padding = false;

        this->scale_x() = std::move(sx);
        this->scale_y() = std::move(sy);
    }

    template <class D>
    inline void xfigure<D>::send_marks_patch() const
    {
        using xw::set_patch_from_property;
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        set_patch_from_property(marks, state, buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }

    template <class D>
    inline void xfigure<D>::send_axes_patch() const
    {
        using xw::set_patch_from_property;
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        set_patch_from_property(axes, state, buffers);
        this->send_patch(std::move(state), std::move(buffers));
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xpl::xfigure>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xfigure>>;
    extern template xw::xmaterialize<xpl::xfigure>::xmaterialize();
    extern template class xw::xgenerator<xpl::xfigure>;
    extern template xw::xgenerator<xpl::xfigure>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xpl::xfigure>>;
#endif

#endif
