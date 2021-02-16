#include "pdt/EndpointNode.hpp"

namespace dunedaq {
namespace pdt {

UHAL_REGISTER_DERIVED_NODE(EndpointNode)

//-----------------------------------------------------------------------------
EndpointNode::EndpointNode(const uhal::Node& aNode) : TimingNode(aNode) {
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
EndpointNode::~EndpointNode() {
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void
EndpointNode::enable(uint32_t partition, uint32_t address) const {
	getNode("csr.ctrl.tgrp").write(partition);

	if (address) {
		getNode("csr.ctrl.int_addr").write(0x1);
		getNode("csr.ctrl.addr").write(address);
	} else {
		getNode("csr.ctrl.int_addr").write(0x0);
	}

	getNode("csr.ctrl.ctr_rst").write(0x1);
	getNode("csr.ctrl.ctr_rst").write(0x0);
	getNode("csr.ctrl.ep_en").write(0x1);
	getNode("csr.ctrl.buf_en").write(0x1);
	getClient().dispatch();
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void
EndpointNode::disable() const {
	getNode("csr.ctrl.ep_en").write(0x0);
    getNode("csr.ctrl.buf_en").write(0x0);
    getClient().dispatch();
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void
EndpointNode::reset(uint32_t partition, uint32_t address) const {

	getNode("csr.ctrl.ep_en").write(0x0);
	getNode("csr.ctrl.buf_en").write(0x0);
	
	enable(partition, address);
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
std::string
EndpointNode::get_status(bool aPrint) const {
	
	std::stringstream lStatus;

	std::vector<std::pair<std::string, std::string> > lEPSummary;

	auto lEPTimestamp = getNode("tstamp").readBlock(2);
	auto lEPEventCounter = getNode("evtctr").read();
	auto lEPBufferCount = getNode("buf.count").read();
	auto lEPControl = read_sub_nodes(getNode("csr.ctrl"), false);
	auto lEPState = read_sub_nodes(getNode("csr.stat"), false);
	auto lEPCounters = getNode("ctrs").readBlock(kCommandNumber);
	getClient().dispatch();

	lEPSummary.push_back(std::make_pair("State", kEndpointStateMap.at(lEPState.find("ep_stat")->second.value())));
	lEPSummary.push_back(std::make_pair("Partition", std::to_string(lEPControl.find("tgrp")->second.value())));
	lEPSummary.push_back(std::make_pair("Address", std::to_string(lEPControl.find("addr")->second.value())));
	lEPSummary.push_back(std::make_pair("Timestamp", format_timestamp(lEPTimestamp)));
	lEPSummary.push_back(std::make_pair("Timestamp (hex)", format_reg_value(tstamp2int(lEPTimestamp))));
	lEPSummary.push_back(std::make_pair("EventCounter", std::to_string(lEPEventCounter.value())));
	std::string lBufferStatusString = !lEPState.find("buf_err")->second.value() ? "OK" : "Error";
	lEPSummary.push_back(std::make_pair("Buffer status", lBufferStatusString));
	lEPSummary.push_back(std::make_pair("Buffer occupancy", std::to_string(lEPBufferCount.value())));

	std::vector<std::pair<std::string, std::string> > lEPCommandCounters;

	for (uint32_t i=0; i < kCommandNumber; ++i) {
		lEPCommandCounters.push_back(std::make_pair(kCommandMap.at(i), std::to_string(lEPCounters[i])));	
	}

	lStatus << format_reg_table(lEPSummary, "Endpoint summary", {"", ""}) << std::endl;
	lStatus << format_reg_table(lEPState, "Endpoint state") << std::endl;
	lStatus << format_reg_table(lEPCommandCounters, "Endpoint counters", {"Command", "Counter"}); 

	if (aPrint) std::cout << lStatus.str();
    return lStatus.str();       
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
uint64_t
EndpointNode::read_timestamp() const {
	auto lTimestamp = getNode("tstamp").readBlock(2);
	getClient().dispatch();
    return tstamp2int(lTimestamp);
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
uint32_t
EndpointNode::read_buffer_count() const {
	auto lBufCount = getNode("buf.count").read();
	getClient().dispatch();
	return lBufCount.value();
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
uhal::ValVector< uint32_t >
EndpointNode::read_data_buffer(bool aReadall) const {
	
	auto lBufCount = getNode("buf.count").read();
	getClient().dispatch();

	ERS_INFO("Words available in readout buffer:      " << format_reg_value(lBufCount));

	uint32_t lEventsToRead = lBufCount.value() / kEventSize;
	
	ERS_INFO("Events available in readout buffer:     " << format_reg_value(lEventsToRead));

	uint32_t lWordsToRead = aReadall ? lBufCount.value() : lEventsToRead * kEventSize;

	ERS_INFO("Words to be read out in readout buffer: " << format_reg_value(lWordsToRead));
	
	if (!lWordsToRead) {
		ERS_LOG("No words to be read out.");
	}
	
	auto lBufData = getNode("buf.data").readBlock(lWordsToRead);
	getClient().dispatch();

    return lBufData;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
std::string
EndpointNode::get_data_buffer_table(bool aReadall, bool aPrint) const {

	std::stringstream lTable;
	auto lBufData = read_data_buffer(aReadall);

	std::vector<std::pair<std::string, uint32_t>> lBufferTable;

	uint32_t i=0;
	for (auto it=lBufData.begin(); it!=lBufData.end(); ++it, ++i) {
		std::stringstream lIndexStream;
		lIndexStream << std::setfill('0') << std::setw(4) << i;
		lBufferTable.push_back(std::make_pair(lIndexStream.str(), *it));
	}
	lTable << format_reg_table(lBufferTable, "Endpoint buffer", {"Word","Data"});
	
	if (aPrint) std::cout << lTable.str();
	return lTable.str();
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
double
EndpointNode::read_clock_frequency() const {
	std::vector<double> lFrequencies = getNode<FrequencyCounterNode>("freq").measure_frequencies(1);
	return lFrequencies.at(0);
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
uint32_t
EndpointNode::read_version() const {
	auto lBufCount = getNode("version").read();
	getClient().dispatch();
	return lBufCount.value();
}
//-----------------------------------------------------------------------------

} // namespace pdt
} // namespace dunedaq