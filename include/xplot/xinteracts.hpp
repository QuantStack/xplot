/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XPLOT_INTERACTS_HPP
#define XPLOT_INTERACTS_HPP

#include <utility>

#include "nlohmann/json.hpp"

#include "xplot.hpp"

namespace nl = nlohmann;

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

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

    protected:

        xinteraction();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using interaction = xw::xmaterialize<xinteraction>;

    template <class T, class R = void>
    struct enable_xinteraction
    {
        using type = std::enable_if_t<std::is_base_of<xinteraction<T>, T>::value, R>;
    };

    template <class T, class R = void>
    using enable_xinteraction_t = typename enable_xinteraction<T, R>::type;

    /*************************
     * xpan_zoom declaration *
     *************************/

    template <class D>
    class xpan_zoom : public xinteraction<D>
    {
    public:

        using base_type = xinteraction<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(bool, derived_type, allow_pan, true);
        XPROPERTY(bool, derived_type, allow_zoom, true);
        XPROPERTY(::nl::json, derived_type, scales, nl::json::object());

    protected:

        xpan_zoom();

        using base_type::base_type;

    private:

        void set_defaults();
    };

    using pan_zoom = xw::xmaterialize<xpan_zoom>;

    /*******************************
     * xinteraction implementation *
     *******************************/

    template <class D>
    inline void xinteraction<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
    }

    template <class D>
    inline void xinteraction<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
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
    inline void xpan_zoom<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);
        set_property_from_patch(allow_pan, patch, buffers);
        set_property_from_patch(allow_zoom, patch, buffers);
        set_property_from_patch(scales, patch, buffers);
    }

    template <class D>
    inline void xpan_zoom<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);
        xwidgets_serialize(allow_pan, state["allow_pan"], buffers);
        xwidgets_serialize(allow_zoom, state["allow_zoom"], buffers);
        xwidgets_serialize(scales, state["scales"], buffers);
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
