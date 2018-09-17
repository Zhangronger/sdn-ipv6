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

#ifndef   	MIH_CALLBACKS_H
#define   	MIH_CALLBACKS_H

#include "ns3/callback.h"
#include "ns3/traced-callback.h"
#include "mihf-id.h"
#include "mih-link-detected-information.h"
#include "mih-link-identifier.h"
#include "mih-mobility-management-support.h"
#include "mih-link-parameter-report.h"
#include "mih-link-down-reason.h"
#include "mih-link-going-down-reason.h"
#include "mih-device-states-request.h"
#include "mih-status.h"
#include "mih-network-type-address.h"
#include "mih-device-states-response.h"
#include "mih-link-states-response.h"
#include "mih-link-status-request.h"
#include "mih-link-status-response.h"
#include "mih-link-configuration-parameter.h"
#include "mih-link-configuration-status.h"
#include "mih-link-action-request.h"
#include "mih-link-action-response.h"
#include "mih-information-service-query-type-list.h"
#include "mih-make-before-break-support.h"
#include "mih-transport-support-list.h"
#include "mih-registration-code.h"
#include "mih-event-list.h"
#include "mih-command-list.h"

namespace ns3 {
  namespace mih {
    // Event service callbacks;
    // Link detected;
    typedef Callback<void, MihfId, LinkDetectedInformationList> MihLinkDetectedIndicationCallback;
    typedef TracedCallback<MihfId, LinkDetectedInformationList> MihLinkDetectedIndicationTracedCallback;
    // Link up;
    typedef Callback<void, MihfId, LinkIdentifier, Address, Address, bool, MobilityManagementSupport> MihLinkUpIndicationCallback;
    typedef TracedCallback<MihfId, LinkIdentifier, Address, Address, bool, MobilityManagementSupport> MihLinkUpIndicationTracedCallback;
    // Link down;
    typedef Callback<void, MihfId, LinkIdentifier, Address, LinkDownReason> MihLinkDownIndicationCallback;
    typedef TracedCallback<MihfId, LinkIdentifier, Address, LinkDownReason> MihLinkDownIndicationTracedCallback;
    // Link parameters report;
    typedef Callback<void, MihfId, LinkIdentifier, LinkParameterReportList> MihLinkParametersReportIndicationCallback;
    typedef TracedCallback<MihfId, LinkIdentifier, LinkParameterReportList> MihLinkParametersReportIndicationTracedCallback;
      // Link going down;
    typedef Callback<void, MihfId, LinkIdentifier, uint64_t, LinkGoingDownReason> MihLinkGoingDownIndicationCallback;
    typedef TracedCallback<MihfId, LinkIdentifier, uint64_t, LinkGoingDownReason> MihLinkGoingDownIndicationTracedCallback;
    // Link handover imminent;
    typedef Callback<void, MihfId, LinkIdentifier, LinkIdentifier, Address, Address> MihLinkHandoverImminentIndicationCallback;
    typedef TracedCallback<MihfId, LinkIdentifier, LinkIdentifier, Address, Address> MihLinkHandoverImminentIndicationTracedCallback;
    // Link handover complete;
    typedef Callback<void, MihfId, LinkIdentifier, LinkIdentifier, Address, Address, Status> MihLinkHandoverCompleteIndicationCallback;
    typedef TracedCallback<MihfId, LinkIdentifier, LinkIdentifier, Address, Address, Status> MihLinkHandoverCompleteIndicationTracedCallback;
    //Link PDU transmit status;
    typedef Callback<void, MihfId, LinkIdentifier, uint16_t, bool> MihLinkPduTransmitStatusIndicationCallback;
    typedef TracedCallback<MihfId, LinkIdentifier, uint16_t, bool> MihLinkPduTransmitStatusIndicationTracedCallback;
    // Command service callbacks;
    // Capability discover;
    typedef Callback<void, MihfId, Status, NetworkTypeAddressList, EventList, MihCommandList, InformationServiceQueryTypeList, TransportSupportList, MakeBeforeBreakSupportList> MihCapabilityDiscoverResponseCallback;
    typedef TracedCallback<MihfId, NetworkTypeAddressList, EventList, MihCommandList, InformationServiceQueryTypeList, TransportSupportList, MakeBeforeBreakSupportList, MihCapabilityDiscoverResponseCallback> MihCapabilityDiscoverIndicationTracedCallback;
    typedef Callback<void, MihfId, NetworkTypeAddressList, EventList, MihCommandList, InformationServiceQueryTypeList, TransportSupportList, MakeBeforeBreakSupportList, MihCapabilityDiscoverResponseCallback> MihCapabilityDiscoverIndicationCallback;
    typedef Callback<void, MihfId, Status, NetworkTypeAddressList, EventList, MihCommandList, InformationServiceQueryTypeList, TransportSupportList, MakeBeforeBreakSupportList> MihCapabilityDiscoverConfirmCallback;
    // Register;
    typedef Callback<void, MihfId, Status, uint32_t> MihRegisterResponseCallback;
    typedef Callback<void, MihfId, LinkIdentifierList, RegistrationCode, MihRegisterResponseCallback> MihRegisterIndicationCallback;
    typedef TracedCallback<MihfId, LinkIdentifierList, RegistrationCode, MihRegisterResponseCallback> MihRegisterIndicationTracedCallback;
    typedef Callback<void, MihfId, Status, uint32_t> MihRegisterConfirmCallback;
    // DeRegister;
    typedef Callback<void, MihfId, Status> MihDeRegisterResponseCallback;
    typedef Callback<void, MihfId, MihDeRegisterResponseCallback>  MihDeRegisterIndicationCallback;
    typedef TracedCallback<MihfId, MihDeRegisterResponseCallback> MihDeRegisterIndicationTracedCallback;
    typedef Callback<void, MihfId, Status> MihDeRegisterConfirmCallback;
    // Event subscribe;
    typedef Callback<void, MihfId, Status, LinkIdentifier, EventList> MihEventSubscribeConfirmCallback;
    // Event unsubscribe;
    typedef Callback<void, MihfId, Status, LinkIdentifier, EventList> MihEventUnsubscribeConfirmCallback;
    // Link get parameters;
    typedef Callback<void, MihfId, Status, DeviceStatesResponseList, LinkStatusResponseList> MihLinkGetParametersConfirmCallback;
    // Link configure thresholds;
    typedef Callback<void, MihfId, Status, LinkIdentifier, LinkConfigurationStatusList> MihLinkConfigureThresholdsConfirmCallback;
    // Link actions;
    typedef Callback<void, MihfId, Status, LinkActionResponseList> MihLinkActionsConfirmCallback;
    /**
     * \param Status The status of the action.
     * \param ScanResponseList The list of discovered networks.
     * \param LinkActionResponse::ActionResult The action result.
     * \param LinkIdentifier The caller device identity.
     * 
     * This callback belongs to the Mih Function and is responsible
     * for building the list of link action responses which will be
     * passed to the callback provided by the caller MihUser.
     *
     * It is worth noting that link action request executions can be
     * delayed, so we need this callback to be called in an
     * asynchronous way. This stands also for the callback provided by
     * the MihUser entity.
     */
    typedef Callback<void, Status, ScanResponseList, LinkActionResponse::ActionResult, LinkIdentifier> LinkActionConfirmCallback;
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_CALLBACKS_H */
