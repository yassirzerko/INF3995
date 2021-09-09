from cflib.crazyflie.log import LogConfig
import logging

logging.basicConfig(level=logging.ERROR)
PERIOD_IN_MS = 1000


class LogConfigUtils:
    @staticmethod
    def getLogConfigs():
        logConfigs = [LogConfigUtils.getMultiRangerLogConfig(
        ), LogConfigUtils.getKalmanEstimateLogConfig(), LogConfigUtils.getStabilizerLogConfig()]
        return logConfigs

    @staticmethod
    def getMultiRangerLogConfig():
        logConfig = LogConfig(name='MultiRangerLogs',
                              period_in_ms=PERIOD_IN_MS)

        logConfig.add_variable('range.back')
        logConfig.add_variable('range.front')
        logConfig.add_variable('range.up')
        logConfig.add_variable('range.left')
        logConfig.add_variable('range.right')

        return logConfig

    @staticmethod
    def getKalmanEstimateLogConfig():
        logConfig = LogConfig(name='KalmanLogs', period_in_ms=PERIOD_IN_MS)

        logConfig.add_variable('stateEstimate.vx')
        logConfig.add_variable('stateEstimate.vy')

        logConfig.add_variable('stateEstimate.x')
        logConfig.add_variable('stateEstimate.y')
        logConfig.add_variable('stateEstimate.z')

        return logConfig

    @staticmethod
    def getStabilizerLogConfig():
        logConfig = LogConfig(name='StabilizerLogs', period_in_ms=PERIOD_IN_MS)

        logConfig.add_variable('stabilizer.roll')
        logConfig.add_variable('stabilizer.pitch')
        logConfig.add_variable('stabilizer.yaw')

        logConfig.add_variable('drone.batteryLevel')
        logConfig.add_variable('drone.droneState')

        return logConfig
