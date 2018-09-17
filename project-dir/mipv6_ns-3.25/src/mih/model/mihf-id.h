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

#ifndef   	MIHF_ID_H
#define   	MIHF_ID_H

#include <string>
#include <ostream>
#include <stdint.h>
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class MihfId : public Tlv {
    public:
      enum {
	MAX_LEN = 253,
      };
      MihfId (void);
      MihfId (std::string mihfid);
      MihfId (MihfId const &o);
      const char * PeekString (void) const;
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      MihfId& operator = (MihfId const &a);
      TLV_TYPE_HELPER_HEADER (MihfId);
    protected:
      friend bool operator == (const MihfId &a, const MihfId &b);
      friend bool operator != (const MihfId &a, const MihfId &b);
      friend bool operator < (const MihfId &a, const MihfId &b);
      std::string m_mihfid;
    };
    std::ostream &operator << (std::ostream &os, const MihfId &mihfId);
    std::istream &operator >> (std::istream &is, MihfId &mihfId);
    
    /**
     * \class ns3::MihfIdValue
     * \brief hold objects of type ns3::MihfId
     */
    
    ATTRIBUTE_HELPER_HEADER (MihfId);

    bool operator == (const MihfId &a, const MihfId &b);
    bool operator != (const MihfId &a, const MihfId &b);
    bool operator < (const MihfId &a, const MihfId &b);
    
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIHF_ID_H */
