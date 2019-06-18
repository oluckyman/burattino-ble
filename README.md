# Burattino

Based on [ble_prov](https://github.com/espressif/esp-idf/tree/master/examples/provisioning/ble_prov) and [custom_config](https://github.com/espressif/esp-idf/tree/master/examples/provisioning/custom_config) examples. Some code maybe redundant.  
 1. Starts BLE provisioning service.  
 1. Waits for Wi-Fi credentials.  
 1. When got credentials, connects to Wi-Fi.  
 1. Waits for `endpoint` and `token` sent via protocomm.  
 1. Makes HTTP request to the received `endpoint` signs it with `token`.  
 1. Repsponds to the protocomm request with Device ID if the endpoint call was successful.  

## Initial Setup
### [Get Started](http://esp-idf.readthedocs.io/en/latest/get-started/)


## When it all set up
### Build and flash

```
make flash
```
### Run
```
make flash monitor
```
To exit monitor `Ctrl+]`
To enter escape mode `Ctrl+T` `<command>`
Some of the commands in escape mode:

 - Restart `Ctrl+R`
 - Build and flash the project `Ctrl+F`
 - Build and flash the app only `Ctrl+R`
 - Display all keyboard shortcuts `Ctrl+H`



### Configure
```
make menuconfig
```
For example, to set the writing speed faster or to reset/persist Wi-Fi credentials.
