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

#ifndef   	MIH_LINK_ACTION_H
#define   	MIH_LINK_ACTION_H

#include <stdint.h>
#include "ns3/ref-count-base.h"
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class LinkAction : public RefCountBase, public Tlv {
    public:
      enum Type {
        NONE = 0,
        LINK_DISCONNECT,
        LINK_LOW_POWER,
        LINK_POWER_DOWN,
        LINK_POWER_UP,
      };
      enum ActionAttribute {
        INVALID = 0x00,
	LINK_SCAN = 0x01 << 1,
	LINK_RESOURCE_RETAIN = 0x01 << 2,
	DATA_FORWARD_REQUEST = 0x01 << 3,
      };
      LinkAction (enum Type actionType = LinkAction::NONE,
		  uint8_t actionAttribute = LinkAction::INVALID);
      LinkAction (LinkAction const &o);
      bool IsEqual (LinkAction const &o);
      uint8_t GetActionAttribute (void);
      void SetActionAttribute (uint8_t actionAttribute);
      void SetType (enum Type code);
      enum Type GetType (void);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (LinkAction);
    protected:
      enum Type m_type;
      uint8_t m_actionAttribute;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_ACTION_H */
