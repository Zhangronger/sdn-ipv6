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

#ifndef   	MIH_COMMAND_LIST_H
#define   	MIH_COMMAND_LIST_H

#include <ostream>
#include <stdint.h>
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class MihCommandList : public Tlv {
    public:
      enum Type {
        INVALID = 0X00000000,
	LINK_GET_PARAMETERS = 0x00000001 << 0,
	LINK_CONFIGURE_THRESHOLDS = 0x00000001 << 1,
	LINK_ACTIONS = 0x00000001 << 2,
	NET_HO_CANDIDATE_QUERY = 0x00000001 << 3,
	NET_HO_COMMIT = 0x00000001 << 3,
	N2N_HO_QUERY_RESOURCES = 0x00000001 << 3,
	N2N_HO_COMMIT = 0x00000001 << 3,
	N2N_HO_COMPLETE = 0x00000001 << 3,
	MN_HO_CANDIDATE_QUERY = 0x00000001 << 4,
	MN_HO_COMMIT = 0x00000001 << 4,
	MN_HO_COMPLETE = 0x00000001 << 4,
      };
      MihCommandList (uint32_t commands = MihCommandList::INVALID);
      MihCommandList (MihCommandList const &o);
      void SetCommandList (uint32_t supportedCommands);
      uint32_t GetCommandList (void);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (MihCommandList);
    protected:
      uint32_t m_bitmap;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_COMMAND_LIST_H */
