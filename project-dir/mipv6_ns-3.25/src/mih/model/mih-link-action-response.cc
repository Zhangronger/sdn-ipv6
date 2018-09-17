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
#include "mih-link-action-response.h"

NS_LOG_COMPONENT_DEFINE ("ns3::mih::LinkActionResponse");

namespace ns3 {
  namespace mih {
    LinkActionResponse::LinkActionResponse (LinkType linkType,  Address l2Address, enum ActionResult actionResult) :
      m_linkType (linkType),
      m_mobileNodeAddress (l2Address),
      m_linkActionResult (actionResult)
    {}
    LinkActionResponse::LinkActionResponse (LinkActionResponse const &o) :
      m_linkType (o.m_linkType),
      m_mobileNodeAddress (o.m_mobileNodeAddress),
      m_linkActionResult (o.m_linkActionResult),
      m_scanResponseList (o.m_scanResponseList)
    {
      NS_LOG_WARN ("Dangerous list copy hack: m_scanResponseList (o.m_scanResponseList)!");
    }
    TLV_TYPE_HELPER_IMPLEM (LinkActionResponse, TLV_LINK_ACTION_RESPONSE);
    Ptr<LinkActionResponse> 
    LinkActionResponse::CreateFromTlvType (uint8_t val)
    {
      NS_ASSERT (val == TLV_LINK_ACTION_RESPONSE);
      return Create<LinkActionResponse> ();
    }
    LinkType
    LinkActionResponse::GetLinkType (void)
    {
      return m_linkType;
    }
    Address 
    LinkActionResponse::GetDeviceLinkAddress (void)
    {
      return m_mobileNodeAddress;
    }
    enum LinkActionResponse::ActionResult 
    LinkActionResponse::GetActionResult (void)
    {
      return m_linkActionResult; 
    }
    ScanResponseListI 
    LinkActionResponse::GetScanResponseListBegin (void)
    {
      return m_scanResponseList.begin ();
    }
    ScanResponseListI 
    LinkActionResponse::GetScanResponseListEnd (void)
    {
      return m_scanResponseList.end ();
    }
    uint32_t 
    LinkActionResponse::GetScanResponseN (void)
    {
      return m_scanResponseList.size ();
    }
    void 
    LinkActionResponse::AddScanResponse (Ptr<ScanResponse> scanResponse)
    {
      NS_ASSERT (scanResponse != 0);
    }
    void
    LinkActionResponse::SetScanResponseList (ScanResponseList scanResponseList)
    {
      m_scanResponseList = scanResponseList;
    }
    ScanResponseList 
    LinkActionResponse::GetScanResponseList (void)
    {
      return m_scanResponseList;
    }
    uint32_t
    LinkActionResponse::GetTlvSerializedSize (void) const
    {
      uint32_t payloadLength = 0;
      uint32_t lengthOfLengthField = 0;
      
      payloadLength = m_linkType.GetTlvSerializedSize () +
        Tlv::GetSerializedSize (m_mobileNodeAddress) +
        Tlv::GetSerializedSizeU8 () +
        ns3::mih::GetTlvSerializedSize (m_scanResponseList);

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      return 1 + lengthOfLengthField + payloadLength;
      
    }
    void 
    LinkActionResponse::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;

      payloadLength = m_linkType.GetTlvSerializedSize () +
        Tlv::GetSerializedSize (m_mobileNodeAddress) +
        Tlv::GetSerializedSizeU8 () +
        ns3::mih::GetTlvSerializedSize (m_scanResponseList);

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field + Length field only;
      
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length field;

      m_linkType.TlvSerialize (buffer);
      Tlv::Serialize (buffer, m_mobileNodeAddress, TLV_MN_LINK_IDENTIFIER);
      Tlv::SerializeU8 (buffer, static_cast<uint8_t> (m_linkActionResult), TLV_LINK_ACTION_RESULT);
      ns3::mih::TlvSerialize (buffer, m_scanResponseList);
    }
    uint32_t
    LinkActionResponse::TlvDeserialize (Buffer &buffer)
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

      totalBytesRead += m_linkType.TlvDeserialize (buffer);
      totalBytesRead += Tlv::Deserialize (buffer, m_mobileNodeAddress, TLV_MN_LINK_IDENTIFIER);
      uint8_t actionResult = 0;
      totalBytesRead += Tlv::DeserializeU8 (buffer, actionResult, TLV_LINK_ACTION_RESULT);
      m_linkActionResult = static_cast<enum LinkActionResponse::ActionResult> (actionResult);
      totalBytesRead += ns3::mih::TlvDeserialize (buffer, m_scanResponseList);

      return totalBytesRead;
    }      
    uint32_t
    GetTlvSerializedSize (const LinkActionResponseList &linkActionResponseList)
    {
      return Tlv::GetSerializedSize<LinkActionResponse> (linkActionResponseList);
    }
    void
    TlvSerialize (Buffer &buffer, const LinkActionResponseList &linkActionResponseList)
    {
      Tlv::Serialize<LinkActionResponse> (buffer, linkActionResponseList, TLV_LINK_ACTION_RESPONSE_LIST);
    }
    uint32_t
    TlvDeserialize (Buffer &buffer, LinkActionResponseList &linkActionResponseList)
    {
      return Tlv::Deserialize<LinkActionResponse> (buffer, linkActionResponseList, TLV_LINK_ACTION_RESPONSE_LIST);    
    }
    std::ostream&
    operator << (std::ostream &os, const LinkActionResponse &rhs)
    {
      std::string actionResStr = "UNDEFINED";
      switch (rhs.m_linkActionResult)
        {
        case LinkActionResponse::SUCCESS :
          actionResStr = "SUCCESS";
          break;
        case LinkActionResponse::FAILURE :
          actionResStr = "FAILURE";
          break;
        case LinkActionResponse::REFUSED :
          actionResStr = "REFUSED";
          break;
        case LinkActionResponse::INCAPABLE :
          actionResStr = "INCAPABLE";
          break;
        default:
          break;
        }
      os << "Link type = " << rhs.m_linkType
         << ", Device LL Address = " << rhs.m_mobileNodeAddress
         << ", Action Result = " << actionResStr
         << ", Scan Response List = ";
      return os;
    }
    std::ostream& 
    operator << (std::ostream &os, const LinkActionResponseList &rhs)
    {
      for (uint32_t j = 0; j < rhs.size (); j++)
        {
          os << *(rhs[j]);
        }
      return os;
    }
    
  } // namespace mih
} // namespace ns3
