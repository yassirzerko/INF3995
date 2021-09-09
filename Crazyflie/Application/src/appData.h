#ifndef SRC_APPDATA_H_
#define SRC_APPDATA_H_
#include "stdint.h"
#include "median_filter.h"
#include "commander.h"
#include "radiolink.h"

typedef enum
{
  NOT_READY,
  READY,
  TAKING_OFF,
  LANDING,
  HOVERING,
  EXPLORATING,
  RETURNING_TO_BASE,
  UPDATING,

} State;

typedef enum
{
  TAKE_OFF_COMMAND = 0,
  LAND_COMMAND,
  START_EXPLORATION_COMMAND,
  RETURN_TO_BASE_COMMAND,
  UNKNOWN_COMMAND,
} Command;

struct RxPacket
{
  uint16_t command;
} __attribute__((packed));

// Structure containing the data of the entire application
struct AppData
{
  bool keep_flying;
  bool taken_off;
  bool on_the_ground;
  bool correctly_initialized;
  bool is_on_exploration_mode;
  float height;
  float nominal_height;
  uint8_t rssi_inter;
  uint8_t rssi_inter_filtered;
  uint8_t rssi_inter_closest;
  float rssi_angle_inter_ext;
  float rssi_angle_inter_closest;
  uint8_t rssi_beacon;
  uint8_t rssi_beacon_filtered;
  uint8_t id_inter_ext;
  setpoint_t setpoint_BG;
  float vel_x_cmd, vel_y_cmd, vel_w_cmd;
  float heading_rad;
  float right_range;
  float front_range;
  float left_range;
  float up_range;
  float back_range;
  float rssi_angle;
  int state;
  float up_range_filtered;
  uint8_t rssi_array_other_drones[9];
  uint64_t time_array_other_drones[9];
  float rssi_angle_array_other_drones[9];
  uint8_t id_inter_closest;
  uint64_t takeoffdelaytime;
  uint8_t multiranger_isinit;
  uint8_t flowdeck_isinit;
  struct MedianFilterFloat medFilt;
  struct MedianFilterFloat medFilt_2;
  struct MedianFilterFloat medFilt_3;
  struct RxPacket rxPacket;
  Command lastCommand;
  State droneState;
  uint64_t address;
  uint8_t my_id;
  P2PPacket p_reply;
  int state_wf;
  point_t pos;
  point_t initialPos;
  int batteryLevel;
  bool outbound;
  int batteryCounter;
};

#endif
