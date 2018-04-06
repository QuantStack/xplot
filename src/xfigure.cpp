#include "xplot/xfigure.hpp"

template class XPLOT_API xw::xmaterialize<xpl::xfigure>;
template xw::xmaterialize<xpl::xfigure>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xfigure>>;
template class XPLOT_API xw::xgenerator<xpl::xfigure>;
template xw::xgenerator<xpl::xfigure>::xgenerator();
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xfigure>>;
