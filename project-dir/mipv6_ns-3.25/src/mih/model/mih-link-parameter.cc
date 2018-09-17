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
#include "mih-link-parameter.h"

namespace ns3 {
  namespace mih {
    LinkParameter::LinkParameter (Ptr<LinkParameterType> parameterType, 
				  Ptr<ParameterValue> parameterValue) :
      m_linkParameterType (parameterType),
      m_parameterValue (parameterValue)
    {
    }
    LinkParameter::LinkParameter (LinkParameter const &o) :
      m_linkParameterType (o.m_linkParameterType),
      m_parameterValue (o.m_parameterValue)
    {}
    TLV_TYPE_HELPER_IMPLEM (LinkParameter, TLV_LINK_PARAMETER)
    Ptr<LinkParameter> 
    LinkParameter::CreateFromTlvType (uint8_t tlvTypeValue)
    {
      NS_ASSERT (tlvTypeValue == TLV_LINK_PARAMETER);
      return Create<LinkParameter> ();
    }
    Ptr<LinkParameterType> 
    LinkParameter::GetLinkParameterType (void)
    {
      return m_linkParameterType;
    }
    Ptr<ParameterValue> 
    LinkParameter::GetParameterValue (void)
    {
      return m_parameterValue;
    }
    LinkParameter::~LinkParameter (void)
    {
      m_linkParameterType = 0;
      m_parameterValue = 0;
    }
    uint32_t
    LinkParameter::GetTlvSerializedSize (void) const
    {
      uint32_t payloadLength = 0;
      uint32_t lengthOfLengthField = 0;

      NS_ASSERT (m_linkParameterType != 0);
      NS_ASSERT (m_parameterValue != 0);

      payloadLength = m_linkParameterType->GetTlvSerializedSize () +
        m_parameterValue->GetTlvSerializedSize ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      return 1 + lengthOfLengthField + payloadLength;      
    }
    void 
    LinkParameter::Print (std::ostream &os) const
    {
      NS_ASSERT (m_linkParameterType != 0);
      NS_ASSERT (m_parameterValue != 0);

      os << "Link Parameter = (";
      m_linkParameterType->Print (os);
      os << " | ";
      m_parameterValue->Print (os);
      os << ")";
    }
    void
    LinkParameter::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;

      NS_ASSERT (m_linkParameterType != 0);
      NS_ASSERT (m_parameterValue != 0);

      payloadLength = m_linkParameterType->GetTlvSerializedSize () +
        m_parameterValue->GetTlvSerializedSize ();
      
      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field + Length field only;
      
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length field;
      
      m_linkParameterType->TlvSerialize (buffer);
      m_parameterValue->TlvSerialize (buffer);
    }
    uint32_t
    LinkParameter::TlvDeserialize (Buffer &buffer)
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
      m_linkParameterType = LinkParameterType::CreateFromTlvType (i.ReadU8 ());
      buffer.RemoveAtStart (totalBytesRead);

      totalBytesRead += m_linkParameterType->TlvDeserialize (buffer);
      i = buffer.Begin ();
      m_parameterValue = ParameterValue::CreateFromTlvType (i.ReadU8 ());
      totalBytesRead += m_parameterValue->TlvDeserialize (buffer);
      return totalBytesRead;
    }
    uint32_t
    GetTlvSerializedSize (const LinkParameterList &linkParameterList)
    {
      return Tlv::GetSerializedSize<LinkParameter> (linkParameterList);
    }
    void
    TlvSerialize (Buffer &buffer, const LinkParameterList &linkParameterList)
    {
      Tlv::Serialize<LinkParameter> (buffer, linkParameterList, TLV_LINK_PARAMETER_LIST);
    }
    uint32_t
    TlvDeserialize (Buffer &buffer, LinkParameterList &linkParameterList)
    {
      return Tlv::Deserialize<LinkParameter> (buffer, linkParameterList, TLV_LINK_PARAMETER_LIST);
    }
  } // namespace mih
} // namespace ns3
