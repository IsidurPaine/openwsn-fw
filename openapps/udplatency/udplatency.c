#include "opendefs.h"
#include "udplatency.h"
#include "openudp.h"
#include "openqueue.h"
#include "openserial.h"
#include "packetfunctions.h"
#include "opentimers.h"
#include "openrandom.h"
#include "opencoap.h"
#include "scheduler.h"
#include "IEEE802154E.h"
#include "idmanager.h"
#include "neighbors.h"
#include "udplatency.h"

//=========================== defines =========================================

/// inter-packet period (in mseconds)
#define UDPLATENCYPERIOD     25000

//=========================== variables =======================================

typedef struct {
	opentimer_id_t  timerId;
} udplatency_vars_t;

udplatency_vars_t udplatency_vars;

//=========================== prototypes ======================================

void udplatency_timer(void);

//=========================== public ==========================================

void udplatency_init() {
	//don't run on dagroot
	if (idmanager_getIsDAGroot()) return;

	udplatency_vars.timerId    = opentimers_start(UDPLATENCYPERIOD,
			TIMER_PERIODIC,TIME_MS,
			udplatency_timer);
}

void udplatency_task(){
	OpenQueueEntry_t* pkt;
	open_addr_t * p;
	open_addr_t  q;

	//prepare packet
	pkt = openqueue_getFreePacketBuffer(COMPONENT_UDPLATENCY);
	if (pkt==NULL) {
		openserial_printError(COMPONENT_UDPLATENCY,ERR_NO_FREE_PACKET_BUFFER,
				(errorparameter_t)0,
				(errorparameter_t)0);
		return;
	}
	pkt->creator                     = COMPONENT_UDPLATENCY;
	pkt->owner                       = COMPONENT_UDPLATENCY;
	pkt->l4_protocol                 = IANA_UDP;
	pkt->l4_sourcePortORicmpv6Type   = WKP_UDP_LATENCY;
	pkt->l4_destination_port         = WKP_UDP_LATENCY;
	pkt->l3_destinationAdd.type 	 = ADDR_128B;
	memcpy(&pkt->l3_destinationAdd.addr_128b[0],&ipAddr_local,16);

	// Il payload contiene ASN (da aggiornare) + ID + ASN
	packetfunctions_reserveHeaderSize(pkt,sizeof(asn_t));
	pkt->payload[0]=255;
	pkt->payload[1]=255;
	pkt->payload[2]=255;
	pkt->payload[3]=255;
	pkt->payload[4]=255;

	packetfunctions_reserveHeaderSize(pkt,2);
	p=idmanager_getMyID(ADDR_64B);
	pkt->payload[0]=p->addr_64b[6];
	pkt->payload[1]=p->addr_64b[7];

	packetfunctions_reserveHeaderSize(pkt,sizeof(asn_t));
	// Done - ora devo ricevere e prendere l'asn
	ieee154e_getAsn(pkt->payload);

	//send packet
	if ((openudp_send(pkt))==E_FAIL) {
		openqueue_freePacketBuffer(pkt);
	}
}

void udplatency_timer() {
	scheduler_push_task(udplatency_task,TASKPRIO_COAP);
}

void udplatency_sendDone(OpenQueueEntry_t* msg, owerror_t error) {
	msg->owner = COMPONENT_UDPLATENCY;
	if (msg->creator!=COMPONENT_UDPLATENCY) {
		openserial_printError(COMPONENT_UDPLATENCY,ERR_UNEXPECTED_SENDDONE,
				(errorparameter_t)0,
				(errorparameter_t)0);
	}
	openqueue_freePacketBuffer(msg);
}

void udplatency_receive(OpenQueueEntry_t* msg) {
	openqueue_freePacketBuffer(msg);
}

//=========================== private =========================================
