// Boost Headers
#include <boost/python/def.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/class.hpp>
#include <boost/python/enum.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/operators.hpp>

#include "pdt/TLUIONode.hpp"
#include "pdt/PC059IONode.hpp"
#include "pdt/FMCIONode.hpp"
#include "pdt/FIBIONode.hpp"

#include "pdt/PDIMasterNode.hpp"

#include "pdt/PDIMasterDesign.hpp"
#include "pdt/FanoutDesign.hpp"
#include "pdt/MasterMuxDesign.hpp"


// Namespace resolution
using namespace boost::python;

namespace pdt {
namespace python {

void
register_top_designs() {

      // PD-I master design on TLU
      class_<pdt::PDIMasterDesign<TLUIONode>, bases<uhal::Node> > ("PDIMasterDesign<TLUIONode>", init<const uhal::Node&>())
      .def("getStatus", &pdt::PDIMasterDesign<TLUIONode>::getStatus)
      .def("applyEndpointDelay", &pdt::PDIMasterDesign<TLUIONode>::applyEndpointDelay)
      .def("measureEndpointRTT", &pdt::PDIMasterDesign<TLUIONode>::measureEndpointRTT)
      ;

      // PD-I master design on fmc
      class_<pdt::PDIMasterDesign<FMCIONode>, bases<uhal::Node> > ("PDIMasterDesign<FMCIONode>", init<const uhal::Node&>())
      .def("getStatus", &pdt::PDIMasterDesign<FMCIONode>::getStatus)
      .def("applyEndpointDelay", &pdt::PDIMasterDesign<FMCIONode>::applyEndpointDelay)
      .def("measureEndpointRTT", &pdt::PDIMasterDesign<FMCIONode>::measureEndpointRTT)
      ;

      // PD-I fanout design on PC059
      class_<pdt::FanoutDesign<PC059IONode,PDIMasterNode>, bases<uhal::Node> > ("FanoutDesign<PC059IONode,PDIMasterNode>", init<const uhal::Node&>())
      .def("switchSFPMUXChannel", &pdt::FanoutDesign<PC059IONode,PDIMasterNode>::switchSFPMUXChannel)
      .def("applyEndpointDelay", &pdt::FanoutDesign<PC059IONode,PDIMasterNode>::applyEndpointDelay)
      .def("measureEndpointRTT", &pdt::FanoutDesign<PC059IONode,PDIMasterNode>::measureEndpointRTT)
      .def("scanSFPMUX", &pdt::FanoutDesign<PC059IONode,PDIMasterNode>::scanSFPMUX)
      ;

      // PD-I fanout design on FIB
      class_<pdt::FanoutDesign<FIBIONode,PDIMasterNode>, bases<uhal::Node> > ("FanoutDesign<FIBIONode,PDIMasterNode>", init<const uhal::Node&>())
      .def("switchSFPMUXChannel", &pdt::FanoutDesign<FIBIONode,PDIMasterNode>::switchSFPMUXChannel)
      .def("applyEndpointDelay", &pdt::FanoutDesign<FIBIONode,PDIMasterNode>::applyEndpointDelay)
      .def("measureEndpointRTT", &pdt::FanoutDesign<FIBIONode,PDIMasterNode>::measureEndpointRTT)
      .def("scanSFPMUX", &pdt::FanoutDesign<FIBIONode,PDIMasterNode>::scanSFPMUX)
      ;

      // PD-I ouroboros design on pc059
      class_<pdt::MasterMuxDesign<PC059IONode,PDIMasterNode>, bases<uhal::Node> > ("MasterMuxDesign<PC059IONode,PDIMasterNode>", init<const uhal::Node&>())
      .def("switchSFPMUXChannel", &pdt::MasterMuxDesign<PC059IONode,PDIMasterNode>::switchSFPMUXChannel)
      .def("applyEndpointDelay", &pdt::MasterMuxDesign<PC059IONode,PDIMasterNode>::applyEndpointDelay)
      .def("measureEndpointRTT", &pdt::MasterMuxDesign<PC059IONode,PDIMasterNode>::measureEndpointRTT)
      .def("scanSFPMUX", &pdt::MasterMuxDesign<PC059IONode,PDIMasterNode>::scanSFPMUX)
      ;

      // PD-I ouroboros design on FIB
      class_<pdt::MasterMuxDesign<FIBIONode,PDIMasterNode>, bases<uhal::Node> > ("MasterMuxDesign<FIBIONode,PDIMasterNode>", init<const uhal::Node&>())
      .def("switchSFPMUXChannel", &pdt::MasterMuxDesign<FIBIONode,PDIMasterNode>::switchSFPMUXChannel)
      .def("applyEndpointDelay", &pdt::MasterMuxDesign<FIBIONode,PDIMasterNode>::applyEndpointDelay)
      .def("measureEndpointRTT", &pdt::MasterMuxDesign<FIBIONode,PDIMasterNode>::measureEndpointRTT)
      .def("scanSFPMUX", &pdt::MasterMuxDesign<FIBIONode,PDIMasterNode>::scanSFPMUX)
      ;

}

} // namespace python
} // namespace pdt