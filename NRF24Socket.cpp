#include "NRF24Socket.h"

bool NRF24Socket::begin() {

    if (this->logger == nullptr) {
        return false;
    }
    if (this->mqttSnMessageHandler == nullptr) {
        return false;
    }
    if(this->nrf24 == nullptr){
        return false;
    }
    if(this->manager == nullptr){
        return false;
    }

    this->broadcastAddress = device_address(RH_BROADCAST_ADDRESS, 0, 0, 0, 0, 0);
    // manager->setThisAddress(OWN_ADDRESS);
    this->ownAddress = device_address(manager->thisAddress(), 0, 0, 0, 0, 0);

    // Default init is 2.402 GHz (channel 2), 2Mbps, 0dBm
    if (!nrf24->init()) {
        return false;
    }
    if (!nrf24->setRF(RH_NRF24::DataRate250kbps, RH_NRF24::TransmitPowerm18dBm)) {
        return false;
    }
    return manager->init();
}

void NRF24Socket::setNrf24(RH_NRF24 *nrf24) {
    NRF24Socket::nrf24 = nrf24;
}

void NRF24Socket::setManager(RHReliableDatagram *manager) {
    NRF24Socket::manager = manager;
}

void NRF24Socket::setLogger(LoggerInterface *logger) {
    NRF24Socket::logger = logger;
}

void NRF24Socket::setMqttSnMessageHandler(MqttSnMessageHandler *mqttSnMessageHandler) {
    NRF24Socket::mqttSnMessageHandler = mqttSnMessageHandler;
}

device_address *NRF24Socket::getBroadcastAddress() {
    return &this->broadcastAddress;
}

device_address *NRF24Socket::getAddress() {
    return &this->ownAddress;
}

uint8_t NRF24Socket::getMaximumMessageLength() {
    return RH_NRF24_MAX_MESSAGE_LEN;
}

bool NRF24Socket::send(device_address *destination, uint8_t *bytes, uint16_t bytes_len) {
    return send(destination, bytes, bytes_len, UINT8_MAX);
}

bool NRF24Socket::send(device_address *destination, uint8_t *bytes, uint16_t bytes_len, uint8_t signal_strength) {
    manager->sendto(bytes, bytes_len, destination->bytes[0]);
    manager->waitPacketSent();
    manager->available(); // put it back to receive mode
    return true;
}

bool NRF24Socket::loop() {
    uint8_t buf_len = RH_NRF24_MAX_MESSAGE_LEN;
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    memset(&buf, 0x0, RH_NRF24_MAX_MESSAGE_LEN);
    device_address from;
    memset(&from.bytes[0], 0x0, sizeof(device_address));
    if (manager->available()) {
        if (manager->recvfrom(buf, &buf_len, &from.bytes[0])) {
            mqttSnMessageHandler->receiveData(&from, (uint8_t *) &buf);
        }
    }
    return true;
}

