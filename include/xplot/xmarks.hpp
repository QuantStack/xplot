/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_MARKS_HPP
#define XPLOT_MARKS_HPP

#include <fstream>
#include <list>
#include <map>
#include <streambuf>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

#include "xproperty/xjson.hpp"

#include "xtl/xoptional.hpp"

#include "xwidgets/xeither.hpp"
#include "xwidgets/xwidget.hpp"

#include "xboxed_container.hpp"
#include "xmaps_config.hpp"
#include "xplot.hpp"
#include "xscales.hpp"

namespace nl = nlohmann;

namespace xpl
{
    inline const std::vector<color_type>& category10()
    {
        static const std::vector<color_type> category = {
            "#1f77b4",
            "#ff7f0e",
            "#2ca02c",
            "#d62728",
            "#9467bd",
            "#8c564b",
            "#e377c2",
            "#7f7f7f",
            "#bcbd22",
            "#17becf"};
        return category;
    }

    inline const std::string topo_load(const std::string& mapname)
    {
        std::string output = XPLOT_MAPS_DIR;
        output += mapname;
        return output;
    }

    /*********************
     * xmark declaration *
     *********************/

    using xmark_scales_type = std::map<std::string, xw::xholder<xscale>>;
    using xmark_tooltip_type = xw::xholder<xw::xwidget>;

    template <class D>
    class xmark : public xplot<D>
    {
    public:

        using base_type = xplot<D>;
        using derived_type = D;

        using scales_type = xmark_scales_type;
        using preserve_domain_type = std::map<std::string, bool>;
        using labels_type = std::vector<std::string>;
        using selected_type = xtl::xoptional<std::vector<int>>;
        using tooltip_type = xtl::xoptional<xmark_tooltip_type>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(scales_type, derived_type, scales);
        XPROPERTY(::nl::json, derived_type, scales_metadata);
        XPROPERTY(preserve_domain_type, derived_type, preserve_domain);
        XPROPERTY(bool, derived_type, display_legend);
        XPROPERTY(labels_type, derived_type, labels);
        XPROPERTY(bool, derived_type, apply_clip, true);
        XPROPERTY(bool, derived_type, visible, true);
        XPROPERTY(::nl::json, derived_type, selected_style, ::nl::json::object());
        XPROPERTY(::nl::json, derived_type, unselected_style, ::nl::json::object());
        XPROPERTY(selected_type, derived_type, selected);
        XPROPERTY(tooltip_type, derived_type, tooltip);
        XPROPERTY(::nl::json, derived_type, tooltip_style, ::nl::json::parse(R"({"opacity": "0.9"})"));
        XPROPERTY(bool, derived_type, enable_hover, true);
        XPROPERTY(::nl::json, derived_type, interactions, ::nl::json::parse(R"({"hover": "tooltip"})"));
        XPROPERTY(std::string, derived_type, tooltip_location, "mouse", XEITHER("mouse", "center"));

    protected:

        xmark();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    template <class T, class R = void>
    struct enable_xmark
    {
        using type = std::enable_if_t<std::is_base_of<xmark<T>, T>::value, R>;
    };

    template <class T, class R = void>
    using enable_xmark_t = typename enable_xmark<T, R>::type;

    /**********************
     * xlines declaration *
     **********************/

    template <class D>
    class xlines : public xmark<D>
    {
    public:

        using base_type = xmark<D>;
        using derived_type = D;

        using data_type = xboxed_container<std::vector<double>>;
        using colors_type = std::vector<color_type>;
        using opacities_type = std::vector<double>;
        using curves_subset_type = std::vector<int>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(data_type, derived_type, x);
        XPROPERTY(data_type, derived_type, y);
        XPROPERTY(colors_type, derived_type, color);
        XPROPERTY(colors_type, derived_type, colors, category10());
        XPROPERTY(colors_type, derived_type, fill_colors);
        XPROPERTY(double, derived_type, stroke_width, 2.0);
        XPROPERTY(std::string, derived_type, labels_visibility, "none", XEITHER("none", "labels"));
        XPROPERTY(curves_subset_type, derived_type, curves_subset);
        XPROPERTY(std::string, derived_type, line_style, "solid", XEITHER("solid", "dashed", "dotted", "dash_dotted"));
        XPROPERTY(std::string, derived_type, interpolation, "linear", XEITHER("linear", "basis", "basis-open", "basis-closed", "bundle", "cardinal", "cardinal-open", "cardinal-closed", "monotone", "step-before", "step-after"));
        XPROPERTY(bool, derived_type, close_path, false);
        XPROPERTY(std::string, derived_type, fill, "none", XEITHER("none", "bottom", "top", "inside"));
        XPROPERTY(xtl::xoptional<std::string>, derived_type, marker, {}, XEITHER_OPTIONAL("circle", "cross", "diamond", "square", "triangle-down", "triangle-up", "arrow", "rectangle", "ellipse"));
        XPROPERTY(int, derived_type, marker_size, 64);
        XPROPERTY(opacities_type, derived_type, opacities);
        XPROPERTY(opacities_type, derived_type, fill_opacities);

    protected:

        template <class XS, class YS>
        xlines(XS&&, YS&&);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using lines = xw::xmaterialize<xlines>;

    /*****************************
     * xscatter_base declaration *
     *****************************/

    template <class D>
    class xscatter_base : public xmark<D>
    {
    public:

        using base_type = xmark<D>;
        using derived_type = D;

        using data_type = xboxed_container<std::vector<double>>;
        using colors_type = std::vector<xtl::xoptional<color_type>>;
        using selected_type = std::vector<int>;

        using callback_type = std::function<void(const nl::json&)>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        void on_drag_start(callback_type);
        void on_drag(callback_type);
        void on_drag_end(callback_type);
        void handle_custom_message(const nl::json&);

        XPROPERTY(data_type, derived_type, x);
        XPROPERTY(data_type, derived_type, y);
        XPROPERTY(data_type, derived_type, color);
        XPROPERTY(data_type, derived_type, opacity);
        XPROPERTY(data_type, derived_type, size);
        XPROPERTY(data_type, derived_type, rotation);
        XPROPERTY(std::vector<double>, derived_type, default_opacities);
        XPROPERTY(::nl::json, derived_type, hovered_style);
        XPROPERTY(::nl::json, derived_type, unhovered_style);
        XPROPERTY(xtl::xoptional<int>, derived_type, hovered_point);
        XPROPERTY(bool, derived_type, enable_move);
        XPROPERTY(bool, derived_type, enable_delete);
        XPROPERTY(bool, derived_type, restrict_x);
        XPROPERTY(bool, derived_type, restrict_y);
        XPROPERTY(bool, derived_type, update_on_move);
        XPROPERTY(selected_type, derived_type, selected);

    protected:

        template <class XS, class YS>
        xscatter_base(XS&&, YS&&);

        template <class XS, class YS, class CS>
        xscatter_base(XS&&, YS&&, CS&&);

        template <class XS, class YS, class SS, class OS>
        xscatter_base(XS&&, YS&&, SS&&, OS&&);

        using base_type::base_type;

    private:

        void set_defaults();

        std::list<callback_type> m_callbacks_drag;
        std::list<callback_type> m_callbacks_drag_start;
        std::list<callback_type> m_callbacks_drag_end;
    };

    /************************
     * xscatter declaration *
     ************************/

    template <class D>
    class xscatter : public xscatter_base<D>
    {
    public:

        using base_type = xscatter_base<D>;
        using derived_type = D;

        using data_type = typename base_type::data_type;
        using colors_type = typename base_type::colors_type;
        using names_type = xboxed_container<std::vector<std::string>>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(data_type, derived_type, skew);
        XPROPERTY(std::string, derived_type, marker, "circle", XEITHER("circle", "cross", "diamond", "square", "triangle-down", "triangle-up", "arrow", "rectangle", "ellipse"));
        XPROPERTY(colors_type, derived_type, colors, {"DeepSkyBlue"});
        XPROPERTY(xtl::xoptional<color_type>, derived_type, stroke);
        XPROPERTY(double, derived_type, stroke_width, 1.5);
        XPROPERTY(double, derived_type, default_skew, 0.5);
        XPROPERTY(int, derived_type, default_size, 64);
        XPROPERTY(names_type, derived_type, names);
        XPROPERTY(bool, derived_type, display_names, true);
        XPROPERTY(bool, derived_type, fill, true);
        XPROPERTY(xtl::xoptional<color_type>, derived_type, drag_color);
        XPROPERTY(double, derived_type, drag_size, 5.);
        XPROPERTY(bool, derived_type, names_unique, true);

    protected:

        template <class XS, class YS>
        xscatter(XS&&, YS&&);

        // TODO: it is not the good way to add several scales
        // because we have no idea which one we pass in the entries
        // could be skew, color, ...
        template <class XS, class YS, class CS>
        xscatter(XS&& xs, YS&& ys, CS&& cs);

        // TODO: same remark as the previous constructor
        template <class XS, class YS, class SS, class OS>
        xscatter(XS&& xs, YS&& ys, SS&& ss, OS&& os);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using scatter = xw::xmaterialize<xscatter>;

    /********************
     * xpie declaration *
     ********************/

    template <class D>
    class xpie : public xmark<D>
    {
    public:

        using base_type = xmark<D>;
        using derived_type = D;

        using data_type = xboxed_container<std::vector<double>>;
        using colors_type = std::vector<color_type>;
        using xboxed_color_type = xboxed_container<std::vector<std::string>>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(data_type, derived_type, color);
        XPROPERTY(colors_type, derived_type, colors, category10());
        XPROPERTY(std::string, derived_type, display_labels, "inside", XEITHER("none", "inside", "outside"));
        XPROPERTY(bool, derived_type, display_values);
        XPROPERTY(double, derived_type, end_angle, 360.0);
        XPROPERTY(std::string, derived_type, font_size, "10px");
        XPROPERTY(std::string, derived_type, font_weight, "normal", XEITHER("bold", "normal", "bolder"));
        XPROPERTY(double, derived_type, inner_radius, 0.1);
        XPROPERTY(xtl::xoptional<color_type>, derived_type, label_color);
        XPROPERTY(std::vector<double>, derived_type, opacities);
        XPROPERTY(double, derived_type, radius, 180.0);
        XPROPERTY(::nl::json, derived_type, scales_metadata);
        XPROPERTY(data_type, derived_type, sizes);
        XPROPERTY(bool, derived_type, sort);
        XPROPERTY(double, derived_type, start_angle);
        XPROPERTY(xtl::xoptional<color_type>, derived_type, stroke);
        XPROPERTY(std::string, derived_type, values_format, ".1f");
        // TODO: x and y must be union of double, date and unicode
        XPROPERTY(double, derived_type, x, 0.5);
        XPROPERTY(double, derived_type, y, 0.5);

    protected:

        xpie();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using pie = xw::xmaterialize<xpie>;

    /**********************
     * xlabel declaration *
     **********************/

    template <class D>
    class xlabel : public xscatter_base<D>
    {
    public:

        using base_type = xscatter_base<D>;
        using derived_type = D;

        using data_type = xboxed_container<std::vector<std::string>>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, align, "start", XEITHER("start", "middle", "end"));
        XPROPERTY(std::vector<color_type>, derived_type, colors);
        XPROPERTY(double, derived_type, default_size, 16.0);
        XPROPERTY(double, derived_type, drag_size, 1.0);
        XPROPERTY(std::string, derived_type, font_unit, "px", XEITHER("px", "em", "pt", "%"));
        XPROPERTY(std::string, derived_type, font_weight, "bold", XEITHER("bold", "normal", "bolder"));
        XPROPERTY(double, derived_type, rotate_angle);
        XPROPERTY(data_type, derived_type, text);
        XPROPERTY(int, derived_type, x_offset);
        XPROPERTY(int, derived_type, y_offset);

    protected:

        template <class XS, class YS>
        xlabel(XS&&, YS&&);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using label = xw::xmaterialize<xlabel>;

    /*********************
     * xhist declaration *
     *********************/

    template <class D>
    class xhist : public xmark<D>
    {
    public:

        using base_type = xmark<D>;
        using derived_type = D;

        using data_type = xboxed_container<std::vector<double>>;
        using colors_type = std::vector<color_type>;
        using opacity_type = std::vector<double>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(int, derived_type, bins, 10);
        XPROPERTY(colors_type, derived_type, colors);
        XPROPERTY(data_type, derived_type, count);
        XPROPERTY(colors_type, derived_type, midpoints);
        XPROPERTY(bool, derived_type, normalized);
        XPROPERTY(std::vector<double>, derived_type, opacities);
        XPROPERTY(data_type, derived_type, sample);
        XPROPERTY(::nl::json, derived_type, scales_metadata);
        XPROPERTY(xtl::xoptional<color_type>, derived_type, stroke);

    protected:

        template <class XS, class YS>
        xhist(XS&&, YS&&);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using hist = xw::xmaterialize<xhist>;

    /************************
     * xboxplot declaration *
     ************************/

    template <class D>
    class xboxplot : public xmark<D>
    {
    public:

        using base_type = xmark<D>;
        using derived_type = D;

        using data_type_x = xboxed_container<std::vector<double>>;
        using data_type_y = xboxed_container<std::vector<std::vector<double>>>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(color_type, derived_type, box_fill_color, "dodgerblue");
        XPROPERTY(std::vector<double>, derived_type, opacities);
        XPROPERTY(color_type, derived_type, outlier_fill_color, "gray");
        XPROPERTY(::nl::json, derived_type, scales_metadata);
        XPROPERTY(xtl::xoptional<color_type>, derived_type, stroke);
        XPROPERTY(data_type_x, derived_type, x);
        XPROPERTY(data_type_y, derived_type, y);

    protected:

        template <class XS, class YS>
        xboxplot(XS&&, YS&&);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using boxplot = xw::xmaterialize<xboxplot>;

    /*********************
     * xbars declaration *
     *********************/

    template <class D>
    class xbars : public xmark<D>
    {
    public:

        using base_type = xmark<D>;
        using derived_type = D;

        using data_type = xboxed_container<std::vector<double>>;
        using colors_type = std::vector<color_type>;
        using opacity_type = std::vector<double>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(data_type, derived_type, x);
        XPROPERTY(data_type, derived_type, y);
        XPROPERTY(double, derived_type, padding, 0.05);
        XPROPERTY(opacity_type, derived_type, opacities);
        XPROPERTY(colors_type, derived_type, color);
        XPROPERTY(colors_type, derived_type, colors, category10());
        XPROPERTY(::nl::json, derived_type, scales_metadata);
        XPROPERTY(xtl::xoptional<color_type>, derived_type, stroke);
        XPROPERTY(std::string, derived_type, align, "center", XEITHER("center", "left", "right"));
        XPROPERTY(std::string, derived_type, color_mode, "auto", XEITHER("auto", "group", "element"));
        XPROPERTY(std::string, derived_type, orientation, "vertical", XEITHER("vertical", "horizontal"));
        XPROPERTY(std::string, derived_type, type, "stacked", XEITHER("stacked", "grouped"));

    protected:

        template <class XS, class YS>
        xbars(XS&&, YS&&);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using bars = xw::xmaterialize<xbars>;

    /*************************
     * xheat_map declaration *
     *************************/

    template <class D>
    class xheat_map : public xmark<D>
    {
    public:

        using base_type = xmark<D>;
        using derived_type = D;

        using coord_type = xboxed_container<std::vector<double>>;
        using array = std::vector<std::vector<double>>;
        using data_type = xboxed_container<array>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(xtl::xoptional<data_type>, derived_type, color);
        XPROPERTY(xtl::xoptional<color_type>, derived_type, null_color, "black");
        XPROPERTY(::nl::json, derived_type, scales_metadata);
        XPROPERTY(xtl::xoptional<coord_type>, derived_type, x);
        XPROPERTY(xtl::xoptional<coord_type>, derived_type, y);

    protected:

        template <class XS, class YS, class CS>
        xheat_map(std::vector<std::vector<double>>&,
                  XS&&, YS&&, CS&&);

        template <class XS, class YS, class CS>
        xheat_map(std::vector<double>&,
                  std::vector<double>&,
                  std::vector<std::vector<double>>&,
                  XS&&, YS&&, CS&&);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using heat_map = xw::xmaterialize<xheat_map>;

    /******************************
     * xgrid_heat_map declaration *
     ******************************/

    template <class D>
    class xgrid_heat_map : public xmark<D>
    {
    public:

        using base_type = xmark<D>;
        using derived_type = D;

        using selected_type = std::vector<std::vector<int>>;
        using data1d_type = xboxed_container<std::vector<double>>;
        using data2d_type = xboxed_container<std::vector<std::vector<double>>>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(::nl::json, derived_type, anchor_style, ::nl::json::object());
        XPROPERTY(data2d_type, derived_type, color);
        XPROPERTY(data1d_type, derived_type, column);
        XPROPERTY(std::string, derived_type, column_align, "start", XEITHER("start", "end"));
        XPROPERTY(xtl::xoptional<color_type>, derived_type, null_color, "black");
        XPROPERTY(double, derived_type, opacity, 1.0);
        XPROPERTY(data1d_type, derived_type, row);
        XPROPERTY(std::string, derived_type, row_align, "start", XEITHER("start", "end"));
        XPROPERTY(::nl::json, derived_type, scales_metadata);
        XPROPERTY(xtl::xoptional<color_type>, derived_type, stroke, "black");
        XPROPERTY(selected_type, derived_type, selected);

    protected:

        template <class XS, class YS, class CS>
        xgrid_heat_map(std::vector<double>&,
                       std::vector<double>&,
                       std::vector<std::vector<double>>&,
                       XS&&, YS&&, CS&&);

        template <class XS, class YS, class CS>
        xgrid_heat_map(std::vector<std::vector<double>>&,
                       XS&&, YS&&, CS&&);

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using grid_heat_map = xw::xmaterialize<xgrid_heat_map>;

    /********************
     * xmap declaration *
     ********************/

    template <class D>
    class xmap : public xmark<D>
    {
    public:

        using base_type = xmark<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(xtl::xoptional<::nl::json>, derived_type, color, ::nl::json::object());
        XPROPERTY(::nl::json, derived_type, colors, ::nl::json::object());
        XPROPERTY(bool, derived_type, hover_highlight, true);
        XPROPERTY(xtl::xoptional<::nl::json>, derived_type, hovered_styles);
        XPROPERTY(::nl::json, derived_type, map_data);
        XPROPERTY(::nl::json, derived_type, scales_metadata);
        XPROPERTY(xtl::xoptional<std::vector<color_type>>, derived_type, selected);
        XPROPERTY(::nl::json, derived_type, selected_styles);
        XPROPERTY(xtl::xoptional<color_type>, derived_type, stroke_color);

    protected:

        template <class GS>
        xmap(xscale<GS>&&);

        template <class GS>
        xmap(const xscale<GS>&);

        template <class GS>
        xmap(std::string, GS&&);

        template <class GS, class CS>
        xmap(GS&&, CS&&);

        template <class GS, class CS>
        xmap(std::string, GS&&, CS&&);

        using base_type::base_type;

    private:

        void set_defaults();
        nl::json read_map(std::string filename);
    };

    using map = xw::xmaterialize<xmap>;

    /************************
     * xmark implementation *
     ************************/

    template <class D>
    inline void xmark<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(scales, patch, buffers);
        set_property_from_patch(scales_metadata, patch, buffers);
        set_property_from_patch(preserve_domain, patch, buffers);
        set_property_from_patch(display_legend, patch, buffers);
        set_property_from_patch(labels, patch, buffers);
        set_property_from_patch(apply_clip, patch, buffers);
        set_property_from_patch(visible, patch, buffers);
        set_property_from_patch(selected_style, patch, buffers);
        set_property_from_patch(unselected_style, patch, buffers);
        set_property_from_patch(selected, patch, buffers);
        set_property_from_patch(tooltip, patch, buffers);
        set_property_from_patch(tooltip_style, patch, buffers);
        set_property_from_patch(enable_hover, patch, buffers);
        set_property_from_patch(interactions, patch, buffers);
        set_property_from_patch(tooltip_location, patch, buffers);
    }

    template <class D>
    inline void xmark<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(scales, state["scales"], buffers);
        xwidgets_serialize(scales_metadata, state["scales_metadata"], buffers);
        xwidgets_serialize(preserve_domain, state["preserve_domain"], buffers);
        xwidgets_serialize(display_legend, state["display_legend"], buffers);
        xwidgets_serialize(labels, state["labels"], buffers);
        xwidgets_serialize(apply_clip, state["apply_clip"], buffers);
        xwidgets_serialize(visible, state["visible"], buffers);
        xwidgets_serialize(selected_style, state["selected_style"], buffers);
        xwidgets_serialize(unselected_style, state["unselected_style"], buffers);
        xwidgets_serialize(selected, state["selected"], buffers);
        xwidgets_serialize(tooltip, state["tooltip"], buffers);
        xwidgets_serialize(tooltip_style, state["tooltip_style"], buffers);
        xwidgets_serialize(enable_hover, state["enable_hover"], buffers);
        xwidgets_serialize(interactions, state["interactions"], buffers);
        xwidgets_serialize(tooltip_location, state["tooltip_location"], buffers);
    }

    template <class D>
    inline xmark<D>::xmark()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xmark<D>::set_defaults()
    {
        this->_model_name() = "MarkModel";
    }

    /*************************
     * xlines implementation *
     *************************/

    template <class D>
    inline void xlines<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(x, patch, buffers);
        set_property_from_patch(y, patch, buffers);
        set_property_from_patch(color, patch, buffers);
        set_property_from_patch(colors, patch, buffers);
        set_property_from_patch(fill_colors, patch, buffers);
        set_property_from_patch(stroke_width, patch, buffers);
        set_property_from_patch(labels_visibility, patch, buffers);
        set_property_from_patch(curves_subset, patch, buffers);
        set_property_from_patch(line_style, patch, buffers);
        set_property_from_patch(interpolation, patch, buffers);
        set_property_from_patch(close_path, patch, buffers);
        set_property_from_patch(fill, patch, buffers);
        set_property_from_patch(marker, patch, buffers);
        set_property_from_patch(marker_size, patch, buffers);
        set_property_from_patch(opacities, patch, buffers);
        set_property_from_patch(fill_opacities, patch, buffers);
    }

    template <class D>
    inline void xlines<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(x, state["x"], buffers);
        xwidgets_serialize(y, state["y"], buffers);
        xwidgets_serialize(color, state["color"], buffers);
        xwidgets_serialize(colors, state["colors"], buffers);
        xwidgets_serialize(fill_colors, state["fill_colors"], buffers);
        xwidgets_serialize(stroke_width, state["stroke_width"], buffers);
        xwidgets_serialize(labels_visibility, state["labels_visibility"], buffers);
        xwidgets_serialize(curves_subset, state["curves_subset"], buffers);
        xwidgets_serialize(line_style, state["line_style"], buffers);
        xwidgets_serialize(interpolation, state["interpolation"], buffers);
        xwidgets_serialize(close_path, state["close_path"], buffers);
        xwidgets_serialize(fill, state["fill"], buffers);
        xwidgets_serialize(marker, state["marker"], buffers);
        xwidgets_serialize(marker_size, state["marker_size"], buffers);
        xwidgets_serialize(opacities, state["opacities"], buffers);
        xwidgets_serialize(fill_opacities, state["fill_opacities"], buffers);
    }

    template <class D>
    template <class XS, class YS>
    inline xlines<D>::xlines(XS&& xs, YS&& ys)
        : base_type()
    {
        set_defaults();

        this->scales()["x"] = std::forward<XS>(xs);
        this->scales()["y"] = std::forward<YS>(ys);
    }

    template <class D>
    inline void xlines<D>::set_defaults()
    {
        this->_model_name() = "LinesModel";
        this->_view_name() = "Lines";
        this->scales_metadata() = {
            {"x", {{"orientation", "horizontal"}, {"dimension", "x"}}},
            {"y", {{"orientation", "vertical"}, {"dimension", "y"}}},
            {"color", {{"dimension", "color"}}}};
    }

    /********************************
     * xscatter_base implementation *
     ********************************/

    template <class D>
    inline void xscatter_base<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(x, patch, buffers);
        set_property_from_patch(y, patch, buffers);
        set_property_from_patch(color, patch, buffers);
        set_property_from_patch(opacity, patch, buffers);
        set_property_from_patch(size, patch, buffers);
        set_property_from_patch(rotation, patch, buffers);
        set_property_from_patch(default_opacities, patch, buffers);
        set_property_from_patch(hovered_style, patch, buffers);
        set_property_from_patch(unhovered_style, patch, buffers);
        set_property_from_patch(hovered_point, patch, buffers);
        set_property_from_patch(enable_move, patch, buffers);
        set_property_from_patch(enable_delete, patch, buffers);
        set_property_from_patch(restrict_x, patch, buffers);
        set_property_from_patch(restrict_y, patch, buffers);
        set_property_from_patch(update_on_move, patch, buffers);
        set_property_from_patch(selected, patch, buffers);
    }

    template <class D>
    inline void xscatter_base<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(x, state["x"], buffers);
        xwidgets_serialize(y, state["y"], buffers);
        xwidgets_serialize(color, state["color"], buffers);
        xwidgets_serialize(opacity, state["opacity"], buffers);
        xwidgets_serialize(size, state["size"], buffers);
        xwidgets_serialize(rotation, state["rotation"], buffers);
        xwidgets_serialize(default_opacities, state["default_opacities"], buffers);
        xwidgets_serialize(hovered_style, state["hovered_style"], buffers);
        xwidgets_serialize(unhovered_style, state["unhovered_style"], buffers);
        xwidgets_serialize(hovered_point, state["hovered_point"], buffers);
        xwidgets_serialize(enable_move, state["enable_move"], buffers);
        xwidgets_serialize(enable_delete, state["enable_delete"], buffers);
        xwidgets_serialize(restrict_x, state["restrict_x"], buffers);
        xwidgets_serialize(restrict_y, state["restrict_y"], buffers);
        xwidgets_serialize(update_on_move, state["update_on_move"], buffers);
        xwidgets_serialize(selected, state["selected"], buffers);
    }

    template <class D>
    template <class XS, class YS>
    inline xscatter_base<D>::xscatter_base(XS&& xs, YS&& ys)
        : base_type()
    {
        set_defaults();

        this->scales()["x"] = std::forward<XS>(xs);
        this->scales()["y"] = std::forward<YS>(ys);
    }

    template <class D>
    template <class XS, class YS, class CS>
    inline xscatter_base<D>::xscatter_base(XS&& xs, YS&& ys, CS&& cs)
        : base_type()
    {
        set_defaults();

        this->scales()["x"] = std::forward<XS>(xs);
        this->scales()["y"] = std::forward<YS>(ys);
        this->scales()["color"] = std::forward<CS>(cs);
    }

    template <class D>
    template <class XS, class YS, class SS, class OS>
    inline xscatter_base<D>::xscatter_base(XS&& xs, YS&& ys, SS&& ss, OS&& os)
        : base_type()
    {
        set_defaults();

        this->scales()["x"] = std::forward<XS>(xs);
        this->scales()["y"] = std::forward<YS>(ys);
        this->scales()["size"] = std::forward<SS>(ss);
        this->scales()["opacities"] = std::forward<OS>(os);
    }

    template <class D>
    inline void xscatter_base<D>::set_defaults()
    {
        this->scales_metadata() = {
            {"x", {{"orientation", "horizontal"}, {"dimension", "x"}}},
            {"y", {{"orientation", "vertical"}, {"dimension", "y"}}},
            {"color", {{"dimension", "color"}}},
            {"size", {{"dimension", "size"}}},
            {"opacity", {{"dimension", "opacity"}}},
            {"rotation", {{"dimension", "rotation"}}}};
    }

    template <class D>
    inline void xscatter_base<D>::on_drag(callback_type cb)
    {
        m_callbacks_drag.emplace_back(std::move(cb));
    }

    template <class D>
    inline void xscatter_base<D>::on_drag_start(callback_type cb)
    {
        m_callbacks_drag_start.emplace_back(std::move(cb));
    }

    template <class D>
    inline void xscatter_base<D>::on_drag_end(callback_type cb)
    {
        m_callbacks_drag_end.emplace_back(std::move(cb));
    }

    template <class D>
    inline void xscatter_base<D>::handle_custom_message(const nl::json& content)
    {
        auto it = content.find("event");
        if (it != content.end() && it.value() == "drag")
        {
            for (auto it = m_callbacks_drag.begin(); it != m_callbacks_drag.end(); ++it)
            {
                it->operator()(content);
            }
        }
        else if (it != content.end() && it.value() == "drag_start")
        {
            for (auto it = m_callbacks_drag_start.begin(); it != m_callbacks_drag_start.end(); ++it)
            {
                it->operator()(content);
            }
        }
        else if (it != content.end() && it.value() == "drag_end")
        {
            for (auto it = m_callbacks_drag_end.begin(); it != m_callbacks_drag_end.end(); ++it)
            {
                it->operator()(content);
            }
        }
    }

    /***************************
     * xscatter implementation *
     ***************************/

    template <class D>
    inline void xscatter<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(skew, patch, buffers);
        set_property_from_patch(marker, patch, buffers);
        set_property_from_patch(colors, patch, buffers);
        set_property_from_patch(stroke, patch, buffers);
        set_property_from_patch(stroke_width, patch, buffers);
        set_property_from_patch(default_skew, patch, buffers);
        set_property_from_patch(default_size, patch, buffers);
        set_property_from_patch(names, patch, buffers);
        set_property_from_patch(display_names, patch, buffers);
        set_property_from_patch(fill, patch, buffers);
        set_property_from_patch(drag_color, patch, buffers);
        set_property_from_patch(drag_size, patch, buffers);
        set_property_from_patch(names_unique, patch, buffers);
    }

    template <class D>
    inline void xscatter<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(skew, state["skew"], buffers);
        xwidgets_serialize(marker, state["marker"], buffers);
        xwidgets_serialize(colors, state["colors"], buffers);
        xwidgets_serialize(stroke, state["stroke"], buffers);
        xwidgets_serialize(stroke_width, state["stroke_width"], buffers);
        xwidgets_serialize(default_skew, state["default_skew"], buffers);
        xwidgets_serialize(default_size, state["default_size"], buffers);
        xwidgets_serialize(names, state["names"], buffers);
        xwidgets_serialize(display_names, state["display_names"], buffers);
        xwidgets_serialize(fill, state["fill"], buffers);
        xwidgets_serialize(drag_color, state["drag_color"], buffers);
        xwidgets_serialize(drag_size, state["drag_size"], buffers);
        xwidgets_serialize(names_unique, state["names_unique"], buffers);
    }

    template <class D>
    template <class XS, class YS>
    inline xscatter<D>::xscatter(XS&& xs, YS&& ys)
        : base_type(std::forward<XS>(xs), std::forward<YS>(ys))
    {
        set_defaults();
    }

    template <class D>
    template <class XS, class YS, class CS>
    inline xscatter<D>::xscatter(XS&& xs, YS&& ys, CS&& cs)
        : base_type(std::forward<XS>(xs), std::forward<YS>(ys), std::forward<CS>(cs))
    {
        set_defaults();
    }

    template <class D>
    template <class XS, class YS, class SS, class OS>
    inline xscatter<D>::xscatter(XS&& xs, YS&& ys, SS&& ss, OS&& os)
        : base_type(std::forward<XS>(xs), std::forward<YS>(ys), std::forward<SS>(ss), std::forward<OS>(os))
    {
        set_defaults();
    }

    template <class D>
    inline void xscatter<D>::set_defaults()
    {
        this->_model_name() = "ScatterModel";
        this->_view_name() = "Scatter";
    }

    /***********************
     * xpie implementation *
     ***********************/

    template <class D>
    inline void xpie<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(color, patch, buffers);
        set_property_from_patch(colors, patch, buffers);
        set_property_from_patch(display_labels, patch, buffers);
        set_property_from_patch(display_values, patch, buffers);
        set_property_from_patch(end_angle, patch, buffers);
        set_property_from_patch(font_size, patch, buffers);
        set_property_from_patch(font_weight, patch, buffers);
        set_property_from_patch(inner_radius, patch, buffers);
        set_property_from_patch(label_color, patch, buffers);
        set_property_from_patch(opacities, patch, buffers);
        set_property_from_patch(radius, patch, buffers);
        set_property_from_patch(scales_metadata, patch, buffers);
        set_property_from_patch(sizes, patch, buffers);
        set_property_from_patch(sort, patch, buffers);
        set_property_from_patch(start_angle, patch, buffers);
        set_property_from_patch(stroke, patch, buffers);
        set_property_from_patch(values_format, patch, buffers);
        set_property_from_patch(x, patch, buffers);
        set_property_from_patch(y, patch, buffers);
    }

    template <class D>
    inline void xpie<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(color, state["color"], buffers);
        xwidgets_serialize(colors, state["colors"], buffers);
        xwidgets_serialize(display_labels, state["display_labels"], buffers);
        xwidgets_serialize(display_values, state["display_values"], buffers);
        xwidgets_serialize(end_angle, state["end_angle"], buffers);
        xwidgets_serialize(font_size, state["font_size"], buffers);
        xwidgets_serialize(font_weight, state["font_weight"], buffers);
        xwidgets_serialize(inner_radius, state["inner_radius"], buffers);
        xwidgets_serialize(label_color, state["label_color"], buffers);
        xwidgets_serialize(opacities, state["opacities"], buffers);
        xwidgets_serialize(radius, state["radius"], buffers);
        xwidgets_serialize(scales_metadata, state["scales_metadata"], buffers);
        xwidgets_serialize(sizes, state["sizes"], buffers);
        xwidgets_serialize(sort, state["sort"], buffers);
        xwidgets_serialize(start_angle, state["start_angle"], buffers);
        xwidgets_serialize(stroke, state["stroke"], buffers);
        xwidgets_serialize(values_format, state["values_format"], buffers);
        xwidgets_serialize(x, state["x"], buffers);
        xwidgets_serialize(y, state["y"], buffers);
    }

    template <class D>
    inline xpie<D>::xpie()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xpie<D>::set_defaults()
    {
        this->_view_name() = "Pie";
        this->_model_name() = "PieModel";
    }

    /*************************
     * xlabel implementation *
     *************************/

    template <class D>
    inline void xlabel<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(align, patch, buffers);
        set_property_from_patch(colors, patch, buffers);
        set_property_from_patch(default_size, patch, buffers);
        set_property_from_patch(drag_size, patch, buffers);
        set_property_from_patch(font_unit, patch, buffers);
        set_property_from_patch(font_weight, patch, buffers);
        set_property_from_patch(rotate_angle, patch, buffers);
        set_property_from_patch(text, patch, buffers);
        set_property_from_patch(x_offset, patch, buffers);
        set_property_from_patch(y_offset, patch, buffers);
    }

    template <class D>
    inline void xlabel<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(align, state["align"], buffers);
        xwidgets_serialize(colors, state["colors"], buffers);
        xwidgets_serialize(default_size, state["default_size"], buffers);
        xwidgets_serialize(drag_size, state["drag_size"], buffers);
        xwidgets_serialize(font_unit, state["font_unit"], buffers);
        xwidgets_serialize(font_weight, state["font_weight"], buffers);
        xwidgets_serialize(rotate_angle, state["rotate_angle"], buffers);
        xwidgets_serialize(text, state["text"], buffers);
        xwidgets_serialize(x_offset, state["x_offset"], buffers);
        xwidgets_serialize(y_offset, state["y_offset"], buffers);
    }

    template <class D>
    template <class XS, class YS>
    inline xlabel<D>::xlabel(XS&& xs, YS&& ys)
        : base_type(std::forward<XS>(xs), std::forward<YS>(ys))
    {
        set_defaults();
    }

    template <class D>
    inline void xlabel<D>::set_defaults()
    {
        this->_view_name() = "Label";
        this->_model_name() = "LabelModel";
    }

    /************************
     * xhist implementation *
     ************************/

    template <class D>
    inline void xhist<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(bins, patch, buffers);
        set_property_from_patch(colors, patch, buffers);
        set_property_from_patch(count, patch, buffers);
        set_property_from_patch(midpoints, patch, buffers);
        set_property_from_patch(normalized, patch, buffers);
        set_property_from_patch(opacities, patch, buffers);
        set_property_from_patch(sample, patch, buffers);
        set_property_from_patch(scales_metadata, patch, buffers);
        set_property_from_patch(stroke, patch, buffers);
    }

    template <class D>
    inline void xhist<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(bins, state["bins"], buffers);
        xwidgets_serialize(colors, state["colors"], buffers);
        xwidgets_serialize(count, state["count"], buffers);
        xwidgets_serialize(midpoints, state["midpoints"], buffers);
        xwidgets_serialize(normalized, state["normalized"], buffers);
        xwidgets_serialize(opacities, state["opacities"], buffers);
        xwidgets_serialize(sample, state["sample"], buffers);
        xwidgets_serialize(scales_metadata, state["scales_metadata"], buffers);
        xwidgets_serialize(stroke, state["stroke"], buffers);
    }

    template <class D>
    template <class XS, class YS>
    inline xhist<D>::xhist(XS&& xs, YS&& ys)
        : base_type()
    {
        set_defaults();

        this->scales()["sample"] = std::forward<XS>(xs);
        this->scales()["count"] = std::forward<YS>(ys);
    }

    template <class D>
    inline void xhist<D>::set_defaults()
    {
        this->_view_name() = "Hist";
        this->_model_name() = "HistModel";
        this->scales_metadata() = {
            {"sample", {{"orientation", "horizontal"}, {"dimension", "x"}}},
            {"count", {{"orientation", "vertical"}, {"dimension", "y"}}}};
    }

    /***************************
     * xboxplot implementation *
     ***************************/

    template <class D>
    inline void xboxplot<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(box_fill_color, patch, buffers);
        set_property_from_patch(opacities, patch, buffers);
        set_property_from_patch(outlier_fill_color, patch, buffers);
        set_property_from_patch(scales_metadata, patch, buffers);
        set_property_from_patch(stroke, patch, buffers);
        set_property_from_patch(x, patch, buffers);
        set_property_from_patch(y, patch, buffers);
    }

    template <class D>
    inline void xboxplot<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(box_fill_color, state["box_fill_color"], buffers);
        xwidgets_serialize(opacities, state["opacities"], buffers);
        xwidgets_serialize(outlier_fill_color, state["outlier_fill_color"], buffers);
        xwidgets_serialize(scales_metadata, state["scales_metadata"], buffers);
        xwidgets_serialize(stroke, state["stroke"], buffers);
        xwidgets_serialize(x, state["x"], buffers);
        xwidgets_serialize(y, state["y"], buffers);
    }

    template <class D>
    template <class XS, class YS>
    inline xboxplot<D>::xboxplot(XS&& xs, YS&& ys)
        : base_type()
    {
        set_defaults();

        this->scales()["x"] = std::forward<XS>(xs);
        this->scales()["y"] = std::forward<YS>(ys);
    }

    template <class D>
    inline void xboxplot<D>::set_defaults()
    {
        this->_view_name() = "Boxplot";
        this->_model_name() = "BoxplotModel";
        this->scales_metadata() = {
            {"x", {{"orientation", "horizontal"}, {"dimension", "x"}}},
            {"y", {{"orientation", "vertical"}, {"dimension", "y"}}}};
    }

    /************************
     * xbars implementation *
     ************************/

    template <class D>
    inline void xbars<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(align, patch, buffers);
        set_property_from_patch(color, patch, buffers);
        set_property_from_patch(color_mode, patch, buffers);
        set_property_from_patch(colors, patch, buffers);
        set_property_from_patch(opacities, patch, buffers);
        set_property_from_patch(orientation, patch, buffers);
        set_property_from_patch(padding, patch, buffers);
        set_property_from_patch(scales_metadata, patch, buffers);
        set_property_from_patch(stroke, patch, buffers);
        set_property_from_patch(type, patch, buffers);
        set_property_from_patch(x, patch, buffers);
        set_property_from_patch(y, patch, buffers);
    }

    template <class D>
    inline void xbars<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(align, state["align"], buffers);
        xwidgets_serialize(color, state["color"], buffers);
        xwidgets_serialize(color_mode, state["color_mode"], buffers);
        xwidgets_serialize(colors, state["colors"], buffers);
        xwidgets_serialize(opacities, state["opacities"], buffers);
        xwidgets_serialize(orientation, state["orientation"], buffers);
        xwidgets_serialize(padding, state["padding"], buffers);
        xwidgets_serialize(scales_metadata, state["scales_metadata"], buffers);
        xwidgets_serialize(stroke, state["stroke"], buffers);
        xwidgets_serialize(type, state["type"], buffers);
        xwidgets_serialize(x, state["x"], buffers);
        xwidgets_serialize(y, state["y"], buffers);
    }

    template <class D>
    template <class XS, class YS>
    inline xbars<D>::xbars(XS&& xs, YS&& ys)
        : base_type()
    {
        set_defaults();

        this->scales()["x"] = std::forward<XS>(xs);
        this->scales()["y"] = std::forward<YS>(ys);
    }

    template <class D>
    inline void xbars<D>::set_defaults()
    {
        this->_view_name() = "Bars";
        this->_model_name() = "BarsModel";
        this->scales_metadata() = {
            {"x", {{"orientation", "horizontal"}, {"dimension", "x"}}},
            {"y", {{"orientation", "vertical"}, {"dimension", "y"}}},
            {"color", {{"dimension", "color"}}}};
    }

    /****************************
     * xheat_map implementation *
     ****************************/

    template <class D>
    inline void xheat_map<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(color, patch, buffers);
        set_property_from_patch(null_color, patch, buffers);
        set_property_from_patch(scales_metadata, patch, buffers);
        set_property_from_patch(x, patch, buffers);
        set_property_from_patch(y, patch, buffers);
    }

    template <class D>
    inline void xheat_map<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(color, state["color"], buffers);
        xwidgets_serialize(null_color, state["null_color"], buffers);
        xwidgets_serialize(scales_metadata, state["scales_metadata"], buffers);
        xwidgets_serialize(x, state["x"], buffers);
        xwidgets_serialize(y, state["y"], buffers);
    }

    template <class D>
    template <class XS, class YS, class CS>
    inline xheat_map<D>::xheat_map(std::vector<std::vector<double>>& color_,
                                   XS&& xs, YS&& ys, CS&& cs)
        : base_type()
    {
        set_defaults();

        this->scales()["x"] = std::forward<XS>(xs);
        this->scales()["y"] = std::forward<YS>(ys);
        this->scales()["color"] = std::forward<CS>(cs);
        color = color_;
        std::vector<double> x_(color_.size());
        std::iota(x_.begin(), x_.end(), 0);
        std::vector<double> y_(color_[0].size());
        std::iota(y_.begin(), y_.end(), 0);
        this->x() = x_;
        this->y() = y_;
    }

    template <class D>
    template <class XS, class YS, class CS>
    inline xheat_map<D>::xheat_map(std::vector<double>& x_,
                                   std::vector<double>& y_,
                                   std::vector<std::vector<double>>& color_,
                                   XS&& xs, YS&& ys, CS&& cs)
        : base_type()
    {
        set_defaults();

        this->scales()["x"] = std::forward<XS>(xs);
        this->scales()["y"] = std::forward<YS>(ys);
        this->scales()["color"] = std::forward<CS>(cs);
        this->color() = color_;
        this->x() = x_;
        this->y() = y_;
    }

    template <class D>
    inline void xheat_map<D>::set_defaults()
    {
        this->_view_name() = "HeatMap";
        this->_model_name() = "HeatMapModel";
        this->scales_metadata() = {
            {"x", {{"orientation", "horizontal"}, {"dimension", "x"}}},
            {"y", {{"orientation", "vertical"}, {"dimension", "y"}}},
            {"color", {{"dimension", "color"}}}};
    }

    /*********************************
     * xgrid_heat_map implementation *
     *********************************/

    template <class D>
    template <class XS, class YS, class CS>
    inline xgrid_heat_map<D>::xgrid_heat_map(std::vector<double>& row_,
                                             std::vector<double>& column_,
                                             std::vector<std::vector<double>>& color_,
                                             XS&& xs, YS&& ys, CS&& cs)
        : base_type()
    {
        set_defaults();

        this->scales()["column"] = std::forward<XS>(xs);
        this->scales()["row"] = std::forward<YS>(ys);
        this->scales()["color"] = std::forward<CS>(cs);
        this->color() = color_;
        this->row() = row_;
        this->column() = column_;
    }

    template <class D>
    template <class XS, class YS, class CS>
    inline xgrid_heat_map<D>::xgrid_heat_map(std::vector<std::vector<double>>& color_,
                                             XS&& xs, YS&& ys, CS&& cs)
        : base_type()
    {
        set_defaults();

        this->scales()["column"] = std::forward<XS>(xs);
        this->scales()["row"] = std::forward<YS>(ys);
        this->scales()["color"] = std::forward<CS>(cs);
        this->color() = color_;
        std::vector<double> row_(color_.size());
        std::iota(row_.begin(), row_.end(), 0);
        std::vector<double> column_(color_[0].size());
        std::iota(column_.begin(), column_.end(), 0);
        this->row() = row_;
        this->column() = column_;
    }

    template <class D>
    inline void xgrid_heat_map<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(anchor_style, patch, buffers);
        set_property_from_patch(color, patch, buffers);
        set_property_from_patch(column, patch, buffers);
        set_property_from_patch(column_align, patch, buffers);
        set_property_from_patch(null_color, patch, buffers);
        set_property_from_patch(opacity, patch, buffers);
        set_property_from_patch(row, patch, buffers);
        set_property_from_patch(row_align, patch, buffers);
        set_property_from_patch(scales_metadata, patch, buffers);
        set_property_from_patch(stroke, patch, buffers);
        set_property_from_patch(selected, patch, buffers);
    }

    template <class D>
    inline void xgrid_heat_map<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(anchor_style, state["anchor_style"], buffers);
        xwidgets_serialize(color, state["color"], buffers);
        xwidgets_serialize(column, state["column"], buffers);
        xwidgets_serialize(column_align, state["column"], buffers);
        xwidgets_serialize(null_color, state["column_align"], buffers);
        xwidgets_serialize(opacity, state["opacity"], buffers);
        xwidgets_serialize(row, state["row"], buffers);
        xwidgets_serialize(row_align, state["row_align"], buffers);
        xwidgets_serialize(scales_metadata, state["scales_metadata"], buffers);
        xwidgets_serialize(stroke, state["stroke"], buffers);
        xwidgets_serialize(selected, state["selected"], buffers);
    }

    template <class D>
    inline void xgrid_heat_map<D>::set_defaults()
    {
        this->_view_name() = "GridHeatMap";
        this->_model_name() = "GridHeatMapModel";
        this->scales_metadata() = {
            {"column", {{"orientation", "horizontal"}, {"dimension", "x"}}},
            {"row", {{"orientation", "vertical"}, {"dimension", "y"}}},
            {"color", {{"dimension", "color"}}}};
    }

    /***********************
     * xmap implementation *
     ***********************/

    template <class D>
    template <class GS>
    inline xmap<D>::xmap(xscale<GS>&& gs)
        : base_type()
    {
        map_data = read_map(topo_load("WorldMap.json"));
        set_defaults();
        this->scales()["projection"] = std::move(gs);
    }

    template <class D>
    template <class GS>
    inline xmap<D>::xmap(const xscale<GS>& gs)
        : base_type()
    {
        map_data = read_map(topo_load("WorldMap.json"));
        set_defaults();
        this->scales()["projection"] = gs;
    }

    template <class D>
    template <class GS>
    inline xmap<D>::xmap(std::string filename, GS&& gs)
        : base_type()
    {
        map_data = read_map(filename);
        set_defaults();
        this->scales()["projection"] = std::forward<GS>(gs);
    }

    template <class D>
    template <class GS, class CS>
    inline xmap<D>::xmap(GS&& gs, CS&& cs)
        : base_type()
    {
        map_data = read_map(topo_load("WorldMap.json"));
        set_defaults();
        this->scales()["projection"] = std::forward<GS>(gs);
        this->scales()["color"] = std::forward<CS>(cs);
    }

    template <class D>
    template <class GS, class CS>
    inline xmap<D>::xmap(std::string filename, GS&& gs, CS&& cs)
        : base_type()
    {
        map_data = read_map(filename);
        set_defaults();
        this->scales()["projection"] = std::forward<GS>(gs);
        this->scales()["color"] = std::forward<CS>(cs);
    }

    template <class D>
    inline void xmap<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(color, patch, buffers);
        set_property_from_patch(colors, patch, buffers);
        set_property_from_patch(hover_highlight, patch, buffers);
        set_property_from_patch(hovered_styles, patch, buffers);
        set_property_from_patch(map_data, patch, buffers);
        set_property_from_patch(scales_metadata, patch, buffers);
        set_property_from_patch(selected, patch, buffers);
        set_property_from_patch(selected_styles, patch, buffers);
        set_property_from_patch(stroke_color, patch, buffers);
    }

    template <class D>
    inline void xmap<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(color, state["color"], buffers);
        xwidgets_serialize(colors, state["colors"], buffers);
        xwidgets_serialize(hover_highlight, state["hover_highlight"], buffers);
        xwidgets_serialize(hovered_styles, state["hovered_styles"], buffers);
        xwidgets_serialize(map_data, state["map_data"], buffers);
        xwidgets_serialize(scales_metadata, state["scales_metadata"], buffers);
        xwidgets_serialize(selected, state["selected"], buffers);
        xwidgets_serialize(selected_styles, state["selected_styles"], buffers);
        xwidgets_serialize(stroke_color, state["stroke_color"], buffers);
    }

    template <class D>
    inline void xmap<D>::set_defaults()
    {
        this->_view_name() = "Map";
        this->_model_name() = "MapModel";
        this->scales_metadata() = {
            {"color", {{"dimension", "color"}}},
            {"projection", {{"dimension", "geo"}}}};
    }

    template <class D>
    inline nl::json xmap<D>::read_map(std::string filename)
    {
        std::ifstream jsonfile(filename);

        // TODO: we should do:
        // return nl::json::parse(jsonfile);

        std::string str((std::istreambuf_iterator<char>(jsonfile)),
                        std::istreambuf_iterator<char>());
        return nlohmann::json::parse(str);
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xpl::xlines>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xlines>>;

    extern template class xw::xmaterialize<xpl::xscatter>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xscatter>>;

    extern template class xw::xmaterialize<xpl::xpie>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xpie>>;
    extern template xw::xmaterialize<xpl::xpie>::xmaterialize();

    extern template class xw::xmaterialize<xpl::xlabel>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xlabel>>;

    extern template class xw::xmaterialize<xpl::xhist>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xhist>>;

    extern template class xw::xmaterialize<xpl::xboxplot>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xboxplot>>;

    extern template class xw::xmaterialize<xpl::xbars>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xbars>>;

    extern template class xw::xmaterialize<xpl::xheat_map>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xheat_map>>;

    extern template class xw::xmaterialize<xpl::xgrid_heat_map>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xgrid_heat_map>>;

    extern template class xw::xmaterialize<xpl::xmap>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xmap>>;
#endif

#endif
