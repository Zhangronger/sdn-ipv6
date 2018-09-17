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

#ifndef   	MIH_LINK_GOING_DOWN_REASON_H
#define   	MIH_LINK_GOING_DOWN_REASON_H

#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class LinkGoingDownReason : public Tlv {
    public:
      enum Type {
	EXPLICIT_DISCONNECT = 0,
	LINK_PARAMETER_DEGRADING = 1,
	LOW_POWER = 2,
	NO_RESOURCE = 3,
        INVALID = 0xff,
      };
      LinkGoingDownReason (enum Type reason = LinkGoingDownReason::INVALID);
      LinkGoingDownReason (LinkGoingDownReason const &o);
      enum Type GetReason (void);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (LinkGoingDownReason);
    protected:
      enum Type m_reason;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_GOING_DOWN_REASON_H */
