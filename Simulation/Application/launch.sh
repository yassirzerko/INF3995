#!/bin/bash
# Launch Project Script!

EXPERIMENT_PATH=../experiments/crazyflie_controlling.argos
WALLS_GENERATOR=../walls-generator/

cd $WALLS_GENERATOR
sed -i 's/^        robots=.*$/        robots="'"$1"'"/g' $EXPERIMENT_PATH
sed -i 's/^        quantity=.*$/        quantity="'"$1"'"/g' $EXPERIMENT_PATH
sed -i 's/^          seed=.*$/          seed="'"$2"'"/g' $EXPERIMENT_PATH
sed -i '/<!--Begin-->/,/<!--End-->/d' $EXPERIMENT_PATH
make clean && make run
sed -i '/<!--Random Walls-->/r bin/generated_argos_elements.txt' $EXPERIMENT_PATH
make clean
