#ifndef TRASNPORTTX
#define TRASNPORTTX

#include <string.h>
#include <omnetpp.h>
#include "packet_m.h"

using namespace omnetpp;

class TransportTx: public cSimpleModule {
private:
    cQueue buffer;
    cMessage *endServiceEvent;
    simtime_t serviceTime;
    simtime_t delayOutput;
    int packetloss;
    int packetSent;
    bool next;

    // Vectores
    cOutVector bufferSizeVector;
    cOutVector packetDropVector;
public:
    TransportTx();
    virtual ~TransportTx();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(TransportTx);

TransportTx::TransportTx() {
    endServiceEvent = NULL;
}

TransportTx::~TransportTx() {
    cancelAndDelete(endServiceEvent);
}

void TransportTx::initialize() {
    buffer.setName("buffer");
    endServiceEvent = new cMessage("endService");
    bufferSizeVector.setName("bufferSize");
    packetDropVector.setName("packetDrop");

    delayOutput = par("delayOutput");
    packetloss = 0;
    packetSent = 0;

    next = true;
}

void TransportTx::finish() {
}

void TransportTx::handleMessage(cMessage *msg) {

    // if msg is signaling an endServiceEvent
    if (msg == endServiceEvent) {
        // if packet in buffer, send next one
        if (!buffer.isEmpty() && next) {

            cPacket *pkt = (cPacket*) buffer.pop();
            send(pkt, "toOut$o");

            // cuento el paquete enviado
            packetSent++;

            // aumento el retraso de la salida
            if (packetSent > 30) {
                packetSent = 0; // reset
                delayOutput = delayOutput * 1.1;
            }

            serviceTime = pkt->getDuration();

            scheduleAt(simTime() + serviceTime + delayOutput, endServiceEvent);
        }
    } else { // msg is packet or feedback

        if (msg->getKind() == 0){ // msg is packet

            if (buffer.getLength() == par("bufferSize").intValue()) {
                delete msg;
                this->bubble("Packet Drop");

                // Metricas
                packetloss++;
                packetDropVector.record(packetloss);
            } else {
                // almaceno el packet
                buffer.insert(msg);
                this->bubble("Encolado");


                // metricas
                bufferSizeVector.record(buffer.getLength());

                if (packetloss > 0 ){
                    packetloss--;
                    packetDropVector.record(packetloss);
                }

                // ------------
                if (!endServiceEvent->isScheduled()) {
                    scheduleAt(simTime(), endServiceEvent);
                }
            }

        } else if (msg->getKind() == 2){ // msg is feedback

            FeedbackPkt * feedback = (FeedbackPkt *) msg;
            // Seteo next segun lo que diga Rx
            next = feedback->getNext();

            // confirmo los paquetes recibidos
            packetSent--;

            if (!next){
                this->bubble("next false");
            }

            delete msg;
        }
    }
}

#endif /* TRASNPORTTX */
