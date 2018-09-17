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

#include "ns3/assert.h"
#include "ns3/log.h"
#include "mih-link-configuration-parameter.h"

NS_LOG_COMPONENT_DEFINE ("LinkConfigurationParameter");

namespace ns3 {
  namespace mih {
    LinkConfigurationParameter::LinkConfigurationParameter (void) :
      m_linkParameterType (0)
    {}
    LinkConfigurationParameter::LinkConfigurationParameter (Ptr<LinkParameterType> linkParameterType,
                                                            uint64_t timerInterval,
                                                            enum LinkConfigurationParameter::ThresholdAction thresholdAction, 
                                                            ThresholdList thresholdList) :
      m_linkParameterType (linkParameterType),
      m_timerInterval (timerInterval),
      m_thresholdAction (thresholdAction),
      m_thresholdList (thresholdList)
    {
      NS_LOG_WARN ("Check this copy hack: m_thresholdList (thresholdList)");
    }
    LinkConfigurationParameter::LinkConfigurationParameter (LinkConfigurationParameter const &o) :
      m_linkParameterType (o.m_linkParameterType),
      m_timerInterval (o.m_timerInterval),
      m_thresholdAction (o.m_thresholdAction),
      m_thresholdList (o.m_thresholdList)
    {
      NS_LOG_WARN ("Check this copy hack: m_thresholdList (o.thresholdList)");
    }
    Ptr<LinkConfigurationParameter> 
    LinkConfigurationParameter::CreateFromTlvType (uint8_t val)
    {
      NS_ASSERT (val == TLV_LINK_CONFIGURATION_PARAMETER);
      return Create<LinkConfigurationParameter> ();
    }
    TLV_TYPE_HELPER_IMPLEM (LinkConfigurationParameter, TLV_LINK_CONFIGURATION_PARAMETER);
    uint32_t 
    LinkConfigurationParameter::GetTlvSerializedSize (void) const
    {
      uint32_t payloadLength = 0;
      uint32_t lengthOfLengthField = 0;
      
      payloadLength = m_linkParameterType->GetTlvSerializedSize () +
        Tlv::GetSerializedSizeU64 () +
        Tlv::GetSerializedSizeU8 () +
        Tlv::GetSerializedSize (m_thresholdList);
      
      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);

      return 1 + lengthOfLengthField + payloadLength;
    }
    void 
    LinkConfigurationParameter::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;

      payloadLength = m_linkParameterType->GetTlvSerializedSize () +
        Tlv::GetSerializedSizeU64 () +
        Tlv::GetSerializedSizeU8 () +
        Tlv::GetSerializedSize (m_thresholdList);
      
      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);

      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field +
                                                 // Length field only;
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length
                                                       // field;
      
      m_linkParameterType->TlvSerialize (buffer);
      Tlv::SerializeU64 (buffer, m_timerInterval, TLV_LINK_CONFIGURATION_TIME_INTERVAL);
      Tlv::SerializeU8 (buffer, static_cast<uint8_t> (m_thresholdAction), TLV_LINK_CONFIGURATION_THRESHOLD_ACTION);
      ns3::mih::TlvSerialize (buffer, m_thresholdList);
    }
    uint32_t 
    LinkConfigurationParameter::TlvDeserialize (Buffer &buffer)
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

      m_linkParameterType = LinkParameterType::CreateFromTlvType (i.ReadU8 ());
      totalBytesRead += m_linkParameterType->TlvDeserialize (buffer);
      totalBytesRead += Tlv::DeserializeU64 (buffer, m_timerInterval, TLV_LINK_CONFIGURATION_TIME_INTERVAL);
      uint8_t thresholdAction = 0;
      totalBytesRead += Tlv::DeserializeU8 (buffer, thresholdAction, TLV_LINK_CONFIGURATION_THRESHOLD_ACTION);
      m_thresholdAction = static_cast<enum ThresholdAction> (thresholdAction);
      totalBytesRead += ns3::mih::TlvDeserialize (buffer, m_thresholdList);

      return totalBytesRead;
    }
    Ptr<LinkParameterType> 
    LinkConfigurationParameter::GetLinkParameterType (void)
    {
      return m_linkParameterType;
    }
    uint64_t 
    LinkConfigurationParameter::GetTimerInterval (void)
    {
      return m_timerInterval;
    }
    ThresholdListI 
    LinkConfigurationParameter::GetThresholdsListBegin (void)
    {
      return m_thresholdList.begin ();
    }
    ThresholdListI 
    LinkConfigurationParameter::GetThresholdsListEnd (void)
    {
      return m_thresholdList.end ();
    }
    uint32_t 
    LinkConfigurationParameter::GetThresholdsN (void)
    {
      return m_thresholdList.size ();
    }
    void 
    LinkConfigurationParameter::AddThresholdItem (Ptr<Threshold> thresholdItem)
    {
      NS_ASSERT (thresholdItem != 0);
      m_thresholdList.push_back (thresholdItem);
    }
    enum LinkConfigurationParameter::ThresholdAction 
    LinkConfigurationParameter::GetThresholdAction (void)
    {
      return m_thresholdAction;
    }
    uint32_t
    GetTlvSerializedSize (const LinkConfigurationParameterList &linkConfigurationParameterList)
    {
      return Tlv::GetSerializedSize<LinkConfigurationParameter> (linkConfigurationParameterList);
    }
    void
    TlvSerialize (Buffer &buffer, const LinkConfigurationParameterList &linkConfigurationParameterList)
    {
      Tlv::Serialize<LinkConfigurationParameter> (buffer, linkConfigurationParameterList, TLV_LINK_CONFIGURATION_PARAMETER_LIST);
    }
    uint32_t
    TlvDeserialize (Buffer &buffer, LinkConfigurationParameterList &linkConfigurationParameterList)
    {
      return Tlv::Deserialize<LinkConfigurationParameter> (buffer, linkConfigurationParameterList, TLV_LINK_CONFIGURATION_PARAMETER_LIST);      
    }
  } // namespace mih
} // namespace ns3
