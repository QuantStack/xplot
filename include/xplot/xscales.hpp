/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_SCALES_HPP
#define XPLOT_SCALES_HPP

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

#include "xtl/xoptional.hpp"

#include "xproperty/xjson.hpp" 

#include "xplot.hpp"

namespace nl = nlohmann;

namespace xpl
{
    /*********************
     * scale declaration *
     *********************/

    template <class D>
    class xscale : public xplot<D>
    {
    public:

        using base_type = xplot<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(bool, derived_type, reverse);
        XPROPERTY(bool, derived_type, allow_padding, true);

    protected:

        xscale();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    template <class T, class R = void>
    struct enable_xscale
    {
        using type = std::enable_if_t<std::is_base_of<xscale<T>, T>::value, R>;
    };

    template <class T, class R = void>
    using enable_xscale_t = typename enable_xscale<T, R>::type;

    /****************************
     * linear_scale declaration *
     ****************************/

    template <class D>
    class xlinear_scale : public xscale<D>
    {
    public:

        using base_type = xscale<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(xtl::xoptional<double>, derived_type, min);
        XPROPERTY(xtl::xoptional<double>, derived_type, max);
        XPROPERTY(bool, derived_type, stabilized, false);
        XPROPERTY(double, derived_type, mid_range, 0.8);
        XPROPERTY(double, derived_type, min_range, 0.6);

    protected:

        xlinear_scale();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using linear_scale = xw::xmaterialize<xlinear_scale>;

    /*************************
     * log_scale declaration *
     *************************/

    template <class D>
    class xlog_scale : public xscale<D>
    {
    public:

        using base_type = xscale<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(xtl::xoptional<double>, derived_type, min);
        XPROPERTY(xtl::xoptional<double>, derived_type, max);

    protected:

        xlog_scale();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using log_scale = xw::xmaterialize<xlog_scale>;

    /******************************
     * xordinal_scale declaration *
     ******************************/

    template <class D>
    class xordinal_scale : public xscale<D>
    {
    public:

        using base_type = xscale<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::vector<double>, derived_type, domain);

    protected:

        xordinal_scale();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using ordinal_scale = xw::xmaterialize<xordinal_scale>;

    /****************************
     * xcolor_scale declaration *
     ****************************/

    template <class D>
    class xcolor_scale : public xscale<D>
    {
    public:

        using base_type = xscale<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::vector<color_type>, derived_type, colors);
        XPROPERTY(xtl::xoptional<double>, derived_type, max);
        XPROPERTY(xtl::xoptional<double>, derived_type, mid);
        XPROPERTY(xtl::xoptional<double>, derived_type, min);
        XPROPERTY(std::string, derived_type, scale_type, "linear");
        XPROPERTY(std::string, derived_type, scheme, "RdYlGn");

    protected:

        xcolor_scale();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using color_scale = xw::xmaterialize<xcolor_scale>;

    /************************************
     * xordinal_color_scale declaration *
     ************************************/

    template <class D>
    class xordinal_color_scale : public xcolor_scale<D>
    {
    public:

        using base_type = xcolor_scale<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);
        XPROPERTY(std::vector<double>, derived_type, domain);

    protected:

        xordinal_color_scale();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using ordinal_color_scale = xw::xmaterialize<xordinal_color_scale>;

    /**************************
     * xgeo_scale declaration *
     **************************/

    template <class D>
    class xgeo_scale : public xscale<D>
    {
    public:

        using base_type = xscale<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

    protected:

        xgeo_scale();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    /*************************
     * xmercator declaration *
     *************************/

    template <class D>
    class xmercator : public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;

        //using pair_type = std::pair<double, double>;
        using pair_type = std::vector<double>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(pair_type, derived_type, center, pair_type({0, 60}));
        XPROPERTY(pair_type, derived_type, rotate, pair_type({0, 0}));
        XPROPERTY(double, derived_type, scale_factor, 190);

    protected:

        xmercator();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using mercator = xw::xmaterialize<xmercator>;

    /*****************************
     * xorthographic declaration *
     *****************************/

    template <class D>
    class xorthographic : public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;
        //using pair_type = std::pair<double, double>;
        using pair_type = std::vector<double>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(pair_type, derived_type, center, pair_type({0, 60}));
        XPROPERTY(double, derived_type, clip_angle, 90.0);
        XPROPERTY(double, derived_type, precision, 0.1);
        XPROPERTY(pair_type, derived_type, rotate, pair_type({0, 0}));
        XPROPERTY(double, derived_type, scale_factor, 145.0);

    protected:

        xorthographic();

    private:

        void set_defaults();
    };

    using orthographic = xw::xmaterialize<xorthographic>;

    /***************************
     * xalbers_usa declaration *
     ***************************/

    template <class D>
    class xalbers_usa : public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(double, derived_type, scale_factor, 1200);

    protected:

        xalbers_usa();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using albers_usa = xw::xmaterialize<xalbers_usa>;

    /***********************
     * xalbers declaration *
     ***********************/

    template <class D>
    class xalbers : public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;

        //using pair_type = std::pair<double, double>;
        using pair_type = std::vector<double>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(pair_type, derived_type, center, pair_type({0, 60}));
        XPROPERTY(pair_type, derived_type, parallels, pair_type({29.5, 45.5}));
        XPROPERTY(double, derived_type, precision, 0.1);
        XPROPERTY(pair_type, derived_type, rotate, pair_type({96, 0}));
        XPROPERTY(double, derived_type, scale_factor, 250);

    protected:

        xalbers();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using albers = xw::xmaterialize<xalbers>;

    /************************
     * scale implementation *
     ************************/

    template <class D>
    inline void xscale<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(reverse, patch, buffers);
        set_property_from_patch(allow_padding, patch, buffers);
    }

    template <class D>
    inline void xscale<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(reverse, state["buffers"], buffers);
        xwidgets_serialize(allow_padding, state["allow_padding"], buffers);
    }

    template <class D>
    inline xscale<D>::xscale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xscale<D>::set_defaults()
    {
        this->_model_name() = "ScaleModel";
        this->_view_name() = "Scale";
    }

    /*******************************
     * linear_scale implementation *
     *******************************/

    template <class D>
    inline void xlinear_scale<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(min, patch, buffers);
        set_property_from_patch(max, patch, buffers);
        set_property_from_patch(stabilized, patch, buffers);
        set_property_from_patch(mid_range, patch, buffers);
        set_property_from_patch(min_range, patch, buffers);
    }

    template <class D>
    inline void xlinear_scale<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(min, state["min"], buffers);
        xwidgets_serialize(max, state["max"], buffers);
        xwidgets_serialize(stabilized, state["stabilized"], buffers);
        xwidgets_serialize(mid_range, state["mid_range"], buffers);
        xwidgets_serialize(min_range, state["min_range"], buffers);
    }

    template <class D>
    inline xlinear_scale<D>::xlinear_scale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xlinear_scale<D>::set_defaults()
    {
        this->_model_name() = "LinearScaleModel";
        this->_view_name() = "LinearScale";
    }

    /****************************
     * log_scale implementation *
     ****************************/

    template <class D>
    inline void xlog_scale<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(min, patch, buffers);
        set_property_from_patch(max, patch, buffers);
    }

    template <class D>
    inline void xlog_scale<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(min, state["min"], buffers);
        xwidgets_serialize(max, state["max"], buffers);
    }

    template <class D>
    inline xlog_scale<D>::xlog_scale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xlog_scale<D>::set_defaults()
    {
        this->_model_name() = "LogScaleModel";
        this->_view_name() = "LogScale";
    }

    /*********************************
     * xordinal_scale implementation *
     *********************************/

    template <class D>
    inline void xordinal_scale<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(domain, patch, buffers);
    }

    template <class D>
    inline void xordinal_scale<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(domain, state["domain"], buffers);
    }

    template <class D>
    inline xordinal_scale<D>::xordinal_scale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xordinal_scale<D>::set_defaults()
    {
        this->_view_name() = "OrdinalScale";
        this->_model_name() = "OrdinalScaleModel";
    }

    /*******************************
     * xcolor_scale implementation *
     *******************************/

    template <class D>
    inline void xcolor_scale<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(colors, patch, buffers);
        set_property_from_patch(max, patch, buffers);
        set_property_from_patch(mid, patch, buffers);
        set_property_from_patch(min, patch, buffers);
        set_property_from_patch(scale_type, patch, buffers);
        set_property_from_patch(scheme, patch, buffers);
    }

    template <class D>
    inline void xcolor_scale<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(colors, state["colors"], buffers);
        xwidgets_serialize(max, state["max"], buffers);
        xwidgets_serialize(mid, state["mid"], buffers);
        xwidgets_serialize(min, state["min"], buffers);
        xwidgets_serialize(scale_type, state["scale_type"], buffers);
        xwidgets_serialize(scheme, state["scheme"], buffers);
    }

    template <class D>
    inline xcolor_scale<D>::xcolor_scale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xcolor_scale<D>::set_defaults()
    {
        this->_view_name() = "ColorScale";
        this->_model_name() = "ColorScaleModel";
    }

    /***************************************
     * xordinal_color_scale implementation *
     ***************************************/

    template <class D>
    inline void xordinal_color_scale<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(domain, patch, buffers);
    }

    template <class D>
    inline void xordinal_color_scale<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(domain, state["domain"], buffers);
    }

    template <class D>
    inline xordinal_color_scale<D>::xordinal_color_scale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xordinal_color_scale<D>::set_defaults()
    {
        this->_view_name() = "OrdinalColorScale";
        this->_model_name() = "OrdinalScaleModel";
    }

    /*****************************
     * xgeo_scale implementation *
     *****************************/

    template <class D>
    inline void xgeo_scale<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
    }

    template <class D>
    inline void xgeo_scale<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
    }

    template <class D>
    inline xgeo_scale<D>::xgeo_scale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xgeo_scale<D>::set_defaults()
    {
        this->_view_name() = "GeoScale";
        this->_model_name() = "GeoScaleModel";
    }

    /****************************
     * xmercator implementation *
     ****************************/

    template <class D>
    inline void xmercator<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(center, patch, buffers);
        set_property_from_patch(rotate, patch, buffers);
        set_property_from_patch(scale_factor, patch, buffers);
    }

    template <class D>
    inline void xmercator<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(center, state["center"], buffers);
        xwidgets_serialize(rotate, state["rotate"], buffers);
        xwidgets_serialize(scale_factor, state["scale_factor"], buffers);
    }

    template <class D>
    inline xmercator<D>::xmercator()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xmercator<D>::set_defaults()
    {
        this->_view_name() = "Mercator";
        this->_model_name() = "MercatorModel";
    }

    /********************************
     * xorthographic implementation *
     ********************************/

    template <class D>
    inline void xorthographic<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(center, patch, buffers);
        set_property_from_patch(clip_angle, patch, buffers);
        set_property_from_patch(precision, patch, buffers);
        set_property_from_patch(rotate, patch, buffers);
        set_property_from_patch(scale_factor, patch, buffers);
    }

    template <class D>
    inline void xorthographic<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(center, state["center"], buffers);
        xwidgets_serialize(clip_angle, state["clip_angle"], buffers);
        xwidgets_serialize(precision, state["precision"], buffers);
        xwidgets_serialize(rotate, state["rotate"], buffers);
        xwidgets_serialize(scale_factor, state["scale_factor"], buffers);
    }

    template <class D>
    inline xorthographic<D>::xorthographic()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xorthographic<D>::set_defaults()
    {
        this->_view_name() = "Orthographic";
        this->_model_name() = "OrthographicModel";
    }

    /******************************
     * xalbers_usa implementation *
     ******************************/

    template <class D>
    inline void xalbers_usa<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(scale_factor, patch, buffers);
    }

    template <class D>
    inline void xalbers_usa<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(scale_factor, state["scale_factor"], buffers);
    }

    template <class D>
    inline xalbers_usa<D>::xalbers_usa()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xalbers_usa<D>::set_defaults()
    {
        this->_view_name() = "AlbersUSA";
        this->_model_name() = "AlbersUSAModel";
    }

    /**************************
     * xalbers implementation *
     **************************/

    template <class D>
    inline void xalbers<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(center, patch, buffers);
        set_property_from_patch(parallels, patch, buffers);
        set_property_from_patch(precision, patch, buffers);
        set_property_from_patch(rotate, patch, buffers);
        set_property_from_patch(scale_factor, patch, buffers);
    }

    template <class D>
    inline void xalbers<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(center, state["center"], buffers);
        xwidgets_serialize(parallels, state["parallels"], buffers);
        xwidgets_serialize(precision, state["precision"], buffers);
        xwidgets_serialize(rotate, state["rotate"], buffers);
        xwidgets_serialize(scale_factor, state["scale_factor"], buffers);
    }

    template <class D>
    inline xalbers<D>::xalbers()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xalbers<D>::set_defaults()
    {
        this->_view_name() = "Albers";
        this->_model_name() = "AlbersModel";
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xpl::xlinear_scale>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xlinear_scale>>;
    extern template xw::xmaterialize<xpl::xlinear_scale>::xmaterialize();

    extern template class xw::xmaterialize<xpl::xlog_scale>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xlog_scale>>;
    extern template xw::xmaterialize<xpl::xlog_scale>::xmaterialize();

    extern template class xw::xmaterialize<xpl::xcolor_scale>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xcolor_scale>>;
    extern template xw::xmaterialize<xpl::xcolor_scale>::xmaterialize();

    extern template class xw::xmaterialize<xpl::xordinal_scale>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xordinal_scale>>;
    extern template xw::xmaterialize<xpl::xordinal_scale>::xmaterialize();

    extern template class xw::xmaterialize<xpl::xordinal_color_scale>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xordinal_color_scale>>;
    extern template xw::xmaterialize<xpl::xordinal_color_scale>::xmaterialize();

    extern template class xw::xmaterialize<xpl::xmercator>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xmercator>>;
    extern template xw::xmaterialize<xpl::xmercator>::xmaterialize();

    extern template class xw::xmaterialize<xpl::xorthographic>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xorthographic>>;
    extern template xw::xmaterialize<xpl::xorthographic>::xmaterialize();

    extern template class xw::xmaterialize<xpl::xalbers>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xalbers>>;
    extern template xw::xmaterialize<xpl::xalbers>::xmaterialize();

    extern template class xw::xmaterialize<xpl::xalbers_usa>;
    extern template class xw::xtransport<xw::xmaterialize<xpl::xalbers_usa>>;
    extern template xw::xmaterialize<xpl::xalbers_usa>::xmaterialize();
#endif

#endif
