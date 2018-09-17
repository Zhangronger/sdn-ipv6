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

#ifndef   	MIH_STATUS_H
#define   	MIH_STATUS_H

#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class Status : public Tlv{
    public:
      enum Type {
        SUCCESS = 0,
        UNSPECIFIED_FAILURE = 1,
        REJECTED = 2,
        AUTHORIZATION_FAILURE = 3,
        NETWORK_ERROR = 4,
        INVALID = 0xff,
      };
      Status (enum Type code = Status::INVALID);
      Status (Status const &o);
      void SetType (enum Type code);
      enum Type GetType (void);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (Status);
    protected:
      friend std::ostream& operator << (std::ostream &os, const Status &a);
      enum Type m_type;
    };

    std::ostream& operator << (std::ostream &os, const Status &a);
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_STATUS_H */
