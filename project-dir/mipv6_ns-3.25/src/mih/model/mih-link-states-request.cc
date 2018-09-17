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

#include "mih-link-states-request.h"

namespace ns3 {
  namespace mih {
    LinkStatesRequest::LinkStatesRequest (uint16_t requestedStates) :
      m_states (requestedStates)
    {}
    LinkStatesRequest::LinkStatesRequest (LinkStatesRequest const &o) :
      m_states (o.m_states)
    {}
    bool 
    LinkStatesRequest::IsEqual (LinkStatesRequest const &o) const
    {
      return (m_states == o.m_states);
    }
    TLV_TYPE_HELPER_IMPLEM (LinkStatesRequest, TLV_LINK_STATES_REQUEST)
    uint16_t 
    LinkStatesRequest::GetStates (void)
    {
      return m_states;
    }
    LinkStatesRequest 
    LinkStatesRequest::operator = (LinkStatesRequest const &o)
    {
      m_states = o.m_states;
      return *this;
    }
    uint32_t
    LinkStatesRequest::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU16 ();
    }
    void
    LinkStatesRequest::Print (std::ostream &os) const
    {
      os << "Link State Request = " << std::hex << (int)m_states << std::endl;
    }
    void 
    LinkStatesRequest::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU16 (buffer, m_states, TLV_LINK_STATES_REQUEST);
    }
    uint32_t
    LinkStatesRequest::TlvDeserialize (Buffer &buffer)
    {
      return Tlv::DeserializeU16 (buffer, m_states, TLV_LINK_STATES_REQUEST);
    }
    
  } // namespace mih
} // namespace ns3
