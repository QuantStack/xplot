#include "xplot/xmarks.hpp"

template class XPLOT_API xw::xmaterialize<xpl::xlines>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xlines>>;

template class XPLOT_API xw::xmaterialize<xpl::xscatter>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xscatter>>;

template class XPLOT_API xw::xmaterialize<xpl::xpie>;
template xw::xmaterialize<xpl::xpie>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xpie>>;

template class XPLOT_API xw::xmaterialize<xpl::xlabel>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xlabel>>;

template class XPLOT_API xw::xmaterialize<xpl::xhist>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xhist>>;

template class XPLOT_API xw::xmaterialize<xpl::xboxplot>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xboxplot>>;

template class XPLOT_API xw::xmaterialize<xpl::xbars>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xbars>>;

template class XPLOT_API xw::xmaterialize<xpl::xheat_map>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xheat_map>>;

template class XPLOT_API xw::xmaterialize<xpl::xgrid_heat_map>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xgrid_heat_map>>;

template class XPLOT_API xw::xmaterialize<xpl::xmap>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xmap>>;
