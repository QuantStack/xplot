#include "xplot/xscales.hpp"

template class XPLOT_API xw::xmaterialize<xpl::xlinear_scale>;
template xw::xmaterialize<xpl::xlinear_scale>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xlinear_scale>>;

template class XPLOT_API xw::xmaterialize<xpl::xlog_scale>;
template xw::xmaterialize<xpl::xlog_scale>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xlog_scale>>;

template class XPLOT_API xw::xmaterialize<xpl::xcolor_scale>;
template xw::xmaterialize<xpl::xcolor_scale>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xcolor_scale>>;

template class XPLOT_API xw::xmaterialize<xpl::xordinal_scale>;
template xw::xmaterialize<xpl::xordinal_scale>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xordinal_scale>>;

template class XPLOT_API xw::xmaterialize<xpl::xordinal_color_scale>;
template xw::xmaterialize<xpl::xordinal_color_scale>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xordinal_color_scale>>;

template class XPLOT_API xw::xmaterialize<xpl::xmercator>;
template xw::xmaterialize<xpl::xmercator>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xmercator>>;

template class XPLOT_API xw::xmaterialize<xpl::xorthographic>;
template xw::xmaterialize<xpl::xorthographic>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xorthographic>>;

template class XPLOT_API xw::xmaterialize<xpl::xalbers>;
template xw::xmaterialize<xpl::xalbers>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xalbers>>;

template class XPLOT_API xw::xmaterialize<xpl::xalbers_usa>;
template xw::xmaterialize<xpl::xalbers_usa>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xalbers_usa>>;
