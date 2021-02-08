#ifndef __PDT_SFPEXPANDERNODE_HPP__
#define __PDT_SFPEXPANDERNODE_HPP__

#include <map>

#include "pdt/I2CSlave.hpp"
#include "pdt/I2CMasterNode.hpp"

namespace pdt
{
PDTExceptionClass(SFPExpanderBankIDError, "Clock configuration error");

/**
 * @class      I2CExpanderSlave
 *
 * @brief      I2C slave class to control SFP expander chips.
 * @author     Alessandro Thea
 * @date       April 2018
 */
class I2CExpanderSlave : public I2CSlave {
public:
    I2CExpanderSlave(const I2CMasterNode* aMaster, uint8_t aSlaveAddress);
    virtual ~I2CExpanderSlave();
  
    /**
     * @brief      Sets the inversion status for a set of channels.
     *
     * @param[in]  aBankId         A bank identifier
     * @param[in]  aInversionMask  A inversion mask
     */
    void setInversion( uint8_t aBankId, uint32_t aInversionMask ) const;

    /**
     * @brief      Set input/output mode for a set of channels
     *
     * @param[in]  aBankId  A bank identifier
     * @param[in]  aIOMask  A io mask
     */
    void setIO( uint8_t aBankId, uint32_t aIOMask ) const;

    /**
     * @brief      Reads inputs values
     *
     * @param[in]  aBankId  A bank identifier
     *
     * @return     { description_of_the_return_value }
     */
    uint32_t readInputs( uint8_t aBankId ) const;

    /**
     * @brief      Writes outputs values.
     *
     * @param[in]  aBankId  A bank identifier
     * @param[in]  aValues  A values
     */
    void setOutputs( uint8_t aBankId,  uint32_t aValues ) const;

    std::vector<uint32_t> debug() const;

    /**
     * @brief      Reads inputs values
     *
     * @param[in]  aBankId  A bank identifier
     *
     * @return     { description_of_the_return_value }
     */
    uint8_t readOutputsConfig( uint8_t aBankId ) const;

private:

    void ensureValidBankId( uint8_t aBankId ) const;

};

/**
 * @class      I2CExpanderNode
 *
 * @brief      uhal::Node implementing single I2C Master Slave connection to
 *             control SFP expander chips.
 * @author     Alessandro Thea
 * @date       April 2018
 */
class I2CExpanderNode : public I2CMasterNode, public I2CExpanderSlave {
    UHAL_DERIVEDNODE(I2CExpanderNode);
public:
    I2CExpanderNode(const uhal::Node& aNode);
    I2CExpanderNode(const I2CExpanderNode& aOther);
    virtual ~I2CExpanderNode();

};


} // namespace pdt

#endif /* __PDT_SFPEXPANDERNODE_HPP__ */