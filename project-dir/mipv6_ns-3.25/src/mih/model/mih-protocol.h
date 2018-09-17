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

#ifndef   	MIH_PROTOCOL_H
#define   	MIH_PROTOCOL_H

#include <map>
#include "ns3/object.h"
#include "ns3/address.h"
#include "mihf-id.h"
#include "mih-network-type-address.h"
#include "mih-event-list.h"
#include "mih-command-list.h"
#include "mih-information-service-query-type-list.h"
#include "mih-transport-support-list.h"
#include "mih-make-before-break-support.h"
#include "mih-callbacks.h"
#include "mih-event-configuration-information.h"
#include "mih-session.h"

namespace ns3 {
  class Node;
  namespace mih {
    class MihProtocol : public Object {
    public:
      static TypeId GetTypeId (void);
      MihProtocol (void);
      virtual ~MihProtocol (void);
      void Init (void);
      void SetNode (Ptr<Node> node);
      Ptr<Node> GetNode (void) const;
      void AddDestinationEntry (MihfId mihfId, Address dest);
      void SendCapabilityDiscoverRequest (MihfId destinationIdentifier,
                                          NetworkTypeAddressList networkTypeAddresses,
                                          EventList events,
                                          MihCommandList commands,
                                          InformationServiceQueryTypeList informationServiceQueryTypes,
                                          TransportSupportList transportSupports,
                                          MakeBeforeBreakSupportList makeBeforeBreakSupports,
                                          MihCapabilityDiscoverConfirmCallback capabilityDiscoverConfirmCallback);
      void SendRegisterRequest (MihfId destinationIdentifier,
                                LinkIdentifierList linkIdentifierList,
                                RegistrationCode registrationCode,
                                MihRegisterConfirmCallback registerConfirmCallback);
      void SendDeRegisterRequest (MihfId destinationIdentifier,
                                  MihDeRegisterConfirmCallback deRegisterConfirmCallback);
      void SendEventSubscribeRequest (MihfId destinationIdentifier,
                                      LinkIdentifier linkIdentifier,
                                      EventConfigurationInformation configurationInformation,
                                      EventList::Type linkDetectedEventType1,
                                      MihLinkDetectedIndicationCallback linkDetectedEventCallback1,
                                      EventList::Type linkUpEventType2,
                                      MihLinkUpIndicationCallback linkUpEventCallback2,
                                      EventList::Type linkDownEventType3,
                                      MihLinkDownIndicationCallback linkDownEventCallback3,
                                      EventList::Type linkParamReportEventType4,
                                      MihLinkParametersReportIndicationCallback linkParamReportEventCallback4,
                                      EventList::Type linkGoingDownEventType5,
                                      MihLinkGoingDownIndicationCallback linkGoingDownEventCallback5,
                                      EventList::Type linkHOImminentEventType6,
                                      MihLinkHandoverImminentIndicationCallback linkHOImminentEventCallback6,
                                      EventList::Type linkHOCompleteEventType7,
                                      MihLinkHandoverCompleteIndicationCallback linkHOCompleteEventCallback7,
                                      EventList::Type linkPduTxStatusEventType8,
                                      MihLinkPduTransmitStatusIndicationCallback linkPduTxStatusEventCallback8,
                                      MihEventSubscribeConfirmCallback subscribeConfirmCallback);
      void SendLinkGetParametersRequest (MihfId destinationIdentifier,
                                         DeviceStatesRequest deviceStatesRequest,
                                         LinkIdentifierList linkIdentifierList,
                                         LinkStatusRequest linkStatusRequest,
                                         MihLinkGetParametersConfirmCallback getParamtersConfirmCallback);
      void SendLinkConfigureThresholdsRequest (MihfId destinationIdentifier,
                                               LinkIdentifier linkIdentifier,
                                               LinkConfigurationParameterList linkConfigurationParameters,
                                               MihLinkConfigureThresholdsConfirmCallback configureThresholdsConfiirmCallback);
    protected:
      virtual void DoDispose (void);
    protected:
      Ptr<Session> GetSession (MihfId fromMihfId, 
                               Address from, 
                               MihfId toMihfId, 
                               Address to, 
                               Ptr<Socket> socket);
      Ptr<Session> StartSession (MihfId fromMihfId, 
                                 Address from, 
                                 MihfId toMihfId, 
                                 Address to);
      bool FindSessionByMihfId (MihfId toMihfId, SessionListI &iter);
      bool FindSessionByToAddress (Address to, SessionListI &iter);
      bool FindSessionBySocket (Ptr<Socket> s, SessionListI &i);
      Address ResolveMihfIdToAddress (MihfId mihfid);
      void HandleRead (Ptr<Socket> socket);
      void ReceiveNewSessionRequest (Ptr<Socket> s, const Address& from);
    private:
      typedef std::map<MihfId, Address> MihfIdAddressTable;
      typedef MihfIdAddressTable::iterator MihfIdAddressTableI;
      MihfIdAddressTable m_mihfIdTable;
      Ptr<Socket> m_serverSocket;
      Ptr<Node> m_node;
      Address m_local;
      SessionList m_sessions;
      TypeId m_tid; // Protocol TypeId
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_PROTOCOL_H */
