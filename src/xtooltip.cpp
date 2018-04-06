#include "xplot/xtooltip.hpp"

template class XPLOT_API xw::xmaterialize<xpl::xtooltip>;
template xw::xmaterialize<xpl::xtooltip>::xmaterialize();
template class XPLOT_API xw::xtransport<xw::xmaterialize<xpl::xtooltip>>;
template class XPLOT_API xw::xgenerator<xpl::xtooltip>;
template xw::xgenerator<xpl::xtooltip>::xgenerator();
template class XPLOT_API xw::xtransport<xw::xgenerator<xpl::xtooltip>>;
