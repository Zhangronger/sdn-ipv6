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

#ifndef   	MIH_LINK_COMMAND_LIST_H
#define   	MIH_LINK_COMMAND_LIST_H

#include <stdint.h>

namespace ns3 {
  namespace mih {
    class LinkCommandList {
    public:
      enum Type {
	EVENT_SUBSCRIBE = 0x00000001 << 1,
	EVENT_UNSUBSCRIBE = 0x00000001 << 2,
	GET_PARAMETERS = 0x00000001 << 3,
	CONFIGURE_THRESHOLD = 0x00000001 << 4,
	ACTION = 0x00000001 << 5,
      };
      LinkCommandList (uint32_t linkCommands);
      LinkCommandList (LinkCommandList const &o);
      uint32_t GetCommandList (void);
    protected:
      uint32_t m_bitmap;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_COMMAND_LIST_H */
