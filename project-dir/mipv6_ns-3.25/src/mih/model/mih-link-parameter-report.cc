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
#include "mih-link-parameter-report.h"

namespace ns3 {
  namespace mih {
    LinkParameterReport::LinkParameterReport (Threshold threshold, 
					      Ptr<LinkParameter> linkParameter) :
      m_linkParameter (linkParameter),
      m_threshold (threshold)
    {}
    LinkParameterReport::LinkParameterReport (LinkParameterReport const &o) :
      m_linkParameter (o.m_linkParameter),
      m_threshold (o.m_threshold)
    {}
    TLV_TYPE_HELPER_IMPLEM (LinkParameterReport, TLV_LINK_PARAMETER_REPORT)
    Ptr<LinkParameter> 
    LinkParameterReport::GetParameter (void)
    {
      return m_linkParameter;
    }
    Threshold
    LinkParameterReport::GetThreshold (void)
    {
      return m_threshold;
    }
    void
    LinkParameterReport::Print (std::ostream &os) const
    {
      NS_ASSERT (m_linkParameter != 0);
      os << "Link Parameter Report = (";
      m_linkParameter->Print (os);
      os << " | ";
      m_threshold.Print (os);
      os << ")";
    }
    uint32_t
    LinkParameterReport::GetTlvSerializedSize (void) const
    {
      uint32_t payloadLength = 0;
      uint32_t lengthOfLengthField = 0;
      
      NS_ASSERT (m_linkParameter != 0);
      payloadLength = m_linkParameter->GetTlvSerializedSize () +
        m_threshold.GetTlvSerializedSize ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);

      return 1 + lengthOfLengthField + payloadLength;
      
    }
    void
    LinkParameterReport::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;
      
      NS_ASSERT (m_linkParameter != 0);
      payloadLength = m_linkParameter->GetTlvSerializedSize () +
        m_threshold.GetTlvSerializedSize ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field + Length field only;
      
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length field;

      m_linkParameter->TlvSerialize (buffer);
      m_threshold.TlvSerialize (buffer);
      
    }
    uint32_t
    LinkParameterReport::TlvDeserialize (Buffer &buffer)
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
      m_linkParameter = LinkParameter::CreateFromTlvType (i.ReadU8 ());
      totalBytesRead += m_linkParameter->TlvDeserialize (buffer);
      totalBytesRead += m_threshold.TlvDeserialize (buffer);

      return totalBytesRead;
      
    }
    Ptr<LinkParameterReport>
    LinkParameterReport::CreateFromTlvType (uint8_t val)
    {
      NS_ASSERT (val == TLV_LINK_PARAMETER_REPORT);
      return Create<LinkParameterReport> ();
    }
    uint32_t
    GetTlvSerializedSize (const LinkParameterReportList &linkParameterReportList)
    {
      return Tlv::GetSerializedSize<LinkParameterReport> (linkParameterReportList);
    }
    void
    TlvSerialize (Buffer &buffer, const LinkParameterReportList &linkParameterReportList)
    {
      Tlv::Serialize<LinkParameterReport> (buffer, linkParameterReportList, TLV_LINK_PARAMETER_REPORT_LIST);
    }
    uint32_t
    TlvDeserialize (Buffer &buffer, LinkParameterReportList &linkParameterReportList)
    {
      return Tlv::Deserialize<LinkParameterReport> (buffer, linkParameterReportList, TLV_LINK_PARAMETER_REPORT_LIST);    
    }
  } // namespace mih
} // namespace ns3
