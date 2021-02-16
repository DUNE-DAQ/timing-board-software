#include <string>
#include <sstream>

namespace dunedaq::pdt
{

// In leiu of UHAL_REGISTER_DERIVED_NODE
//-----------------------------------------------------------------------------
template< class IO>
uhal::Node* EndpointDesign<IO>::clone() const { 
    return new EndpointDesign<IO> ( static_cast<const EndpointDesign<IO>&> ( *this ) );
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
template< class IO>
EndpointDesign<IO>::EndpointDesign(const uhal::Node& aNode) : TopDesign<IO>(aNode) {
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
template< class IO>
EndpointDesign<IO>::~EndpointDesign() {
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
template<class IO>
std::string EndpointDesign<IO>::get_status(bool aPrint) const {
	std::stringstream lStatus;
	lStatus << this->get_io_node().get_pll_status();
	uint32_t lNumberOfEndpointNodes = EndpointDesign<IO>::get_number_of_endpoint_nodes();
	for (uint32_t i=0; i < lNumberOfEndpointNodes; ++i) {
		lStatus << "Endpoint node " << i << " status" << std::endl;
		lStatus << this->get_endpoint_node(i).get_status();
	}
	if (aPrint) std::cout << lStatus.str();
	return lStatus.str();
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
template< class IO>
void EndpointDesign<IO>::enable(uint32_t aEptId) const {
	 this->get_endpoint_node(aEptId).enable();
}
//-----------------------------------------------------------------------------

}