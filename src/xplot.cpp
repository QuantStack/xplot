#include "xleaflet/xmap.hpp"

template class XLEAFLET_API xw::xmaterialize<xleaflet::xmap>;
template xw::xmaterialize<xleaflet::xmap>::xmaterialize();
template class XLEAFLET_API xw::xtransport<xw::xmaterialize<xleaflet::xmap>>;
template class XLEAFLET_API xw::xgenerator<xleaflet::xmap>;
template xw::xgenerator<xleaflet::xmap>::xgenerator();
template class XLEAFLET_API xw::xtransport<xw::xgenerator<xleaflet::xmap>>;
