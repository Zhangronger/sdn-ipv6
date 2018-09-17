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
#include "mih-network-identifier.h"

namespace ns3 {
  namespace mih {
    NetworkIdentifier::NetworkIdentifier (std::string networkIdentifier) : 
      m_networkIdentifier (networkIdentifier)
    {
      NS_ASSERT (networkIdentifier.length () <= 253);
    }
    NetworkIdentifier::NetworkIdentifier (NetworkIdentifier const &o) :
      m_networkIdentifier ( o.m_networkIdentifier)
    {
      m_networkIdentifier = o.m_networkIdentifier;
    }
    TLV_TYPE_HELPER_IMPLEM (NetworkIdentifier, TLV_NETWORK_IDENTIFIER)
    const char * 
    NetworkIdentifier::PeekString (void)
    {
      return m_networkIdentifier.c_str ();
    }
    uint32_t 
    NetworkIdentifier::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeString (m_networkIdentifier);
    }
    void
    NetworkIdentifier::Print (std::ostream &os) const
    {
      os << "NetworkIdentifier = " << m_networkIdentifier << std::endl;
    }
    void 
    NetworkIdentifier::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeString (buffer, m_networkIdentifier, GetTlvTypeValue ());
    }
    uint32_t 
    NetworkIdentifier::TlvDeserialize (Buffer &buffer)
    {
      return Tlv::DeserializeString (buffer, m_networkIdentifier, GetTlvTypeValue ());
    }
  } // namespace mih
} // namespace ns3
