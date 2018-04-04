#include "xplot/xfigure.hpp"
#include "xplot/xmarks.hpp"

// Figure
template class XPLOT_API xw::xmaterialize<xpl::xfigure>;
template xw::xmaterialize<xpl::xfigure>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xfigure>>;
template class XPLOT_API xw::xgenerator<xpl::xfigure>;
template xw::xgenerator<xpl::xfigure>::xgenerator();
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xfigure>>;

// Marks
template class XPLOT_API xw::xmaterialize<xpl::xlines>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xlines>>;
template class XPLOT_API xw::xgenerator<xpl::xlines>;
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xlines>>;

template class XPLOT_API xw::xmaterialize<xpl::xscatter>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xscatter>>;
template class XPLOT_API xw::xgenerator<xpl::xscatter>;
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xscatter>>;

template class XPLOT_API xw::xmaterialize<xpl::xhist>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xhist>>;
template class XPLOT_API xw::xgenerator<xpl::xhist>;
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xhist>>;

template class XPLOT_API xw::xmaterialize<xpl::xbars>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xbars>>;
template class XPLOT_API xw::xgenerator<xpl::xbars>;
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xbars>>;
