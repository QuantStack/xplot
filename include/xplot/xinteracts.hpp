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

    template <class D>
    class xinteraction : public xplot<D>
    {
    public:

        using base_type = xplot<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

    protected:

        xinteraction();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using interaction = xw::xmaterialize<xinteraction>;

    using interaction_generator = xw::xgenerator<xinteraction>;

    /*************************
     * xpan_zoom declaration *
     *************************/

    template <class D>
    class xpan_zoom : public xinteraction<D>
    {
    public:

        using base_type = xinteraction<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(bool, derived_type, allow_pan, true);
        XPROPERTY(bool, derived_type, allow_zoom, true);
        XPROPERTY(::xeus::xjson, derived_type, scales, xeus::xjson::object());

    protected:

        xpan_zoom();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using pan_zoom = xw::xmaterialize<xpan_zoom>;

    using pan_zoom_generator = xw::xgenerator<xpan_zoom>;

    /*******************************
     * xinteraction implementation *
     *******************************/

    template <class D>
    inline void xinteraction<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
    }

    template <class D>
    inline void xinteraction<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
    }

    template <class D>
    inline xinteraction<D>::xinteraction()
        : base_type()
    {
        set_defaults();
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
    inline void xpan_zoom<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
        xw::set_property_from_patch(allow_pan, patch, buffers);
        xw::set_property_from_patch(allow_zoom, patch, buffers);
        xw::set_property_from_patch(scales, patch, buffers);
    }

    template <class D>
    inline void xpan_zoom<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
        xw::set_patch_from_property(allow_pan, state, buffers);
        xw::set_patch_from_property(allow_zoom, state, buffers);
        xw::set_patch_from_property(scales, state, buffers);
    }

    template <class D>
    inline xpan_zoom<D>::xpan_zoom()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xpan_zoom<D>::set_defaults()
    {
        this->_view_name() = "PanZoom";
        this->_model_name() = "PanZoomModel";
    }
}
#endif
