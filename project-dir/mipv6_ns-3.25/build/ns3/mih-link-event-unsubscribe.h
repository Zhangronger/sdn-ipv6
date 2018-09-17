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

#ifndef   	MIH_LINK_EVENT_UNSUBSCRIBE_H
#define   	MIH_LINK_EVENT_UNSUBSCRIBE_H

#include "mih-status.h"
#include "mih-event-list.h"

namespace ns3 {
  namespace mih {
    class LinkEventUnsubscribeConfirm {
    public:
      LinkEventUnsubscribeConfirm (enum Status::Type status = Status::INVALID,
                                   uint32_t events = EventList::INVALID);
      LinkEventUnsubscribeConfirm (LinkEventUnsubscribeConfirm const &o);
      Status GetStatus (void);
      EventList GetEventList (void);
    protected:
      Status m_status;
      EventList m_events;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_EVENT_UNSUBSCRIBE_H */
