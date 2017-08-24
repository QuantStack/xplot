/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_SCALES_HPP
#define XPLOT_SCALES_HPP

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
     * geo_scale declaration    *
     ****************************/

    template <class D>
    class xgeo_scale : public xscale<D>
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

    /***************************
     * mercator declaration    *
     ***************************/

    template <class D>
    class xmercator : public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;

        xmercator();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(double, derived_type, scale_factor, 190);
        XPROPERTY(std::pair<double, double>, derived_type, center, {0, 60});
        XPROPERTY(std::pair<double, double>, derived_type, rotate, {0, 0});
        
    private:

        void set_defaults();
    };

    using mercator = xw::xmaterialize<xmercator>;

    /*************************
     * albers declaration    *
     *************************/

    template <class D>
    class xalbers : public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;

        xalbers();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(double, derived_type, scale_factor, 250);
        XPROPERTY(std::pair<double, double>, derived_type, rotate, {96, 0});
        XPROPERTY(std::pair<double, double>, derived_type, center, {0, 60});
        XPROPERTY(std::pair<double, double>, derived_type, parallels, {29.5, 45.5});
        XPROPERTY(double, derived_type, precision, 0.1);
        
    private:

        void set_defaults();
    };

    using albers = xw::xmaterialize<xalbers>;

    /*****************************
     * albers_usa declaration    *
     *****************************/

    template <class D>
    class xalbers_usa : public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;

        xalbers();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(double, derived_type, scale_factor, 1200);
        
    private:

        void set_defaults();
    };

    using albers_usa = xw::xmaterialize<xalbers_usa>;

    /***********************************
     * equi_rectangular declaration    *
     ***********************************/

    template <class D>
    class xequi_rectangular : public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;

        xequi_rectangular();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(double, derived_type, scale_factor, 145);
        XPROPERTY(std::pair<double, double>, derived_type, center, {0, 60});
        
    private:

        void set_defaults();
    };

    using equi_rectangular = xw::xmaterialize<xequi_rectangular>;

    /*******************************
     * orthographic declaration    *
     *******************************/

    template <class D>
    class xorthographic : public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;

        xorthographic();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(double, derived_type, scale_factor, 145);
        XPROPERTY(std::pair<double, double>, derived_type, center, {0, 60});
        XPROPERTY(std::pair<double, double>, derived_type, rotate, {0, 60});
        XPROPERTY(double, derived_type, clip_angle, 90);
        XPROPERTY(double, derived_type, precision, 0.1);
        
    private:

        void set_defaults();
    };

    using orthographic = xw::xmaterialize<xorthographic>;

    /***************************
     * gnomonic declaration    *
     ***************************/

    template <class D>
    class xgnomonic : public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;

        xgnomonic();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(double, derived_type, scale_factor, 145);
        XPROPERTY(std::pair<double, double>, derived_type, center, {0, 60});
        XPROPERTY(double, derived_type, precision, 0.1);
        XPROPERTY(double, derived_type, clip_angle, 89.999);
        
    private:

        void set_defaults();
    };

    using ognomonic = xw::xmaterialize<xgnomonic>;

    /********************************
     * stereographic declaration    *
     ********************************/

    template <class D>
    class xstereographic : public xgeo_scale<D>
    {
    public:

        using base_type = xgeo_scale<D>;
        using derived_type = D;

        xstereographic();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(double, derived_type, scale_factor, 145);
        XPROPERTY(std::pair<double, double>, derived_type, center, {0, 60});
        XPROPERTY(double, derived_type, precision, 0.1);
        XPROPERTY(std::pair<double, double>, derived_type, rotate, {96, 0});
        XPROPERTY(double, derived_type, clip_angle, 179.9999);
        
    private:

        void set_defaults();
    };

    using stereographic = xw::xmaterialize<xstereographic>;

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

        XPROPERTY(XOPTIONAL(double), derived_type, min);
        XPROPERTY(XOPTIONAL(double), derived_type, max);
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

        XPROPERTY(XOPTIONAL(double), derived_type, min);
        XPROPERTY(XOPTIONAL(double), derived_type, max);

    private:

        void set_defaults();
    };

    using log_scale = xw::xmaterialize<xlog_scale>;

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

    /****************************
     * geo_scale implementation *
     ****************************/

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

    /***************************
     * mercator implementation *
     ***************************/

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

        XOBJECT_SET_PROPERTY_FROM_PATCH(scale_factor, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(center, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(rotate, patch);
    }

    template <class D>
    inline xeus::xjson xmercator<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(scale_factor, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(center, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(rotate, state);

        return state;
    }

    template <class D>
    inline void xmercator<D>::set_defaults()
    {
        this->_view_name() = "Mercator";
        this->_model_name() = "MercatorModel";
    }

    /*************************
     * albers implementation *
     *************************/

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

        XOBJECT_SET_PROPERTY_FROM_PATCH(scale_factor, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(rotate, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(center, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(parallels, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(precision, patch);
    }

    template <class D>
    inline xeus::xjson xalbers<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(scale_factor, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(rotate, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(center, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(parallels, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(precision, state);

        return state;
    }

    template <class D>
    inline void xalbers<D>::set_defaults()
    {
        this->_view_name() = "Albers";
        this->_model_name() = "AlbersModel";
    }

    /*****************************
     * albers_usa implementation *
     *****************************/

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

    /***********************************
     * equi_rectangular implementation *
     ***********************************/

    template <class D>
    inline xequi_rectangular<D>::xequi_rectangular()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xequi_rectangular<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(scale_factor, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(center, patch);
    }

    template <class D>
    inline xeus::xjson xequi_rectangular<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(scale_factor, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(center, state);

        return state;
    }

    template <class D>
    inline void xequi_rectangular<D>::set_defaults()
    {
        this->_view_name() = "EquiRectangular";
        this->_model_name() = "EquiRectangularModel";
    }

    /***********************************
     * orthographic implementation *
     ***********************************/

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

        XOBJECT_SET_PROPERTY_FROM_PATCH(scale_factor, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(center, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(rotate, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(clip_angle, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(precision, patch);
    }

    template <class D>
    inline xeus::xjson xorthographic<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(scale_factor, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(center, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(rotate, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(clip_angle, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(precision, state);

        return state;
    }

    template <class D>
    inline void xorthographic<D>::set_defaults()
    {
        this->_view_name() = "Orthographic";
        this->_model_name() = "OrthographicModel";
    }

    /***********************************
     * gnomonic implementation *
     ***********************************/

    template <class D>
    inline xgnomonic<D>::xgnomonic()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xgnomonic<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(scale_factor, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(center, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(precision, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(clip_angle, patch);
    }

    template <class D>
    inline xeus::xjson xgnomonic<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(scale_factor, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(center, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(precision, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(clip_angle, state);

        return state;
    }

    template <class D>
    inline void xgnomonic<D>::set_defaults()
    {
        this->_view_name() = "Gnomonic";
        this->_model_name() = "GnomonicModel";
    }

    /***********************************
     * stereographic implementation *
     ***********************************/

    template <class D>
    inline xstereographic<D>::xstereographic()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xstereographic<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(scale_factor, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(center, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(precision, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(rotate, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(clip_angle, patch);
    }

    template <class D>
    inline xeus::xjson xstereographic<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(scale_factor, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(center, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(precision, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(rotate, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(clip_angle, state);

        return state;
    }

    template <class D>
    inline void xstereographic<D>::set_defaults()
    {
        this->_view_name() = "Stereographic";
        this->_model_name() = "StereographicModel";
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
}

#endif
