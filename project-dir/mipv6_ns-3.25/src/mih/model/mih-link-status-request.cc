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
#include "mih-link-status-request.h"

NS_LOG_COMPONENT_DEFINE ("ns3::mih::LinkStatusRequest");

namespace ns3 {
  namespace mih {
    LinkStatusRequest::LinkStatusRequest (void)
    {}
    LinkStatusRequest::LinkStatusRequest (LinkStatesRequest linkStatesRequest,
					  LinkDescriptorsRequest linkDescriptorsRequest) :
      m_linkStatesRequest (linkStatesRequest),
      m_linkDescriptorsRequest (linkDescriptorsRequest)
    {}
    LinkStatusRequest::LinkStatusRequest (LinkStatusRequest const &o) :
      m_linkStatesRequest (o.m_linkStatesRequest),
      m_linkDescriptorsRequest (o.m_linkDescriptorsRequest),
      m_linkParameterList (o.m_linkParameterList)
    {
      NS_LOG_WARN ("Dangerous list copy hack: m_linkParameterList (o.m_linkParameterList)!");
    }
    TLV_TYPE_HELPER_IMPLEM (LinkStatusRequest, TLV_LINK_STATUS_REQUEST)
    LinkStatesRequest
    LinkStatusRequest::GetLinkStatesRequest (void)
    {
      return m_linkStatesRequest;
    }
    LinkDescriptorsRequest 
    LinkStatusRequest::GetLinkDescriptorsRequest (void)
    {
      return m_linkDescriptorsRequest;
    }
    LinkParameterTypeListI 
    LinkStatusRequest::LinkParameterTypeListBegin (void)
    {
      return m_linkParameterList.begin ();
    }
    LinkParameterTypeListI 
    LinkStatusRequest::LinkParameterTypeListEnd (void)
    {
      return m_linkParameterList.end ();
    }
    void 
    LinkStatusRequest::AddLinkParameterTypeItem (Ptr<LinkParameterType> linkparameterType)
    {
      NS_ASSERT_MSG (linkparameterType != 0, "Illegal NULL pointer addressing!");
      m_linkParameterList.push_back (linkparameterType);
    }
    uint32_t
    LinkStatusRequest::GetLinkParameterTypeN (void)
    {
      return m_linkParameterList.size ();
    }
    LinkParameterTypeList 
    LinkStatusRequest::GetLinkParameterTypeList (void)
    {
      return m_linkParameterList;
    }
    LinkStatusRequest
    LinkStatusRequest::operator = (LinkStatusRequest const &o) 
    {
      m_linkStatesRequest = o.m_linkStatesRequest;
      m_linkDescriptorsRequest = o.m_linkDescriptorsRequest;
      m_linkParameterList = o.m_linkParameterList;
      return *this;
    }
    uint32_t
    LinkStatusRequest::GetTlvSerializedSize (void) const
    {
      uint32_t payloadLength = 0;
      uint32_t lengthOfLengthField = 0;

      payloadLength = m_linkStatesRequest.GetTlvSerializedSize () +
        m_linkDescriptorsRequest.GetTlvSerializedSize () +
        ns3::mih::GetTlvSerializedSize (m_linkParameterList);

      if (payloadLength <= 128)
        {
          lengthOfLengthField = 1;
        }
      else if (payloadLength <= (1 << 8))
        {
          lengthOfLengthField = 2;
        }
      else if (payloadLength <= (1 << 16))
        {
          lengthOfLengthField = 3;
        }
      else if (payloadLength <= (1 << 24))
        {
          lengthOfLengthField = 4;
        }
      else
        {
          NS_ASSERT_MSG (0, "Need extending TLV length field to 5 bytes!");
        }
      
      return 1 + payloadLength + lengthOfLengthField;
    }
    void 
    LinkStatusRequest::Print (std::ostream &os) const
    {
      os << "Link Status Request = [" << std::endl;
      m_linkStatesRequest.Print (os);
      m_linkDescriptorsRequest.Print (os);
      for (uint32_t i = 0; i < m_linkParameterList.size (); i++)
        {
          m_linkParameterList[i]->Print (os);
        }
      os << "]" << std::endl;
    }
    void
    LinkStatusRequest::TlvSerialize (Buffer &buffer) const
    {
      // Modify this ...
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;

      payloadLength += m_linkStatesRequest.GetTlvSerializedSize ();
      payloadLength += m_linkDescriptorsRequest.GetTlvSerializedSize ();
      payloadLength += ns3::mih::GetTlvSerializedSize (m_linkParameterList);

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field + Length field only;
      
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length field;

      m_linkStatesRequest.TlvSerialize (buffer);
      m_linkDescriptorsRequest.TlvSerialize (buffer);
      ns3::mih::TlvSerialize (buffer, m_linkParameterList);
    }
    uint32_t 
    LinkStatusRequest::TlvDeserialize (Buffer &buffer)
    {
      uint32_t totalBytesRead = 0;
      uint32_t roomSize;
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLengthValue = 0;
      Buffer::Iterator i = buffer.Begin ();
      NS_ASSERT_MSG (i.ReadU8 () == GetTlvTypeValue (), "List TLV type values mismatch!");
      totalBytesRead++;
      roomSize = i.ReadU8 ();
      totalBytesRead++;
      if (roomSize <= 128)
        {
          payloadLengthValue = roomSize;
        }
      else // MSB is 1
        {
          lengthOfLengthField = roomSize - 128;
          for (uint32_t j = 0; j < lengthOfLengthField; j++)
            {
              payloadLengthValue <<= 8;
              payloadLengthValue += i.ReadU8 ();
              totalBytesRead++;
            }
          payloadLengthValue += 128;
        }
      buffer.RemoveAtStart (totalBytesRead); // Type + Length;
      totalBytesRead += m_linkStatesRequest.TlvDeserialize (buffer);
      totalBytesRead += m_linkDescriptorsRequest.TlvDeserialize (buffer);
      totalBytesRead += ns3::mih::TlvDeserialize (buffer, m_linkParameterList);
      return totalBytesRead;
    }
  } // namespace mih
} // namespace ns3
