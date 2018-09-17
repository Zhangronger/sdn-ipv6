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

#ifndef   	MIH_LINK_DESCRIPTORS_REQUEST_H
#define   	MIH_LINK_DESCRIPTORS_REQUEST_H

#include <ostream>
#include <stdint.h>
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class LinkDescriptorsRequest : public Tlv {
    public:
      enum Type {
        INVALID = 0x0000,
	NUMBER_OF_COS = 0x0001 << 0,
	NUMBER_OF_QUEUES = 0x0001 << 1,
      };
      LinkDescriptorsRequest (uint16_t descriptors = LinkDescriptorsRequest::INVALID);
      LinkDescriptorsRequest (LinkDescriptorsRequest const &o);
      bool IsEqual (LinkDescriptorsRequest const &o) const;
      uint16_t GetDescriptors (void);
      LinkDescriptorsRequest operator = (LinkDescriptorsRequest const &o);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (LinkDescriptorsRequest);
    protected:
      uint16_t m_descriptors;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_DESCRIPTORS_REQUEST_H */
