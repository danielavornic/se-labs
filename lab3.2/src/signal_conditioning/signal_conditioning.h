#ifndef SIGNAL_CONDITIONING_H
#define SIGNAL_CONDITIONING_H

#define WINDOW_SIZE 5
#define SPIKE_THRESHOLD_PERCENT 80
#define AXIS_COUNT 2
#define SALT_AND_PEPPER_FILTER_THRESHOLD 25.0f

float saltAndPepperFilter(float value, int axis);
float weightedAverageFilter(float value, int axis);
float applyPhysicalLimits(float value, float minValue, float maxValue);

#endif