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

#ifndef   	MIH_LINK_TYPE_H
#define   	MIH_LINK_TYPE_H

#include <ostream>
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class LinkType : public Tlv {
    public:
      enum Type {
        RESERVED = 0,
        GSM = 1,
        GPRS = 2,
        EDGE = 3,
        ETHERNET = 15,
        OTHER = 18,
        WIRELESS_802_11 = 19,
        WIRELESS_CDMA_2000 = 22,
        UMTS = 23,
        WIRELESS_CDMA_2000_HRPD = 24,
        WIRELESS_802_16 = 27,
        WIRELESS_802_20 = 28,
        WIRELESS_802_22 = 29,
        INVALID = 0xff,
      };
      LinkType (enum Type typ = LinkType::INVALID);
      LinkType (LinkType const &o);
      LinkType& operator= (const LinkType &o);
      void SetType (enum Type code);
      enum Type GetType (void);
      bool IsEqual (LinkType const &o) const;
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (LinkType);
    protected:
      friend bool operator == (LinkType const &a, LinkType const &b);
      friend bool operator != (LinkType const &a, LinkType const &b);
      friend std::ostream& operator << (std::ostream &os, const LinkType &a);
      enum Type m_type;
    };
    bool operator == (LinkType const &a, LinkType const &b);
    bool operator != (LinkType const &a, LinkType const &b);
    std::ostream& operator << (std::ostream &os, const LinkType &a);
  }
}

#endif 	    /* !MIH_LINK_TYPE_H */
