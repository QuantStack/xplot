#include "xplot/xaxes.hpp"

template class XPLOT_API xw::xmaterialize<xpl::xaxis>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xaxis>>;
template class XPLOT_API xw::xgenerator<xpl::xaxis>;
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xaxis>>;

template class XPLOT_API xw::xmaterialize<xpl::xcolor_axis>;
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xcolor_axis>>;
template class XPLOT_API xw::xgenerator<xpl::xcolor_axis>;
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xcolor_axis>>;
