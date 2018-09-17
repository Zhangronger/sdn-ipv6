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

#include "mih-event-list.h"

namespace ns3 {
  namespace mih {
    EventList::EventList (uint32_t events) :
      m_events (events)
    {}
    EventList::EventList (EventList const &o) :
      m_events (o.m_events)
    {}
    TLV_TYPE_HELPER_IMPLEM (EventList, TLV_MIH_EVENT_LIST)    
    bool 
    EventList::IsEqual (EventList const &o) const 
    {
      return (m_events == o.m_events);
    }
    bool 
    EventList::IsOfType (enum Type type)
    {
      return ((m_events & static_cast<uint32_t> (type)) != 0);
    }
    void 
    EventList::SetEventList (uint32_t supportedEvent) 
    {
      m_events = supportedEvent;
    }
    uint32_t
    EventList::GetEventList (void)
    {
      return m_events;
    }
    uint32_t 
    EventList::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU32 ();
    }
    void 
    EventList::Print (std::ostream &os) const
    {
      os <<
        "Events = 0x" << std::hex << (uint32_t)m_events 
                    << std::endl
        ;
    }
    void
    EventList::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU32 (buffer, m_events, TLV_MIH_EVENT_LIST);
    }
    uint32_t 
    EventList::TlvDeserialize (Buffer &buffer)
    {
      return Tlv::DeserializeU32 (buffer, m_events, TLV_MIH_EVENT_LIST);
    }
  } // namespace mih
} // namespace ns3
