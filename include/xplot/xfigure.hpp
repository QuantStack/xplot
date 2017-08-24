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

#include "xwidgets/xholder_id.hpp"
#include "xwidgets/xwidget.hpp"

#include "xaxes.hpp"
#include "xmarks.hpp"
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

        xfigure();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(std::string, derived_type, title);
        XPROPERTY(axes_type, derived_type, axes);
        XPROPERTY(marks_type, derived_type, marks);
        //XPROPERTY(::xeus::xjson, derived_type, interaction);
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
        XPROPERTY(X_CASELESS_STR_ENUM(top-right, top, top-left, left, bottom-left, bottom, bottom-right, right), derived_type, legend_location, "top-right");
        XPROPERTY(int, derived_type, animation);

    private:

        void set_defaults();
    };

    using figure = xw::xmaterialize<xfigure>;

    /**************************
     * xfigure implementation *
     **************************/

    template <class D>
    inline xfigure<D>::xfigure()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xfigure<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(title, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(axes, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(marks, patch);
        //XOBJECT_SET_PROPERTY_FROM_PATCH(interaction, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(scale_x, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(scale_y, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(title_style, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(background_style, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(min_aspect_ratio, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(max_aspect_ratio, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(fig_margin, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(padding_x, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(padding_y, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(legend_location, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(animation, patch);
    }

    template <class D>
    inline xeus::xjson xfigure<D>::get_state() const
    {
        xeus::xjson state =  base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(title, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(axes, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(marks, state);
        //XOBJECT_SET_PATCH_FROM_PROPERTY(interaction, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(scale_x, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(scale_y, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(title_style, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(background_style, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(min_aspect_ratio, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(max_aspect_ratio, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(fig_margin, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(padding_x, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(padding_y, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(legend_location, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(animation, state);

        return state;
    }

    template <class D>
    inline void xfigure<D>::set_defaults()
    {
        this->_model_name() = "FigureModel";
        this->_model_module() = "bqplot";
        this->_view_name() = "Figure";
        this->_view_module() = "bqplot";

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
}

#endif
