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

#include "mih-link-event-subscribe.h"

namespace ns3 {
  namespace mih {
    LinkEventSubscribeConfirm::LinkEventSubscribeConfirm (enum Status::Type status,
							  uint32_t events) :
      m_status (status),
      m_events (events)
    {}
    LinkEventSubscribeConfirm::LinkEventSubscribeConfirm (LinkEventSubscribeConfirm const &o) :
      m_status (o.m_status),
      m_events (o.m_events)
    {}
    Status 
    LinkEventSubscribeConfirm::GetStatus (void)
    {
      return m_status;
    }
    EventList
    LinkEventSubscribeConfirm::GetEventList (void)
    {
      return m_events;
    }
    LinkEventSubscribeConfirm 
    LinkEventSubscribeConfirm::operator = (const LinkEventSubscribeConfirm &o)
    {
      m_status = o.m_status;
      m_events = o.m_events;
      return *this;
    }

  } // namespace mih
} // namespace ns3
