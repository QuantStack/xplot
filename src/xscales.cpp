#include "xplot/xscales.hpp"

template class XPLOT_API xw::xmaterialize<xpl::xlinear_scale>;
template xw::xmaterialize<xpl::xlinear_scale>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xlinear_scale>>;
template class XPLOT_API xw::xgenerator<xpl::xlinear_scale>;
template xw::xgenerator<xpl::xlinear_scale>::xgenerator();
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xlinear_scale>>;

template class XPLOT_API xw::xmaterialize<xpl::xlog_scale>;
template xw::xmaterialize<xpl::xlog_scale>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xlog_scale>>;
template class XPLOT_API xw::xgenerator<xpl::xlog_scale>;
template xw::xgenerator<xpl::xlog_scale>::xgenerator();
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xlog_scale>>;

template class XPLOT_API xw::xmaterialize<xpl::xcolor_scale>;
template xw::xmaterialize<xpl::xcolor_scale>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xcolor_scale>>;
template class XPLOT_API xw::xgenerator<xpl::xcolor_scale>;
template xw::xgenerator<xpl::xcolor_scale>::xgenerator();
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xcolor_scale>>;

template class XPLOT_API xw::xmaterialize<xpl::xordinal_scale>;
template xw::xmaterialize<xpl::xordinal_scale>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xordinal_scale>>;
template class XPLOT_API xw::xgenerator<xpl::xordinal_scale>;
template xw::xgenerator<xpl::xordinal_scale>::xgenerator();
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xordinal_scale>>;

template class XPLOT_API xw::xmaterialize<xpl::xordinal_color_scale>;
template xw::xmaterialize<xpl::xordinal_color_scale>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xordinal_color_scale>>;
template class XPLOT_API xw::xgenerator<xpl::xordinal_color_scale>;
template xw::xgenerator<xpl::xordinal_color_scale>::xgenerator();
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xordinal_color_scale>>;

template class XPLOT_API xw::xmaterialize<xpl::xmercator>;
template xw::xmaterialize<xpl::xmercator>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xmercator>>;
template class XPLOT_API xw::xgenerator<xpl::xmercator>;
template xw::xgenerator<xpl::xmercator>::xgenerator();
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xmercator>>;

template class XPLOT_API xw::xmaterialize<xpl::xorthographic>;
template xw::xmaterialize<xpl::xorthographic>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xorthographic>>;
template class XPLOT_API xw::xgenerator<xpl::xorthographic>;
template xw::xgenerator<xpl::xorthographic>::xgenerator();
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xorthographic>>;

template class XPLOT_API xw::xmaterialize<xpl::xalbers>;
template xw::xmaterialize<xpl::xalbers>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xalbers>>;
template class XPLOT_API xw::xgenerator<xpl::xalbers>;
template xw::xgenerator<xpl::xalbers>::xgenerator();
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xalbers>>;

template class XPLOT_API xw::xmaterialize<xpl::xalbers_usa>;
template xw::xmaterialize<xpl::xalbers_usa>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xalbers_usa>>;
template class XPLOT_API xw::xgenerator<xpl::xalbers_usa>;
template xw::xgenerator<xpl::xalbers_usa>::xgenerator();
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xalbers_usa>>;
