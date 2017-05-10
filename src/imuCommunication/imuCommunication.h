/**
 * @file imuCommunication.h
 * @brief Declares functions that communicate with accelerometer and parse the data into Vectors
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef IMU_COMMUNICATION_H_
#define IMU_COMMUNICATION_H_

#define GYRO_MODE 2 /* 1000 degrees/s, see datasheet */
#define GYRO_DEG_S 1000
#define ACCEL_MODE 1 /* 4g/s, see datasheet */
#define ACCEL_G_S 4
#define IMU_SAMPLE_RATE 312 /* sample rate of imu in herz */
#define IMU_SAMPLE_RATE_DIVIDER 25 /* Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV), GOR is 8kHz in default filtering */

#include <vectorQueue.h>
#include <stdint.h>
#include <vectorMaths.h>
#include <twiProtocol.h>

/**
 * @brief Queues used for storing and processing sampled data
 *        Pointers will be modified to point to one of the four queues, in order
 *        to be able to swap memory locations for processing and sampling without
 *        copying.
 */
typedef struct imuQueues {
  vectorQueue one;
  vectorQueue two;
  vectorQueue three;
  vectorQueue four;

  vectorQueue* gyro_sample_ptr; /**> Sampling queue for gyro data */
  vectorQueue* accel_sample_ptr; /**> Sampling queue for accel data */
  vectorQueue* gyro_processing_ptr; /**> Processing queue for gyro data */
  vectorQueue* accel_processing_ptr; /**> Processing queue for accel data */
} imuQueues;

/**
 * @brief sets up IMU with desired settings
 */
void imu_init(void);

/**
 * @brief sets up IMU registers for samping
 */
void imu_init_sampling(void);

/**
 * @brief sets up IMU register for sporadic communication
 */
void imu_uninit_sampling(void);

/**
 * @brief parses high and low bytes to 16-bit int
 * @param high high bits
 * @param low low bits
 * @return 16-bit integer containing acceleration
 */
int16_t imu_parse(uint8_t high, uint8_t low);

/**
 * @brief gets the x acceleration
 * @return x acceleration
 */
int16_t imu_get_x_acceleration(void);

/**
 * @brief gets the y acceleration
 * @return y acceleration
 */
int16_t imu_get_y_acceleration(void);

/**
 * @brief gets the z acceleration
 * @return z acceleration
 */
int16_t imu_get_z_acceleration(void);

/**
 * @brief gets the acceleration in all directions
 * @return acceleration vector
 */
Vector imu_get_acceleration(void);

/**
 * @brief gets the x angular velocity
 * @return x angular velocity
 */
int16_t imu_get_x_angular(void);

/**
 * @brief gets the y angular velocity
 * @return y angular velocity
 */
int16_t imu_get_y_angular(void);

/**
 * @brief gets the z acceleration
 * @return z acceleration
 */
int16_t imu_get_z_angular(void);

/**
 * @brief gets the acceleration in all directions
 * @return angular velocity vector
 */
Vector imu_get_angular(void);
#endif
