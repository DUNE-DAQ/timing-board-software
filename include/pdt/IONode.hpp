/**
 * @file IONode.hpp
 *
 * IONode is a base class providing an interface
 * to for IO firmware blocks.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TIMING_BOARD_SOFTWARE_INCLUDE_PDT_IONODE_HPP_
#define TIMING_BOARD_SOFTWARE_INCLUDE_PDT_IONODE_HPP_

// PDT Headers
#include "pdt/TimingNode.hpp"

#include "TimingIssues.hpp"

#include "pdt/I2CMasterNode.hpp"
#include "pdt/I2CSlave.hpp"
#include "pdt/SI534xNode.hpp"
#include "pdt/I2CExpanderNode.hpp"
#include "pdt/DACNode.hpp"
#include "pdt/FrequencyCounterNode.hpp"
#include "pdt/I2CSFPNode.hpp"

// uHal Headers
#include "uhal/DerivedNode.hpp"

// C++ Headers
#include <chrono>

namespace dunedaq {
namespace pdt {

/**
 * @brief      Base class for timing IO nodes.
 */
class IONode : public TimingNode {
protected:
    const std::string mUIDI2CBus;
    const std::string mUIDI2CDevice;
    const std::string mPLLI2CBus;
    const std::string mPLLI2CDevice;
    const std::vector<std::string> mClockNames;
    const std::vector<std::string> mSFPI2CBuses;


    /**
     * @brief      Reset timing node.
     */
    virtual void writeSoftResetRegister() const;
public:
    IONode(const uhal::Node& aNode, std::string aUIDI2CBus, std::string aUIDI2CDevice, std::string aPLLI2CBus, std::string aPLLI2CDevice, std::vector<std::string> aClockNames, std::vector<std::string> aSFPI2CBuses);
    virtual ~IONode();

    /**
     * @brief      Read the word identifying the timing board.
     *
     * @return     { description_of_the_return_value }
     */
    virtual uint32_t read_board_type() const;

    /**
     * @brief      Read the word identifying the FPFA carrier board.
     *
     * @return     { description_of_the_return_value }
     */
    virtual uint32_t read_carrier_type() const;

    /**
     * @brief      Read the word identifying the firmware design in the FPGA.
     *
     * @return     { description_of_the_return_value }
     */
    virtual uint32_t read_design_type() const;

    /**
     * @brief      Read the word containing the timing board UID.
     *
     * @return     { description_of_the_return_value }
     */
    virtual uint64_t read_board_uid() const;

    /**
     * @brief      Read the word identifying the timing board.
     *
     * @return     { description_of_the_return_value }
     */
    virtual BoardRevision get_board_revision() const;

    /**
     * @brief      Print hardware information
     */
    virtual std::string get_hardware_info(bool aPrint=false) const;

    /**
     * @brief      Get the full config path.
     *
     * @return     { description_of_the_return_value }
     */
    virtual std::string get_full_clock_config_file_path(const std::string& aClockConfigFile, int32_t aMode=-1) const;

    /**
     * @brief      Get the an I2C chip.
     *
     * @return     { description_of_the_return_value }
     */
    template < class T> 
    std::unique_ptr<const T> get_i2c_device(const std::string& i2cBusName, const std::string& i2cDeviceName) const;

    /**
     * @brief      Get the PLL chip.
     *
     * @return     { description_of_the_return_value }
     */
    virtual std::unique_ptr<const SI534xSlave> get_pll() const;

    /**
     * @brief      Configure clock chip.
     */
    virtual void configure_pll(const std::string& aClockConfigFile="") const;

    /**
     * @brief      Read frequencies of on-board clocks.
     */
    virtual std::vector<double> read_clock_frequencies() const;

    /**
     * @brief      Print frequencies of on-board clocks.
     */
    virtual std::string get_clock_frequencies_table(bool aPrint=false) const;

    /**
     * @brief      Print status of on-board PLL.
     */
    virtual std::string get_pll_status(bool aPrint=false) const;

    /**
     * @brief      Print status of on-board SFP.
     */
    virtual std::string get_sfp_status(uint32_t aSFPId, bool aPrint=false) const;

    /**
     * @brief      control tx laser of on-board SFP softly (I2C command)
     */
    virtual void switch_sfp_soft_tx_control_bit(uint32_t aSFPId, bool aOn) const;

    /**
     * @brief      Reset timing node.
     */
    virtual void soft_reset() const;

    /**
     * @brief      Reset timing node.
     */
    virtual void reset(const std::string& aClockConfigFile="") const = 0;
};

} // namespace pdt
} // namespace dunedaq

#include "pdt/detail/IONode.hxx"

#endif // TIMING_BOARD_SOFTWARE_INCLUDE_PDT_IONODE_HPP_