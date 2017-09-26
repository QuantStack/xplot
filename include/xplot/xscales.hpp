/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_SCALES_HPP
#define XPLOT_SCALES_HPP

#include "xtl/xoptional.hpp"

#include "xplot.hpp"

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

        xscale();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(bool, derived_type, reverse);
        XPROPERTY(bool, derived_type, allow_padding);

    private:

        void set_defaults();
    };

    /****************************
     * linear_scale declaration *
     ****************************/

    template <class D>
    class xlinear_scale : public xscale<D>
    {
    public:

        using base_type = xscale<D>;
        using derived_type = D;

        xlinear_scale();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(xtl::xoptional<double>, derived_type, min);
        XPROPERTY(xtl::xoptional<double>, derived_type, max);
        XPROPERTY(bool, derived_type, stabilized, false);
        XPROPERTY(double, derived_type, mid_range, 0.8);
        XPROPERTY(double, derived_type, min_range, 0.6);

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

        xlog_scale();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(xtl::xoptional<double>, derived_type, min);
        XPROPERTY(xtl::xoptional<double>, derived_type, max);

    private:

        void set_defaults();
    };

    using log_scale = xw::xmaterialize<xlog_scale>;

    /******************************
    * xordinal_scale declaration *
    ******************************/

    template<class D>
    class xordinal_scale: public xscale<D> 
    {
    public:

        using base_type = xscale<D>;
        using derived_type = D;
        
        xordinal_scale();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(std::vector<double>, derived_type, domain);

    private:
        
        void set_defaults();
    };

    using ordinal_scale = xw::xmaterialize<xordinal_scale>;

    /****************************
    * xcolor_scale declaration *
    ****************************/

    template<class D>
    class xcolor_scale: public xscale<D>
    {
    public:

        using base_type = xscale<D>;
        using derived_type = D;

        xcolor_scale();

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(std::vector<color_type>, derived_type, colors);
        XPROPERTY(xtl::xoptional<double>, derived_type, max);
        XPROPERTY(xtl::xoptional<double>, derived_type, mid);
        XPROPERTY(xtl::xoptional<double>, derived_type, min);
        XPROPERTY(X_CASELESS_STR_ENUM(linear), derived_type, scale_type, "linear");
        XPROPERTY(std::string, derived_type, scheme, "RdYlGn");

    private:

        void set_defaults();
    };

    using color_scale = xw::xmaterialize<xcolor_scale>;

    /**************************
    * xgeo_scale declaration *
    **************************/

    template<class D>
    class xgeo_scale: public xscale<D>
    {
    public:

        using base_type = xscale<D>;
        using derived_type = D;

        xgeo_scale();
        
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

    private:

        void set_defaults();
    };

    using geo_scale = xw::xmaterialize<xgeo_scale>;

    /*************************
    * xmercator declaration *
    *************************/

    template<class D>
    class xmercator: public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;
        //using pair_type = std::pair<double, double>;
        using pair_type = std::vector<double>;
        
        xmercator();

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(pair_type, derived_type, center, pair_type({0, 60}));
        XPROPERTY(pair_type, derived_type, rotate, pair_type({0, 0}));
        XPROPERTY(double, derived_type, scale_factor, 190);

    private:

        void set_defaults();
    };

    using mercator = xw::xmaterialize<xmercator>;

    /*****************************
    * xorthographic declaration *
    *****************************/

    template<class D>
    class xorthographic: public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;
        //using pair_type = std::pair<double, double>;
        using pair_type = std::vector<double>;
        
        xorthographic();

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(pair_type, derived_type, center, pair_type({0, 60}));
        XPROPERTY(double, derived_type, clip_angle, 90.0);
        XPROPERTY(double, derived_type, precision, 0.1);
        XPROPERTY(pair_type, derived_type, rotate, pair_type({0, 0}));
        XPROPERTY(double, derived_type, scale_factor, 145.0);

    private:

        void set_defaults();
    };

    using orthographic = xw::xmaterialize<xorthographic>;

    /***************************
    * xalbers_usa declaration *
    ***************************/

    template<class D>
    class xalbers_usa: public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;

        xalbers_usa();

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(double, derived_type, scale_factor, 1200);

    private:

        void set_defaults();
    };

    using albers_usa = xw::xmaterialize<xalbers_usa>;

    /***********************
    * xalbers declaration *
    ***********************/

    template<class D>
    class xalbers: public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;
        //using pair_type = std::pair<double, double>;
        using pair_type = std::vector<double>;

        xalbers();

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(pair_type, derived_type, center, pair_type({0, 60}));
        XPROPERTY(pair_type, derived_type, parallels, pair_type({29.5, 45.5}));
        XPROPERTY(double, derived_type, precision, 0.1);
        XPROPERTY(pair_type, derived_type, rotate, pair_type({96, 0}));
        XPROPERTY(double, derived_type, scale_factor, 250);

    private:

        void set_defaults();
    };

    using albers = xw::xmaterialize<xalbers>;

    /************************
     * scale implementation *
     ************************/

    template <class D>
    inline xscale<D>::xscale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xscale<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(reverse, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(allow_padding, patch);
    }

    template <class D>
    inline xeus::xjson xscale<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(reverse, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(allow_padding, state);

        return state;
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
    inline xlinear_scale<D>::xlinear_scale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xlinear_scale<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(min, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(max, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(stabilized, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(mid_range, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(min_range, patch);
    }

    template <class D>
    inline xeus::xjson xlinear_scale<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(min, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(max, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(stabilized, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(mid_range, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(min_range, state);

        return state;
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
    inline xlog_scale<D>::xlog_scale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xlog_scale<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(min, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(max, patch);
    }

    template <class D>
    inline xeus::xjson xlog_scale<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(min, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(max, state);

        return state;
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
    inline xordinal_scale<D>::xordinal_scale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xordinal_scale<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(domain, patch);
    }

    template <class D>
    inline xeus::xjson xordinal_scale<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();
        XOBJECT_SET_PATCH_FROM_PROPERTY(domain, state);

        return state;
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
    inline xcolor_scale<D>::xcolor_scale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xcolor_scale<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(colors, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(max, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(mid, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(min, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(scale_type, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(scheme, patch);
    }

    template <class D>
    inline xeus::xjson xcolor_scale<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();
        XOBJECT_SET_PATCH_FROM_PROPERTY(colors, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(max, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(mid, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(min, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(scale_type, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(scheme, state);

        return state;
    }

    template <class D>
    inline void xcolor_scale<D>::set_defaults()
    {
        this->_view_name() = "ColorScale";
        this->_model_name() = "ColorScaleModel";
    }

    /*****************************
    * xgeo_scale implementation *
    *****************************/

    template <class D>
    inline xgeo_scale<D>::xgeo_scale()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xgeo_scale<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
    }

    template <class D>
    inline xeus::xjson xgeo_scale<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        return state;
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
    inline xmercator<D>::xmercator()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xmercator<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(center, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(rotate, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(scale_factor, patch);
    }

    template <class D>
    inline xeus::xjson xmercator<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();
        XOBJECT_SET_PATCH_FROM_PROPERTY(center, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(rotate, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(scale_factor, state);

        return state;
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
    inline xorthographic<D>::xorthographic()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xorthographic<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(center, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(clip_angle, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(precision, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(rotate, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(scale_factor, patch);
    }

    template <class D>
    inline xeus::xjson xorthographic<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();
        XOBJECT_SET_PATCH_FROM_PROPERTY(center, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(clip_angle, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(precision, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(rotate, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(scale_factor, state);

        return state;
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
    inline xalbers_usa<D>::xalbers_usa()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xalbers_usa<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(scale_factor, patch);
    }

    template <class D>
    inline xeus::xjson xalbers_usa<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();
        XOBJECT_SET_PATCH_FROM_PROPERTY(scale_factor, state);

        return state;
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
    inline xalbers<D>::xalbers()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xalbers<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(center, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(parallels, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(precision, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(rotate, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(scale_factor, patch);
    }

    template <class D>
    inline xeus::xjson xalbers<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();
        XOBJECT_SET_PATCH_FROM_PROPERTY(center, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(parallels, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(precision, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(rotate, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(scale_factor, state);

        return state;
    }

    template <class D>
    inline void xalbers<D>::set_defaults()
    {
        this->_view_name() = "Albers";
        this->_model_name() = "AlbersModel";
    }
}

#endif
