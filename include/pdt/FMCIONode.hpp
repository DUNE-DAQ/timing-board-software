/**
 * @file FMCIONode.hpp
 *
 * FMCIONode is a class providing an interface
 * to the FMC IO firmware block.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TIMING_BOARD_SOFTWARE_INCLUDE_PDT_FMCIONODE_HPP_
#define TIMING_BOARD_SOFTWARE_INCLUDE_PDT_FMCIONODE_HPP_

// PDT Headers
#include "pdt/IONode.hpp"
#include "TimingIssues.hpp"

// uHal Headers
#include "uhal/DerivedNode.hpp"

// C++ Headers
#include <chrono>

namespace dunedaq {
namespace pdt {

/**
 * @brief      Class for the timing FMC board.
 */
class FMCIONode : public IONode {
    UHAL_DERIVEDNODE(FMCIONode)

public:
    FMCIONode(const uhal::Node& aNode);
    virtual ~FMCIONode();
    
    /**
     * @brief     Get status string, optionally print.
     */
    std::string get_status(bool aPrint=false) const override;

    /**
     * @brief      Reset timing node.
     */
    void reset(const std::string& aClockConfigFile="") const override;

};

} // namespace pdt
} // namespace dunedaq

#endif // TIMING_BOARD_SOFTWARE_INCLUDE_PDT_FMCIONODE_HPP_