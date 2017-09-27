/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_INTERACTS_HPP
#define XPLOT_INTERACTS_HPP

#include "xplot.hpp"

namespace xpl
{
    /****************************
    * xinteraction declaration *
    ****************************/

    template<class D>
    class xinteraction: public xplot<D>
    {
    public:

        using base_type = xplot<D>;
        using derived_type = D;
        
        xinteraction();
        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

    private:

        void set_defaults();
    };

    using interaction = xw::xmaterialize<xinteraction>;

    /*************************
    * xpan_zoom declaration *
    *************************/

    template<class D>
    class xpan_zoom: public xinteraction<D>
    {
    public:

        using base_type = xinteraction<D>;
        using derived_type = D;

        xpan_zoom();

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson& patch);

        XPROPERTY(bool, derived_type, allow_pan, true);
        XPROPERTY(bool, derived_type, allow_zoom, true);
        XPROPERTY(::xeus::xjson, derived_type, scales);

    private:

        void set_defaults();
    };

    using pan_zoom = xw::xmaterialize<xpan_zoom>;

    /*******************************
    * xinteraction implementation *
    *******************************/

    template <class D>
    inline xinteraction<D>::xinteraction()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xinteraction<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
    }

    template <class D>
    inline xeus::xjson xinteraction<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        return state;
    }

    template <class D>
    inline void xinteraction<D>::set_defaults()
    {
        this->_view_name() = "Interaction";
        this->_model_name() = "BaseModel";
    }

    /****************************
    * xpan_zoom implementation *
    ****************************/

    template <class D>
    inline xpan_zoom<D>::xpan_zoom()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xpan_zoom<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(allow_pan, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(allow_zoom, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(scales, patch);
    }

    template <class D>
    inline xeus::xjson xpan_zoom<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();
        XOBJECT_SET_PATCH_FROM_PROPERTY(allow_pan, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(allow_zoom, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(scales, state);

        return state;
    }

    template <class D>
    inline void xpan_zoom<D>::set_defaults()
    {
        this->_view_name() = "PanZoom";
        this->_model_name() = "PanZoomModel";
    }
}
#endif