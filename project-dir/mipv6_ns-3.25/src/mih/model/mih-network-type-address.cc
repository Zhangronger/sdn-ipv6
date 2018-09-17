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
#include "mih-network-type-address.h"

NS_LOG_COMPONENT_DEFINE ("NetworkTypeAddress");

namespace ns3 {
  namespace mih {
    NetworkTypeAddress::NetworkTypeAddress (LinkType linkType,
					    Address linkAddress) :
      m_linkType (linkType),
      m_linkAddress (linkAddress)
    {}
    NetworkTypeAddress::NetworkTypeAddress (NetworkTypeAddress const &o) :
      m_linkType (o.m_linkType),
      m_linkAddress (o.m_linkAddress)
    {}
    TLV_TYPE_HELPER_IMPLEM (NetworkTypeAddress, TLV_NETWORK_TYPE_ADDRESS)
    Ptr<NetworkTypeAddress> 
    NetworkTypeAddress::CreateFromTlvType (uint8_t tlvTypeValue)
    {
      NS_ASSERT (tlvTypeValue == TLV_NETWORK_TYPE_ADDRESS);
      return Create<NetworkTypeAddress> ();
    }
    LinkType 
    NetworkTypeAddress::GetLinkType (void)
    {
      return m_linkType;
    }
    Address 
    NetworkTypeAddress::GetLinkAddress (void)
    {
      return m_linkAddress;
    }
    uint32_t 
    NetworkTypeAddress::GetTlvSerializedSize (void) const
    {
      return m_linkType.GetTlvSerializedSize ()  + 
        Tlv::GetSerializedSize (m_linkAddress) + 
        1 + 1 // Type + Length
        ;
    }
    void 
    NetworkTypeAddress::Print (std::ostream &os) const
    {
      os << "["
        "LinkType = " << m_linkType << " "
        "Link Address = " << m_linkAddress << "]" << std::endl
        ;
    }
    void
    NetworkTypeAddress::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      buffer.AddAtEnd (2); // Type + Length room space;
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ());
      i.WriteU8 (GetTlvSerializedSize () - 2);
      m_linkType.TlvSerialize (buffer);
      Tlv::Serialize (buffer, m_linkAddress, TLV_LINK_ADDRESS);
    }
    uint32_t 
    NetworkTypeAddress::TlvDeserialize (Buffer &buffer)
    {
      uint32_t size = 0;
      Buffer::Iterator i = buffer.Begin ();
      NS_ASSERT (i.ReadU8 () == GetTlvTypeValue ());
      buffer.RemoveAtStart (2); // Type + Length;
      size  += m_linkType.TlvDeserialize (buffer);
      size  += Tlv::Deserialize (buffer, m_linkAddress, TLV_LINK_ADDRESS);
      return size + 2; // + Type + Length;
    }
    std::ostream &
    operator << (std::ostream &os, const NetworkTypeAddress &a)
    {
      os <<
        "Network Type Address = [\n\t" << a.m_linkType << "\n\t"
                               << "Link Address = " << a.m_linkAddress <<
        "\n]" << std::endl
        ;
      return os;
    }
    std::ostream &
    operator << (std::ostream &os, NetworkTypeAddressList &a)
    {
      for (NetworkTypeAddressListI i = a.begin (); i != a.end (); i++)
        {
          os << *(*i);
        }
      return os;
    }
    uint32_t 
    GetTlvSerializedSize (NetworkTypeAddressList &networkTypeAddressList)
    {
      return Tlv::GetSerializedSize<NetworkTypeAddress> (networkTypeAddressList);
    }
    void 
    TlvSerialize (Buffer &buffer, NetworkTypeAddressList &networkTypeAddressList)
    {
      return Tlv::Serialize<NetworkTypeAddress> (buffer, networkTypeAddressList, TLV_NETWORK_TYPE_ADDRESS_LIST);
    }
    uint32_t 
    TlvDeserialize (Buffer &buffer, NetworkTypeAddressList &networkTypeAddressList)
    {
      return Tlv::Deserialize<NetworkTypeAddress> (buffer, networkTypeAddressList, TLV_NETWORK_TYPE_ADDRESS_LIST);
    }
  } // namespace mih
} // namespace ns3
