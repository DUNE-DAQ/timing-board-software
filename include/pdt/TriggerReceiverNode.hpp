#ifndef TIMING_BOARD_SOFTWARE_INCLUDE_PDT_TRIGGERRECEIVERNODE_HPP_
#define TIMING_BOARD_SOFTWARE_INCLUDE_PDT_TRIGGERRECEIVERNODE_HPP_

// uHal Headers
#include "uhal/DerivedNode.hpp"

// PDT Headers
#include "pdt/TimingNode.hpp"

namespace pdt {

/**
 * @brief      Class for master global node.
 */
class TriggerReceiverNode : public TimingNode {
    UHAL_DERIVEDNODE(TriggerReceiverNode)
public:
    TriggerReceiverNode(const uhal::Node& aNode);
    virtual ~TriggerReceiverNode();

    /**
     * @brief     Print the status of the timing node.
     */
    std::string getStatus(bool aPrint=false) const override;
    
    /**
     * @brief     Enable trigger rx endpoint
     */
    void enable() const;

    /**
     * @brief     Disable trigger rx endpoint
     */
    void disable() const;

    /**
     * @brief     Reset trigger rx endpoint
     */
    void reset() const;

    /**
     * @brief     Enable external triggers
     */
    void enableTriggers() const;

    /**
     * @brief     Disable external triggers
     */
    void disableTriggers() const;

};

} // namespace pdt

#endif // TIMING_BOARD_SOFTWARE_INCLUDE_PDT_TRIGGERRECEIVERNODE_HPP_