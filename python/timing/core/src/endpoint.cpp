#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "timing/EndpointNode.hpp"
#include "timing/CRTNode.hpp"

namespace py = pybind11;

namespace dunedaq {
namespace timing {
namespace python {

void
register_endpoint(py::module& m) {
  py::class_<timing::EndpointNode, uhal::Node> (m, "EndpointNode")
      .def(py::init<const uhal::Node&>())
      .def("disable", &timing::EndpointNode::disable)
      .def("enable", &timing::EndpointNode::enable, py::arg("partition") = 0, py::arg("address") = 0)
      .def("reset", &timing::EndpointNode::reset, py::arg("partition") = 0, py::arg("address") = 0)
      .def("read_buffer_count", &timing::EndpointNode::read_buffer_count)
      .def("read_data_buffer", &timing::EndpointNode::read_data_buffer, py::arg("read_all") = false)
      .def("get_data_buffer_table", &timing::EndpointNode::get_data_buffer_table, py::arg("read_all") = false, py::arg("print_out") = false)
      .def("read_version", &timing::EndpointNode::read_version)
      .def("read_timestamp", &timing::EndpointNode::read_timestamp)
      .def("read_clock_frequency", &timing::EndpointNode::read_clock_frequency)
      ;

  py::class_<timing::CRTNode, uhal::Node> (m, "CRTNode")
      .def(py::init<const uhal::Node&>())
      .def("disable", &timing::CRTNode::disable)
      .def("enable", &timing::CRTNode::enable)
      .def("get_status", &timing::CRTNode::get_status, py::arg("print_out") = false)
      .def("read_last_pulse_timestamp", &timing::CRTNode::read_last_pulse_timestamp)
      ;
}

} // namespace python
} // namespace timing
} // namespace dunedaq