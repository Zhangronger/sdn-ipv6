/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */            
/*
 * Copyright (c) 2008 IT-SUDPARIS
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Providence SALUMU M. <Providence.Salumu_Munga@it-sudparis.eu>
 */

#include "ns3/log.h"
#include "ns3/assert.h"
#include "mih-link-configuration-status.h"

NS_LOG_COMPONENT_DEFINE ("LinkConfigurationStatus");

namespace ns3 {
  namespace mih {
    
    LinkConfigurationStatus::LinkConfigurationStatus (Ptr<LinkParameterType> linkParameterType, 
                                                      Threshold threshold, 
                                                      bool configurationStatus) :
      m_linkParameterType (linkParameterType),
      m_threshold (threshold),
      m_configurationStatus (configurationStatus)
    {
      //      NS_ASSERT (linkParameterType != 0);
    }
    LinkConfigurationStatus::LinkConfigurationStatus (LinkConfigurationStatus const &o) :
      m_linkParameterType (o.m_linkParameterType),
      m_threshold (o.m_threshold),
      m_configurationStatus (o.m_configurationStatus)
    {
      NS_LOG_WARN ("Dangerous PTR copy: m_linkParameterType (o.m_linkParameterType)");
    }
    TLV_TYPE_HELPER_IMPLEM (LinkConfigurationStatus, TLV_LINK_CONFIGURATION_STATUS);
    Ptr<LinkConfigurationStatus> 
    LinkConfigurationStatus::CreateFromTlvType (uint8_t val)
    {
      NS_ASSERT (val == TLV_LINK_CONFIGURATION_STATUS);
      return Create<LinkConfigurationStatus> ();
    }
    LinkConfigurationStatus::~LinkConfigurationStatus (void)
    {
      m_linkParameterType = 0;
    }
    void 
    LinkConfigurationStatus::SetLinkParameterType (Ptr<LinkParameterType> linkParameterType)
    {
      m_linkParameterType = linkParameterType;
    }
    Ptr<LinkParameterType> 
    LinkConfigurationStatus::LinkConfigurationStatus::GetLinkParameterType (void)
    {
      return m_linkParameterType;
    }
    Threshold 
    LinkConfigurationStatus::GetThreshold (void)
    {
      return m_threshold;
    }
    bool 
    LinkConfigurationStatus::IsSuccess (void)
    {
      return m_configurationStatus;
    }
    uint32_t 
    LinkConfigurationStatus::GetTlvSerializedSize (void) const
    {
      uint32_t payloadLength = 0;
      uint32_t lengthOfLengthField = 0;
      
      NS_ASSERT (m_linkParameterType != 0);
      payloadLength = m_linkParameterType->GetTlvSerializedSize () +
        m_threshold.GetTlvSerializedSize () +
        Tlv::GetSerializedSizeBool ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      return 1 + lengthOfLengthField + payloadLength;
      
    }
    void
    LinkConfigurationStatus::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;
      
      payloadLength = m_linkParameterType->GetTlvSerializedSize () +
        m_threshold.GetTlvSerializedSize () +
        Tlv::GetSerializedSizeBool ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field +
                                                 // Length field only;

      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length field;

      m_linkParameterType->TlvSerialize (buffer);
      m_threshold.TlvSerialize (buffer);
      Tlv::SerializeBool (buffer, 
                          m_configurationStatus, 
                          TLV_LINK_CONFIGURATION_STATUS);
    }
    uint32_t 
    LinkConfigurationStatus::TlvDeserialize (Buffer &buffer)
    {
      uint32_t totalBytesRead = 0;
      uint32_t roomSize;
      uint32_t payloadLengthValue = 0;
      Buffer::Iterator i = buffer.Begin ();
      NS_ASSERT (i.ReadU8 () == GetTlvTypeValue ());
      totalBytesRead++;
      roomSize = i.ReadU8 ();
      totalBytesRead++;
      
      totalBytesRead += Tlv::ReadPayloadLengthField (i, roomSize, payloadLengthValue);
      buffer.RemoveAtStart (totalBytesRead);

      i = buffer.Begin ();
      Ptr<LinkParameterType> linkParamType = LinkParameterType::CreateFromTlvType (i.ReadU8 ());
      totalBytesRead += linkParamType->TlvDeserialize (buffer);
      totalBytesRead += m_threshold.TlvDeserialize (buffer);
      totalBytesRead += Tlv::DeserializeBool (buffer, 
                                              m_configurationStatus, 
                                              TLV_LINK_CONFIGURATION_STATUS);
      
      return totalBytesRead;
    }
    uint32_t
    GetTlvSerializedSize (const LinkConfigurationStatusList &linkConfigurationStatusList)
    {
      return Tlv::GetSerializedSize<LinkConfigurationStatus> (linkConfigurationStatusList);
    }
    void
    TlvSerialize (Buffer &buffer, const LinkConfigurationStatusList &linkConfigurationStatusList)
    {
      Tlv::Serialize<LinkConfigurationStatus> (buffer, linkConfigurationStatusList, TLV_LINK_CONFIGURATION_STATUS_LIST);
    }
    uint32_t
    TlvDeserialize (Buffer &buffer, LinkConfigurationStatusList &linkConfigurationStatusList)
    {
      return Tlv::Deserialize<LinkConfigurationStatus> (buffer, linkConfigurationStatusList, TLV_LINK_CONFIGURATION_STATUS_LIST);      
    }
  } // namespace mih
} // namespace ns3
