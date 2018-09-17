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

#include "mih-link-states-response.h"

namespace ns3 {
  namespace mih {
    CHOICE_HELPER_PURE_VIRTUAL_IMPLEM (LinkStatesResponse)
    TLV_TYPE_HELPER_IMPLEM (LinkStatesResponse, TLV_LINK_STATES_RESPONSE)
    uint32_t 
    LinkStatesResponse::GetTlvSerializedSize (void) const
    {
      NS_ASSERT (0);
      return 0;
    }
    void 
    LinkStatesResponse::Print (std::ostream &os) const 
    {
      NS_ASSERT (0);
    }
    void 
    LinkStatesResponse::TlvSerialize (Buffer &buffer) const
    {
      NS_ASSERT (0);
    }
    uint32_t 
    LinkStatesResponse::TlvDeserialize (Buffer &buffer)
    {
          NS_ASSERT (0);
          return 0;
    }
    uint32_t
    GetTlvSerializedSize (const LinkStatesResponseList &linkStatesResponseList)
    {
      return Tlv::GetSerializedSize<LinkStatesResponse> (linkStatesResponseList);
    }
    void
    TlvSerialize (Buffer &buffer, const LinkStatesResponseList &linkStatesResponseList)
    {
      Tlv::Serialize<LinkStatesResponse> (buffer, linkStatesResponseList, TLV_LINK_STATES_RESPONSE_LIST);
    }
    uint32_t
    TlvDeserialize (Buffer &buffer, LinkStatesResponseList &linkStatesResponseList)
    {
      return Tlv::Deserialize<LinkStatesResponse> (buffer, linkStatesResponseList, TLV_LINK_STATES_RESPONSE_LIST);      
    }
  } // namespace mih
} // namespace ns3
