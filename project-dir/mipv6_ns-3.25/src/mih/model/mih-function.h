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

#ifndef   	MIH_FUNCTION_H
#define   	MIH_FUNCTION_H

#include <vector>
#include <stdint.h>
#include "ns3/object.h"
#include "ns3/callback.h"
#include "ns3/traced-callback.h"
#include "ns3/address.h"
#include "ns3/event-id.h"
#include "mih-callbacks.h"
#include "mihf-id.h"
#include "mih-link-detected-information.h"
#include "mih-link-identifier.h"
#include "mih-mobility-management-support.h"
#include "mih-link-parameter-report.h"
#include "mih-link-going-down-reason.h"
#include "mih-device-states-request.h"
#include "mih-status.h"
#include "mih-device-states-response.h"
#include "mih-link-states-response.h"
#include "mih-link-status-request.h"
#include "mih-link-configuration-parameter.h"
#include "mih-link-action-request.h"
#include "mih-link-action-response.h"
#include "mih-information-service-query-type-list.h"
#include "mih-make-before-break-support.h"
#include "mih-transport-support-list.h"
#include "mih-registration-code.h"
#include "mih-network-type-address.h"
#include "mih-event-configuration-information.h"
#include "mih-link-sap.h"

namespace ns3 {
  namespace mih {
    class MihFunction : public Object {
    public:
      static TypeId GetTypeId (void);
      MihFunction (void);
      virtual ~MihFunction (void);
      MihfId GetMihfId (void) const;
      void SetMihfId (MihfId mihfId);
      bool Register (Ptr<MihLinkSap> mihLinkSap);
      void CapabilityDiscover (MihfId destinationIdentifier,
                               NetworkTypeAddressList networkTypeAddresses,
                               EventList events,
                               MihCommandList commands,
                               InformationServiceQueryTypeList informationServiceQueryTypes,
                               TransportSupportList transportSupports,
                               MakeBeforeBreakSupportList makeBeforeBreakSupports,
                               MihCapabilityDiscoverConfirmCallback capabilityDiscoverConfirmCallback);
      void RegisterMihCapabilityDiscoverIndicationCallback (MihCapabilityDiscoverIndicationCallback capabilityDiscoverIndicationCallback);
      void Register (MihfId destinationIdentifier,
                     LinkIdentifierList linkIdentifierList,
                     RegistrationCode registrationCode,
                     MihRegisterConfirmCallback registerConfirmCallback);
      void RegisterMihRegisterIndicationCallback (MihRegisterIndicationCallback registerIndicationCallback);
      void DeRegister (MihfId destinationIdentifier,
                       MihDeRegisterConfirmCallback deRegisterConfirmCallback);
      void RegisterMihDeRegisterIndicationCallback (MihDeRegisterIndicationCallback deRegister);
      void EventSubscribe (MihfId destinationIdentifier,
                           LinkIdentifier linkIdentifier,
                           MihEventSubscribeConfirmCallback subscribeConfirmCallback,
                           EventList::Type eventType1,
                           CallbackBase cb1,
                           EventList::Type eventType2 = EventList::INVALID,
                           CallbackBase cb2 = CallbackBase (),
                           EventList::Type eventType3 = EventList::INVALID,
                           CallbackBase cb3 = CallbackBase (),
                           EventList::Type eventType4 = EventList::INVALID,
                           CallbackBase cb4 = CallbackBase (),
                           EventList::Type eventType5 = EventList::INVALID,
                           CallbackBase cb5 = CallbackBase (),
                           EventList::Type eventType6 = EventList::INVALID,
                           CallbackBase cb6 = CallbackBase (),
                           EventList::Type eventType7 = EventList::INVALID,
                           CallbackBase cb7 = CallbackBase (),
                           EventList::Type eventType8 = EventList::INVALID,
                           CallbackBase cb8 = CallbackBase ());
      void EventUnsubscribe (MihfId destinationIdentifier,
                             LinkIdentifier linkIdentifier,
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
                             MihEventUnsubscribeConfirmCallback unsubscribeConfirmCallback);
      void LinkGetParameters (MihfId destinationIdentifier,
                              DeviceStatesRequest deviceStatesRequest,
                              LinkIdentifierList linkIdentifierList,
                              LinkStatusRequest linkStatusRequest,
                              MihLinkGetParametersConfirmCallback getParamtersConfirmCallback);
      void LinkConfigureThresholds (MihfId destinationIdentifier,
                                    LinkIdentifier linkIdentifier,
                                    LinkConfigurationParameterList linkConfigurationParameters,
                                    MihLinkConfigureThresholdsConfirmCallback configureThresholdsConfiirmCallback);
      void LinkActions (MihfId destinationIdentifier,
                        LinkActionRequestList actionRequestList,
                        MihLinkActionsConfirmCallback actionsConfirmCallback);
      
    protected:
      virtual void DoDispose (void);
      MihfId m_mihfId;
      MihCapabilityDiscoverIndicationTracedCallback m_mihCapabilityDiscoverIndicationTracedCallback;
      MihRegisterIndicationTracedCallback m_mihRegisterIndicationTracedCallback;
      MihDeRegisterIndicationTracedCallback m_mihDeRegisterIndicationTracedCallback;
      MihLinkSapList m_registeredMihLinkSapList;

      MihLinkActionsConfirmCallback m_postponedActionsConfirmCallback;
      LinkActionResponseList m_linkActionResponseList;
      std::vector<EventId> m_linkActionConfirmEventIds;
      EventId m_linkActionsCompleteEvent;
      uint32_t m_actionRequestN;
      bool m_linkActionsComplete;

    private:
      friend class MihProtocol;
      bool FindMihLinkSap (LinkIdentifier linkIdentifier, MihLinkSapListI &iter);
      MihLinkSapListI GetRegisteredMihLinkSapListBegin (void);
      MihLinkSapListI GetRegisteredMihLinkSapListEnd (void);
      uint32_t GetRegisteredMihLinkSapListN (void);
      // EventSubscribe
      void EventSubscribe (MihfId destinationIdentifier,
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

      // Register
      void RegisterIndication (MihfId mihfid, 
                               LinkIdentifierList linkIdentifierList, 
                               RegistrationCode registrationCode,
                               MihRegisterResponseCallback responseCallback);
      // CapabilityDiscover;
      void CapabilityDiscoverIndication (MihfId mihfId,
                                         NetworkTypeAddressList networkTypeAddresses,
                                         EventList events,
                                         MihCommandList commands,
                                         InformationServiceQueryTypeList informationServiceQueryTypes,
                                         TransportSupportList transportSupports,
                                         MakeBeforeBreakSupportList makeBeforeBreakSupports,
                                         MihCapabilityDiscoverResponseCallback capabilityDiscoverResponseCallback);
      // LinkActions;
      void ConfirmLinkAction (Status status, 
                              ScanResponseList scans,
                              LinkActionResponse::ActionResult actionResult, 
                              LinkIdentifier linkIdentifier);
      void LinkActionsComplete (void);
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_FUNCTION_H */
