//
//  VoxelAgentData.cpp
//  hifi
//
//  Created by Stephen Birarda on 3/21/13.
//
//

#include "VoxelAgentData.h"
#include <cstring>
#include <cstdio>

VoxelAgentData::VoxelAgentData() {
    init();
}

void VoxelAgentData::init() {
    rootMarkerNode = new MarkerNode();
    _voxelPacket = new unsigned char[MAX_VOXEL_PACKET_SIZE];
    _voxelPacketAvailableBytes = MAX_VOXEL_PACKET_SIZE;
    _voxelPacketAt = _voxelPacket;
    resetVoxelPacket();
}

void VoxelAgentData::resetVoxelPacket() {
    _voxelPacket[0] = 'V';
    _voxelPacketAt = &_voxelPacket[1];
    _voxelPacketAvailableBytes = MAX_VOXEL_PACKET_SIZE-1;
    _voxelPacketWaiting = false;
}

void VoxelAgentData::writeToPacket(unsigned char* buffer, int bytes) {
    memcpy(_voxelPacketAt, buffer, bytes);
    _voxelPacketAvailableBytes -= bytes;
    _voxelPacketAt += bytes;
    _voxelPacketWaiting = true;
}

VoxelAgentData::~VoxelAgentData() {
    delete rootMarkerNode;
    delete[] _voxelPacket;
}

VoxelAgentData::VoxelAgentData(const VoxelAgentData &otherAgentData) {
    memcpy(&_position, &otherAgentData._position, sizeof(_position));
    init();
}

VoxelAgentData* VoxelAgentData::clone() const {
    return new VoxelAgentData(*this);
}
