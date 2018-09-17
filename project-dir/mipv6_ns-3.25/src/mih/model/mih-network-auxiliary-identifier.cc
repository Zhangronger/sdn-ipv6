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

#include "mih-network-auxiliary-identifier.h"

#include "ns3/assert.h"

namespace ns3 {
  namespace mih {
    NetworkAuxiliaryIdentifier::NetworkAuxiliaryIdentifier (std::string networkAuxiliaryIdentifier) :
      m_networkAuxiliaryIdentifier (networkAuxiliaryIdentifier)
    {
      NS_ASSERT (networkAuxiliaryIdentifier.length () <= 253);
    }
    NetworkAuxiliaryIdentifier::NetworkAuxiliaryIdentifier (NetworkAuxiliaryIdentifier const &o) :
      m_networkAuxiliaryIdentifier (o.m_networkAuxiliaryIdentifier)
    {}
    TLV_TYPE_HELPER_IMPLEM (NetworkAuxiliaryIdentifier, TLV_NETWORK_AUXILIARY_IDENTIFIER)
    const char* 
    NetworkAuxiliaryIdentifier::PeekString (void)
    {
      return m_networkAuxiliaryIdentifier.c_str ();
    }
    uint32_t 
    NetworkAuxiliaryIdentifier::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeString (m_networkAuxiliaryIdentifier);
    }
    void
    NetworkAuxiliaryIdentifier::Print (std::ostream &os) const
    {
      os << "NetworkAuxiliaryIdentifier = " << m_networkAuxiliaryIdentifier << std::endl;
    }
    void 
    NetworkAuxiliaryIdentifier::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeString (buffer, m_networkAuxiliaryIdentifier, GetTlvTypeValue ());
    }
    uint32_t 
    NetworkAuxiliaryIdentifier::TlvDeserialize (Buffer &buffer)
    {
      return Tlv::DeserializeString (buffer, m_networkAuxiliaryIdentifier, GetTlvTypeValue ());
    }
  } // namespace mih
} // namespace ns3
