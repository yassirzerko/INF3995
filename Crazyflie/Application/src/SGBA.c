#include "SGBA.h"
#include "wallfollowing_multiranger_onboard.h"

#include <math.h>
#include <stdlib.h>

#include "usec_time.h"

float state_start_time;

//static variables only used for initialization
static bool first_run = true;
static float ref_distance_from_wall = 0;
static float max_speed = 0.5;

//Make variable
uint8_t rssi_threshold = 58;           // normal batteries 50/52/53/53 bigger batteries 55/57/59
uint8_t rssi_collision_threshold = 50; // normal batteris 43/45/45/46 bigger batteries 48/50/52

float initialPosX;
float initialPosY;

// Converts degrees to radians.
#define deg2rad(angleDegrees) (angleDegrees * (float)M_PI / 180.0f)

// Converts radians to degrees.
#define rad2deg(angleRadians) (angleRadians * 180.0f / (float)M_PI)

static int transition(int new_state)
{

  float t = usecTimestamp() / 1e6;
  state_start_time = t;

  return new_state;
}

// Static helper functions
static bool logicIsCloseTo(float real_value, float checked_value, float margin)
{
  if (real_value > checked_value - margin && real_value < checked_value + margin)
  {
    return true;
  }
  else
  {
    return false;
  }
}

static float wraptopi(float number)
{
  if (number > (float)M_PI)
  {
    return (number - (float)(2 * M_PI));
  }
  else if (number < (float)(-1 * M_PI))
  {
    return (number + (float)(2 * M_PI));
  }
  else
  {
    return (number);
  }
}

// Command functions
static void commandTurn(float *vel_w, float max_rate)
{
  *vel_w = max_rate;
}

uint8_t maxValue(uint8_t myArray[], int size)
{
  int i;
  uint8_t maxValue = myArray[0];

  for (i = 1; i < size; ++i)
  {
    if (myArray[i] > maxValue)
    {
      maxValue = myArray[i];
    }
  }
  return maxValue;
}

// statemachine functions
static float wanted_angle = 0;

void init_SGBA_controller(float new_ref_distance_from_wall, float max_speed_ref,
                          float begin_wanted_heading, float initPositionX, float initPositionY)
{
  ref_distance_from_wall = new_ref_distance_from_wall;
  max_speed = max_speed_ref;
  wanted_angle = begin_wanted_heading;
  first_run = true;
  initialPosX = initPositionX;
  initialPosY = initPositionY;
}

int SGBA_controller(float *vel_x, float *vel_y, float *vel_w, float *rssi_angle, int *state_wallfollowing,
                    float front_range, float left_range, float right_range, float back_range,
                    float current_heading, float current_pos_x, float current_pos_y, uint8_t rssi_beacon,
                    uint8_t rssi_inter, float rssi_angle_inter, bool priority, bool outbound, bool *keep_flying)
{

  // Initalize static variables
  static int state = 2;
  static int state_wf = 0;
  static float wanted_angle_dir = 0;
  static float pos_x_hit = 0;
  static float pos_y_hit = 0;
  static float pos_x_sample = 0;
  static float pos_y_sample = 0;
  static bool overwrite_and_reverse_direction = false;
  static float direction = 1;
  static bool cannot_go_to_goal = false;
  static bool rssi_sample_reset = false;

  static bool first_time_inbound = true;
  static float wanted_angle_hit = 0;

  // if it is reinitialized
  if (first_run)
  {

    wanted_angle_dir = wraptopi(current_heading - wanted_angle); // to determine the direction when turning to goal

    overwrite_and_reverse_direction = false;
    state = 2;

    float t = usecTimestamp() / 1e6;
    state_start_time = t;
    first_run = false;
  }

  if (first_time_inbound && !outbound)
  {
    wraptopi(wanted_angle - 3.14f);
    wanted_angle_dir = wraptopi(current_heading - wanted_angle);
    state = transition(2);
    first_time_inbound = false;
  }

  /***********************************************************
   * State definitions
   ***********************************************************/
  // 1 = forward
  // 2 = rotate_to_goal
  // 3 = wall_following
  // 4 = move out of way

  /***********************************************************
   * Handle state transitions
   ***********************************************************/

  if (state == 1)
  { //FORWARD
    if (front_range < ref_distance_from_wall + 0.2f)
    {

      // if looping is detected, reverse direction (only on outbound)
      if (overwrite_and_reverse_direction)
      {
        direction = -1.0f * direction;
        overwrite_and_reverse_direction = false;
      }
      else
      {
        if (left_range < right_range && left_range < 2.0f)
        {
          direction = -1.0f;
        }
        else if (left_range > right_range && right_range < 2.0f)
        {
          direction = 1.0f;
        }
        else if (left_range > 2.0f && right_range > 2.0f)
        {
          direction = 1.0f;
        }
        else
        {
        }
      }

      pos_x_hit = current_pos_x;
      pos_y_hit = current_pos_y;
      wanted_angle_hit = wanted_angle;

      wall_follower_init(0.4, 0.5, 3);

      state = transition(3); //wall_following
    }
  }
  else if (state == 2)
  { //ROTATE_TO_GOAL
    // check if heading is close to the preferred_angle
    bool goal_check = logicIsCloseTo(wraptopi(current_heading - wanted_angle), 0, 0.1f);
    if (front_range < ref_distance_from_wall + 0.2f)
    {
      cannot_go_to_goal = true;
      wall_follower_init(0.4, 0.5, 3);

      state = transition(3); //wall_following
    }
    if (goal_check)
    {
      state = transition(1); //forward
    }
  }
  else if (state == 3)
  { //WALL_FOLLOWING

    // if another drone is close and there is no right of way, move out of the way
    if (priority == false && rssi_inter < rssi_threshold)
    {
      if (outbound)
      {
        if ((rssi_angle_inter < 0 && wanted_angle < 0) || (rssi_angle_inter > 0 && wanted_angle > 0))
        {
          wanted_angle = -1 * wanted_angle;
          wanted_angle_dir = wraptopi(current_heading - wanted_angle);
          //state= transition(2);
        }
      }
      if (rssi_inter < rssi_collision_threshold)
      {
        state = transition(4);
      }
    }

    // If going forward with wall following and cannot_go_to_goal bool is still on
    //    turn it off!
    if (state_wf == 5 && cannot_go_to_goal)
    {
      cannot_go_to_goal = false;
    }

    // Check if the goal is reachable from the current point of view of the agent
    float bearing_to_goal = wraptopi(wanted_angle - current_heading);
    bool goal_check_WF = false;
    if (direction == -1)
    {
      goal_check_WF = (bearing_to_goal < 0 && bearing_to_goal > -1.5f);
    }
    else
    {
      goal_check_WF = (bearing_to_goal > 0 && bearing_to_goal < 1.5f);
    }

    // Check if bug went into a looping while wall following,
    //    if so, then forse the reverse direction predical.
    float rel_x_loop = current_pos_x - pos_x_hit; //  diff_rssi = (int)prev_rssi - (int)rssi_beacon;
    float rel_y_loop = current_pos_y - pos_y_hit;
    float loop_angle = wraptopi(atan2(rel_y_loop, rel_x_loop));

    if (fabs(wraptopi(wanted_angle_hit + 3.14f - loop_angle)) < 1.0)
    {
      overwrite_and_reverse_direction = true;
    }
    else
    {
    }

    // if during wallfollowing, agent goes around wall, and heading is close to rssi _angle
    //      got to rotate to goal
    if ((state_wf == 6 || state_wf == 8) && goal_check_WF && front_range > ref_distance_from_wall + 0.4f && !cannot_go_to_goal)
    {
      wanted_angle_dir = wraptopi(current_heading - wanted_angle); // to determine the direction when turning to goal
      state = transition(2);                                       //rotate_to_goal
    }

    // If going straight
    //    determine by the gradient of the crazyradio what the approx direction is.
    if (state_wf == 5)
    {

      if (!outbound)
      {
        // Reset sample gathering
        if (rssi_sample_reset)
        {
          pos_x_sample = current_pos_x;
          pos_y_sample = current_pos_y;
          rssi_sample_reset = false;
        }

        // if the crazyflie traveled for 1 meter, than measure if it went into the right path
        float rel_x_sample = current_pos_x - pos_x_sample;
        float rel_y_sample = current_pos_y - pos_y_sample;
        float distance = sqrt(rel_x_sample * rel_x_sample + rel_y_sample * rel_y_sample);
        if (distance > 1.0f)
        {
          rssi_sample_reset = true;
          wanted_angle = wraptopi(atan2(initialPosY - current_pos_y, initialPosX - current_pos_x));
        }
      }
    }
    else
    {
      rssi_sample_reset = true;
    }
  }
  else if (state == 4)
  { //MOVE_OUT_OF_WAY
    // once the drone has gone by, rotate to goal
    if (rssi_inter >= rssi_collision_threshold)
    {

      state = transition(2); //rotate_to_goal
    }
  }

  /***********************************************************
   * Handle state actions
   ***********************************************************/

  float temp_vel_x = 0;
  float temp_vel_y = 0;
  float temp_vel_w = 0;

  if (state == 1)
  { //FORWARD
    // stop moving if there is another drone in the way
    // forward max speed
    if (left_range < ref_distance_from_wall)
    {
      temp_vel_y = -0.2f;
    }
    if (right_range < ref_distance_from_wall)
    {
      temp_vel_y = 0.2f;
    }
    temp_vel_x = 0.5;
    //}
  }
  else if (state == 2)
  { //ROTATE_TO_GOAL
    // rotate to goal, determined on the sign
    if (wanted_angle_dir < 0)
    {
      commandTurn(&temp_vel_w, 0.5);
    }
    else
    {
      commandTurn(&temp_vel_w, -0.5);
    }
  }
  else if (state == 3)
  { //WALL_FOLLOWING
    //Get the values from the wallfollowing
    if (direction == -1)
    {
      state_wf = wall_follower(&temp_vel_x, &temp_vel_y, &temp_vel_w, front_range, left_range, current_heading, direction);
    }
    else
    {
      state_wf = wall_follower(&temp_vel_x, &temp_vel_y, &temp_vel_w, front_range, right_range, current_heading, direction);
    }
  }
  else if (state == 4)
  { //MOVE_AWAY

    float save_distance = 0.7f;
    if (left_range < save_distance)
    {
      temp_vel_y = temp_vel_y - 0.5f;
    }
    if (right_range < save_distance)
    {
      temp_vel_y = temp_vel_y + 0.5f;
    }
    if (front_range < save_distance)
    {
      temp_vel_x = temp_vel_x - 0.5f;
    }
    if (back_range < save_distance)
    {
      temp_vel_x = temp_vel_x + 0.5f;
    }
  }

  *rssi_angle = wanted_angle;
  *state_wallfollowing = state_wf;

  *vel_x = temp_vel_x;
  *vel_y = temp_vel_y;
  *vel_w = temp_vel_w;

  float differenceX = current_pos_x - initialPosX;
  float differenceY = current_pos_y - initialPosY;
  float distanceFromBase = differenceX * differenceX + differenceY * differenceY;
  const float desiredDistanceFromBase = 0.3F;
  if (distanceFromBase < desiredDistanceFromBase && !outbound)
  {
    *keep_flying = false;
  }
  return state;
}
