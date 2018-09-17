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

#include "mih-link-parameter-type.h"

namespace ns3 {
  namespace mih {
    CHOICE_HELPER_PURE_VIRTUAL_IMPLEM (LinkParameterType)
    TLV_TYPE_HELPER_IMPLEM (LinkParameterType, TLV_LINK_PARAMETER_TYPE)
    uint32_t 
    GetTlvSerializedSize (const LinkParameterTypeList &linkParameterTypeList)
    {
      return Tlv::GetSerializedSize<LinkParameterType> (linkParameterTypeList);
    }
    void 
    TlvSerialize (Buffer &buffer, const LinkParameterTypeList &linkParameterTypeList)
    {
      return Tlv::Serialize<LinkParameterType> (buffer, linkParameterTypeList, TLV_LINK_PARAMETER_TYPE_LIST);
    }
    uint32_t 
    TlvDeserialize (Buffer &buffer, LinkParameterTypeList &linkParameterTypeList)
    {
      return Tlv::Deserialize<LinkParameterType> (buffer, linkParameterTypeList, TLV_LINK_PARAMETER_TYPE_LIST);
    }
  } // namespace mih
} // namespace ns3
