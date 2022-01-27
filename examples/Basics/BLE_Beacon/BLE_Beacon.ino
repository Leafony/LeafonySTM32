//=====================================================================
//  Leafony Platform sample sketch
//     Application  : STM32 Simple BLE Beacon Example
//     Processor    : STM32L452RE (Nucleo-64/Nucleo L452RE)
//     Arduino IDE  : 1.8.15
//     STM32 Core   : Ver1.9.0
//
//     Leaf configuration
//       (1) AC02 BLE Sugar
//       (2) AP03 STM32 MCU
//       (3) AZ01 USB
//
//    (c) 2021 LEAFONY SYSTEMS Co., Ltd
//    Released under the MIT license
//    https://opensource.org/licenses/MIT
//
//      Rev.00 2021/04/01 First release
//=====================================================================
#include <LeafonySTM32.h>

#define SLEEP_INTERVAL (8)
#define WAKE_INTERVAL  (1)

static LeafonySTM32 leafony;

volatile bool bSystemBootBle = false;

void setupBLE()
{
  // set up internal status handlers
  leafony.ble.onBusy(onBusy);
  leafony.ble.onIdle(onIdle);
  leafony.ble.onTimeout(onTimeout);

  // set up BGLib event handlers
  leafony.ble.ble_evt_gatt_server_attribute_value(my_evt_gatt_server_attribute_value);
  leafony.ble.ble_evt_le_connection_opend(my_evt_le_connection_opend);
  leafony.ble.ble_evt_le_connection_closed(my_evt_le_connection_closed);
  leafony.ble.ble_evt_system_boot(my_evt_system_boot);
  leafony.ble.ble_evt_system_awake(my_evt_system_awake);
  leafony.ble.ble_rsp_system_get_bt_address(my_rsp_system_get_bt_address);

  leafony.ble.init();
}

void StartAdvData()
{
  // Advertising data; 25byte MAX
  uint8_t adv_data[] = {
    // AD Structure 1: Flag
    (2),  //0: field length
    BGLIB_GAP_AD_TYPE_FLAGS,  //1: field type (0x01)
    (6),  //2: data
    // AD Structure 2: Complete local name
    (7),  //3: field length
    BGLIB_GAP_AD_TYPE_LOCALNAME_COMPLETE,  //4: field type (0x09)
    ('L'),  //5:
    ('e'),  //6:
    ('a'),  //7:
    ('f'),  //8:
    ('_'),  //9:
    ('A'),  //10:
    // AD Structure 3: Manufacture specific
    (13),   //11: field length
    (0xff), //12: field type (0xff)
    ('H'),  //13:
    ('E'),  //14:
    ('L'),  //15:
    ('L'),  //16:
    ('O'),  //17:
    (' '),  //18:
    ('B'),  //19:
    ('E'),  //20:
    ('A'),  //21:
    ('C'),  //22:
    ('O'),  //23:
    ('N'),  //24:
  };

  // Register advertising packet
  leafony.ble.setAdvData(sizeof(adv_data), adv_data);
  // Start advertising
  leafony.ble.startAdv();
}

void setup()
{
  Serial.begin(115200);
  LowPower.begin(); // Configure low power
  setupBLE();
}

void loop()
{
  StartAdvData();
  Serial.println(F("Start advertise"));
  Serial.flush();

  // Continue Advertising (during that STM32 sleeps.)
  LowPower.deepSleep(WAKE_INTERVAL * 1000);

  Serial.println(F("Sleep BLE"));
  leafony.ble.sleep();

  Serial.println(F("Sleep STM32"));
  Serial.println(F(">>> Sleep >>>"));
  Serial.flush();

  LowPower.deepSleep(SLEEP_INTERVAL * 1000);
  Serial.println(F("Wakeup STM32"));

  leafony.ble.wakeup();
  Serial.println(F("Wakeup BLE"));

  Serial.println(F("<<< Wake up <<<"));
}

// called when the module begins sending a command
void onBusy()
{
}

// called when the module receives a complete response or "system_boot" event
void onIdle()
{
}

// called when the parser does not read the expected response in the specified time limit
void onTimeout()
{
}

// called immediately before beginning UART TX of a command
void onBeforeTXCommand()
{
}

// called immediately after finishing UART TX
void onTXCommandComplete()
{
}

// called when the attribute value changed
void my_evt_gatt_server_attribute_value(const struct ble_msg_gatt_server_attribute_value_evt_t *msg)
{
}

// called when the connection is opened
void my_evt_le_connection_opend(const ble_msg_le_connection_opend_evt_t *msg)
{
}

// called when connection is closed
void my_evt_le_connection_closed(const struct ble_msg_le_connection_closed_evt_t *msg)
{
}

// called when the system booted
void my_evt_system_boot(const ble_msg_system_boot_evt_t *msg)
{
  Serial.print("###\tsystem_boot: { ");
  Serial.print("major: ");
  Serial.print(msg->major, HEX);
  Serial.print(", minor: ");
  Serial.print(msg->minor, HEX);
  Serial.print(", patch: ");
  Serial.print(msg->patch, HEX);
  Serial.print(", build: ");
  Serial.print(msg->build, HEX);
  Serial.print(", bootloader_version: ");
  Serial.print(msg->bootloader, HEX);
  Serial.print(", hw: ");
  Serial.print(msg->hw, HEX);
  Serial.println(" }");

  bSystemBootBle = true;
}

// called when the system awake
void my_evt_system_awake(void)
{
  Serial.println("###\tsystem_awake");
}

//
void my_rsp_system_get_bt_address(const struct ble_msg_system_get_bt_address_rsp_t *msg)
{
  Serial.print("###\tsystem_get_bt_address: { ");
  Serial.print("address: ");
  for (int i = 0; i < 6; i++)
  {
    Serial.print(msg->address.addr[i], HEX);
  }
  Serial.println(" }");

  unsigned short addr = 0;
  char cAddr[30];
  addr = msg->address.addr[0] + (msg->address.addr[1] * 0x100);
  sprintf(cAddr, "Device name is Leaf_A_#%05d ", addr);
  Serial.println(cAddr);
}