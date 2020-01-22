#include "xplot/xfigure.hpp"

template class XPLOT_API xw::xmaterialize<xpl::xfigure>;
template xw::xmaterialize<xpl::xfigure>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xfigure>>;
