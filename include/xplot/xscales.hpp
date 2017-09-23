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
}

#endif
