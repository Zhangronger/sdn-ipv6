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

#ifndef   	MIH_LINK_SAP_H
#define   	MIH_LINK_SAP_H

#include <vector>
#include "ns3/callback.h"
#include "ns3/traced-callback.h"
#include "ns3/object.h"
#include "ns3/event-id.h"
#include "mih-callbacks.h"
#include "mih-event-list.h"
#include "mih-link-configuration-parameter.h"
#include "mih-link-event-subscribe.h"
#include "mih-link-event-unsubscribe.h"
#include "mih-link-get-parameters.h"
#include "mih-link-configure-thresholds.h"
#include "mih-link-action.h"
#include "mih-link-capability-discover.h"

namespace ns3 {
  namespace mih {
    class DeviceStatesResponse;

    class MihLinkSap : public Object {
    public:
      static TypeId GetTypeId (void);
      virtual ~MihLinkSap (void);
      virtual LinkType GetLinkType (void) = 0;
      virtual void SetLinkType (LinkType linkType) = 0;
      virtual Address GetLinkAddress (void) = 0;
      virtual void SetLinkAddress (Address addr) = 0;
      virtual LinkIdentifier GetLinkIdentifier (void) = 0;
      virtual void SetLinkIdentifier (LinkIdentifier linkId) = 0;
      virtual Address GetPoAAddress (void) = 0;
      virtual void SetPoAAddress (Address addr) = 0;
      // Event Service
      virtual void LinkDetected (MihfId sourceMihfId, 
                                 LinkDetectedInformationList linkDetectedInfoList);
      virtual void LinkUp (MihfId sourceMihfId, 
                           LinkIdentifier linkIdentifier, 
                           Address oldAR, 
                           Address newAR,
                           bool ipRenewal,
                           MobilityManagementSupport mobilitySupport);
      virtual void LinkDown (MihfId sourceMihfId,
                             LinkIdentifier linkIdentifier,
                             Address oldAR,
                             LinkDownReason reason);
      virtual void LinkParametersReport (MihfId sourceMihfId,
                                         LinkIdentifier linkIdentifier,
                                         LinkParameterReportList parameters);
      virtual void LinkGoingDown (MihfId sourceMihfId,
                                  LinkIdentifier linkIdentifier, 
                                  uint64_t timeInterval,
                                  LinkGoingDownReason reason);
      virtual void LinkHandoverImminent (MihfId sourceMihfId,
                                         LinkIdentifier oldLinkIdentifier,
                                         LinkIdentifier newLinkIdentifier, 
                                         Address oldAR, Address newAR);
      virtual void LinkHandoverComplete (MihfId sourceMihfId,
                                         LinkIdentifier oldLinkIdentifier,
                                         LinkIdentifier newLinkIdentifier, 
                                         Address oldAR, 
                                         Address newAR, 
                                         Status handoverStatus);
      virtual void LinkPduTransmitStatus (MihfId sourceMihfId,
                                          LinkIdentifier linkIdentifier, 
                                          uint16_t packetIdentifier, 
                                          bool transmissionStatus);
      // Command Service
      virtual LinkCapabilityDiscoverConfirm CapabilityDiscover (void) = 0;
      virtual LinkEventSubscribeConfirm EventSubscribe (EventList::Type linkDetectedEventType1,
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
                                                        MihLinkPduTransmitStatusIndicationCallback linkPduTxStatusEventCallback8);
      virtual LinkEventUnsubscribeConfirm EventUnsubscribe (EventList::Type linkDetectedEventType1,
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
                                                            MihLinkPduTransmitStatusIndicationCallback linkPduTxStatusEventCallback8);
      virtual LinkGetParametersConfirm GetParameters (LinkParameterTypeList linkParametersRequest, 
                                                      LinkStatesRequest linkStatesRequest, 
                                                      LinkDescriptorsRequest descriptors) = 0;
      virtual LinkConfigureThresholdsConfirm ConfigureThresholds (LinkConfigurationParameterList configureParameters) = 0;
      virtual EventId Action (LinkAction action, 
                              uint64_t executionDelay, 
                              Address poaLinkAddress,
                              LinkActionConfirmCallback actionConfirmCb) = 0;
      
    protected:
      friend class MihFunction;
      // Device states;
      virtual Ptr<DeviceStatesResponse> GetDeviceStates (void) = 0;
      
      // MIES TracedCallback;
      MihLinkDetectedIndicationTracedCallback m_linkDetectedTraceCallback;
      MihLinkUpIndicationTracedCallback m_linkUpTracedCallback;
      MihLinkDownIndicationTracedCallback m_linkDownTracedCallback;
      MihLinkParametersReportIndicationTracedCallback m_linkParametersReportTracedCallback;
      MihLinkGoingDownIndicationTracedCallback m_linkGoingDownTracedCallback;
      MihLinkHandoverImminentIndicationTracedCallback m_linkHOImminentTracedCallback;
      MihLinkHandoverCompleteIndicationTracedCallback m_linkHOCompleteTracedCallback;
      MihLinkPduTransmitStatusIndicationTracedCallback m_linkPduTxStatusTracedCallback;
    };
    typedef std::vector<Ptr<MihLinkSap> > MihLinkSapList;
    typedef MihLinkSapList::iterator MihLinkSapListI;
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_SAP_H */
