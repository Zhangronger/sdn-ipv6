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

#ifndef   	MIH_TLV_OBJECT_FACTORY_H
#define   	MIH_TLV_OBJECT_FACTORY_H

#include <map>
#include <stdint.h>
#include "ns3/ptr.h"
#include "ns3/assert.h"
#include "ns3/callback.h"

namespace ns3 {
  namespace mih {
    /**
     * This factory class bears the callback map used to create object
     * based on their tlv type value. The template type T is that of
     * the parent class type.
     */

    template <typename T>
      class TlvObjectFactory
      {
      public:
	Ptr<T> Create (uint8_t tlv);
	void AddTlvTypeConstructor 
	  (uint8_t tlv, Callback<Ptr<T> > cb);
      private:
	std::map<uint8_t, Callback<Ptr<T> > > m_constructorMap;
      };

    template <typename T>
    Ptr<T>
    TlvObjectFactory<T>::Create (uint8_t tlv)
      {
	NS_ASSERT (m_constructorMap.count (tlv) == 1);
	return (m_constructorMap[tlv] ());
      }
    template <typename T>
    void
    TlvObjectFactory<T>::AddTlvTypeConstructor
      (uint8_t tlv, Callback<Ptr<T> > cb)
       {
	 if (m_constructorMap.count (tlv) != 0)
	   {
	     return;
	   }
	 m_constructorMap[tlv] = cb;
       }
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_TLV_OBJECT_FACTORY_H */
