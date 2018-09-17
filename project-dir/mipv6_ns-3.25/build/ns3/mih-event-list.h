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

#ifndef   	MIH_EVENT_LIST_H
#define   	MIH_EVENT_LIST_H

#include <ostream>
#include <stdint.h>
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class EventList : public Tlv {
    public:
      enum Type {
        INVALID = 0x00000000,
	LINK_DETECTED = 0x00000001 << 0,
	LINK_UP = 0x00000001 << 1,
	LINK_DOWN = 0x00000001 << 2,
	LINK_PARAMETERS_REPORT = 0x00000001 << 3,
	LINK_GOING_DOWN = 0x00000001 << 4,
	LINK_HANDOVER_IMMINENT = 0x00000001 << 5,
	LINK_HANDOVER_COMPLETE = 0x00000001 << 6,
	LINK_PDU_TRANSMIT_STATUS = 0x00000001 << 7,
      };
      EventList (uint32_t events = EventList::INVALID);
      EventList (EventList const &o);
      bool IsEqual (EventList const &o) const;
      void SetEventList (uint32_t supportedEvent);
      uint32_t GetEventList (void);
      bool IsOfType (enum Type type);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (EventList);
    protected:
      uint32_t m_events;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_EVENT_LIST_H */
