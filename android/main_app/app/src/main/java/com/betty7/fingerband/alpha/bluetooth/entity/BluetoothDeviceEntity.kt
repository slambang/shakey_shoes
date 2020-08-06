package com.betty7.fingerband.alpha.bluetooth.entity

data class BluetoothDeviceEntity(
    val id: Int,
    val macAddress: String,
    val serviceUuid: String,
    val baudRateBits: Int,
    val pairingPin: String
)
