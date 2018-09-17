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

#include "mih-link-capability-discover.h"

namespace ns3 {
  namespace mih {
    LinkCapabilityDiscoverConfirm::LinkCapabilityDiscoverConfirm (enum Status::Type status,
								  uint32_t events,
								  uint32_t commands) :
      m_status (status),
      m_events (events),
      m_commands (commands)
    {}
    LinkCapabilityDiscoverConfirm::LinkCapabilityDiscoverConfirm (LinkCapabilityDiscoverConfirm const &o) :
      m_status (o.m_status),
      m_events (o.m_events),
      m_commands (o.m_commands)
    {}
    Status 
    LinkCapabilityDiscoverConfirm::GetStatus (void)
    {
      return m_status;
    }
    EventList 
    LinkCapabilityDiscoverConfirm::GetEventList (void)
    {
      return m_events;
    }
    LinkCommandList 
    LinkCapabilityDiscoverConfirm::GetCommandList (void)
    {
      return m_commands;
    }
  } // namespace mih
} // namespace ns3
