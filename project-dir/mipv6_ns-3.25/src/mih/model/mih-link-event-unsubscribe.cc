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

#include "mih-link-event-unsubscribe.h"

namespace ns3 {
  namespace mih {
    LinkEventUnsubscribeConfirm::LinkEventUnsubscribeConfirm (enum Status::Type status,
							      uint32_t events) :
      m_status (status),
      m_events (events)
    {}
    LinkEventUnsubscribeConfirm::LinkEventUnsubscribeConfirm (LinkEventUnsubscribeConfirm const &o) :
      m_status (o.m_status),
      m_events (o.m_events)
    {}
    Status
    LinkEventUnsubscribeConfirm::GetStatus (void)
    {
      return m_status;
    }
    EventList
    LinkEventUnsubscribeConfirm::GetEventList (void)
    {
      return m_events;
    }
  } // namespace mih
} // namespace ns3
