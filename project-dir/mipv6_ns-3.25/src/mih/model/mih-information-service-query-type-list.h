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

#ifndef   	MIH_INFORMATION_SERVICE_QUERY_TYPE_LIST_H
#define   	MIH_INFORMATION_SERVICE_QUERY_TYPE_LIST_H

#include <ostream>
#include <stdint.h>
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class InformationServiceQueryTypeList {
    public:
      enum Type {
        INVALID = 0x0000000000000000,
	BITMAP_DATA = 0x0000000000000001 << 0,
	RDF_DATA = 0x0000000000000001 << 1,
	RDF_SCHEMA_URL = 0x0000000000000001 << 2,
	RDF_SCHEMA = 0x0000000000000001 << 3,
	IE_NETWORK_TYPE = 0x0000000000000001 << 4,
	IE_OPERATOR_ID = 0x0000000000000001 << 5,
	IE_SERVICE_PROVIDER_ID = 0x0000000000000001 << 6,
	IE_COUNTRY_CODE = 0x0000000000000001 << 7,
	IE_NETWORK_ID = 0x0000000000000001 << 8,
	IE_NETWORK_AUX_ID = 0x0000000000000001 << 9,
	IE_ROAMING_PARTNERS = 0x0000000000000001 << 10,
	IE_COST = 0x0000000000000001 << 11,
	IE_NETWORK_QOS = 0x0000000000000001 << 12,
	IE_NETWORK_DATA_RATE = 0x0000000000000001 << 13,
	IE_NET_REGULT_DOMAIN = 0x0000000000000001 << 14,
	IE_NET_FREQUENCY_BAND = 0x0000000000000001 << 15,
	IE_NET_CFG_METHODS = 0x0000000000000001 << 16,
	IE_NET_CAPABILITIES = 0x0000000000000001 << 17,
	IE_NET_SUPPORTED_LCP = 0x0000000000000001 << 18,
	IE_NET_MOB_MGMT_PROT = 0x0000000000000001 << 19,
	IE_NET_EMSERV_PROXY = 0x0000000000000001 << 20,
	IE_NET_IMS_PROXY_CSCF = 0x0000000000000001 << 21,
	IE_NET_MOBILE_NETWORK = 0x0000000000000001 << 22,
	IE_POA_LINK_ADDRESS = 0x0000000000000001 << 23,
	IE_POA_LOCATION = 0x0000000000000001 << 24,
	IE_POA_CHANNEL_RANGE = 0x0000000000000001 << 25,
	IE_POA_SYSTEM_INFO = 0x0000000000000001 << 26,
	IE_POA_SUBNET_INFO = 0x0000000000000001 << 27,
	IE_POA_IP_ADDRESS = 0x0000000000000001 << 28,
      };
      InformationServiceQueryTypeList (uint64_t queryTypes = InformationServiceQueryTypeList::INVALID);
      InformationServiceQueryTypeList (InformationServiceQueryTypeList const &o);
      virtual ~InformationServiceQueryTypeList (void);
      uint64_t GetInformationServiceQueryTypes (void);
      void SetInformationServiceQueryTypes (uint64_t queryTypes);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (InformationServiceQueryTypeList);
    protected:
      uint64_t m_bitmap;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_INFORMATION_SERVICE_QUERY_TYPE_LIST_H */
